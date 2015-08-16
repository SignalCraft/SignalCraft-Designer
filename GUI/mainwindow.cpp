#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QListWidgetItem *itm = new QListWidgetItem(QIcon(":/images/opamp.jpg"), "My Item");
    ui->listWidget->addItem(itm);
    ui->graphicsView->setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
