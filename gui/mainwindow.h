#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "flowchart/flowchart.h"
#include "usb/deviceconnection.h"
class QGraphicsScene;
class QModelIndex;
class MyItemModel;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    MyItemModel *blocks;
    qreal xScale = 0.2;
    qreal yScale = 0.2;
    FlowChart flow;
    DeviceConnection *device = new DeviceConnection();
protected slots:
    void handleCurrentItemChanged(const QModelIndex& current, const QModelIndex&);
    void handleZoomIn();
    void handleZoomOut();
    void handleConnect(bool);
    void handleSaveAs();
    void handleToggleLED();
    void handleCompile();
};

#endif // MAINWINDOW_H
