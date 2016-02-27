#include "compiler/datatype.h"

DataType::DataType() {
    m_dtt = DTT_NONE;
}

DataType::DataType(DataTypeType dtt) {
    m_dtt = dtt;
}

DataType::DataType(DataTypeType dtt, int afpPrecision) {
    m_dtt = dtt;
    m_afpPrecision = afpPrecision;
}

bool DataType::isBool() const {
    return (m_dtt == DTT_BOOL);
}

bool DataType::isInt() const {
    return (m_dtt == DTT_INT);
}

bool DataType::isAFP() const {
    return (m_dtt == DTT_AFP);
}

bool DataType::isFloat() const {
    return (m_dtt == DTT_FLOAT);
}

int DataType::afpPrecision() const {
    if (!isAFP()) {
        // debug error condition
    }
    return m_afpPrecision;
}
