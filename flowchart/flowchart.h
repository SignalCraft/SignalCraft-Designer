#ifndef FLOWCHART_H
#define FLOWCHART_H

#include <QString>
#include <QHash>
#include <QPointF>
#include "flowchart/block.h"
#include "flowchart/blocktype.h"

class FlowChart {
public:
    FlowChart();
    FlowChart(QHash<int, Block> blocks);
    int addBlock(BlockType blockType, QPointF pos);
    void connect(int sourceBlockID, QString sourcePinName, int sinkBlockID, QString sinkPinName);
    void moveBlock(int blockIndex, QPointF pos);
    void setBlockOptionValues(int blockIndex, QHash<QString, QString> optionValues);
    QPointF blockPos(int blockIndex) const;
    QHash<int, Block> blocks() const;
    Block block(int blockIndex) const;
private:
    QHash<int, Block> m_blocks;
    int m_currentIndex = 0;
};

#endif // FLOWCHART_H
