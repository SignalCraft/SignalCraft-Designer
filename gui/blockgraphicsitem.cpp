#include "gui/blockgraphicsitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QSize>
#include <QTextOption>
#include "flowchart/blocktype.h"
#include "flowchart/datatype.h"
#include "gui/pingraphicsitem.h"

BlockGraphicsItem::BlockGraphicsItem(BlockType blockType, int index)
{
    m_blockType = blockType;
    blockIndex = index;

    int numLines = 1 + std::max(blockType.inputs.size(), blockType.outputs.size());
    int height = 100 * numLines;
    m_boundingRect = QRectF(-200, -height/2, 400, height);

    int i = 0;
    for (auto input = blockType.inputs.constBegin(); input != blockType.inputs.constEnd(); input++) {
        QString pinName = input.key();
        DataType t = input.value();
        PinGraphicsItem *pgi = new PinGraphicsItem(this, pinName, t);
        pgi->setParentItem(this);
        pgi->setPos(-200, (-height/2)+100*(1+i));
        i++;
    }

    i=0;
    for (auto output = blockType.outputs.constBegin(); output != blockType.outputs.constEnd(); output++) {
        QString pinName = output.key();
        DataType t = output.value();
        PinGraphicsItem *pgi = new PinGraphicsItem(this, pinName, t);
        pgi->setParentItem(this);
        pgi->setPos(0, (-height/2)+100*(1+i));
        i++;
    }
}

void BlockGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(QBrush(QColor(128,128,255)));
    painter->setPen(QColor(0,0,0));
    painter->drawRoundedRect(boundingRect(), 20, 20);
    painter->setFont(QFont("Helveteca", 40));
    QRectF textRect(boundingRect().topLeft(), QSize(400, 100));
    painter->drawText(textRect, blockType().name, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
}

QRectF BlockGraphicsItem::boundingRect() const {
    return m_boundingRect;
}

BlockType BlockGraphicsItem::blockType() {
    return m_blockType;
}
