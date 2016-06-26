#ifndef JSONFORQT_H
#define JSONFORQT_H

#include <QJsonValue>
#include <QPointF>
#include <QPoint>
#include <QSet>
#include <QHash>
#include <QMap>
#include <QString>

QJsonValue QPointF_toJson(QPointF obj);
QPointF QPointF_fromJson(QJsonValue node, bool *ok = NULL);

QJsonValue QPoint_toJson(QPoint obj);
QPoint QPoint_fromJson(QJsonValue node, bool *ok = NULL);

QJsonValue QHash_QString_QString_toJson(QHash<QString, QString> obj);
QHash<QString, QString> QHash_QString_QString_fromJson(QJsonValue node, bool *ok = NULL);

QJsonValue QMap_QString_QString_toJson(QMap<QString, QString> obj);
QMap<QString, QString> QMap_QString_QString_fromJson(QJsonValue node, bool *ok = NULL);

#endif // JSONFORQT_H
