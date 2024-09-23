#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "treeitem.h"
#include "DataStorage/datastorage.h"
#include <QAbstractItemModel>
#include <QPixmap>

class TreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit TreeModel(DataStorage *dataStorage, QObject *parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    TreeItem *rootItem;
    DataStorage* m_dataStorage;
    void loadData();
};
#endif
