#include "automatictypecast.h"

#include "datatype.h"
#include <QString>

AutomaticTypeCast::AutomaticTypeCast() {
    m_valid = true;
    m_leftShiftAmount = 0;
}

AutomaticTypeCast::AutomaticTypeCast(DataType in, DataType out) {
    if (in.isAFP() && out.isAFP()) {
        m_valid = true;
        m_leftShiftAmount = out.afpPrecision() - in.afpPrecision();
    } else {
        // error condition
        m_valid = false;
    }
}

QString AutomaticTypeCast::code(QString inName, QString outName) const {
    if (m_valid) {
        if (m_leftShiftAmount == 0) {
            return "";
        } else if (m_leftShiftAmount > 0) {
            return outName + " = (" + inName + " << " + QString::number(m_leftShiftAmount) + ");\n";
        } else {
            return outName + " = (" + inName + " >> " + QString::number(-m_leftShiftAmount) + ");\n";
        }
    } else {
        // error condition
        return "#error Error: tried to generate code for an invalid AutomaticTypeCast object";
    }
}
