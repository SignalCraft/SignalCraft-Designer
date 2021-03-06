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
     *
     * A BlockPin is invalid if its index is negative.
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
BlockPin BlockPin_fromJson(QJsonValue node, bool *ok = NULL);

QJsonValue QHash_QString_BlockPin_toJson(QHash<QString, BlockPin> obj);
QHash<QString, BlockPin> QHash_QString_BlockPin_fromJson(QJsonValue node, bool *ok = NULL);

QJsonValue QMap_QString_BlockPin_toJson(QMap<QString, BlockPin> obj);
QMap<QString, BlockPin> QMap_QString_BlockPin_fromJson(QJsonValue node, bool *ok = NULL);

QJsonValue QHash_QString_QSet_BlockPin_toJson(QHash<QString, QSet<BlockPin>> obj);
QHash<QString, QSet<BlockPin>> QHash_QString_QSet_BlockPin_fromJson(QJsonValue node, bool *ok = NULL);

QJsonValue QMap_QString_QSet_BlockPin_toJson(QMap<QString, QSet<BlockPin>> obj);
QMap<QString, QSet<BlockPin>> QMap_QString_QSet_BlockPin_fromJson(QJsonValue node, bool *ok = NULL);

QJsonValue QSet_BlockPin_toJson(QSet<BlockPin> obj);
QSet<BlockPin> QSet_BlockPin_fromJson(QJsonValue node, bool *ok = NULL);

#endif // BLOCKPIN_H
