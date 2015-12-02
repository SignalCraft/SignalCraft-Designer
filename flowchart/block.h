#ifndef BLOCK_H
#define BLOCK_H

#include <flowchart/blocktype.h>
#include <QString>
#include <QHash>
#include <QSet>
#include <QPointF>
#include <utility>

/**
 * The immutable BlockPin class identifies a pin on a specific block in a flowchart.
 */
class BlockPin {
public:
    /**
     * Construct an invalid BlockPin.
     */
    BlockPin();

    /**
     * Construct a BlockPin.
     * @param blockNum the block's index
     * @param pinName the name of the specific pin on the block
     */
    BlockPin(int blockNum, QString pinName);

    /**
     * Determine whether or not this BlockPin is valid.
     * A BlockPin is valid if its index is nonnegative.
     * @return true if this is a valid BlockPin, false otherwise
     */
    bool isValid() const;

    /**
     * Two BlockPins are equal if they have the same block index and pin name.
     * @param other the other BlockPin
     * @return true if the two BlockPins are the same, false otherwise
     */
    bool operator==(const BlockPin &other) const;

    /**
     * @return the block index
     */
    int blockNum() const;

    /**
     * @return the pin name
     */
    QString pinName() const;

private:
    int m_blockNum;
    QString m_pinName;
};

uint qHash(const BlockPin b);

/**
 * The Block class represents a specific instance of a block type in a flow chart.
 */
class Block {
public:
    /**
     * Construct an invalid Block.
     */
    Block();

    /**
     * Construct a block with no connections.
     * @param blockType the block's type
     * @param pos the block's position
     */
    Block(BlockType blockType, QPointF pos);

    /**
     * Construct a block with the given connections.
     * @param blockType the block's type
     * @param pos the block's position
     * @param inputConnections a mapping from input pin names to the BlockPin that drives that input pin
     * @param outputConnections a mapping from output pin names to the set of BlockPins driven by that output pin
     */
    Block(BlockType blockType, QPointF pos, QHash<QString, BlockPin> inputConnections, QHash< QString, QSet< BlockPin > > outputConnections);

    /**
     * Determine whether or not this Block is valid.
     * A Block is valid if its blockType is valid.
     * @return true if this is a valid Block, false otherwise
     */
    bool isValid() const;

    /**
     * Connect the given output pin to the given BlockPin.
     * @param outputPinName the name of the output pin
     * @param inputPin the BlockPin to connect to
     */
    void connectOutput(QString outputPinName, BlockPin inputPin);

    /**
     * Connect the given input pin to the given BlockPin.
     * @param inputPinName the name of the input pin
     * @param outputPin the BlockPin to connect to
     */
    void connectInput(QString inputPinName, BlockPin outputPin);

    /**
     * Set this block's position.
     * @param pos the new position
     */
    void setPos(QPointF pos);

    /**
     * Set the values of all of this block's options.
     * @param optionValues a mapping from each of this block's option names to its value
     */
    void setOptionValues(QHash<QString, QString> optionValues);

    /**
     * Determine whether or not the named input pin on this block is connected.
     * @param inputPinName the name of an input pin
     * @return true if the input pin is connected, false otherwise
     */
    bool inputIsConnected(QString inputPinName) const;

    /**
     * @return this block's position
     */
    QPointF pos() const;

    /**
     * @return this block's type
     */
    BlockType blockType() const;

    /**
     * @return a mapping from input pin names to the BlockPin that drives that input pin
     */
    QHash<QString, BlockPin> inputConnections() const;

    /**
     * @return a mapping from output pin names to the set of BlockPins driven by that output pin
     */
    QHash< QString, QSet< BlockPin > > outputConnections() const;

    /**
     * @return a mapping from each of this block's option names to its value
     */
    QHash<QString, QString> optionValues() const;

private:
    QPointF m_pos;
    BlockType m_blockType;
    QHash<QString, BlockPin> m_inputConnections;
    QHash< QString, QSet< BlockPin > > m_outputConnections;
    QHash<QString, QString> m_optionValues;
};

#endif // BLOCK_H
