#include "wiregraphicsitem.h"

#include "flowchart/flowchart.h"
#include "flowchart/block.h"
#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

WireGraphicsItem::WireGraphicsItem(FlowChart *flow, BlockPin blockPin) {
    m_flow = flow;
    m_blockPin = blockPin;
}

QRectF WireGraphicsItem::boundingRect() const {

}

QPainterPath WireGraphicsItem::shape() const {

}

bool WireGraphicsItem::contains(const QPointF & point) const {

}

void WireGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) {
    painter->setPen(QPen(QColor(0,0,0), 15));
    auto otherBlockPins = m_flow->blocks[m_blockPin.first].outputConnections[m_blockPin.second];
    for (BlockPin otherBlockPin : otherBlockPins) {
        //QPointF myPoint = m_flow->blockOutputPinPos(m_blockPin);
    }
    //painter->drawLine();
}

