#ifndef FLOWCHART_H
#define FLOWCHART_H

#include <QString>
#include <QHash>
#include <QPointF>
#include "flowchart/block.h"
#include "flowchart/blocktype.h"

class FlowChart
{
public:
    FlowChart();
    int addBlock(BlockType blockType, QPointF pos);
    void connect(int sourceBlockID, QString sourcePinName, int sinkBlockID, QString sinkPinName);
    void moveBlock(int blockIndex, QPointF pos);
    QPointF blockPos(int blockIndex);
    QHash<int, Block> blocks;
protected:
    int currentIndex = 0;
};

#endif // FLOWCHART_H
