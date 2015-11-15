#include "gui/mygraphicsview.h"

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
#include "gui/blockgraphicsitem.h"
#include "flowchart/flowchart.h"
#include "flowchart/blocktype.h"
#include "gui/pingraphicsitem.h"
#include "gui/wiregraphicsitem.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void MyGraphicsView::setFlowChart(FlowChart *f) {
    flow = f;
}

void MyGraphicsView::setBlockTypes(QMap<QString, BlockType> *blockTypes) {
    m_blockTypes = blockTypes;
}

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void MyGraphicsView::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void MyGraphicsView::dragLeaveEvent(QDragLeaveEvent*) { }

void MyGraphicsView::dropEvent(QDropEvent *event) {
    addBlockByCenter((*m_blockTypes)[event->mimeData()->text()], event->pos());
}

void MyGraphicsView::setCurrentBlockType(BlockType blockType) {
    m_currentBlockType = blockType;
}

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        addBlockByCenter(m_currentBlockType, event->pos());
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event) {
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

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event) {
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

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
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
                    flow->connect(static_cast<BlockGraphicsItem*>(a->parentItem())->blockIndex, a->pinName(),
                                  static_cast<BlockGraphicsItem*>(b->parentItem())->blockIndex, b->pinName());
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

void MyGraphicsView::addBlock(BlockType blockType, QPoint viewPos) {
    QPointF scenePos = mapToScene(viewPos);
    addBlockInternal(blockType, scenePos);
}

void MyGraphicsView::addBlockByCenter(BlockType blockType, QPoint viewPos) {
    QPointF scenePos = mapToScene(viewPos) - QPointF(blockType.displayWidth()/2, blockType.displayHeight()/2);
    addBlockInternal(blockType, scenePos);
}

void MyGraphicsView::addBlockInternal(BlockType blockType, QPointF scenePos) {
    int blockIndex = flow->addBlock(blockType, scenePos);
    QGraphicsItem *itm = new BlockGraphicsItem(blockType, blockIndex);
    itm->setPos(scenePos);
    this->scene()->addItem(itm);
    for (QString outputBlockPinName : blockType.outputs().keys()) {
        WireGraphicsItem *wgi = new WireGraphicsItem(flow, BlockPin(blockIndex, outputBlockPinName));
        wgi->setPos(QPointF(0,0));
        this->scene()->addItem(wgi);
    }

}

void MyGraphicsView::moveBlock(BlockGraphicsItem *blockGraphics, QPoint viewPos) {
    int blockIndex = blockGraphics->blockIndex;
    QPointF scenePos = mapToScene(viewPos);
    flow->moveBlock(blockIndex, scenePos);
    blockGraphics->setPos(scenePos);
}

