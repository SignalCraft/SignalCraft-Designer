#include "flowchart/blocktype.h"

BlockType::BlockType() { }

qreal BlockType::displayWidth() {
    return 400;
}

qreal BlockType::displayHeight() {
    return 100*(1+std::max(inputs.size(), outputs.size()));
}

QPointF BlockType::inputPinPos(QString pinName) {
    int pinIndex = 0;
    for (auto inputPin : inputs.keys()) {
        if (inputPin == pinName) {
            break;
        }
        pinIndex++;
    }
    return inputPinIndexToPos(pinIndex);
}

QPointF BlockType::outputPinPos(QString pinName) {
    int pinIndex = 0;
    for (auto outputPin : outputs.keys()) {
        if (outputPin == pinName) {
            break;
        }
        pinIndex++;
    }
    return outputPinIndexToPos(pinIndex);
}

QPointF BlockType::inputPinCenterPos(QString pinName) {
    return inputPinPos(pinName) + QPointF(100, 50);
}

QPointF BlockType::outputPinCenterPos(QString pinName) {
    return outputPinPos(pinName) + QPointF(100, 50);
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

bool BlockType::isPinOutput(QString pinName) {
    return outputs.contains(pinName);
}
