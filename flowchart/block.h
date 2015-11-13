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

class Block {
public:
    Block();
    Block(BlockType blockType, QPointF pos);
    Block(BlockType blockType, QPointF pos, QHash<QString, BlockPin> inputConnections, QHash< QString, QSet< BlockPin > > outputConnections);
    void connectOutput(QString outputPinName, BlockPin inputPin);
    void connectInput(QString inputPinName, BlockPin outputPin);
    void setPos(QPointF pos);
    bool inputIsConnected(QString inputPinName) const;
    QPointF pos() const;
    BlockType blockType() const;
    QHash<QString, BlockPin> inputConnections() const;
    QHash< QString, QSet< BlockPin > > outputConnections() const;
private:
    QPointF m_pos;
    BlockType m_blockType;
    QHash<QString, BlockPin> m_inputConnections;
    QHash< QString, QSet< BlockPin > > m_outputConnections;
};

#endif // BLOCK_H
