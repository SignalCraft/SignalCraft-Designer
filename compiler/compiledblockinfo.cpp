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
    OverloadResult overloadResult;
    QHash<QString, DataType> pinDataTypes;
    QHash<QString, AutomaticTypeCast> pinTypeCasts;
    BlockType bt = blockTypes->value(block.blockTypeName());
    // determine overload result if necessary
    if (bt.overloadType() == OVERLOADTYPE_NONE) {
        overloadResult = OVERLOADRESULT_NONE;
    } else {
        if (bt.overloadType() == OVERLOADTYPE_INT_AFP_FLOAT) {
            overloadResult = OVERLOADRESULT_INT;
        } else if (bt.overloadType() == OVERLOADTYPE_AFP_FLOAT) {
            overloadResult = OVERLOADRESULT_AFP;
        }
        for (QString inputPinName : bt.inputs().keys()) {
            PinType inputPinType = bt.inputs().value(inputPinName);
            if (inputPinType == PINTYPE_OVERLOAD) {
                BlockPin source = block.inputConnections().value(inputPinName);
                DataType sourceDataType = compiledBlocks[source.blockNum()].pinDataType(source.pinName());
                if (isLargerThan(sourceDataType, overloadResult)) {
                    if (sourceDataType.isInt()) {
                        overloadResult = OVERLOADRESULT_INT;
                    } else if (sourceDataType.isAFP()) {
                        overloadResult = OVERLOADRESULT_AFP;
                    } else if (sourceDataType.isFloat()) {
                        overloadResult = OVERLOADRESULT_FLOAT;
                    } else {
                        // error condition
                    }
                }
            }
        }
    }
    // determine the minimum AFP precision
    /*
     * Temporary placeholder algorithm:
     *   - All AFP inputs (including overloads if applicable) have their input
     *     precision set to the minimum of all the precisions of incoming AFP
     *     wires connected to AFP inputs, or to 0 if there are no such wires.
     *   - All AFP outputs (including overloads if applicable) have their
     *     output precision set to one plus the precision of all AFP inputs
     *     (including overloads if applicable), unless there are no AFP inputs,
     *     in which case the output precision is set to 27.
     */
    int inputPrecision = 99999;
    bool hasAFPInput = false;
    for (QString inputPinName : bt.inputs().keys()) {
        PinType inputPinType = bt.inputs().value(inputPinName);
        if (inputPinType == PINTYPE_AFP || (inputPinType == PINTYPE_OVERLOAD && overloadResult == OVERLOADRESULT_AFP)) {
            hasAFPInput = true;
            BlockPin source = block.inputConnections().value(inputPinName);
            DataType sourceDataType = compiledBlocks[source.blockNum()].pinDataType(source.pinName());
            if (sourceDataType.isAFP()) {
                if (sourceDataType.afpPrecision() < inputPrecision) {
                    inputPrecision = sourceDataType.afpPrecision();
                }
            }
        }
    }
    if (inputPrecision == 99999) {
        inputPrecision = 0;
    }
    int outputPrecision;
    if (hasAFPInput) {
        outputPrecision = inputPrecision + 1;
    } else {
        outputPrecision = 27;
    }
    // determine each input typecast
    for (QString inputPinName : bt.inputs().keys()) {
        PinType inputPinType = bt.inputs().value(inputPinName);
        DataType inputDataType;
        if (inputPinType == PINTYPE_BOOL) {
            inputDataType = DATATYPE_BOOL;
        } else if (inputPinType == PINTYPE_INT) {
            inputDataType = DATATYPE_INT;
        } else if (inputPinType == PINTYPE_AFP) {
            inputDataType = DATATYPE_AFP(inputPrecision);
        } else if (inputPinType == PINTYPE_FLOAT) {
            inputDataType = DATATYPE_FLOAT;
        } else if (inputPinType == PINTYPE_OVERLOAD) {
            if (overloadResult == OVERLOADRESULT_INT) {
                inputDataType = DATATYPE_INT;
            } else if (overloadResult == OVERLOADRESULT_AFP) {
                inputDataType = DATATYPE_AFP(inputPrecision);
            } else if (overloadResult == OVERLOADRESULT_FLOAT) {
                inputDataType = DATATYPE_FLOAT;
            } else {
                // error condition
                inputDataType = DataType();
            }
        }
        BlockPin source = block.inputConnections().value(inputPinName);
        DataType sourceDataType = compiledBlocks[source.blockNum()].pinDataType(source.pinName());
        AutomaticTypeCast typeCast(sourceDataType, inputDataType);
        pinTypeCasts[inputPinName] = typeCast;
    }
    // determine each output datatype
    for (QString outputPinName : bt.outputs().keys()) {
        PinType outputPinType = bt.outputs().value(outputPinName);
        DataType outputDataType;
        if (outputPinType == PINTYPE_BOOL) {
            outputDataType = DATATYPE_BOOL;
        } else if (outputPinType == PINTYPE_INT) {
            outputDataType = DATATYPE_INT;
        } else if (outputPinType == PINTYPE_AFP) {
            outputDataType = DATATYPE_AFP(outputPrecision);
        } else if (outputPinType == PINTYPE_FLOAT) {
            outputDataType = DATATYPE_FLOAT;
        } else if (outputPinType == PINTYPE_OVERLOAD) {
            if (overloadResult == OVERLOADRESULT_INT) {
                outputDataType = DATATYPE_INT;
            } else if (overloadResult == OVERLOADRESULT_AFP) {
                outputDataType = DATATYPE_AFP(outputPrecision);
            } else if (overloadResult == OVERLOADRESULT_FLOAT) {
                outputDataType = DATATYPE_FLOAT;
            } else {
                // error condition
                outputDataType = DataType();
            }
        }
        pinDataTypes[outputPinName] = outputDataType;
    }
    return CompiledBlockInfo(blockIndex, block, bt, overloadResult, pinDataTypes, pinTypeCasts);
}

CompiledBlockInfo::CompiledBlockInfo() {
    m_blockIndex = 0;
    m_block = Block();
    m_blockType = BlockType();
}

CompiledBlockInfo::CompiledBlockInfo(int blockIndex, Block block, BlockType blockType, OverloadResult overloadResult, QHash<QString, DataType> pinDataTypes, QHash<QString, AutomaticTypeCast> pinTypeCasts) {
    m_blockIndex = blockIndex;
    m_block = block;
    m_blockType = blockType;
    m_overloadResult = overloadResult;
    m_pinDataTypes = pinDataTypes;
    m_pinTypeCasts = pinTypeCasts;
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

OverloadResult CompiledBlockInfo::overloadResult() const {
    return m_overloadResult;
}

DataType CompiledBlockInfo::pinDataType(QString pinName) const {
    return m_pinDataTypes.value(pinName);
}

AutomaticTypeCast CompiledBlockInfo::pinTypeCast(QString pinName) const {
    return m_pinTypeCasts.value(pinName);
}

QString CompiledBlockInfo::code() const {
    QString fullCode;

    for (QString inputPinName : m_pinTypeCasts.keys()) {
        AutomaticTypeCast typeCast = m_pinTypeCasts.value(inputPinName);
        BlockPin wireSource = m_block.inputConnections()[inputPinName];
        QString wireName = "wire_" + QString::number(wireSource.blockNum()) + "_" + wireSource.pinName();
        fullCode += typeCast.code(wireName, wireName);
    }

    QVector<BlockPin> wireBlockPins;
    for (QString inputPinName : m_pinTypeCasts.keys()) {
        BlockPin wireSource = m_block.inputConnections()[inputPinName];
        wireBlockPins.push_back(wireSource);
    }
    for (QString outputPinName : m_pinDataTypes.keys()) {
        BlockPin outputBlockPin(m_blockIndex, outputPinName);
        wireBlockPins.push_back(outputBlockPin);
    }

    QString funcCall = m_blockType.name();
    funcCall += "(";
    funcCall += "&block_options_";
    funcCall += QString::number(m_blockIndex);
    if (0 < wireBlockPins.size()) {
        funcCall += ",";
    }
    for (int i = 0; i < wireBlockPins.size(); i++) {
        BlockPin wireSource = wireBlockPins[i];
        funcCall += "&wire_";
        funcCall += QString::number(wireSource.blockNum());
        funcCall += "_";
        funcCall += wireSource.pinName();
        if (i < wireBlockPins.size() - 1) {
            funcCall += ",";
        }
    }
    funcCall += ");\n";

    fullCode += funcCall;
    return fullCode;
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
