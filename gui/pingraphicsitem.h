#ifndef PINGRAPHICSITEM_H
#define PINGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QString>
#include "flowchart/datatype.h"

class PinGraphicsItem : public QGraphicsItem
{
public:
    PinGraphicsItem(QGraphicsItem *parent, QString pinName, DataType pinType);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    QRectF boundingRect() const override;
    QString pinName();
    DataType pinType();
protected:
    QString m_pinName;
    DataType m_pinType;
};

#endif // PINGRAPHICSITEM_H
