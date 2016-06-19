#ifndef PINGRAPHICSITEM_H
#define PINGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QString>
#include "pintype.h"
#include "blockgraphicsitem.h"

/**
 * @brief The PinGraphicsItem class is a QGraphicsItem that represents a block's pin.
 */
class PinGraphicsItem : public QGraphicsItem {
public:
    /**
     * Construct a PinGraphicsItem.
     * @param parent the BlockGraphicsItem that this pin belongs to
     * @param pinName the pin's name
     * @param pinPinType the pin's data type
     * @param isOutput true if the pin is an output, false if it's an input
     */
    PinGraphicsItem(BlockGraphicsItem *parent, QString pinName, PinType pinType, bool isOutput);

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;

    QRectF boundingRect() const override;

    /**
     * @return the pin's name
     */
    QString pinName() const;

    /**
     * @return the pin's type
     */
    PinType pinType() const;

    /**
     * @return true if this pin is an output, false if it's an input
     */
    bool isOutput() const;

private:
    QString m_pinName;
    PinType m_pinType;
    bool m_isOutput;
};

#endif // PINGRAPHICSITEM_H
