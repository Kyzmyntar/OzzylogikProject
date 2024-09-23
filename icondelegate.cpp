#include "icondelegate.h"

IconDelegate::IconDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void IconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        QString iconPath;
        QString iconName = index.data(Qt::UserRole).toString();

        if (index.parent().isValid())
        {
            iconPath = QString(":/Icons/Operators/%1.png").arg(iconName);
        }
        else
        {
            iconPath = QString(":/Icons/Countries/%1.png").arg(iconName);
        }

        QPixmap pixmap(iconPath);
        if (!pixmap.isNull())
        {
            QPixmap scaledPixmap = pixmap.scaled(QSize (24, 24), Qt::KeepAspectRatio, Qt::SmoothTransformation);

            QRect iconRect = option.rect;
            int x = iconRect.x() + (iconRect.width() - scaledPixmap.width()) / 2;
            int y = iconRect.y() + (iconRect.height() - scaledPixmap.height()) / 2;
            painter->drawPixmap(x, y, scaledPixmap);
        }
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

