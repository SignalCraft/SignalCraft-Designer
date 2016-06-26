#include "flowchartgraphicsview.h"

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QString>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRectF>
#include <QPointF>
#include <QVector>
#include <QMimeData>
#include <QContextMenuEvent>
#include <QMenu>
#include <QHash>
#include "blockgraphicsitem.h"
#include "flowchart.h"
#include "blocktype.h"
#include "pingraphicsitem.h"
#include "wiregraphicsitem.h"
#include "blockoptionsdialog.h"
#include "blockpin.h"

FlowChartGraphicsView::FlowChartGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void FlowChartGraphicsView::setFlowChart(FlowChart *f) {
    flow = f;
}

void FlowChartGraphicsView::setBlockTypes(QHash<QString, BlockType> *blockTypes) {
    m_blockTypes = blockTypes;
}

void FlowChartGraphicsView::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void FlowChartGraphicsView::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void FlowChartGraphicsView::dragLeaveEvent(QDragLeaveEvent*) { }

void FlowChartGraphicsView::dropEvent(QDropEvent *event) {
    addBlockByCenter((*m_blockTypes)[event->mimeData()->text()], event->pos());
}

void FlowChartGraphicsView::setCurrentBlockType(BlockType blockType) {
    m_currentBlockType = blockType;
}

void FlowChartGraphicsView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        addBlockByCenter(m_currentBlockType, event->pos());
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void FlowChartGraphicsView::mousePressEvent(QMouseEvent *event) {
    if (mouseMode == NONE && event->button() == Qt::LeftButton) {
        mouseDownPos = event->pos();
        QList<QGraphicsItem*> clickedItems = items(event->pos());
        if (clickedItems.isEmpty()) {
            mouseMode = DRAG_CANVAS;
        } else {
            auto pin = dynamic_cast<PinGraphicsItem*>(clickedItems[0]);
            if (pin) {
                mouseMode = CONNECT;
                pinBeingConnected = pin;
            } else {
                auto block = dynamic_cast<BlockGraphicsItem*>(clickedItems[0]);
                if (block) {
                    mouseMode = DRAG_BLOCK;
                    blockBeingDragged = block;
                    blockDragMouseOffset = mapFromScene(block->pos()) - event->pos();
                }
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void FlowChartGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        if (mouseMode == CONNECT) {
            // nothing yet
        } else if (mouseMode == DRAG_BLOCK) {
            moveBlock(blockBeingDragged, event->pos() + blockDragMouseOffset);
        } else if (mouseMode == DRAG_CANVAS) {
            QGraphicsView::mouseMoveEvent(event);
        }
    }
}

void FlowChartGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (mouseMode == CONNECT) {
            int distance = (event->pos() - mouseDownPos).manhattanLength();
            if (distance >= 1) {
                QList<QGraphicsItem*> bList = items(event->pos());
                PinGraphicsItem* a = pinBeingConnected;
                PinGraphicsItem* b = NULL;
                for (QGraphicsItem* bRaw : bList) {
                    b = dynamic_cast<PinGraphicsItem*>(bRaw);
                    if (b) {
                        break;
                    }
                }
                if (a && b) {
                    BlockPin aBlockPin(static_cast<BlockGraphicsItem*>(a->parentItem())->blockIndex, a->pinName());
                    BlockPin bBlockPin(static_cast<BlockGraphicsItem*>(b->parentItem())->blockIndex, b->pinName());
                    flow->connect(aBlockPin, bBlockPin);
                    scene()->invalidate();
                }
            }
        } else if (mouseMode == DRAG_BLOCK) {
            // nothing yet
        } else if (mouseMode == DRAG_CANVAS) {
            // nothing yet
        }
        mouseMode = NONE;
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void FlowChartGraphicsView::contextMenuEvent(QContextMenuEvent * event) {
    QList<QGraphicsItem*> qgiList = items(event->pos());
    BlockGraphicsItem* bgi = NULL;
    for (QGraphicsItem* qgi : qgiList) {
        bgi = dynamic_cast<BlockGraphicsItem*>(qgi);
        if (bgi) {
            break;
        }
    }
    if (bgi) {
        BlockType bt = bgi->blockType();
        int blockIndex = bgi->blockIndex;
        QPoint globalPos = mapToGlobal(event->pos());
        QMenu myMenu;
        QAction optionsAction(bt.displayName() + " options", this);
        connect(&optionsAction, &QAction::triggered, this, [this, blockIndex]{ handleBlockOptions(blockIndex); });
        myMenu.addAction(&optionsAction);
        myMenu.addSeparator();
        QAction deleteAction("Delete", this);
        connect(&deleteAction, &QAction::triggered, this, [this, blockIndex]{ handleBlockDelete(blockIndex); });
        myMenu.addAction(&deleteAction);
        myMenu.exec(globalPos);
    }
}

void FlowChartGraphicsView::handleBlockOptions(int blockIndex) {
    BlockType bt = flow->blockType(blockIndex);
    BlockOptionsDialog bod(*flow, blockIndex, this);
    bod.exec();
    flow->setBlockOptionValues(blockIndex, bod.optionValues());
}

// This is a terrible implementation. To fix this, store pointers to graphics
// items in a structured way.
void FlowChartGraphicsView::handleBlockDelete(int blockIndex) {
    BlockGraphicsItem *bgi = NULL;
    WireGraphicsItem *wgi = NULL;
    for (QGraphicsItem *qgi : this->scene()->items()) {
        bgi = dynamic_cast<BlockGraphicsItem*>(qgi);
        wgi = dynamic_cast<WireGraphicsItem*>(qgi);
        if (bgi) {
            if (bgi->blockIndex == blockIndex) {
                scene()->removeItem(bgi);
            }
        } else if (wgi) {
            if (wgi->blockPin().blockNum() == blockIndex) {
                scene()->removeItem(wgi);
            }
        }
    }
    flow->removeBlock(blockIndex);
}

void FlowChartGraphicsView::addBlock(BlockType blockType, QPoint viewPos) {
    QPointF scenePos = mapToScene(viewPos);
    addBlockInternal(blockType, scenePos);
}

void FlowChartGraphicsView::addBlockByCenter(BlockType blockType, QPoint viewPos) {
    QPointF scenePos = mapToScene(viewPos) - QPointF(blockType.displayWidth()/2, blockType.displayHeight()/2);
    addBlockInternal(blockType, scenePos);
}

void FlowChartGraphicsView::addBlockInternal(BlockType blockType, QPointF scenePos) {
    int blockIndex = flow->addBlock(blockType.name(), scenePos);
    addGraphicsItems(blockType, blockIndex, scenePos);
}

void FlowChartGraphicsView::moveBlock(BlockGraphicsItem *blockGraphics, QPoint viewPos) {
    int blockIndex = blockGraphics->blockIndex;
    QPointF scenePos = mapToScene(viewPos);
    flow->moveBlock(blockIndex, scenePos);
    blockGraphics->setPos(scenePos);
}

void FlowChartGraphicsView::syncGraphicsItems() {
    for (QGraphicsItem* item : this->scene()->items()) {
        this->scene()->removeItem(item);
    }
    for (int blockIndex : flow->blockIndeces()) {
        BlockType blockType = flow->blockType(blockIndex);
        addGraphicsItems(blockType, blockIndex, flow->blockPos(blockIndex));
    }
}

void FlowChartGraphicsView::addGraphicsItems(BlockType blockType, int blockIndex, QPointF scenePos) {
    QGraphicsItem *itm = new BlockGraphicsItem(blockType, blockIndex);
    itm->setPos(scenePos);
    this->scene()->addItem(itm);
    for (QString outputBlockPinName : blockType.outputs().keys()) {
        WireGraphicsItem *wgi = new WireGraphicsItem(flow, BlockPin(blockIndex, outputBlockPinName));
        wgi->setPos(QPointF(0,0));
        this->scene()->addItem(wgi);
    }
}

