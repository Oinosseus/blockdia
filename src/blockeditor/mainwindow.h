#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget *widgetMain;

private slots:
    void slotActionNewBlock();
    void slotActionQuit();
};

#endif // MAINWINDOW_H
