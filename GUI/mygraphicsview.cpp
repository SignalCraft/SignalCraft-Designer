#include "mygraphicsview.h"
#include "block.h"
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent)
{

}

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event) {
    const Block *block = qobject_cast<const Block *>(event->mimeData());
    qDebug() << event->mimeData()->formats();
    if (!block) {
        event->acceptProposedAction();
    }
}

void MyGraphicsView::dropEvent(QDropEvent *event) {

}

