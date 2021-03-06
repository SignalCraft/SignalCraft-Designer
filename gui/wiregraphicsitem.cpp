#include "wiregraphicsitem.h"

#include "flowchart.h"
#include "block.h"
#include <QRectF>
#include <QSizeF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include "blockpin.h"

QPointF WireGraphicsItem::blockInputPinPos(const BlockPin bp) const {
    QPointF blockPos = m_flow->blockPos(bp.blockNum());
    BlockType blockType = m_flow->blockType(bp.blockNum());
    QPointF relativePinPos = blockType.inputPinCenterPos(bp.pinName());
    QPointF pinPos = blockPos + relativePinPos;
    return pinPos;
}

QPointF WireGraphicsItem::blockOutputPinPos(const BlockPin bp) const {
    QPointF blockPos = m_flow->blockPos(bp.blockNum());
    BlockType blockType = m_flow->blockType(bp.blockNum());
    QPointF relativePinPos = blockType.outputPinCenterPos(bp.pinName());
    QPointF pinPos = blockPos + relativePinPos;
    return pinPos;
}

WireGraphicsItem::WireGraphicsItem(FlowChart *flow, BlockPin blockPin) {
    m_flow = flow;
    m_blockPin = blockPin;
}

BlockPin WireGraphicsItem::blockPin() const {
    return m_blockPin;
}

QRectF WireGraphicsItem::boundingRect() const {
    QPointF myPinPos = blockOutputPinPos(m_blockPin);
    QRectF bounds(myPinPos, QSizeF(0,0));
    auto otherBlockPins = m_flow->blockOutputConnection(m_blockPin);
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
    auto otherBlockPins = m_flow->blockOutputConnection(m_blockPin);
    for (BlockPin otherBlockPin : otherBlockPins) {
        QPointF otherPinPos = blockInputPinPos(otherBlockPin);
        painter->drawLine(myPinPos, otherPinPos);
    }
}

