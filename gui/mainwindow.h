#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "flowchart/flowchart.h"
#include "gui/applicationdata.h"
class QGraphicsScene;
class QModelIndex;
class BlockTypeListModel;

namespace Ui {
    class MainWindow;
}

/**
 * A MainWindow is the main window of the program, containing the flow chart and the block type list.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    /**
     * Consruct a MainWindow with the given ApplicationData.
     * @param _appData the application data
     * @param parent the optional parent widget
     */
    explicit MainWindow(ApplicationData _appData, QWidget *parent = 0);

    ~MainWindow();

protected slots:
    void handleCurrentItemChanged(const QModelIndex& current, const QModelIndex& previous);
    void handleZoomIn();
    void handleZoomOut();
    void handleSaveAs();
    void handleLoad();
    void handleCompile();
    void handleProgram();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    BlockTypeListModel *blocks;
    qreal xScale = 0.2;
    qreal yScale = 0.2;
    FlowChart flow;
    ApplicationData appData;
};

#endif // MAINWINDOW_H
