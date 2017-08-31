#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "processbrowser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    QTabWidget *widgetMain;
    ProcessBrowser *processBrowser;

private slots:
    void slotFileOpen(QString filePath);
    void slotActionQuit();
};

#endif // MAINWINDOW_H
