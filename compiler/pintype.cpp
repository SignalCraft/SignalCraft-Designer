#include "pintype.h"

#include <QJsonValue>
#include <QHash>
#include <QString>
#include <QMap>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

QJsonValue PinType_toJson(PinType obj) {
    return QJsonValue((int)obj);
}

PinType PinType_fromJson(QJsonValue node, bool *ok) {
    bool success = node.isDouble() && (node.toInt() == node.toDouble());
    if (ok) {
        *ok = success;
    }
    return (PinType)(node.toInt());
}

QJsonValue QHash_QString_PinType_toJson(QHash<QString, PinType> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = PinType_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QHash<QString, PinType> QHash_QString_PinType_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QHash<QString, PinType> obj;
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
        PinType value = PinType_fromJson(item["value"], &callSuccess);
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

QJsonValue QMap_QString_PinType_toJson(QMap<QString, PinType> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = PinType_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QMap<QString, PinType> QMap_QString_PinType_fromJson(QJsonValue node, bool *ok) {
    bool success = true;
    bool callSuccess;
    QMap<QString, PinType> obj;
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
        PinType value = PinType_fromJson(item["value"], &callSuccess);
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
