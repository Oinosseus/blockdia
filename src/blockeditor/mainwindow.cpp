#include "mainwindow.h"

#include <QLabel>
#include <QDockWidget>
#include <QSettings>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include <blockbrowser.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // menu - file
    QMenu *menuFile = new QMenu("File", this);
    this->menuBar()->addMenu(menuFile);

    // action - quit
    QAction *actQuit = new QAction("quit", this);
    menuFile->addAction(actQuit);
    actQuit->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(actQuit, SIGNAL(triggered(bool)), this, SLOT(slotActionQuit()));

    // central widget
    this->widgetMain = new QTabWidget(this);
    this->setCentralWidget(this->widgetMain);

    // block browser dock
    QDockWidget *dock = new QDockWidget("", this);
    dock->setObjectName("BlockBrowser");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dock->setWidget(new BlockBrowser(this));
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

void MainWindow::slotActionQuit()
{
    this->close();
}
