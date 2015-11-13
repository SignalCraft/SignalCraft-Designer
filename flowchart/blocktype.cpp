#include "flowchart/blocktype.h"

#include <QtGlobal>
#include <QPointF>
#include <QString>

BlockType::BlockType() { }

BlockType::BlockType(QString name, QMap<QString, DataType> inputs, QMap<QString, DataType> outputs) {
    m_name = name;
    m_inputs = inputs;
    m_outputs = outputs;
}

QPointF BlockType::inputPinPos(QString pinName) const {
    int pinIndex = 0;
    for (auto inputPin : inputs().keys()) {
        if (inputPin == pinName) {
            break;
        }
        pinIndex++;
    }
    return inputPinIndexToPos(pinIndex);
}

QPointF BlockType::outputPinPos(QString pinName) const {
    int pinIndex = 0;
    for (auto outputPin : outputs().keys()) {
        if (outputPin == pinName) {
            break;
        }
        pinIndex++;
    }
    return outputPinIndexToPos(pinIndex);
}

QPointF BlockType::inputPinCenterPos(QString pinName) const {
    return inputPinPos(pinName) + QPointF(100, 50);
}

QPointF BlockType::outputPinCenterPos(QString pinName) const {
    return outputPinPos(pinName) + QPointF(100, 50);
}

qreal BlockType::displayWidth() const {
    return 400;
}

qreal BlockType::displayHeight() const {
    return 100*(1+std::max(inputs().size(), outputs().size()));
}

bool BlockType::isPinOutput(QString pinName) const {
    return outputs().contains(pinName);
}


QString BlockType::name() const {
    return m_name;
}

QMap<QString, DataType> BlockType::inputs() const {
    return m_inputs;
}

QMap<QString, DataType> BlockType::outputs() const {
    return m_outputs;
}

QPointF BlockType::inputPinIndexToPos(int pinIndex) {
    return QPointF(0, 100*(1+pinIndex));
}

QPointF BlockType::outputPinIndexToPos(int pinIndex) {
    return QPointF(200, 100*(1+pinIndex));
}

QPointF BlockType::inputPinIndexToCenterPos(int pinIndex) {
    return inputPinIndexToPos(pinIndex) + QPointF(100, 50);
}

QPointF BlockType::outputPinIndexToCenterPos(int pinIndex) {
    return outputPinIndexToPos(pinIndex) + QPointF(100, 50);
}
