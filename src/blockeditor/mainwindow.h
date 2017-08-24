#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QList>

#include <libblockdia.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget *widgetMain;
    QList<libblockdia::Block*> justCreatedBlocks;

private slots:
    void slotFileOpen(QString filePath);
    void slotActionNewBlock();
    void slotActionQuit();
    void slotBlockChanged(libblockdia::Block *block);
};

#endif // MAINWINDOW_H
