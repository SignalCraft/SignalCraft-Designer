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

void MyGraphicsView::dropEvent(QDropEvent *event) {
    addBlock(currentBlockName, event->pos());
}

void MyGraphicsView::setCurrentBlock(QString name) {
    currentBlockName = name;
}

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        addBlock(currentBlockName, event->pos());
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event) {
    if (connectMode && (event->button() == Qt::LeftButton)) {
        mouseDownPos = event->pos();
        connecting = true;
    }
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (connectMode && connecting && (event->button() == Qt::LeftButton)) {
        int distance = (event->pos() - mouseDownPos).manhattanLength();
        connecting = false;
        if (distance >= 1) {
            QList<QGraphicsItem*> aList = items(mouseDownPos);
            QList<QGraphicsItem*> bList = items(event->pos());
            if (!aList.empty() && !bList.empty()) {
                BlockGraphicsItem* a = dynamic_cast<BlockGraphicsItem*>(aList[0]);
                BlockGraphicsItem* b = dynamic_cast<BlockGraphicsItem*>(bList[0]);
                BlockType aBlockType = (*m_blockTypes)[QString((flow->blocks[a->blockIndex]).blockTypeName.c_str())];
                BlockType bBlockType = (*m_blockTypes)[QString((flow->blocks[a->blockIndex]).blockTypeName.c_str())];
                if (a && b) {
                    flow->connect(a->blockIndex, aBlockType.outputs.begin().key().toStdString(),
                                  b->blockIndex, bBlockType.inputs.begin().key().toStdString());
                }
            }
        }
    }
    scene()->invalidate(sceneRect());
    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::drawBackground(QPainter *painter, const QRectF &) {
    painter->setPen(QPen(QColor(0,0,0), 30));
    for (QGraphicsItem* item : items()) {
        BlockGraphicsItem* blockItem = dynamic_cast<BlockGraphicsItem*>(item);
        if (blockItem) {
            Block root = flow->blocks[blockItem->blockIndex];
            QPointF rootPt = QPointF(root.xPos, root.yPos);
            auto children = root.outputConnections;
            for (auto const childs : children) {
                for (auto const child : childs.second) {
                    Block childBlock = flow->blocks[child.first];
                    QPointF childPt = QPointF(childBlock.xPos, childBlock.yPos);
                    painter->drawLine(rootPt, childPt);
                }
            }
        }
    }
}

void MyGraphicsView::addBlock(QString name, QPoint viewPos) {
    QPointF scenePos = mapToScene(viewPos);
    int blockIndex = flow->addBlock(name.toStdString(), scenePos.x(), scenePos.y());
    QGraphicsItem *itm = new BlockGraphicsItem(name, blockIndex);
    itm->setPos(scenePos);
    this->scene()->addItem(itm);
}

