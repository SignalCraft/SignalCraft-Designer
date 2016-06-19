#ifndef BLOCKGRAPHICSITEM_H
#define BLOCKGRAPHICSITEM_H

#include <QGraphicsItem>
#include "blocktype.h"

/**
 * The BlockGraphicsItem class is a QGraphicsItem that represents a block.
 */
class BlockGraphicsItem : public QGraphicsItem {
public:
    /**
     * Construct a BlockGraphicsItem.
     * @param blockType the block's BlockType
     * @param index the block's index
     */
    BlockGraphicsItem(BlockType blockType, int index);

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;

    QRectF boundingRect() const override;

    /**
     * @return the block's BlockType
     */
    BlockType blockType();

    /**
     * Stores the block's index
     */
    int blockIndex; // TODO: accessor

private:
    BlockType m_blockType;
    QRectF m_boundingRect;
};

#endif // BLOCKGRAPHICSITEM_H
