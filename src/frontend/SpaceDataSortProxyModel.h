#ifndef SPACEDATASORTPROXYMODEL_H
#define SPACEDATASORTPROXYMODEL_H

#include <QSortFilterProxyModel>

class SpaceDataSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SpaceDataSortProxyModel(QObject* =nullptr);
    virtual ~SpaceDataSortProxyModel();

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // SPACEDATASORTPROXYMODEL_H
