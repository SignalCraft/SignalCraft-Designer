#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QHash>
#include <QString>
#include <QContextMenuEvent>
#include "flowchart/blocktype.h"
#include "gui/blockgraphicsitem.h"
#include "gui/pingraphicsitem.h"
#include <QPoint>

class FlowChart;

/**
 * The MouseMode enum represents what kind of action the mouse is currently
 * doing, if anything.
 */
enum MouseMode {NONE, CONNECT, DRAG_BLOCK, DRAG_CANVAS};

/**
 * The FlowChartGraphicsView class displays a FlowChart by wrapping around both
 * a FlowChart object and a QGraphicsScene, so that neither of those objects
 * need to be accessed directly.
 */
class FlowChartGraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    /**
     * Construct a FlowChartGraphicsView.
     * @param parent the optional parent widget
     */
    FlowChartGraphicsView(QWidget *parent);

    /**
     * Set the FlowChart to be displayed.
     * @param f the new FlowChart
     */
    void setFlowChart(FlowChart *f);

    /**
     * Set the mapping from block type names to BlockTypes, by pointer
     * @param blockTypes a pointer to the BlockTypes mapping
     */
    void setBlockTypes(QHash<QString, BlockType> *blockTypes);

    /**
     * Remove all current graphics items, and replace them with what they
     * should be according to the flowchart
     */
    void syncGraphicsItems();


public slots:
    /**
     * Set the curent block type, to be used in the case of a double click.
     * @param blockType the current block type
     */
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

private:
    BlockType m_currentBlockType;
    FlowChart *flow;
    QPoint mouseDownPos;
    QHash<QString, BlockType> *m_blockTypes;
    MouseMode mouseMode = NONE;
    PinGraphicsItem *pinBeingConnected;
    BlockGraphicsItem *blockBeingDragged;
    QPoint blockDragMouseOffset;
    void addBlockInternal(BlockType blockType, QPointF scenePos); // TODO: should be refactored into custom graphicsscene class
    void addGraphicsItems(BlockType blockType, int blockIndex, QPointF scenePos);
    void contextMenuEvent(QContextMenuEvent * event) override;
};

#endif // MYGRAPHICSVIEW_H
