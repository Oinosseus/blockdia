#include "mainwindow.h"

#include <QLabel>
#include <QDockWidget>
#include <QSettings>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // ========================================================================
    //                                   File Menu
    // ========================================================================

    // menu - file
    QMenu *menuFile = new QMenu("File", this);
    this->menuBar()->addMenu(menuFile);

    // action - new block
    QAction *actNewBlock = new QAction("new block", this);
    menuFile->addAction(actNewBlock);
    actNewBlock->setShortcut(Qt::Key_N | Qt::CTRL);
    connect(actNewBlock, SIGNAL(triggered(bool)), this, SLOT(slotActionNewBlock()));

    // action - save
    QAction *actSave = new QAction("save block", this);
    menuFile->addAction(actSave);
    actSave->setShortcut(Qt::Key_S | Qt::CTRL);
    connect(actSave, SIGNAL(triggered(bool)), this, SLOT(slotActionSave()));

    // action - save as
    QAction *actSaveAs = new QAction("save block as", this);
    menuFile->addAction(actSaveAs);
    actSaveAs->setShortcut(Qt::Key_S | Qt::CTRL | Qt::SHIFT);
    connect(actSaveAs, SIGNAL(triggered(bool)), this, SLOT(slotActionSaveAs()));

    // action - close
    QAction *actClose = new QAction("close block", this);
    menuFile->addAction(actClose);
    actClose->setShortcut(Qt::Key_W | Qt::CTRL);
    connect(actClose, SIGNAL(triggered(bool)), this, SLOT(slotActionClose()));

    // action - quit
    QAction *actQuit = new QAction("quit", this);
    menuFile->addAction(actQuit);
    actQuit->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(actQuit, SIGNAL(triggered(bool)), this, SLOT(slotActionQuit()));


    // ========================================================================
    //                                   View Menu
    // ========================================================================

    // menu - view
    QMenu *menuView = new QMenu("View", this);
    this->menuBar()->addMenu(menuView);

    // action - zoom default
    QAction *actViewZoomDefault = new QAction("zoom default", this);
    menuView->addAction(actViewZoomDefault);
    actViewZoomDefault->setShortcut(Qt::Key_0 | Qt::CTRL);
    connect(actViewZoomDefault, SIGNAL(triggered(bool)), this, SLOT(slotActionViewZoomDefault()));


    // ========================================================================
    //                                   Sub Widgets
    // ========================================================================

    // central widget
    this->widgetMain = new QTabWidget(this);
    this->setCentralWidget(this->widgetMain);

    // block browser
    this->blockBrowser = new BlockBrowser(this);
    connect(this->blockBrowser, SIGNAL(signalFileOpen(QString)), this, SLOT(slotFileOpen(QString)));

    // block browser dock
    QDockWidget *dock = new QDockWidget("", this);
    dock->setObjectName("BlockBrowser");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    dock->setWidget(this->blockBrowser);
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
    QTabWidget *tw = (QTabWidget *) this->centralWidget();

    // check if file is already open
    // in this case set it as current tab and abort opening
    QList<libblockdia::Block*> openBlocks = this->openFilePathHash.keys();
    for (int ib=0; ib < openBlocks.size(); ++ib) {
        if (this->openFilePathHash[openBlocks.at(ib)] == filePath) {
            for (int iv = 0; iv < tw->count(); ++iv) {
                if (static_cast<libblockdia::ViewBlockEditor*>(tw->widget(iv))->block() == openBlocks.at(ib)) {
                    tw->setCurrentIndex(iv);
                    break;
                }
            }
            return;
        }
    }

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

    // remember opened file
    this->openFilePathHash[block] = filePath;

    // Ignore the first change signal for just created block
    // Because instantiating the block causes the signal.
    this->ignoreChangedBlocks.append(block);

    // open new tab for block
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
    this->unsavedBlocks.append(block);
    connect(block, SIGNAL(signalSomethingChanged(libblockdia::Block*)), this, SLOT(slotBlockChanged(libblockdia::Block*)));
}

void MainWindow::slotActionSave()
{
    // get tab widget
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    if (tw->count() == 0) return;

    // get objects
    int currentIndex = tw->currentIndex();
    libblockdia::ViewBlockEditor *editor = static_cast<libblockdia::ViewBlockEditor*>(tw->currentWidget());
    libblockdia::Block *block = editor->block();


    QFile *f = Q_NULLPTR;

    // file path is already known
    if (this->openFilePathHash.contains(block)) {
        f = new QFile(this->openFilePathHash[block]);
    }

    // open file dialog
    else {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Block", this->blockBrowser->currentRootPath(), "XML (*.xml)");
        this->openFilePathHash[block] = fileName;
        f = new QFile(fileName);
    }

    // check if file is valid
    if (!f || !f->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot open file for writing!");
        return;
    }

    // export block
    block->exportBlockDef(f);

    // catch unsaved blocks
    this->unsavedBlocks.removeAll(block);

    // close file
    if (f) {
        f->close();
        f->deleteLater();
        f = Q_NULLPTR;
    }

    // update tab text
    tw->setTabText(currentIndex, block->typeId());
}

void MainWindow::slotActionSaveAs()
{
    // get tab widget
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    if (tw->count() == 0) return;

    // get objects
    int currentIndex = tw->currentIndex();
    libblockdia::ViewBlockEditor *editor = static_cast<libblockdia::ViewBlockEditor*>(tw->currentWidget());
    libblockdia::Block *block = editor->block();

    QFile *f = Q_NULLPTR;

    // open file dialog
    QString defaultPath = (this->openFilePathHash.contains(block)) ? this->openFilePathHash[block] : this->blockBrowser->currentRootPath();
    QString fileName = QFileDialog::getSaveFileName(this, "Save Block As", defaultPath, "XML (*.xml)");
    this->openFilePathHash[block] = fileName;
    f = new QFile(fileName);

    // file path is already known
    if (this->openFilePathHash.contains(block)) {
        f = new QFile(this->openFilePathHash[block]);
    }

    // check if file is valid
    if (!f || !f->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot open file for writing!");
        return;
    }

    // export block
    block->exportBlockDef(f);

    // catch unsaved blocks
    this->unsavedBlocks.removeAll(block);

    // close file
    if (f) {
        f->close();
        f->deleteLater();
        f = Q_NULLPTR;
    }

    // remember file path
    this->openFilePathHash[block] = fileName;

    // update tab text
    tw->setTabText(currentIndex, block->typeId());
}

void MainWindow::slotActionQuit()
{
    this->close();
}

void MainWindow::slotActionClose()
{
    // get tab widget
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    if (tw->count() == 0) return;

    // get objects
    int currentIndex = tw->currentIndex();
    libblockdia::ViewBlockEditor *editor = static_cast<libblockdia::ViewBlockEditor*>(tw->currentWidget());
    libblockdia::Block *block = editor->block();

    // catch unsaved blocks
    if (this->unsavedBlocks.contains(block)) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Unsaved Block", "Save data before closing the block?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        // save before closing
        if (reply == QMessageBox::Save) {

            // call save as
            this->slotActionSaveAs();

            // abort operation if still unsaved
            if (this->unsavedBlocks.contains(block)) return;
        }

        // close without saving
        else if (reply == QMessageBox::Discard) {
            // do nothing in this case
        }

        // abort close action
        else {
            return;
        }

    }

    // forget current file and block
    if (this->openFilePathHash.contains(block)) this->openFilePathHash.remove(block);
    this->unsavedBlocks.removeAll(block);

    // delete block
    block->deleteLater();
    editor->deleteLater();
    tw->removeTab(currentIndex);
}

void MainWindow::slotActionViewZoomDefault()
{
    // get tab widget
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    if (tw->count() == 0) return;

    // get objects
    libblockdia::ViewBlockEditor *editor = static_cast<libblockdia::ViewBlockEditor*>(tw->currentWidget());

    // reset transformation
    editor->setTransform(QTransform());
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

    // catch unsaved changed
    if (!this->unsavedBlocks.contains(block)) this->unsavedBlocks.append(block);

    // add astresik to tab name if it contains unsaved changes
    QTabWidget *tw = (QTabWidget *) this->centralWidget();
    for (int i=0; i < tw->count(); ++i) {
        libblockdia::ViewBlockEditor *editor = static_cast<libblockdia::ViewBlockEditor*>(tw->widget(i));
        if (editor->block() == block) {
            tw->setTabText(i, block->typeId() + " *");
        }
    }
}
