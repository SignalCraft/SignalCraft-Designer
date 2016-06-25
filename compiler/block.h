#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include <QHash>
#include <QSet>
#include <QPointF>
#include "blockpin.h"
#include <QJsonValue>

/**
 * The Block class represents a specific instance of a block type in a flow
 * chart.
 *
 * In addition to the name of its block type, a Block stores its position,
 * input and output connections, and the values of any set options.
 */
class Block {
public:
    /**
     * Construct an invalid Block.
     *
     * A Block is invalid if its typename is empty.
     */
    Block();

    /**
     * Construct a block with no connections.
     * @param blockTypeName the block's type name
     * @param pos the block's position
     */
    Block(QString blockTypeName, QPointF pos);

    /**
     * Construct a block with the given connections.
     * @param blockTypeName the block's type name
     * @param pos the block's position
     * @param inputConnections a mapping from input pin names to the BlockPin that drives that input pin
     * @param outputConnections a mapping from output pin names to the set of BlockPins driven by that output pin
     */
    Block(QString blockTypeName, QPointF pos, QHash<QString, BlockPin> inputConnections, QHash< QString, QSet< BlockPin > > outputConnections);

    /**
     * Determine whether or not this Block is valid.
     * A Block is valid if its blockTypeName is not empty.
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
     * Disconnect the given output pin from the given BlockPin.
     * @param outputPinName the name of the output pin
     * @param inputPin the BlockPin to disconnect from
     */
    void disconnectOutput(QString outputPinName, BlockPin inputPin);

    /**
     * Connect the given input pin to the given BlockPin.
     * @param inputPinName the name of the input pin
     * @param outputPin the BlockPin to connect to
     */
    void connectInput(QString inputPinName, BlockPin outputPin);

    /**
     * Disconnect the given input pin from its associated BlockPin.
     * @param inputPinName the name of the input pin
     */
    void disconnectInput(QString inputPinName);

    /**
     * Set this block's position.
     * @param pos the new position
     */
    void setPos(QPointF pos);

    /**
     * Set the value of one of this block's options.
     * @param optionName the name of the option to set
     * @param value the value to set the option to
     */
    void setOptionValue(QString optionName, QString value);

    /**
     * Reset this block's option values to the defaults.
     */
    void resetOptionValues();

    /**
     * @return this block's position
     */
    QPointF pos() const;

    /**
     * @return this block's type name
     */
    QString blockTypeName() const;

    /**
     * @return true if this block has connected inputs, false if not
     */
    bool hasInputConnections() const;

    /**
     * Query the BlockPin that the named input pin is connected to.
     *
     * @param inputPinName the name of the input pin to query
     * @return the BlockPin that the given input pin connects to, or an invalid
     * BlockPin if it is not connected
     */
    BlockPin inputConnection(QString inputPinName) const;

    /**
     * Query the set of BlockPins that the named output pin is connected to.
     *
     * @param otuputPinName the name of the output pin to query
     * @return the set of BlockPins that the given output pin connects to
     */
    QSet<BlockPin> outputConnection(QString outputPinName) const;

    /**
     * Query the set value of one of this block's options.
     *
     * @param optionName the name of the option to query.
     * @return the set value of this option, or an empty string if no value has been set.
     */
    QString optionValue(QString optionName) const;

    /**
     * @return a mapping from each of this block's option names to its value
     */
    QHash<QString, QString> optionValues() const; // TODO: Remove this leaky interface. Should be handled by CompiledBlockInfo.

    /**
     * @return the JSON representation of this block
     */
    QJsonValue toJson() const;

private:
    QPointF m_pos;
    QString m_blockTypeName;
    QHash<QString, BlockPin> m_inputConnections;
    QHash< QString, QSet< BlockPin > > m_outputConnections;
    QHash<QString, QString> m_optionValues;
};

QJsonValue Block_toJson(Block obj);
Block Block_fromJson(QJsonValue node);

QJsonValue QHash_int_Block_toJson(QHash<int, Block> obj);
QHash<int, Block> QHash_int_Block_fromJson(QJsonValue node);

QJsonValue QMap_int_Block_toJson(QMap<int, Block> obj);
QMap<int, Block> QMap_int_Block_fromJson(QJsonValue node);

#endif // BLOCK_H
