#ifndef DATATYPE
#define DATATYPE

#include <QJsonValue>

/**
 * The DataType enum represents the type of data carried by a wire.
 */
enum DataType { ANALOG = 1, DIGITAL = 2, ANALOG_BUS = 3, DIGITAL_BUS = 4 };

QJsonValue DataType_toJson(DataType obj);
DataType DataType_fromJson(QJsonValue node);

#endif // DATATYPE

