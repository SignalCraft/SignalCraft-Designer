#ifndef JSONFORQT_H
#define JSONFORQT_H

#include <QJsonValue>
#include <QPointF>
#include <QPoint>
#include <QSet>
#include <QHash>
#include <QMap>
#include <QString>
#include "flowchart/blockpin.h"
#include "flowchart/datatype.h"
#include "flowchart/blockoption.h"
#include "flowchart/block.h"

QJsonValue QPointF_toJson(QPointF obj);
QPointF QPointF_fromJson(QJsonValue node);

QJsonValue QPoint_toJson(QPoint obj);
QPoint QPoint_fromJson(QJsonValue node);

QJsonValue QHash_QString_QString_toJson(QHash<QString, QString> obj);
QHash<QString, QString> QHash_QString_QString_fromJson(QJsonValue node);

QJsonValue QMap_QString_QString_toJson(QMap<QString, QString> obj);
QMap<QString, QString> QMap_QString_QString_fromJson(QJsonValue node);

QJsonValue QHash_QString_DataType_toJson(QHash<QString, DataType> obj);
QHash<QString, DataType> QHash_QString_DataType_fromJson(QJsonValue node);

QJsonValue QMap_QString_DataType_toJson(QMap<QString, DataType> obj);
QMap<QString, DataType> QMap_QString_DataType_fromJson(QJsonValue node);

QJsonValue QHash_QString_BlockPin_toJson(QHash<QString, BlockPin> obj);
QHash<QString, BlockPin> QHash_QString_BlockPin_fromJson(QJsonValue node);

QJsonValue QMap_QString_BlockPin_toJson(QMap<QString, BlockPin> obj);
QMap<QString, BlockPin> QMap_QString_BlockPin_fromJson(QJsonValue node);

QJsonValue QHash_QString_BlockOption_toJson(QHash<QString, QSharedPointer<const BlockOption>> obj);
QHash<QString, QSharedPointer<const BlockOption>> QHash_QString_BlockOption_fromJson(QJsonValue node);

QJsonValue QMap_QString_BlockOption_toJson(QMap<QString, QSharedPointer<const BlockOption>> obj);
QMap<QString, QSharedPointer<const BlockOption>> QMap_QString_BlockOption_fromJson(QJsonValue node);

QJsonValue QHash_QString_QSet_BlockPin_toJson(QHash<QString, QSet<BlockPin>> obj);
QHash<QString, QSet<BlockPin>> QHash_QString_QSet_BlockPin_fromJson(QJsonValue node);

QJsonValue QMap_QString_QSet_BlockPin_toJson(QMap<QString, QSet<BlockPin>> obj);
QMap<QString, QSet<BlockPin>> QMap_QString_QSet_BlockPin_fromJson(QJsonValue node);

QJsonValue QHash_int_Block_toJson(QHash<int, Block> obj);
QHash<int, Block> QHash_int_Block_fromJson(QJsonValue node);

QJsonValue QMap_int_Block_toJson(QMap<int, Block> obj);
QMap<int, Block> QMap_int_Block_fromJson(QJsonValue node);

QJsonValue QSet_BlockPin_toJson(QSet<BlockPin> obj);
QSet<BlockPin> QSet_BlockPin_fromJson(QJsonValue node);

#endif // JSONFORQT_H
