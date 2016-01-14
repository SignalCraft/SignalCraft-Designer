#ifndef DATATYPE
#define DATATYPE

#include <QJsonValue>

/**
 * The DataType enum represents the type of data carried by a wire.
 */
enum DataType { FLOAT = 1, BOOL = 2, INTEGER = 3, FLOAT_ARRAY = 4, BOOL_ARRAY = 5, INTEGER_ARRAY = 6 };

QJsonValue DataType_toJson(DataType obj);
DataType DataType_fromJson(QJsonValue node);

#endif // DATATYPE

