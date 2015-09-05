#ifndef PINGRAPHICSITEM_H
#define PINGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QString>
#include "flowchart/datatype.h"

class PinGraphicsItem : public QGraphicsItem
{
public:
    PinGraphicsItem(QGraphicsItem *parent, QString pinName, DataType pinDataType, bool isOutput);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    QRectF boundingRect() const override;
    QString pinName();
    DataType pinDataType();
    bool isOutput();
protected:
    QString m_pinName;
    DataType m_pinDataType;
    bool m_isOutput;
};

#endif // PINGRAPHICSITEM_H
