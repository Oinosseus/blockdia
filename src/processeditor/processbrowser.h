#ifndef PROCESSBROWSER_H
#define PROCESSBROWSER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>


class ProcessBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessBrowser(QWidget *parent = nullptr);
    QString currentRootPath(void);

signals:
    void signalFileOpen(QString filePath);

public slots:

private slots:
    void slotDirBrowse(void);
    void slotItemClicked(QModelIndex idx);

private:
    QTreeView *viewFsTree;
    QFileSystemModel *modelFs;
};

#endif // PROCESSBROWSER_H
