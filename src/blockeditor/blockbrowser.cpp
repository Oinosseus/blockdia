#include "blockbrowser.h"

#include <QLabel>
#include <QFileSystemModel>
#include <QTreeView>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include <QSettings>

BlockBrowser::BlockBrowser(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vbl = new QVBoxLayout(this);
    this->setLayout(vbl);

    // create directory browse button
    QPushButton *btnDirBrowse = new QPushButton("Change Base Directory", this);
    vbl->addWidget(btnDirBrowse, 0, Qt::AlignCenter);
    connect(btnDirBrowse, SIGNAL(clicked(bool)), this, SLOT(slotDirBrowse()));

    // create tree view with model
    this->viewFsTree = new QTreeView(this);
    this->modelFs = new QFileSystemModel(this);
    this->modelFs->setRootPath(QDir::currentPath());
    this->viewFsTree->setModel(this->modelFs);
    vbl->addWidget(this->viewFsTree, 1);

    // layout treeview
    this->viewFsTree->setHeaderHidden(true);
    this->viewFsTree->setColumnHidden(1, true);
    this->viewFsTree->setColumnHidden(2, true);
    this->viewFsTree->setColumnHidden(3, true);

    // load base path
    QSettings s;
    this->viewFsTree->setRootIndex(this->modelFs->index(s.value("BlockBrowser/BasePath").toString()));

}

void BlockBrowser::slotDirBrowse()
{
    // get current root path
    QString dirPath = this->modelFs->rootPath();

    // promt dialog for new root path
    dirPath = QFileDialog::getExistingDirectory(this, "Base Directory", dirPath, QFileDialog::ShowDirsOnly);

    // set path to treeview
    this->viewFsTree->setRootIndex(this->modelFs->index(dirPath));

    // save path
    QSettings s;
    s.setValue("BlockBrowser/BasePath", dirPath);
}
