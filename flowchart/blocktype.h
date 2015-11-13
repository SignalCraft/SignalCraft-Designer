#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <QMap>
#include <QString>
#include "flowchart/datatype.h"
#include <QPointF>
#include <QtGlobal>

class BlockType {
public:
    BlockType();
    BlockType(QString name, QMap<QString, DataType> inputs, QMap<QString, DataType> outputs);
    QPointF inputPinPos(QString pinName) const;
    QPointF outputPinPos(QString pinName) const;
    QPointF inputPinCenterPos(QString pinName) const;
    QPointF outputPinCenterPos(QString pinName) const;
    qreal displayWidth() const;
    qreal displayHeight() const;
    bool isPinOutput(QString pinName) const;
    QString name() const;
    QMap<QString, DataType> inputs() const;
    QMap<QString, DataType> outputs() const;
public:
    static QPointF inputPinIndexToPos(int pinIndex);
    static QPointF outputPinIndexToPos(int pinIndex);
    static QPointF inputPinIndexToCenterPos(int pinIndex);
    static QPointF outputPinIndexToCenterPos(int pinIndex);
private:
    QString m_name;
    QMap<QString, DataType> m_inputs;
    QMap<QString, DataType> m_outputs;
};

#endif // BLOCKTYPE_H
