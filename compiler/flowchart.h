#ifndef FLOWCHART_H
#define FLOWCHART_H

#include <QString>
#include <QMap>
#include <QHash>
#include <QPointF>
#include "block.h"
#include "blocktype.h"

/**
 * The FlowChart class represents a user-written program as a set of
 * interconnected blocks, in the context of block type information
 *
 * A FlowChart contains a number of blocks, each identified by a non-negative
 * index. Though connection information is stored by the block, the handling
 * of requests to connect arbritrary pins is handeled by FlowChart.
 *
 * A FlowChart also stores a pointer to a mapping of block type names to
 * BlockTypes, to provide context for its operations.
 */
class FlowChart {
public:
    /**
     * Construct an empty FlowChart.
     */
    FlowChart();

    /**
     * Construct a FlowChart with the given block mapping and block types.
     * @param blocks a mapping from indexes to blocks
     * @param a pointer to a mapping from block type names to block types.
     */
    FlowChart(QHash<int, Block> blocks, QHash<QString, BlockType> *blockTypes);

    /**
     * Add a new block to this FlowChart.
     * @param blockTypeName the type name of the new block
     * @param pos the position of the new block
     * @return the new block's index
     */
    int addBlock(QString blockTypeName, QPointF pos);

    /**
     * Remove the indexed block from this flowchart, cleaning up all the
     * connetions associated with it.
     * @param blockIndex the block's index
     */
    void removeBlock(int blockIndex);

    /**
     * Connect two BlockPins to each other.
     * This method only suceedes if one of the pins is an input and the other is an output.
     * @param first the first BlockPin
     * @param second the second BlockPin
     */
    void connect(BlockPin first, BlockPin second);

    /**
     * Move a block to the given position.
     * @param blockIndex the index of the block to move
     * @param pos the block's new position
     */
    void moveBlock(int blockIndex, QPointF pos);

    /**
     * Set a block's mapping of option names to values.
     * @param blockIndex the index of the block to manipulate
     * @param optionValues the complete mapping of option names to values
     */
    void setBlockOptionValues(int blockIndex, QHash<QString, QString> optionValues);

    /**
     * @return the list of valid indeces that map to blocks in this Flowchart
     */
    QList<int> blockIndeces() const;

    /**
     * Get a block's position.
     * @param blockIndex the index of the block
     * @return the block's position
     */
    QPointF blockPos(int blockIndex) const;

    /**
     * @return a pointer to the mapping of block type names to BlockTypes
     */
    const QHash<QString, BlockType> *blockTypes() const; // TODO: remove

    QString blockTypeName(int blockIndex) const;

    /**
     * Get a block's type name.
     * @param blockIndex the block's index
     * @return the block's type name
     */
    QString blockTypeName(int blockIndex) const;

    /**
     * Get the type of the block with the given index
     * @param blockIndex the block's index
     * @return the block's type
     */
    BlockType blockType(int blockIndex) const;

    /**
     * Get the BlockPin that the given block's named input pin is connected to, or an invalid BlockPin if it's not connected.
     * @param blockIndex the block's index
     * @param inputPinName the block's input pin name
     * @return the output BlockPin that the input pin is connected to
     */
    BlockPin blockInputConnection(int blockIndex, QString inputPinName) const;

    /**
     * Get the BlockPin that the given input BlockPin is connected to, or an invalid BlockPin if it's not connected.
     * @param input the input BlockPin
     * @return the output BlockPin that the input pin is connected to
     */
    BlockPin blockInputConnection(BlockPin input) const;

    /**
     * Get the set of BlockPins that the given block's named output pin is connected to.
     * @param blockIndex the block's index
     * @param inputPinName the block's output pin name
     * @return the set of input BlockPin that the output pin is connected to
     */
    QSet<BlockPin> blockOutputConnection(int blockIndex, QString outputPinName) const;

    /**
     * Get the set of BlockPins that the given output BlockPin is connected to.
     * @param input the output BlockPin
     * @return the set of input BlockPins that the output pin is connected to
     */
    QSet<BlockPin> blockOutputConnection(BlockPin output) const;

    /**
     * Get the value of one of the given block's options.
     * @param blockIndex the block's index
     * @param optionName the name of the option
     * @param defaultValue the option's default value
     * @return the set value for that block's option, or the default value if no value was set
     */
    QString blockOptionValue(int blockIndex, QString optionName, QString defaultValue = "") const;

    /**
     * Determine whether or not the given block has any input connections
     * @param blockIndex the block's index
     * @return true if the block has at least one input connection, or false otherwise
     */
    bool blockHasInputConnections(int blockIndex) const;

    /**
     * @return the flowchart's JSON representation
     */
    QJsonValue toJson() const;

public: // for CompiledBlockInfo
    QHash<int, Block> m_blocks;
private:
    const QHash<QString, BlockType> *m_blockTypes;
    int m_currentIndex = 0;
};

QJsonValue FlowChart_toJson(FlowChart obj);
FlowChart FlowChart_fromJsonWithBlockTypes(QJsonValue node, QHash<QString, BlockType> *blockTypes, bool *ok = NULL);

#endif // FLOWCHART_H
