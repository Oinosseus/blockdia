#include "mainwindow.h"

#include <QLabel>
#include <QDockWidget>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // central widget
    this->widgetMain = new QTabWidget(this);
    this->setCentralWidget(this->widgetMain);

    // block browser dock
    QDockWidget *dock = new QDockWidget("Block Browser", this);
    dock->setObjectName("BlockBrowser");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dock->setWidget(new QLabel("Hello World"));
    dock->setFloating(false);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::LeftDockWidgetArea, dock);

    // restore window state
    QSettings s;
    this->restoreState(s.value("Mainwindow/State").toByteArray());
    this->restoreGeometry(s.value("MainWindow/Geometry").toByteArray());

}

MainWindow::~MainWindow()
{
    // save window state
    QSettings s;
    s.setValue("MainWindow/State", this->saveState());
    s.setValue("MainWindow/Geometry", this->saveGeometry());
}
