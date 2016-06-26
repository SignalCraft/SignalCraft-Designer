#include "blockpin.h"

#include <QString>
#include <QHash>
#include <QMap>
#include <QSet>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

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

BlockPin BlockPin_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    QJsonObject nodeObj = node.toObject();
    QJsonValue blockNumVal = nodeObj["blockNum"];
    if (!blockNumVal.isDouble() || (blockNumVal.toInt() != blockNumVal.toDouble())) {
        success = false;
    }
    int blockNum = blockNumVal.toInt();
    QJsonValue pinNameVal = nodeObj["pinName"];
    if (!pinNameVal.isString()) {
        success = false;
    }
    QString pinName = pinNameVal.toString();
    if (ok) {
        *ok = success;
    }
    return BlockPin(blockNum, pinName);
}

QJsonValue QHash_QString_BlockPin_toJson(QHash<QString, BlockPin> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = BlockPin_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QHash<QString, BlockPin> QHash_QString_BlockPin_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QHash<QString, BlockPin> obj;
    if (!node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QJsonValue keyVal = item["key"];
        if (!keyVal.isString()) {
            success = false;
        }
        QString key = keyVal.toString();
        BlockPin value = BlockPin_fromJson(item["value"], &callSuccess);
        if (!callSuccess) {
            success = false;
        }
        obj.insert(key, value);
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}

QJsonValue QMap_QString_BlockPin_toJson(QMap<QString, BlockPin> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = BlockPin_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QMap<QString, BlockPin> QMap_QString_BlockPin_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QMap<QString, BlockPin> obj;
    if (!node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QJsonValue keyVal = item["key"];
        if (!keyVal.isString()) {
            success = false;
        }
        QString key = keyVal.toString();
        BlockPin value = BlockPin_fromJson(item["value"], &callSuccess);
        if (!callSuccess) {
            success = false;
        }
        obj.insert(key, value);
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}

QJsonValue QHash_QString_QSet_BlockPin_toJson(QHash<QString, QSet<BlockPin>> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = QSet_BlockPin_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QHash<QString, QSet<BlockPin>> QHash_QString_QSet_BlockPin_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QHash<QString, QSet<BlockPin>> obj;
    if (!node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QJsonValue keyVal = item["key"];
        if (!keyVal.isString()) {
            success = false;
        }
        QString key = keyVal.toString();
        QSet<BlockPin> value = QSet_BlockPin_fromJson(item["value"], &callSuccess);
        if (!callSuccess) {
            success = false;
        }
        obj.insert(key, value);
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}

QJsonValue QMap_QString_QSet_BlockPin_toJson(QMap<QString, QSet<BlockPin>> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = QSet_BlockPin_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QMap<QString, QSet<BlockPin>> QMap_QString_QSet_BlockPin_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QMap<QString, QSet<BlockPin>> obj;
    if (!node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QJsonValue keyVal = item["key"];
        if (!keyVal.isString()) {
            success = false;
        }
        QString key = keyVal.toString();
        QSet<BlockPin> value = QSet_BlockPin_fromJson(item["value"], &callSuccess);
        if (!callSuccess) {
            success = false;
        }
        obj.insert(key, value);
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}

QJsonValue QSet_BlockPin_toJson(QSet<BlockPin> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        nodeArr.append(BlockPin_toJson(*i));
    }
    return nodeArr;
}

QSet<BlockPin> QSet_BlockPin_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QSet<BlockPin> obj;
    if (node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        obj.insert(BlockPin_fromJson(*i, &callSuccess));
        if (!callSuccess) {
            success = false;
        }
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}
