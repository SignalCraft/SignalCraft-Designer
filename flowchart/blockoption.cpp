#include "blockoption.h"

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include "flowchart/jsonforqt.h"

BlockOption::BlockOption() { }

BlockOption::BlockOption(QString displayName, QString defaultValue, BlockOptionType type) {
    m_displayName = displayName;
    m_defaultValue = defaultValue;
    m_type = type;
}

BlockOption BlockOption::makeComboBox(QString displayName, QString defaultValue, QMap<QString, QString> choices) {
    BlockOption bo(displayName, defaultValue, BLOCK_OPTION_TYPE_COMBOBOX);
    bo.m_choices = choices;
    return bo;
}

BlockOption BlockOption::makeInteger(QString displayName, QString defaultValue, int minimum, int maximum) {
    BlockOption bo(displayName, defaultValue, BLOCK_OPTION_TYPE_INTEGER);
    bo.m_minimum = minimum;
    bo.m_maximum = maximum;
    return bo;
}

QString BlockOption::displayName() const {
    return m_displayName;
}

QString BlockOption::defaultValue() const {
    return m_defaultValue;
}

BlockOptionType BlockOption::type() const {
    return m_type;
}

// Combobox:

QMap<QString, QString> BlockOption::choices() const {
    return m_choices;
}

// Integer:

int BlockOption::minimum() const {
    return m_minimum;
}

int BlockOption::maximum() const {
    return m_maximum;
}

QJsonValue BlockOptionType_toJson(BlockOptionType obj) {
    return QJsonValue((int)obj);
}

BlockOptionType BlockOptionType_fromJson(QJsonValue node) {
    return (BlockOptionType)(node.toInt());
}

QJsonValue BlockOption_toJson(BlockOption obj) {
    QJsonObject nodeObj;
    nodeObj["displayName"] = obj.displayName();
    nodeObj["defaultValue"] = obj.defaultValue();
    nodeObj["type"] = BlockOptionType_toJson(obj.type());
    switch (obj.type()) {
    case BLOCK_OPTION_TYPE_COMBOBOX:
        nodeObj["choices"] = QMap_QString_QString_toJson(obj.choices());
        break;
    case BLOCK_OPTION_TYPE_INTEGER:
        nodeObj["minimum"] = obj.minimum();
        nodeObj["maximum"] = obj.maximum();
        break;
    }
    return nodeObj;
}

BlockOption BlockOption_fromJson(QJsonValue node) {
    QJsonObject nodeObj = node.toObject();
    QString displayName = nodeObj["displayName"].toString();
    QString defaultValue = nodeObj["defaultValue"].toString();
    BlockOptionType type = BlockOptionType_fromJson(nodeObj["type"]);
    BlockOption result;
    QMap<QString, QString> choices;
    int minimum;
    int maximum;
    switch (type) {
    case BLOCK_OPTION_TYPE_COMBOBOX:
        choices = QMap_QString_QString_fromJson(nodeObj["choices"]);
        result = BlockOption::makeComboBox(displayName, defaultValue, choices);
        break;
    case BLOCK_OPTION_TYPE_INTEGER:
        minimum = nodeObj["minimum"].toInt();
        maximum = nodeObj["maximum"].toInt();
        result = BlockOption::makeInteger(displayName, defaultValue, minimum, maximum);
        break;
    }
    return result;
}

QJsonValue QHash_QString_BlockOption_toJson(QHash<QString, BlockOption> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = BlockOption_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QHash<QString, BlockOption> QHash_QString_BlockOption_fromJson(QJsonValue node) {
    QHash<QString, BlockOption> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        BlockOption value = BlockOption_fromJson(item["value"]);
        obj.insert(key, value);
    }
    return obj;
}

QJsonValue QMap_QString_BlockOption_toJson(QMap<QString, BlockOption> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = BlockOption_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QMap<QString, BlockOption> QMap_QString_BlockOption_fromJson(QJsonValue node) {
    QMap<QString, BlockOption> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        BlockOption value = BlockOption_fromJson(item["value"]);
        obj.insert(key, value);
    }
    return obj;
}

