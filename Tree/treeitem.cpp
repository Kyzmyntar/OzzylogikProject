#include "treeitem.h"

TreeItem::TreeItem(const QString &name, const QString &iconName, TreeItem *parent)
    : m_name(name), m_iconName(iconName), m_parentItem(parent)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *child)
{
    m_childItems.append(child);
}

TreeItem *TreeItem::child(int row) const
{
    return m_childItems.value(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();

}

int TreeItem::row() const
{
    if (m_parentItem)
    {
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
    }
    return 0;
}

TreeItem *TreeItem::parentItem() const
{
    return m_parentItem;
}

QVariant TreeItem::data(int column) const
{
    if (column == 0)
    {
        return m_name;
    }
    else if (column == 1)
    {
        return m_iconName;
    }
    return QVariant();
}
