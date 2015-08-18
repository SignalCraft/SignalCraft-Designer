#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
class FlowChart;

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicsView(QWidget *parent);
    void setFlowChart(FlowChart *f);
public slots:
    void setCurrentBlock(QString name);
protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
protected slots:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void addBlock(QString name, QPoint viewPos);
    QString currentBlockName;
    FlowChart *flow;
    QPoint mouseDownPos;
public:
    bool connectMode = false;
private:
    bool connecting = false;
};

#endif // MYGRAPHICSVIEW_H
