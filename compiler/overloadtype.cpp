#include "overloadtype.h"

#include <QJsonValue>

QJsonValue OverloadType_toJson(OverloadType obj) {
    return QJsonValue((int)obj);
}

OverloadType OverloadType_fromJson(QJsonValue node, bool *ok) {
    bool success = node.isDouble() && (node.toInt() == node.toDouble());
    if (ok) {
        *ok = success;
    }
    return (OverloadType)(node.toInt());
}
