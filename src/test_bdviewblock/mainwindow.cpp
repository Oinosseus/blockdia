#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <libblockdia.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    libblockdia::ViewBlock *view = new libblockdia::ViewBlock();
    this->setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
