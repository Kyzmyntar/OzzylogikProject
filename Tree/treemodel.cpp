#include "treemodel.h"

TreeModel::TreeModel(DataStorage *dataStorage, QObject *parent)
    : QAbstractItemModel(parent), m_dataStorage(dataStorage)
{
    rootItem = new TreeItem();
    loadData();
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        return item->data(0);
    }
    else if (role == Qt::UserRole)
    {
        return item->data(1);
    }

    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex&) const
{
    return 2;
}

void TreeModel::loadData()
{
    QList<Country> countries = m_dataStorage->getCountries();
    for (const Country &country : countries)
    {
        QVector<QVariant> countryData;
        countryData << country.name << country.code;
        TreeItem *countryItem = new TreeItem(country.name, country.code, rootItem);
        rootItem->appendChild(countryItem);

        QVector<Operator> operators = m_dataStorage->getOperators(country.mcc);
        for (const Operator &op : operators)
        {
            TreeItem *operatorItem = new TreeItem(op.name, QString("%1_%2").arg(op.mcc).arg(op.mnc), countryItem);
            countryItem->appendChild(operatorItem);
        }
    }
}


