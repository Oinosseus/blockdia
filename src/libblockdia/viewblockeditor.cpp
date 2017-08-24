#include "viewblockeditor.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

#include <parameterint.h>

libblockdia::ViewBlockEditor::ViewBlockEditor(Block *block, QWidget *parent) : QGraphicsView(parent)
{
    this->_block = block;

    QGraphicsScene *scene = new QGraphicsScene(this);
//    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(this->_block->getGraphicsItem());
    this->setScene(scene);

    this->show();
}

libblockdia::Block *libblockdia::ViewBlockEditor::block()
{
    return this->_block;
}
