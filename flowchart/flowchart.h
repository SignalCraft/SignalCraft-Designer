#ifndef FLOWCHART_H
#define FLOWCHART_H

#include <QString>
#include <QHash>
#include <QPointF>
#include "flowchart/block.h"
#include "flowchart/blocktype.h"

/**
 * The FlowChart class represents a user-written program as a set of
 * interconnected blocks.
 *
 * A FlowChart contains a number of blocks, each identified by a non-negative
 * index. Though connection information is stored by the block, the handling
 * of requests to connect arbritrary pins is handeled by FlowChart.
 */
class FlowChart {
public:
    /**
     * Construct an empty FlowChart.
     */
    FlowChart();

    /**
     * Construct a FlowChart with the given mapping from indexes to blocks.
     * @param blocks a mapping from indexes to blocks
     */
    FlowChart(QHash<int, Block> blocks);

    /**
     * Add a new block to this FlowChart.
     * @param blockType the type of the new block
     * @param pos the position of the new block
     * @return the new block's index
     */
    int addBlock(BlockType blockType, QPointF pos);

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
     * Get the block with the given index
     * @param blockIndex the block's index
     * @return the block
     */
    Block block(int blockIndex) const;

private:
    QHash<int, Block> m_blocks;
    int m_currentIndex = 0;
};

#endif // FLOWCHART_H
