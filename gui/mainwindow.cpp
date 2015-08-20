#include "gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "compiler/compiler.h"

#include <QStandardItem>
#include "gui/myitemmodel.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QStandardItem *item1 = new QStandardItem("Input");
    QStandardItem *item2 = new QStandardItem("Output");
    QStandardItem *item3 = new QStandardItem("Logging");
    QStandardItem *item4 = new QStandardItem("Addition");
    QStandardItem *item5 = new QStandardItem("Subtraction");
    QStandardItem *item6 = new QStandardItem("Multiplication");
    QStandardItem *item7 = new QStandardItem("Division");
    blocks = new MyItemModel();
    blocks->setItem(0, item1);
    blocks->setItem(1, item2);
    blocks->setItem(2, item3);
    blocks->setItem(3, item4);
    blocks->setItem(4, item5);
    blocks->setItem(5, item6);
    blocks->setItem(6, item7);
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
    connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::handleToggleLED);
    connect(ui->compileButton, &QPushButton::pressed, this, &MainWindow::handleCompile);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleCurrentItemChanged(const QModelIndex& current, const QModelIndex&) {
    ui->graphicsView->setCurrentBlock(blocks->itemFromIndex(current)->text());
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

void MainWindow::handleToggleLED() {
    device->toggleLED();
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
