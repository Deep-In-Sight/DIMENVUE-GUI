#include "SpaceDataModel.h"
#include <QHash>
#include <qqml.h>
#include <QDateTime>
#include <QDebug>
#include "scanList.hpp"
#include "scanView.hpp"

struct SpaceData {
#if defined (USE_SCANVIEWPTR)
    int index;
    dimenvue::backend::ScanViewPtr pScanView;
    bool checked;
#else
    int index;
    QString spaceName;
    QUrl spaceImageUrl;
    float spaceArea;
    QDateTime scanTime;
    bool checked;
#endif
};

QDateTime tmToQDateTime(const std::tm& t)
{
    QDate date(t.tm_year, t.tm_mon, t.tm_yday);
    QTime time(t.tm_hour, t.tm_min, t.tm_sec);

    return QDateTime(date, time);
}

//=============================================================================
//  P R I V A T E
//=============================================================================
class SpaceDataModelPrivate
{
public:
    QList<SpaceData> data;
    QHash<int, QByteArray> roleNames;
    int lastIndex = 0;

    SpaceDataModelPrivate()
    {
        roleNames[SpaceDataModel::IndexRole] = "index";
        roleNames[SpaceDataModel::SpaceNameRole] = "name";
        roleNames[SpaceDataModel::SpaceImageRole] = "image";
        roleNames[SpaceDataModel::SpaceAreaRole] = "area";
        roleNames[SpaceDataModel::SpaceScanTimeRole] = "time";
        roleNames[SpaceDataModel::CheckedRole] = "checked";
    }
};

//=============================================================================
//  PUBLIC
//=============================================================================
SpaceDataModel::SpaceDataModel(QObject* parent)
    : QAbstractListModel(parent)
    , d(new SpaceDataModelPrivate)
{}

SpaceDataModel::~SpaceDataModel()
{}

bool SpaceDataModel::registToQml()
{
    auto ret = qmlRegisterType<SpaceDataModel>("com.dimenvue", 1, 0, "SpaceDataModel");

    qDebug() << "qmlRegisterType<SpaceDataModel>: " << ret;

    return 0 != ret;
}

int SpaceDataModel::rowCount(const QModelIndex &parent) const
{
    auto ret = d->data.size();

    return ret;
}

QVariant SpaceDataModel::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    if (0 <= row && row < d->data.size()) {
        auto& value = d->data[row];
#if defined (USE_SCANVIEWPTR)
        auto stat = value.pScanView->getStats();
#endif

        switch (role) {
        case IndexRole:
            return value.index;
#if defined (USE_SCANVIEWPTR)
        case SpaceNameRole:
        {
            auto stdName = stat.name;
#ifdef QT_DEBUG
            stdName += "-";
            stdName += stat.path;
#endif
            return QString::fromStdString(stdName);
        }
        case SpaceImageRole:
            return QString::fromStdString(stat.thumbnailPath);
        case SpaceAreaRole:
            return stat.areaSizeSqM;
        case SpaceScanTimeRole:
            return tmToQDateTime(stat.createdTime);
#else
        case SpaceNameRole:
            return value.spaceName;
        case SpaceImageRole:
            return value.spaceImageUrl;
        case SpaceAreaRole:
            return value.spaceArea;
        case SpaceScanTimeRole:
            return value.scanTime;
#endif
        case CheckedRole:
            return value.checked;
        default:
            qDebug() << "[Error] Invalid Role: " << role;
            break;
        }
    }

    return QVariant{};
}

bool SpaceDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto row = index.row();
    if (0 <= row && row < d->data.size()) {
        auto& v = d->data[row];

        switch (role) {
        case IndexRole:
            v.index = value.toInt();
            break;
#if defined (USE_SCANVIEWPTR)
        case SpaceNameRole:
        case SpaceImageRole:
        case SpaceAreaRole:
        case SpaceScanTimeRole:
            break;
#else
        case SpaceNameRole:
            v.spaceName = value.toString();
            break;
        case SpaceImageRole:
            v.spaceImageUrl = value.toUrl();
            break;
        case SpaceAreaRole:
            v.spaceArea = value.toFloat();
            break;
        case SpaceScanTimeRole:
            v.scanTime = value.toDateTime();
            break;
#endif
        case CheckedRole:
            v.checked = value.toBool();
            break;
        default:
            qDebug() << "[Error] Invalid Role: " << role;
            break;
        }

        emit dataChanged(index, index);//, QVector<int>(role));
        return true;
    } else {
        return false;
    }
}

QHash<int, QByteArray> SpaceDataModel::roleNames() const
{
    return d->roleNames;
}

void SpaceDataModel::checkAll()
{
    for (auto& v : d->data) {
        v.checked = true;
    }
    auto start = index(0);
    auto end = index(d->data.size() -1);

    emit dataChanged(start, end);
}

void SpaceDataModel::uncheckAll()
{
    for (auto& v : d->data) {
        v.checked = false;
    }
    auto start = index(0);
    auto end = index(d->data.size() -1);

    emit dataChanged(start, end);
}

void SpaceDataModel::removeChecked()
{
    auto index = 0;
    for (auto iter=d->data.begin(); iter != d->data.end(); ) {
        if (iter->checked) {
            emit beginRemoveRows(QModelIndex(), index, index);
            iter = d->data.erase(iter);
            emit endRemoveRows();
        } else {
            iter++;
            index++;
        }
    }
    qDebug() << "removeChecked(): d->data.size(): " << d->data.size();
}

void SpaceDataModel::clear()
{
    d->data.clear();
}

bool SpaceDataModel::remove(int index)
{
    int i=0;
    for (auto& v : d->data) {
        if (v.index == index) {
            d->data.removeAt(i);
            return true;
        }
        i++;
    }
    return false;
}

std::list<dimenvue::backend::ScanViewPtr> SpaceDataModel::checkedItems() const
{
    auto list = std::list<dimenvue::backend::ScanViewPtr>{};

    for (auto& v : d->data) {
        if (v.checked) {
#if defined(USE_SCANVIEWPTR)
            auto name = v.pScanView->getStats().name;
            list.push_back(v.pScanView);
#else
            list.append(v.spaceName);
#endif
        }
    }
    return list;
}

dimenvue::backend::ScanViewPtr SpaceDataModel::getView(int index) const
{
    for (auto& v : d->data) {
        if (v.index == index) {
            return v.pScanView;
        }
    }
    qDebug() << "[Error] can't find view(index: " << index << ")";
    return nullptr;
}

#if defined (USE_SCANVIEWPTR)
bool SpaceDataModel::append(dimenvue::backend::ScanViewPtr &scanViewPtr, int index)
{
    auto newIndex = (0 <= index) ? index : d->lastIndex;

    auto data = SpaceData {
            newIndex,
            scanViewPtr,
            false
    };
    d->data.append(data);
    if (0 <= index) {
        d->lastIndex = index + 1;
    } else {
        d->lastIndex++;
    }

    return true;
}
#else
bool SpaceDataModel::append(int index, const QString &name, const QUrl &imageUrl, float area, const QDateTime &scanTime)
{
    auto data = SpaceData{
            index,
            name,
            imageUrl,
            area,
            scanTime,
            false
    };
    d->data.append(data);

    return true;
}
#endif

#if (0)
int SpaceDataModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}


QModelIndex SpaceDataModel::parent(const QModelIndex &child) const
{
    return QModelIndex{};
}

QVariant SpaceDataModel::data(const QModelIndex &index, int role) const
{
    return QVariant{};
}

QModelIndex SpaceDataModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex{};
}
#endif
