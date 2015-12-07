#include "flowchart/datatype.h"

#include <QJsonValue>

QJsonValue DataType_toJson(DataType obj) {
    return QJsonValue((int)obj);
}

DataType DataType_fromJson(QJsonValue node) {
    return (DataType)(node.toInt());
}
