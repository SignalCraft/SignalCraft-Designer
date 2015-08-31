#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMap>
#include <QString>
#include "flowchart/blocktype.h"
class FlowChart;

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
    void drawBackground(QPainter *painter, const QRectF &rect) override;
protected slots:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *) override;
    void dropEvent(QDropEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void addBlock(BlockType blockType, QPoint viewPos);
    BlockType m_currentBlockType;
    FlowChart *flow;
    QPoint mouseDownPos;
    QMap<QString, BlockType> *m_blockTypes;
public:
    bool connectMode = false;
private:
    bool connecting = false;
};

#endif // MYGRAPHICSVIEW_H
