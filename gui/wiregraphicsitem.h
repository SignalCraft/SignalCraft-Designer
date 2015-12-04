#ifndef WIREGRAPHICSITEM_H
#define WIREGRAPHICSITEM_H

#include <QGraphicsPathItem>
#include "flowchart/flowchart.h"
#include "flowchart/blockpin.h"
#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

/**
 * The WireGraphicsItem class is a QGraphicsItem that represents a wire.
 */
class WireGraphicsItem : public QGraphicsPathItem {
public:
    /**
     * Construct a WireGraphicsItem.
     * @param flow the flowchart containing the wire
     * @param blockPin the blockpin that sources the wire
     */
    WireGraphicsItem(FlowChart *flow, BlockPin blockPin);

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;

private:
    FlowChart *m_flow;
    BlockPin m_blockPin;
    QPointF blockInputPinPos(const BlockPin bp) const; // TODO: should be refactored into flowchart
    QPointF blockOutputPinPos(const BlockPin bp) const; // TODO: should be refactored into flowchart
};

#endif // WIREGRAPHICSITEM_H
