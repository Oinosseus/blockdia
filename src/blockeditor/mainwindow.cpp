#include "mainwindow.h"

#include <QLabel>
#include <QDockWidget>
#include <QSettings>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include <libblockdia.h>

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

    // block browser
    BlockBrowser *browser = new BlockBrowser(this);
    connect(browser, SIGNAL(signalFileOpen(QString)), this, SLOT(slotFileOpen(QString)));

    // block browser dock
    QDockWidget *dock = new QDockWidget("", this);
    dock->setObjectName("BlockBrowser");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dock->setWidget(browser);
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

void MainWindow::slotFileOpen(QString filePath)
{

}

void MainWindow::slotActionNewBlock()
{
    // create new block editor
    libblockdia::Block *block = new libblockdia::Block(this);
    block->setTypeName("New Block Type *");
    block->setTypeId("NBT");
    libblockdia::ViewBlockEditor *bEditor = new libblockdia::ViewBlockEditor(block);

    // add block editor to central widget
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    int index = tw->addTab(bEditor, block->typeId() + "*");
    tw->setCurrentIndex(index);
}

void MainWindow::slotActionQuit()
{
    this->close();
}
