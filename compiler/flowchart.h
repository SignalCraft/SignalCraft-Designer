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
     * Get a block's position.
     * @param blockIndex the index of the block
     * @return the block's position
     */
    QPointF blockPos(int blockIndex) const;

    /**
     * @return a mapping of block indexes to Block objects
     */
    QHash<int, Block> blocks() const; // TODO: remove

    /**
     * @return a pointer to the mapping of block time names to BlockTypes
     */
    const QHash<QString, BlockType> *blockTypes() const; // TODO: remove

    /**
     * Get the block with the given index
     * @param blockIndex the block's index
     * @return the block
     */
    Block block(int blockIndex) const;

private:
    QHash<int, Block> m_blocks;
    const QHash<QString, BlockType> *m_blockTypes;
    int m_currentIndex = 0;
};

#endif // FLOWCHART_H
