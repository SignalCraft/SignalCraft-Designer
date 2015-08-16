#ifndef BLOCK_H
#define BLOCK_H

#include <QPoint>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QMimeData>

class Block : public QMimeData, public QListWidgetItem
{
    Q_OBJECT
public:
    Block();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPoint dragStartPosition;
};

#endif // BLOCK_H
