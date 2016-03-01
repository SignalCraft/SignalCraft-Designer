#ifndef AUTOMATICTYPECAST_H
#define AUTOMATICTYPECAST_H

#include "compiler/datatype.h"
#include <QString>

/**
 * The AutomaticTypeCast class represents the automatic typecast that is
 * determined at compile-time at one of a block's input pins
 */
class AutomaticTypeCast {
public:
    /**
     * This constructor creates a AutomaticTypeCast that does nothing
     */
    AutomaticTypeCast();

    /**
     * This constructor creates an AutomaticTypeCast between two DataTypes
     * @param in the input data type
     * @param out the output data type
     */
    AutomaticTypeCast(DataType in, DataType out);

    /**
     * Generate the line of C code, including the newline, that performs this type conversion
     * @param inName the name of the input wire variable
     * @param outName the name of the output wire variable
     * @return the generated line of C code
     */
    QString code(QString inName, QString outName) const;
private:
    bool m_valid;
    int m_leftShiftAmount;
};

#endif // AUTOMATICTYPECAST_H
