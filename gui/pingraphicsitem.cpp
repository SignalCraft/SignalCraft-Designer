#include "gui/pingraphicsitem.h"

#include <QGraphicsItem>
#include <QString>
#include "flowchart/datatype.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QTextOption>

PinGraphicsItem::PinGraphicsItem(QGraphicsItem *parent, QString pinName, DataType pinType) : QGraphicsItem(parent) {
    m_pinName = pinName;
    m_pinType = pinType;
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

QString PinGraphicsItem::pinName() {
    return m_pinName;
}

DataType PinGraphicsItem::pinType() {
    return m_pinType;
}

