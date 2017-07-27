#include "mainwindow.h"

#include <QLabel>
#include <QDockWidget>
#include <QSettings>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include <block.h>
#include <parameterint.h>
#include <viewblockeditor.h>

#include <blockbrowser.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // menu - file
    QMenu *menuFile = new QMenu("File", this);
    this->menuBar()->addMenu(menuFile);

    // action - new block
    QAction *actNewBlock = new QAction("new block", this);
    menuFile->addAction(actNewBlock);
    actNewBlock->setShortcut(Qt::Key_N | Qt::CTRL);
    connect(actNewBlock, SIGNAL(triggered(bool)), this, SLOT(slotActionNewBlock()));

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

void MainWindow::slotActionNewBlock()
{
    // create new block editor
    bd::Block *block = new bd::Block(this);
    block->setInstanceName("InstanceName");
    block->setTypeName("TypeName");
    block->setInstanceId("InstanceId");
    block->setTypeId("TypeId");
    bd::ParameterInt(block, "Parameter1");
    bd::ViewBlockEditor *bEditor = new bd::ViewBlockEditor(block);

    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    tw->addTab(bEditor, "*");
}

void MainWindow::slotActionQuit()
{
    this->close();
}
