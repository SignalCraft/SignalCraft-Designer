#ifndef BLOCKGRAPHICSITEM_H
#define BLOCKGRAPHICSITEM_H

#include <QGraphicsItem>

class BlockGraphicsItem : public QGraphicsItem
{
public:
    BlockGraphicsItem(QString name_, int index);
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;
    QRectF boundingRect() const override;
    QString name;
    int blockIndex;
};

#endif // BLOCKGRAPHICSITEM_H