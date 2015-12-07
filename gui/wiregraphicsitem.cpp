#include "wiregraphicsitem.h"

#include "flowchart/flowchart.h"
#include "flowchart/block.h"
#include <QRectF>
#include <QSizeF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include "flowchart/blockpin.h"

QPointF WireGraphicsItem::blockInputPinPos(const BlockPin bp) const {
    Block block = m_flow->block(bp.blockNum());
    QPointF blockPos = block.pos();
    BlockType blockType = m_flow->blockTypes()->value(block.blockTypeName());
    QPointF relativePinPos = blockType.inputPinCenterPos(bp.pinName());
    QPointF pinPos = blockPos + relativePinPos;
    return pinPos;
}

QPointF WireGraphicsItem::blockOutputPinPos(const BlockPin bp) const {
    Block block = m_flow->block(bp.blockNum());
    QPointF blockPos = block.pos();
    BlockType blockType = m_flow->blockTypes()->value(block.blockTypeName());
    QPointF relativePinPos = blockType.outputPinCenterPos(bp.pinName());
    QPointF pinPos = blockPos + relativePinPos;
    return pinPos;
}

WireGraphicsItem::WireGraphicsItem(FlowChart *flow, BlockPin blockPin) {
    m_flow = flow;
    m_blockPin = blockPin;
}

QRectF WireGraphicsItem::boundingRect() const {
    QPointF myPinPos = blockOutputPinPos(m_blockPin);
    QRectF bounds(myPinPos, QSizeF(0,0));
    auto otherBlockPins = m_flow->block(m_blockPin.blockNum()).outputConnections()[m_blockPin.pinName()];
    for (BlockPin otherBlockPin : otherBlockPins) {
        QPointF otherPinPos = blockInputPinPos(otherBlockPin);
        if (otherPinPos.x() < bounds.left()) {
            bounds.setLeft(otherPinPos.x());
        } else if (otherPinPos.x() > bounds.right()) {
            bounds.setRight(otherPinPos.x());
        }
        if (otherPinPos.y() < bounds.top()) {
            bounds.setTop(otherPinPos.y());
        } else if (otherPinPos.y() > bounds.bottom()) {
            bounds.setBottom(otherPinPos.y());
        }
    }
    return bounds;
}

QPainterPath WireGraphicsItem::shape() const {
    return QPainterPath();
}

void WireGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(QPen(QColor(0,0,0), 15));
    QPointF myPinPos = blockOutputPinPos(m_blockPin);
    auto otherBlockPins = m_flow->block(m_blockPin.blockNum()).outputConnections()[m_blockPin.pinName()];
    for (BlockPin otherBlockPin : otherBlockPins) {
        QPointF otherPinPos = blockInputPinPos(otherBlockPin);
        painter->drawLine(myPinPos, otherPinPos);
    }
}

