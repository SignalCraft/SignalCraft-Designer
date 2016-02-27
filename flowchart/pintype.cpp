#include "flowchart/pintype.h"

#include <QJsonValue>

QJsonValue PinType_toJson(PinType obj) {
    return QJsonValue((int)obj);
}

PinType PinType_fromJson(QJsonValue node) {
    return (PinType)(node.toInt());
}
