#include "jsonforqt.h"

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QPointF>
#include <QPoint>
#include <QSet>
#include <QHash>
#include <QMap>
#include <QString>

QJsonValue QPointF_toJson(QPointF point) {
    QJsonObject nodeObj;
    nodeObj["x"] = point.x();
    nodeObj["y"] = point.y();
    return nodeObj;
}

QPointF QPointF_fromJson(QJsonValue node, bool *ok = NULL) {
    bool success;
    QJsonObject nodeObj = node.toObject();
    QJsonValue xVal = nodeObj["x"];
    QJsonValue yVal = nodeObj["y"];
    success = xVal.isDouble() && yVal.isDouble();
    if (ok) {
        *ok = success;
    }
    return QPointF(xVal.toDouble(), yVal.toDouble());
}

QJsonValue QPoint_toJson(QPoint point) {
    QJsonObject nodeObj;
    nodeObj["x"] = point.x();
    nodeObj["y"] = point.y();
    return nodeObj;
}

QPoint QPoint_fromJson(QJsonValue node, bool *ok = NULL) {
    bool success;
    QJsonObject nodeObj = node.toObject();
    QJsonValue xVal = nodeObj["x"];
    QJsonValue yVal = nodeObj["y"];
    success = xVal.isDouble() && xVal.toDouble() == xVal.toInt() && yVal.isDouble() && yVal.toDouble() == yVal.toInt();
    if (ok) {
        *ok = success;
    }
    return QPoint(xVal.toInt(), yVal.toInt());
}

QJsonValue QHash_QString_QString_toJson(QHash<QString, QString> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = i.value();
        nodeArr.append(item);
    }
    return nodeArr;
}

QHash<QString, QString> QHash_QString_QString_fromJson(QJsonValue node, bool *ok = NULL) {
    bool success = true;
    QHash<QString, QString> obj;
    if (!node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QJsonValue keyVal = item["key"];
        QJsonValue valueVal = item["value"];
        if (!keyVal.isString() || !valueVal.isString()) {
            success = false;
        } else {
            obj.insert(keyVal.toString(), valueVal.toString());
        }
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}

QJsonValue QMap_QString_QString_toJson(QMap<QString, QString> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = i.value();
        nodeArr.append(item);
    }
    return nodeArr;
}

QMap<QString, QString> QMap_QString_QString_fromJson(QJsonValue node, bool *ok = NULL) {
    bool success = true;
    QMap<QString, QString> obj;
    if (!node.isArray()) {
        success = false;
    }
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QJsonValue keyVal = item["key"];
        QJsonValue valueVal = item["value"];
        if (!keyVal.isString() || !valueVal.isString()) {
            success = false;
        } else {
            obj.insert(keyVal.toString(), valueVal.toString());
        }
    }
    if (ok) {
        *ok = success;
    }
    return obj;
}
