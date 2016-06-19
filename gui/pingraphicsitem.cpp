#include "pingraphicsitem.h"

#include <QGraphicsItem>
#include <QString>
#include "pintype.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QTextOption>
#include "blockgraphicsitem.h"

PinGraphicsItem::PinGraphicsItem(BlockGraphicsItem *parent, QString pinName, PinType pinType, bool isOutput) : QGraphicsItem(parent) {
    m_pinName = pinName;
    m_pinType = pinType;
    m_isOutput = isOutput;
}

void PinGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*) {
    QRectF rect(0, 0, 200, 100);
    painter->setBrush(QBrush(QColor(128,255,128)));
    painter->setPen(QColor(0,0,0));
    painter->drawRoundedRect(rect, 20, 20);
    painter->setFont(QFont("Helveteca", 40));
    painter->drawText(rect, pinName(), QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
}

QRectF PinGraphicsItem::boundingRect() const {
    return QRectF(0, 0, 200, 100);
}

QString PinGraphicsItem::pinName() const {
    return m_pinName;
}

PinType PinGraphicsItem::pinType() const {
    return m_pinType;
}

bool PinGraphicsItem::isOutput() const {
    return m_isOutput;
}

