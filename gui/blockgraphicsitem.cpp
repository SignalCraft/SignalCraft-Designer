#include "blockgraphicsitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QSize>
#include <QTextOption>
#include "blocktype.h"
#include "pintype.h"
#include "pingraphicsitem.h"

BlockGraphicsItem::BlockGraphicsItem(BlockType blockType, int index)
{
    m_blockType = blockType;
    blockIndex = index;
    qreal width = blockType.displayWidth();
    qreal height = blockType.displayHeight();
    m_boundingRect = QRectF(0, 0, width, height);

    int i = 0;
    for (QString pinName : blockType.inputs().keys()) {
        PinType t = blockType.inputs()[pinName];
        PinGraphicsItem *pgi = new PinGraphicsItem(this, pinName, t, false);
        pgi->setParentItem(this);
        pgi->setPos(blockType.inputPinIndexToPos(i));
        i++;
    }

    i=0;
    for (QString pinName : blockType.outputs().keys()) {
        PinType t = blockType.outputs()[pinName];
        PinGraphicsItem *pgi = new PinGraphicsItem(this, pinName, t, true);
        pgi->setParentItem(this);
        pgi->setPos(blockType.outputPinIndexToPos(i));
        i++;
    }
}

void BlockGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(QBrush(QColor(128,128,255)));
    painter->setPen(QColor(0,0,0));
    painter->drawRoundedRect(boundingRect(), 20, 20);
    painter->setFont(QFont("Helveteca", 40));
    QRectF textRect(boundingRect().topLeft(), QSize(400, 100));
    painter->drawText(textRect, blockType().displayName(), QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
}

QRectF BlockGraphicsItem::boundingRect() const {
    return m_boundingRect;
}

BlockType BlockGraphicsItem::blockType() {
    return m_blockType;
}
