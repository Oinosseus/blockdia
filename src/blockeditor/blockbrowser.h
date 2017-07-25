#ifndef BLOCKBROWSER_H
#define BLOCKBROWSER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>

class BlockBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit BlockBrowser(QWidget *parent = nullptr);
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

#endif // BLOCKBROWSER_H
