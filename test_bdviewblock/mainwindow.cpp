#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewblock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bd::ViewBlock *view = new bd::ViewBlock();
    this->setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
