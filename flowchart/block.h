#ifndef BLOCK_H
#define BLOCK_H

#include <flowchart/blocktype.h>
#include <QString>
#include <QHash>
#include <QSet>
#include <QPointF>
#include <utility>

class BlockPin {
public:
    BlockPin();
    BlockPin(int blockNum, QString pinName);
    bool operator==(const BlockPin &other) const;
    int blockNum() const;
    QString pinName() const;
private:
    int m_blockNum;
    QString m_pinName;
};

uint qHash(const BlockPin b);

class Block
{
public:
    Block();
    Block(BlockType _blockType, QPointF _pos);
    void connectOutput(QString outputPinName, BlockPin inputPin);
    void connectInput(QString inputPinName, BlockPin outputPin);
    bool inputIsConnected(QString inputPinName);
    QPointF pos;
    BlockType blockType;
    QHash<QString, BlockPin> inputConnections;
    QHash< QString, QSet< BlockPin > > outputConnections;
};

#endif // BLOCK_H
