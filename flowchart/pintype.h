#ifndef DATATYPE
#define DATATYPE

#include <QJsonValue>

/**
 * The PinType enum represents the datatype behavior of a pin.
 *
 * - PINTYPE_BOOL pins handle only DATATYPE_BOOL data: true or false values.
 *
 * - PINTYPE_INT pins handle only DATATYPE_INT data: 32-bit signed integers.
 *
 * - PINTYPE_AFP pins handle only DATATYPE_AFP(P) data: 32-bit signed
 *   "automatic fixed-point" values with a certain compile-time constant
 *   precision value P.
 *
 * - PINTYPE_FLOAT pins handle only DATATYPE_FLOAT data: true or false values.
 *
 * - PINTYPE_OVERLOAD pins can handle one of several data types, determined by
 *   its block's OverloadType.
 *
 */
enum PinType { PINTYPE_BOOL, PINTYPE_INT, PINTYPE_AFP, PINTYPE_FLOAT, PINTYPE_OVERLOAD };

QJsonValue PinType_toJson(PinType obj);
PinType PinType_fromJson(QJsonValue node);

#endif // DATATYPE

