#include "flowchart/blockpin.h"

#include <QString>
#include <QHash>
#include <QJsonValue>
#include <QJsonObject>

BlockPin::BlockPin() {
    m_blockNum = -1;
    m_pinName = "";
}

BlockPin::BlockPin(int blockNum, QString pinName) {
    m_blockNum = blockNum;
    m_pinName = pinName;
}

bool BlockPin::isValid() const {
    return m_blockNum >= 0;
}

bool BlockPin::operator==(const BlockPin &other) const {
    return (blockNum() == other.blockNum()) && (pinName() == other.pinName());
}

int BlockPin::blockNum() const {
    return m_blockNum;
}

QString BlockPin::pinName() const {
    return m_pinName;
}

uint qHash(const BlockPin b) {
    return (b.blockNum() * 31) + qHash(b.pinName());
}

QJsonValue BlockPin_toJson(BlockPin obj) {
    QJsonObject nodeObj;
    nodeObj["blockNum"] = obj.blockNum();
    nodeObj["pinName"] = obj.pinName();
    return nodeObj;
}

BlockPin BlockPin_fromJson(QJsonValue node) {
    QJsonObject nodeObj = node.toObject();
    int blockNum = nodeObj["blockNum"].toInt();
    QString pinName = nodeObj["pinName"].toString();
    return BlockPin(blockNum, pinName);
}
