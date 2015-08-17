#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItem>
#include "myitemmodel.h"

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

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(xScale, yScale);
    ui->graphicsView->setSceneRect(-10000, -10000, 20000, 20000);
    ui->graphicsView->centerOn(0,0);

    connect(ui->listView_io->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::handleCurrentItemChanged);
    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::handleZoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::handleZoomOut);
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
