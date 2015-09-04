#ifndef WIREGRAPHICSITEM_H
#define WIREGRAPHICSITEM_H

#include <QGraphicsPathItem>
#include "flowchart/flowchart.h"
#include "flowchart/block.h"
#include <QRectF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class WireGraphicsItem : public QGraphicsPathItem
{
public:
    WireGraphicsItem(FlowChart *flow, BlockPin blockPin);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    bool contains(const QPointF & point) const override;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
protected:
    FlowChart *m_flow;
    BlockPin m_blockPin;
};

#endif // WIREGRAPHICSITEM_H
