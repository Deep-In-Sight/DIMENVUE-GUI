#include "SpaceDataSortProxyModel.h"
#include "SpaceDataModel.h"
#include <QDebug>
#include <QDateTime>

SpaceDataSortProxyModel::SpaceDataSortProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{}

SpaceDataSortProxyModel::~SpaceDataSortProxyModel()
{}

bool SpaceDataSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    return true;
}

bool SpaceDataSortProxyModel::lessThan(const QModelIndex &l, const QModelIndex &r) const
{
    auto role = sortRole();

    switch (role) {
    case SpaceDataModel::IndexRole:
        {
            auto lValue = l.data(role).toInt();
            auto rValue = r.data(role).toInt();

            return lValue < rValue;
        }

    case SpaceDataModel::SpaceNameRole:
        {
            auto lValue = l.data(role).toString();
            auto rValue = r.data(role).toString();

            return lValue < rValue;
        }

    case SpaceDataModel::SpaceAreaRole:
        {
            auto lValue = l.data(role).toFloat();
            auto rValue = r.data(role).toFloat();

            return lValue < rValue;
        }

    case SpaceDataModel::SpaceScanTimeRole:
        {
            auto lValue = l.data(role).toDateTime();
            auto rValue = r.data(role).toDateTime();

            return lValue < rValue;
        }

    default:
        break;
    }

    return true;
}
