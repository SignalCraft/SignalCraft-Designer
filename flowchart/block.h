#ifndef BLOCK_H
#define BLOCK_H

#include <flowchart/blocktype.h>
#include <QString>
#include <QHash>
#include <QSet>
#include <QPointF>
#include <utility>

typedef std::pair<int, QString> BlockPin;

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
