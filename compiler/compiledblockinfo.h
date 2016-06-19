#ifndef COMPILEDBLOCKINFO_H
#define COMPILEDBLOCKINFO_H

#include "datatype.h"
#include <QHash>
#include <QString>
#include "automatictypecast.h"
#include "block.h"
#include "overloadresult.h"
#include "blocktype.h"

/**
 * The immutable CompiledBlockInfo class represents all of the information
 * about a specific block that is determined at compile-time.
 *
 * Specifically, this class stores the overloading result,  the exact DataType
 * of each output pin, and the AutomaticTypeCast for any input pin
 */
class CompiledBlockInfo {
public:
    /**
     * Compile the given block in the context of the given compiled blocks
     *
     * @param blockIndex the block's index in the flowchart
     *
     * @param block the block to compile
     *
     * @param compiledBlocks a mapping from block index to CompiledBlockInfo
     * object, that must contain all of the given block's dependencies
     *
     * @param blockTypes a pointer to the mapping of block type names to
     * BlockType objects
     *
     * @return the compiled block
     */
    static CompiledBlockInfo compileBlock(int blockIndex, Block block, QHash<int, CompiledBlockInfo> compiledBlocks, const QHash<QString, BlockType> *blockTypes);

    /**
     * Construct an invalid CompiledBlockInfo, with blockIndex = 0
     */
    CompiledBlockInfo();

    /**
     * Construct a CompiledBlockInfo with the given compile-time data
     *
     * @param blockIndex the block's index in the flowchart
     *
     * @param block the block itself
     *
     * @param blockType the block's BlockType
     *
     * @param pinDataTypes a complete mapping from output pin names to
     * DataType
     *
     * @param code the block's C code
     *
     * @param compiledOptionValues a mapping from option names to compiled
     * option values
     */
    CompiledBlockInfo(int blockIndex, Block block, BlockType blockType, QHash<QString, DataType> pinDataTypes, QString code, QHash<QString, QString>);

    /**
     * @return the block's index
     */
    int blockIndex() const;

    /**
     * @return the block itself
     */
    Block block() const;

    /**
     * @return the block's BlockType
     */
    BlockType blockType() const;

    /**
     * @param pinName the name of an output pin
     * @return the DataType of the named output pin
     */
    DataType pinDataType(QString pinName) const;

    /**
     * @return the line of C code for this block, including the newline
     */
    QString code() const;

    /**
     * @return the lines of C code for declaring the wires defined by this
     * block's outputs
     */
    QString wireCode() const;

    /**
     * @return a mapping from option names to the compiled option values
     */
    QHash<QString, QString> compiledOptionValues() const;

private:
    int m_blockIndex;
    Block m_block;
    BlockType m_blockType;
    QHash<QString, DataType> m_pinDataTypes;
    QString m_code;
    QHash<QString, QString> m_compiledOptionValues;
};

#endif // COMPILEDBLOCKINFO_H
