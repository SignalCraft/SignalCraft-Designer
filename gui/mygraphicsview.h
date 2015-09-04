#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMap>
#include <QString>
#include "flowchart/blocktype.h"
#include "gui/blockgraphicsitem.h"
#include <QPoint>
class FlowChart;

enum MouseMode {NONE, CONNECT, DRAG_BLOCK, DRAG_CANVAS};

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicsView(QWidget *parent);
    void setFlowChart(FlowChart *f);
    void setBlockTypes(QMap<QString, BlockType> *blockTypes);
public slots:
    void setCurrentBlockType(BlockType blockType);
protected:
    void addBlock(BlockType blockType, QPoint viewPos);
    void addBlockByCenter(BlockType blockType, QPoint viewPos);
    void moveBlock(BlockGraphicsItem *blockGraphics, QPoint viewPos);
protected slots:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *) override;
    void dropEvent(QDropEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
protected:
    BlockType m_currentBlockType;
    FlowChart *flow;
    QPoint mouseDownPos;
    QMap<QString, BlockType> *m_blockTypes;
    MouseMode mouseMode = NONE;
    BlockGraphicsItem *blockBeingDragged;
    QPoint blockDragMouseOffset;
    void addBlockInternal(BlockType blockType, QPointF scenePos); // should be refactored into custom graphicsscene class
};

#endif // MYGRAPHICSVIEW_H
