#ifndef BLOCKPIN_H
#define BLOCKPIN_H

#include <QString>
#include <QJsonValue>

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

QJsonValue BlockPin_toJson(BlockPin obj);
BlockPin BlockPin_fromJson(QJsonValue node);

#endif // BLOCKPIN_H
