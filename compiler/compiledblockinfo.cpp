#include "compiledblockinfo.h"

#include <QHash>
#include <QString>
#include "compiler/datatype.h"

CompiledBlockInfo::CompiledBlockInfo(QHash<QString, DataType> pinDataTypes) {
    m_pinDataTypes = pinDataTypes;
}

DataType CompiledBlockInfo::pinDataType(QString pinName) const {
    return m_pinDataTypes.value(pinName);
}
