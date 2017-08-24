#include "mainwindow.h"

#include <QLabel>
#include <QDockWidget>
#include <QSettings>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QFile>
#include <QMessageBox>

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
    // open file
    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot open file!");
        return;
    }

    // parse block
    libblockdia::Block * block = libblockdia::Block::parseBlockDef(&f);
    f.close();
    if (!block) {
        QMessageBox::critical(this, "Error", "Error on parsing file!");
        return;
    }

    // Ignore the first change signal for just created block
    // Because instantiating the block causes the signal.
    this->ignoreChangedBlocks.append(block);

    // open new tab for block
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    int index = tw->addTab(new libblockdia::ViewBlockEditor(block), block->typeId());
    tw->setCurrentIndex(index);

    // catch changes inside the block
    connect(block, SIGNAL(signalSomethingChanged(libblockdia::Block*)), this, SLOT(slotBlockChanged(libblockdia::Block*)));
}

void MainWindow::slotActionNewBlock()
{
    // create new block
    libblockdia::Block *block = new libblockdia::Block(this);
    block->setTypeName("New Block Type *");
    block->setTypeId("NBT");

    // create new block editor
    libblockdia::ViewBlockEditor *bEditor = new libblockdia::ViewBlockEditor(block);

    // add block editor to central widget
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    int index = tw->addTab(bEditor, block->typeId() + "*");
    tw->setCurrentIndex(index);

    // catch changes inside the block
    connect(block, SIGNAL(signalSomethingChanged(libblockdia::Block*)), this, SLOT(slotBlockChanged(libblockdia::Block*)));
}

void MainWindow::slotActionQuit()
{
    this->close();
}

void MainWindow::slotBlockChanged(libblockdia::Block *block)
{
    // check if the block was just created
    // In this case ignore the change signal
    // because it is emitted because of instantiating the block
    if (this->ignoreChangedBlocks.contains(block)) {
        this->ignoreChangedBlocks.removeAll(block);
        return;
    }

    // add astresik to tab name if it contains unsaved changes
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    for (int i=0; i < tw->count(); ++i) {
        libblockdia::ViewBlockEditor *editor = static_cast<libblockdia::ViewBlockEditor*>(tw->widget(i));
        if (editor->block() == block) {
            tw->setTabText(i, block->typeId() + "*");
        }
    }
}
