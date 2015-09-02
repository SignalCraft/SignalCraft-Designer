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
#include "gui/blockgraphicsitem.h"
#include "flowchart/flowchart.h"
#include "flowchart/blocktype.h"
#include "gui/pingraphicsitem.h"

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
    addBlock(m_currentBlockType, event->pos());
}

void MyGraphicsView::setCurrentBlockType(BlockType blockType) {
    m_currentBlockType = blockType;
}

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        addBlock(m_currentBlockType, event->pos());
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
            } else {
                auto block = dynamic_cast<BlockGraphicsItem*>(clickedItems[0]);
                if (block) {
                    mouseMode = DRAG_BLOCK;
                    blockBeingDragged = block;
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
            moveBlock(blockBeingDragged, event->pos());
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
                QList<QGraphicsItem*> aList = items(mouseDownPos);
                QList<QGraphicsItem*> bList = items(event->pos());
                PinGraphicsItem* a = NULL;
                PinGraphicsItem* b = NULL;
                for (QGraphicsItem* aRaw : aList) {
                    a = dynamic_cast<PinGraphicsItem*>(aRaw);
                    if (a) {
                        break;
                    }
                }
                for (QGraphicsItem* bRaw : bList) {
                    b = dynamic_cast<PinGraphicsItem*>(bRaw);
                    if (b) {
                        break;
                    }
                }
                if (a && b) {
                    flow->connect(static_cast<BlockGraphicsItem*>(a->parentItem())->blockIndex, a->pinName().toStdString(),
                                  static_cast<BlockGraphicsItem*>(b->parentItem())->blockIndex, b->pinName().toStdString());
                }
            }
        } else if (mouseMode == DRAG_BLOCK) {
            // nothing yet
        } else if (mouseMode == DRAG_CANVAS) {
            // nothing yet
        }
        mouseMode = NONE;
        scene()->invalidate(sceneRect());
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void MyGraphicsView::drawBackground(QPainter *painter, const QRectF &rect) {
    painter->setPen(QPen(QColor(0,0,0), 30));
    for (QGraphicsItem* item : items()) {
        BlockGraphicsItem* blockItem = dynamic_cast<BlockGraphicsItem*>(item);
        if (blockItem) {
            Block root = flow->blocks[blockItem->blockIndex];
            QPointF rootPt = QPointF(root.xPos, root.yPos);
            auto outConnections = root.outputConnections;
            for (auto const outConnection : outConnections) {
                //std::string myPinName = outConnection.first;
                auto otherBlockPins = outConnection.second;
                for (auto const otherBlockPin : otherBlockPins) {
                    int otherBlockIndex = otherBlockPin.first;
                    //std::string otherPinName = otherBlockPin.second;
                    Block otherBlock = flow->blocks[otherBlockIndex];
                    QPointF childPt = QPointF(otherBlock.xPos, otherBlock.yPos);
                    painter->drawLine(rootPt, childPt);
                }
            }
        }
    }
    QGraphicsView::drawBackground(painter, rect);
}

void MyGraphicsView::addBlock(BlockType blockType, QPoint viewPos) {
    QPointF scenePos = mapToScene(viewPos);
    int blockIndex = flow->addBlock(blockType.name.toStdString(), scenePos.x(), scenePos.y());
    QGraphicsItem *itm = new BlockGraphicsItem(blockType, blockIndex);
    itm->setPos(scenePos);
    this->scene()->addItem(itm);
}

void MyGraphicsView::moveBlock(BlockGraphicsItem *blockGraphics, QPoint viewPos) {
    int blockIndex = blockGraphics->blockIndex;
    QPointF scenePos = mapToScene(viewPos);
    flow->moveBlock(blockIndex, scenePos.x(), scenePos.y());
    blockGraphics->setPos(scenePos);
}

