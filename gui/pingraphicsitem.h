#ifndef PINGRAPHICSITEM_H
#define PINGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QString>
#include "flowchart/datatype.h"

/**
 * @brief The PinGraphicsItem class is a QGraphicsItem that represents a block's pin.
 */
class PinGraphicsItem : public QGraphicsItem {
public:
    /**
     * Construct a PinGraphicsItem.
     * @param parent the BlockGraphicsItem that this pin belongs to
     * @param pinName the pin's name
     * @param pinDataType the pin's data type
     * @param isOutput true if the pin is an output, false if it's an input
     */
    PinGraphicsItem(QGraphicsItem *parent, QString pinName, DataType pinDataType, bool isOutput);

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;

    QRectF boundingRect() const override;

    /**
     * @return the pin's name
     */
    QString pinName();

    /**
     * @return the pin's data type
     */
    DataType pinDataType();

    /**
     * @return true if this pin is an output, false if it's an input
     */
    bool isOutput();

private:
    QString m_pinName;
    DataType m_pinDataType;
    bool m_isOutput;
};

#endif // PINGRAPHICSITEM_H
