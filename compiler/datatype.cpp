#include "datatype.h"

#include <QString>

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

bool DataType::isValid() const {
    return (m_dtt != DTT_NONE);
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

QString DataType::toString() const {
    if (isBool()) {
        return "BOOL";
    } else if (isInt()) {
        return "INT";
    } else if (isAFP()) {
        return "AFP(" + QString::number(afpPrecision()) + ")";
    } else if (isFloat()) {
        return "FLOAT";
    } else {
        return "INVALID"; // error condition
    }
}
