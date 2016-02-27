#ifndef COMPILEDBLOCKINFO_H
#define COMPILEDBLOCKINFO_H

#include "compiler/datatype.h"
#include <QHash>
#include <QString>

/**
 * The immutable CompiledBlockInfo class represents all of the information
 * about a specific block that is determined at compile-time.
 *
 * Specifically, this class stores the exact DataType of each output pin.
 *
 * In the future, this class may store information about automatic type
 * conversions at the input pins.
 */
class CompiledBlockInfo {
public:
    /**
     * Construct a CompiledBlockInfo with the given mapping from output pin
     * names to DataTypes.
     * @param pinDataTypes a mapping from output pin names to DataTypes
     */
    CompiledBlockInfo(QHash<QString, DataType> pinDataTypes);

    /**
     * @return the DataTypes of the named output pin
     */
    DataType pinDataType(QString pinName) const;

private:
    QHash<QString, DataType> m_pinDataTypes;
};

#endif // COMPILEDBLOCKINFO_H
