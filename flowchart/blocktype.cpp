#include "flowchart/blocktype.h"

#include <QtGlobal>
#include <QPointF>
#include <QString>
#include <QSharedPointer>

BlockType::BlockType() {
    m_name = "";
}

BlockType::BlockType(QString name, QString displayName, QMap<QString, DataType> inputs, QMap<QString, DataType> outputs, QMap<QString, QSharedPointer<const BlockOption> > options) {
    m_name = name;
    m_displayName = displayName;
    m_inputs = inputs;
    m_outputs = outputs;
    m_options = options;
}

bool BlockType::isValid() const {
    return !m_name.isEmpty();
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

QString BlockType::displayName() const {
    return m_displayName;
}

QMap<QString, DataType> BlockType::inputs() const {
    return m_inputs;
}

QMap<QString, DataType> BlockType::outputs() const {
    return m_outputs;
}

QMap<QString, QSharedPointer<const BlockOption> > BlockType::options() const {
    return m_options;
}

QHash<QString, QString> BlockType::defaultOptionValues() const {
    QHash<QString, QString> defaults;
    for (QString optionName : options().keys()) {
        QSharedPointer<const BlockOption> option = options()[optionName];
        defaults[optionName] = option->defaultValue();
    }
    return defaults;
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
