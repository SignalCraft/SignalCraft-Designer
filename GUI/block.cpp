#include "block.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

Block::Block()
{

}

void Block::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

void Block::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    drag->setMimeData(this);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);


}

