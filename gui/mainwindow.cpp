#include "gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "compiler/compiler.h"

#include <QStandardItem>
#include "gui/myitemmodel.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "gui/applicationdata.h"
#include "flowchart/blocktype.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    blocks = new MyItemModel();
    ui->listView_io->setModel(blocks);
    ui->listView_io->setAcceptDrops(false);

    ui->graphicsView->setFlowChart(&flow);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(xScale, yScale);
    ui->graphicsView->setSceneRect(-10000, -10000, 20000, 20000);
    ui->graphicsView->centerOn(0,0);

    connect(ui->listView_io->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::handleCurrentItemChanged);
    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::handleZoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::handleZoomOut);
    connect(ui->actionConnect, &QAction::toggled, this, &MainWindow::handleConnect);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::handleSaveAs);
    connect(ui->pushButton_compile, &QPushButton::pressed, this, &MainWindow::handleCompile);
    connect(ui->pushButton_program, &QPushButton::pressed, this, &MainWindow::handleProgram);
}

MainWindow::MainWindow(ApplicationData _appData) : MainWindow() {
    appData = _appData;
    int i = 0;
    for (BlockType bt : appData.blockTypes) {
        QStandardItem *item = new QStandardItem(bt.name);
        blocks->setItem(i, item);
        i++;
    }

    ui->graphicsView->setBlockTypes(&(appData.blockTypes));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleCurrentItemChanged(const QModelIndex& current, const QModelIndex&) {
    ui->graphicsView->setCurrentBlockType(appData.blockTypes[blocks->itemFromIndex(current)->text()]);
}

void MainWindow::handleZoomIn() {
    ui->graphicsView->scale(1.1, 1.1);
}

void MainWindow::handleZoomOut() {
    ui->graphicsView->scale(1/1.1, 1/1.1);
}

void MainWindow::handleConnect(bool enabled) {
    ui->graphicsView->setDragMode(enabled ? QGraphicsView::NoDrag : QGraphicsView::ScrollHandDrag);
    ui->graphicsView->connectMode = enabled;
}

void MainWindow::handleSaveAs() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save As", "", ".flow");
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    Json::StyledWriter json;
    out << json.write(FlowChart::jsonComposeFlowChart(flow)).c_str();
    file.close();
}

void MainWindow::handleCompile(){
    std::string picCode = generatePicCode(flow);
    QString filePath = QFileDialog::getSaveFileName(this, "Save PicCode", "", ".c");
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << picCode.c_str();
    file.close();
}

void MainWindow::handleProgram() {
    int result = device.sendProgram();
    ui->label_actionStatus->setText(QString("Result =") + QString::number(result));
}
