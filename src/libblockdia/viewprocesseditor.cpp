#include "viewprocesseditor.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

libblockdia::ViewProcessEditor::ViewProcessEditor(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
//    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    this->setScene(scene);

    this->show();
}

void libblockdia::ViewProcessEditor::wheelEvent(QWheelEvent *e)
{
    // zoom if CTRL was pressed
    if (e->modifiers() & Qt::ControlModifier) {

        // zoom in
        if (e->angleDelta().y() > 0) {
            this->scale(1.07, 1.07);
        }

        // zoom out
        else if (e->angleDelta().y() < 0){
            this->scale(0.93, 0.93);
        }

    } else {
        e->ignore();
    }
}
