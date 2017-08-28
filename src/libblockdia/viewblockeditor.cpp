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

void libblockdia::ViewBlockEditor::wheelEvent(QWheelEvent *e)
{
    // zoom if CTRL was pressed
    if (e->modifiers() & Qt::ControlModifier) {

        // zoom in
        if (e->angleDelta().x() < 0) {
            this->scale(1.1, 1.1);
        }

        // zoom out
        else if (e->angleDelta().x() > 0){
            this->scale(0.9, 0.9);
        }

    } else {
        e->ignore();
    }
}
