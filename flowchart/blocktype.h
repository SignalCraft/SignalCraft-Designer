#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <QMap>
#include <QString>
#include "flowchart/datatype.h"
#include <QPointF>

class BlockType
{
public:
    BlockType();
    QString name;
    QMap<QString, DataType> inputs;
    QMap<QString, DataType> outputs;
    QPointF inputPinPos(QString pinName);
    QPointF outputPinPos(QString pinName);
    QPointF inputPinCenterPos(QString pinName);
    QPointF outputPinCenterPos(QString pinName);
    qreal displayWidth();
    qreal displayHeight();
    QPointF inputPinIndexToPos(int pinIndex);
    QPointF outputPinIndexToPos(int pinIndex);
    QPointF inputPinIndexToCenterPos(int pinIndex);
    QPointF outputPinIndexToCenterPos(int pinIndex);
    bool isPinOutput(QString pinName);
};

#endif // BLOCKTYPE_H
