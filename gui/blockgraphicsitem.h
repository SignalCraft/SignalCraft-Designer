#ifndef BLOCKGRAPHICSITEM_H
#define BLOCKGRAPHICSITEM_H

#include <QGraphicsItem>
#include "flowchart/blocktype.h"

class BlockGraphicsItem : public QGraphicsItem
{
public:
    BlockGraphicsItem(BlockType blockType, int index);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    QRectF boundingRect() const override;
    BlockType blockType();
    BlockType m_blockType;
    int blockIndex;
    QRectF m_boundingRect;
};

#endif // BLOCKGRAPHICSITEM_H
