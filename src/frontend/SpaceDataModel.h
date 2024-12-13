#ifndef SPACEDATAMODEL_H
#define SPACEDATAMODEL_H

#include "scanList.hpp"
#include <QAbstractItemModel>
#include <QScopedPointer>

#define USE_SCANVIEWPTR

class SpaceDataModelPrivate;

class SpaceDataModel : public QAbstractListModel
{
    Q_OBJECT

  public:
    SpaceDataModel(QObject *parent = nullptr);
    virtual ~SpaceDataModel();

    enum RoleNames
    {
        IndexRole = Qt::UserRole,
        SpaceImageRole,
        SpaceNameRole,
        SpaceAreaRole,
        SpaceScanTimeRole,
        CheckedRole
    };
    Q_ENUM(RoleNames)

    static bool registToQml();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void checkAll();
    Q_INVOKABLE void uncheckAll();
    Q_INVOKABLE void removeChecked();

#if defined(USE_SCANVIEWPTR)
    bool append(dimenvue::backend::ScanViewPtr &, int index = -1);
#else
    bool append(int index, const QString &name, const QUrl &imageUrl, float area, const QDateTime &scanTime);
#endif
    void clear();
    bool remove(int index);
    std::list<dimenvue::backend::ScanViewPtr> checkedItems() const;
    dimenvue::backend::ScanViewPtr getView(int index) const;

#if (0)
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
#endif
  private:
    QScopedPointer<SpaceDataModelPrivate> d;
};

#endif // SPACEDATAMODEL_H
