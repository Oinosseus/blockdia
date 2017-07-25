#ifndef BLOCKBROWSER_H
#define BLOCKBROWSER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>

class BlockBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit BlockBrowser(QWidget *parent = nullptr);

signals:

public slots:

private slots:
    void slotDirBrowse(void);

private:
    QTreeView *viewFsTree;
    QFileSystemModel *modelFs;
};

#endif // BLOCKBROWSER_H
