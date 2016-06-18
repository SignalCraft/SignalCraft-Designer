#ifndef DATATYPE_H
#define DATATYPE_H

#include <QString>

// For internal use only (this file)
enum DataTypeType { DTT_NONE, DTT_BOOL, DTT_INT, DTT_AFP, DTT_FLOAT };

/**
 * The DataType class represents the exact type of data carried by a wire.
 *
 * A wire's DataType is determined at compile-time, and includes the specific
 * precision of an AFP value if necessary.
 */
class DataType {
public:
    /**
     * This constructor creates an invalid DataType object
     */
    DataType();

    /**
     * This constructor creates a DataType object with no precision (not AFP)
     * @param dtt the type of this DataType (not AFP)
     */
    DataType(DataTypeType dtt);

    /**
     * This constructor creates a DataType object with the given precision
     * (for AFP)
     * @param dtt the type of this DataType (only AFP)
     * @param afpPrecision the precision of this AFP DataType
     */
    DataType(DataTypeType dtt, int afpPrecision);

    /**
     * @return true if this DataType is valid, false if not
     */
    bool isValid() const;

    /**
     * @return true if this DataType is DATATYPE_BOOL, false if not
     */
    bool isBool() const;

    /**
     * @return true if this DataType is DATATYPE_INT, false if not
     */
    bool isInt() const;

    /**
     * @return true if this DataType is DATATYPE_AFP, false if not
     */
    bool isAFP() const;

    /**
     * @return true if this DataType is DATATYPE_FLOAT, false if not
     */
    bool isFloat() const;

    /**
     * @return the precision of this DataType, assuming it is AFP
     */
    int afpPrecision() const;

    /**
     * @return the string representation of this DataType
     */
    QString toString() const;

private:
    DataTypeType m_dtt;
    int m_afpPrecision;
};

// Constructor macros
#define DATATYPE_BOOL DataType(DTT_BOOL)
#define DATATYPE_INT DataType(DTT_INT)
#define DATATYPE_AFP(P) DataType(DTT_AFP, (P))
#define DATATYPE_FLOAT DataType(DTT_FLOAT)

#endif // DATATYPE_H
