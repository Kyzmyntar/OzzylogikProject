#ifndef TREEITEM_H
#define TREEITEM_H

#include <QString>
#include <QVariant>
#include <QList>

class TreeItem
{
public:
    explicit TreeItem(const QString &name = "", const QString &code = "", TreeItem *parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);
    TreeItem *child(int row) const;
    int childCount() const;
    int row() const;
    TreeItem *parentItem() const;
    QVariant data(int column) const;

private:
    //Country or operator name
    QString m_name;
    //The name of the icon from the resources
    QString m_iconName;
    TreeItem *m_parentItem;
    QList<TreeItem*> m_childItems;
};

#endif
