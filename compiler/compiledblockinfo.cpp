#include "compiledblockinfo.h"

#include <QHash>
#include <QString>
#include "compiler/datatype.h"
#include "compiler/automatictypecast.h"
#include "flowchart/block.h"
#include "compiler/overloadresult.h"
#include "flowchart/blocktype.h"
#include "flowchart/overloadtype.h"
#include "compiler/datatype.h"
#include <QVector>
#include "compiler/lisp_exp.h"
#include "compiler/c_stmt.h"

bool isLargerThan(DataType a, OverloadResult b) {
    int diff = 0;
    
    if (a.isInt()) {
        diff += 1;
    } else if (a.isAFP()) {
        diff += 2;
    } else if (a.isFloat()) {
        diff += 3;
    } else {
        // error condition
        return false;
    }
    
    if (b == OVERLOADRESULT_INT) {
        diff -= 1;
    } else if (b == OVERLOADRESULT_AFP) {
        diff -= 2;
    } else if (b == OVERLOADRESULT_FLOAT) {
        diff -= 3;
    } else {
        // error condition
        return false;
    }
    
    return (diff > 0);
}

CompiledBlockInfo CompiledBlockInfo::compileBlock(int blockIndex, Block block, QHash<int, CompiledBlockInfo> compiledBlocks, const QHash<QString, BlockType> *blockTypes) {
    QHash<QString, DataType> pinDataTypes;
    BlockType bt = blockTypes->value(block.blockTypeName());

    lisp_exp parseTree = bt.parseTree();
    QHash<QString, DataType> dataTypes;
    QHash<QString, QString> wireNames;
    // add input data types and wire names to the environment
    for (QString inputPinName : bt.inputs().keys()) {
        BlockPin source = block.inputConnections().value(inputPinName);
        DataType sourceDataType = compiledBlocks[source.blockNum()].pinDataType(source.pinName());
        QString wireName = "wire_" + QString::number(source.blockNum()) + "_" + source.pinName();
        dataTypes[inputPinName] = sourceDataType;
        wireNames[inputPinName] = wireName;
    }
    // add option data types and wire names to the environment
    for (QString optionName : bt.options().keys()) {
        QString optionLispSymbolName = "options." + optionName;
        QString optionWireName = "block_options_" + QString::number(blockIndex) + "_" + optionName;
        DataType optionDataType = DATATYPE_INT; // TODO: temporary cop-out from the problem of determining option data types
        dataTypes[optionLispSymbolName] = optionDataType;
        wireNames[optionLispSymbolName] = optionWireName;
    }
    // add storage data types and wire names to the environment
    for (QString storageName : bt.storage().keys()) {
        QString storageWireName = "wire_" + QString::number(blockIndex) + "_" + storageName;
        DataType storageDataType = DATATYPE_INT; // TODO: temporary cop-out from the problem of determining storage data types
        dataTypes[storageName] = storageDataType;
        wireNames[storageName] = storageWireName;
    }
    // add output wire names to the environment
    for (QString outputPinName : bt.outputs().keys()) {
        QString wireName = "wire_" + QString::number(blockIndex) + "_" + outputPinName;
        wireNames[outputPinName] = wireName;
    }
    c_stmt code = c_stmt::fromLispExp(parseTree, dataTypes, wireNames);
    for (QString outputPinName : bt.outputs().keys() + bt.storage().keys()) {
        QString outputWireName = "wire_" + QString::number(blockIndex) + "_" + outputPinName;
        DataType outputDataType = code.outputTypes().value(outputWireName);
        pinDataTypes[outputPinName] = outputDataType;
    }

    return CompiledBlockInfo(blockIndex, block, bt, pinDataTypes, code.code());
}

CompiledBlockInfo::CompiledBlockInfo() {
    m_blockIndex = 0;
    m_block = Block();
    m_blockType = BlockType();
}

CompiledBlockInfo::CompiledBlockInfo(int blockIndex, Block block, BlockType blockType, QHash<QString, DataType> pinDataTypes, QString code) {
    m_blockIndex = blockIndex;
    m_block = block;
    m_blockType = blockType;
    m_pinDataTypes = pinDataTypes;
    m_code = code;
}

int CompiledBlockInfo::blockIndex() const {
    return m_blockIndex;
}

Block CompiledBlockInfo::block() const {
    return m_block;
}

BlockType CompiledBlockInfo::blockType() const {
    return m_blockType;
}

DataType CompiledBlockInfo::pinDataType(QString pinName) const {
    return m_pinDataTypes.value(pinName);
}

QString CompiledBlockInfo::code() const {
    // TODO: move code generation into here
    return m_code;
}

QString CompiledBlockInfo::wireCode() const {
    QString fullCode;
    for (QString outputPinName : m_pinDataTypes.keys()) {
        DataType outputDataType = m_pinDataTypes.value(outputPinName);
        if (outputDataType.isBool()) {
            fullCode += "bool ";
        } else if (outputDataType.isInt()) {
            fullCode += "int ";
        } else if (outputDataType.isAFP()) {
            fullCode += "int ";
        } else if (outputDataType.isFloat()) {
            fullCode += "float ";
        } else {
            // error condition
        }
        fullCode += "wire_" + QString::number(m_blockIndex) + "_" + outputPinName + ";\n";
    }
    return fullCode;
}
