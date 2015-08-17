#include "mygraphicsview.h"

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
#include "blockgraphicsitem.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

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

void MyGraphicsView::addBlock(QString name, QPoint viewPos) {
    QGraphicsItem *itm = new BlockGraphicsItem(name);
    QPointF scenePoint = mapToScene(viewPos);
    itm->setPos(scenePoint);
    this->scene()->addItem(itm);
}

