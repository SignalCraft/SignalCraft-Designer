#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "compiler.h"

#include <QStandardItem>
#include "blocktypelistmodel.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "applicationdata.h"
#include "blocktype.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QProcess>
#include <QString>
#include <QList>

MainWindow::MainWindow(ApplicationData _appData, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->listView_io->setAcceptDrops(false);

    flow.setBlockTypes(&_appData.blockTypes);

    ui->graphicsView->setFlowChart(&flow);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(xScale, yScale);
    ui->graphicsView->setSceneRect(-10000, -10000, 20000, 20000);
    ui->graphicsView->centerOn(0,0);

    appData = _appData;

    blocks = new BlockTypeListModel(appData.blockTypes.values());

    ui->listView_io->setModel(blocks);

    connect(ui->listView_io->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::handleCurrentItemChanged);

    ui->graphicsView->setBlockTypes(&(appData.blockTypes));

    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::handleZoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::handleZoomOut);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::handleSaveAs);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::handleLoad);
    connect(ui->pushButton_compile, &QPushButton::pressed, this, &MainWindow::handleCompile);
    connect(ui->pushButton_program, &QPushButton::pressed, this, &MainWindow::handleProgram);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleCurrentItemChanged(const QModelIndex& current, const QModelIndex&) {
    ui->graphicsView->setCurrentBlockType(blocks->blockTypeAt(current));
}

void MainWindow::handleZoomIn() {
    ui->graphicsView->scale(1.1, 1.1);
}

void MainWindow::handleZoomOut() {
    ui->graphicsView->scale(1/1.1, 1/1.1);
}

void MainWindow::handleSaveAs() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save As", "", ".flow");
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QJsonDocument doc(FlowChart_toJson(flow).toObject());
    QByteArray bytes = doc.toJson();
    file.write(bytes);
}

void MainWindow::handleLoad() {
    QString filePath = QFileDialog::getOpenFileName(this, "Save As", "", ".flow");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray bytes = file.readAll();
    auto doc = QJsonDocument::fromJson(bytes);
    flow = FlowChart_fromJson(doc.object());
    flow.setBlockTypes(&appData.blockTypes);
    ui->graphicsView->setFlowChart(&flow);
    ui->graphicsView->syncGraphicsItems();
}

void MainWindow::handleCompile(){
    QString picCode = generatePicCode(flow);
    //QString filePath = QFileDialog::getSaveFileName(this, "Save PicCode", "", ".c");
    QString filePath = "GccApplication1.c";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << picCode;
    file.close();

    QString exefile = "\"C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\shellUtils\\make.exe\"";
    QList<QString> args;
    args.append("-C");
    args.append("build-firmware");
    args.append("all");
    QProcess::execute(exefile, args);
}

void MainWindow::handleProgram() {
    QString exefile = "\"C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\atbackend\\atprogram.exe\"";
    QList<QString> args;
    args.append("-t");
    args.append("edbg");
    args.append("-i");
    args.append("SWD");
    args.append("-d");
    args.append("atsamg55j19");
    args.append("program");
    args.append("-f");
    args.append("build-firmware\\GccApplication1.elf");
    QProcess::execute(exefile, args);
}
