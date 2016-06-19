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

PinType PinType_fromJson(QJsonValue node) {
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

QHash<QString, PinType> QHash_QString_PinType_fromJson(QJsonValue node) {
    QHash<QString, PinType> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        PinType value = PinType_fromJson(item["value"]);
        obj.insert(key, value);
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

QMap<QString, PinType> QMap_QString_PinType_fromJson(QJsonValue node) {
    QMap<QString, PinType> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        PinType value = PinType_fromJson(item["value"]);
        obj.insert(key, value);
    }
    return obj;
}
