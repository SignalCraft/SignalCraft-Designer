#ifndef OVERLOADTYPE_H
#define OVERLOADTYPE_H

#include <QJsonValue>

/**
 * The OverloadType enum represents the type of overloading used by a block type.
 */
enum OverloadType { OVERLOADTYPE_NONE, OVERLOADTYPE_INT_AFP_FLOAT, OVERLOADTYPE_AFP_FLOAT };

QJsonValue OverloadType_toJson(OverloadType obj);
OverloadType OverloadType_fromJson(QJsonValue node, bool *ok = NULL);

#endif // OVERLOADTYPE_H
