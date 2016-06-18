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

QPointF QPointF_fromJson(QJsonValue node) {
    QJsonObject nodeObj = node.toObject();
    qreal x = nodeObj["x"].toDouble();
    qreal y = nodeObj["y"].toDouble();
    return QPointF(x, y);
}

QJsonValue QPoint_toJson(QPoint point) {
    QJsonObject nodeObj;
    nodeObj["x"] = point.x();
    nodeObj["y"] = point.y();
    return nodeObj;
}

QPoint QPoint_fromJson(QJsonValue node) {
    QJsonObject nodeObj = node.toObject();
    int x = nodeObj["x"].toInt();
    int y = nodeObj["y"].toInt();
    return QPoint(x, y);
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

QHash<QString, QString> QHash_QString_QString_fromJson(QJsonValue node) {
    QHash<QString, QString> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        QString value = item["value"].toString();
        obj.insert(key, value);
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

QMap<QString, QString> QMap_QString_QString_fromJson(QJsonValue node) {
    QMap<QString, QString> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        QString value = item["value"].toString();
        obj.insert(key, value);
    }
    return obj;
}
