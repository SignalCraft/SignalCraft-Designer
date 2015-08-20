#include "gui/blockgraphicsitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QTextOption>

BlockGraphicsItem::BlockGraphicsItem(QString name_, int index)
{
    name = name_;
    blockIndex = index;
}

void BlockGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*) {
    QRectF rect(-100, -50, 200, 100);
    painter->setBrush(QBrush(QColor(128,128,255)));
    painter->setPen(QColor(0,0,0));
    painter->drawRoundedRect(rect, 20, 20);
    painter->setFont(QFont("Helveteca", 40));
    painter->drawText(rect, name, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
}

QRectF BlockGraphicsItem::boundingRect() const {
    return QRectF(-100, -50, 200, 100);
}

