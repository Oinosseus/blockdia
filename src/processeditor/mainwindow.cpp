#include "mainwindow.h"

#include <QTabWidget>
#include <QDockWidget>
#include <QSettings>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // ========================================================================
    //                                   File Menu
    // ========================================================================

    // menu - file
    QMenu *menuFile = new QMenu("File", this);
    this->menuBar()->addMenu(menuFile);

    // action - quit
    QAction *actQuit = new QAction("quit", this);
    menuFile->addAction(actQuit);
    actQuit->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(actQuit, SIGNAL(triggered(bool)), this, SLOT(slotActionQuit()));



    // ========================================================================
    //                                 Main Window
    // ========================================================================

    this->setWindowTitle("Process Editor");

    // central widget
    this->widgetMain = new QTabWidget(this);
    this->setCentralWidget(this->widgetMain);

    // process browser
    this->processBrowser = new ProcessBrowser(this);
    connect(this->processBrowser, SIGNAL(signalFileOpen(QString)), this, SLOT(slotFileOpen(QString)));

    // process browser dock
    QDockWidget *dock = new QDockWidget("", this);
    dock->setObjectName("ProcessBrowser");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dock->setWidget(this->processBrowser);
    dock->setFloating(false);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::LeftDockWidgetArea, dock);

    // restore window state
    QSettings s;
    this->restoreState(s.value("Mainwindow/State").toByteArray());
    this->restoreGeometry(s.value("MainWindow/Geometry").toByteArray());
}

void MainWindow::slotFileOpen(QString filePath)
{

}

void MainWindow::slotActionQuit()
{
    this->close();
}
