#include "overloadtype.h"

#include <QJsonValue>

QJsonValue OverloadType_toJson(OverloadType obj) {
    return QJsonValue((int)obj);
}

OverloadType OverloadType_fromJson(QJsonValue node) {
    return (OverloadType)(node.toInt());
}
