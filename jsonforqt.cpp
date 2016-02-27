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
#include "flowchart/blockpin.h"
#include "flowchart/pintype.h"
#include "flowchart/blockoption.h"
#include "flowchart/block.h"

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

QHash<QString, BlockPin> QHash_QString_BlockPin_fromJson(QJsonValue node) {
    QHash<QString, BlockPin> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        BlockPin value = BlockPin_fromJson(item["value"]);
        obj.insert(key, value);
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

QMap<QString, BlockPin> QMap_QString_BlockPin_fromJson(QJsonValue node) {
    QMap<QString, BlockPin> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        BlockPin value = BlockPin_fromJson(item["value"]);
        obj.insert(key, value);
    }
    return obj;
}

QJsonValue QHash_QString_BlockOption_toJson(QHash<QString, QSharedPointer<const BlockOption>> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = BlockOption_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QHash<QString, QSharedPointer<const BlockOption>> QHash_QString_BlockOption_fromJson(QJsonValue node) {
    QHash<QString, QSharedPointer<const BlockOption>> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        QSharedPointer<const BlockOption> value = BlockOption_fromJson(item["value"]);
        obj.insert(key, value);
    }
    return obj;
}

QJsonValue QMap_QString_BlockOption_toJson(QMap<QString, QSharedPointer<const BlockOption>> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = BlockOption_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QMap<QString, QSharedPointer<const BlockOption>> QMap_QString_BlockOption_fromJson(QJsonValue node) {
    QMap<QString, QSharedPointer<const BlockOption>> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        QSharedPointer<const BlockOption> value = BlockOption_fromJson(item["value"]);
        obj.insert(key, value);
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

QHash<QString, QSet<BlockPin>> QHash_QString_QSet_BlockPin_fromJson(QJsonValue node) {
    QHash<QString, QSet<BlockPin>> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        QSet<BlockPin> value = QSet_BlockPin_fromJson(item["value"]);
        obj.insert(key, value);
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

QMap<QString, QSet<BlockPin>> QMap_QString_QSet_BlockPin_fromJson(QJsonValue node) {
    QMap<QString, QSet<BlockPin>> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        QString key = item["key"].toString();
        QSet<BlockPin> value = QSet_BlockPin_fromJson(item["value"]);
        obj.insert(key, value);
    }
    return obj;
}

QJsonValue QHash_int_Block_toJson(QHash<int, Block> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = Block_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QHash<int, Block> QHash_int_Block_fromJson(QJsonValue node) {
    QHash<int, Block> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        int key = item["key"].toInt();
        Block value = Block_fromJson(item["value"]);
        obj.insert(key, value);
    }
    return obj;
}

QJsonValue QMap_int_Block_toJson(QMap<int, Block> obj) {
    QJsonArray nodeArr;
    for (auto i = obj.constBegin(); i != obj.constEnd(); i++) {
        QJsonObject item;
        item["key"] = i.key();
        item["value"] = Block_toJson(i.value());
        nodeArr.append(item);
    }
    return nodeArr;
}

QMap<int, Block> QMap_int_Block_fromJson(QJsonValue node) {
    QMap<int, Block> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        QJsonObject item = (*i).toObject();
        int key = item["key"].toInt();
        Block value = Block_fromJson(item["value"]);
        obj.insert(key, value);
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

QSet<BlockPin> QSet_BlockPin_fromJson(QJsonValue node) {
    QSet<BlockPin> obj;
    QJsonArray nodeArr = node.toArray();
    for (auto i = nodeArr.constBegin(); i != nodeArr.constEnd(); i++) {
        obj.insert(BlockPin_fromJson(*i));
    }
    return obj;
}

