#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bdviewblock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BDViewBlock *view = new BDViewBlock();
    this->setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
