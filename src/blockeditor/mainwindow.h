#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QList>
#include <QHash>

#include <libblockdia.h>
#include <blockbrowser.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget *widgetMain;
    BlockBrowser *blockBrowser;
    QList<libblockdia::Block*> ignoreChangedBlocks;
    QHash<libblockdia::Block*, QString> openFilePathHash;

private slots:
    void slotFileOpen(QString filePath);
    void slotActionNewBlock();
    void slotActionSave();
    void slotActionSaveAs();
    void slotActionQuit();
    void slotBlockChanged(libblockdia::Block *block);
};

#endif // MAINWINDOW_H
