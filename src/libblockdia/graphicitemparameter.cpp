#include "graphicitemparameter.h"

#include <QList>
#include <QMenu>

libblockdia::GraphicItemParameter::GraphicItemParameter(Block *block, int parameterIndex, QGraphicsItem *parent) : GraphicItemTextBox(parent)
{
    this->block = block;
    this->parameterIndex = parameterIndex;
    this->setBgColor(QColor("#ffe"));
}

void libblockdia::GraphicItemParameter::updateData()
{
    QString txt;
    QList<Parameter *> paramList = this->block->getParameters();

    // get parameter data
    if (this->parameterIndex >= 0 && this->parameterIndex <= paramList.size()) {
        txt = paramList.at(this->parameterIndex)->name();
        txt += " = ";
        txt += paramList.at(this->parameterIndex)->strValue();
        if (paramList.at(this->parameterIndex)->isPublic()) txt += " (public)";
        else txt += " (private)";
    }

    // update text
    GraphicItemTextBox::updateData(txt);
}

void libblockdia::GraphicItemParameter::updateData(int parameterIndex)
{
    this->parameterIndex = parameterIndex;
    this->updateData();
}

void libblockdia::GraphicItemParameter::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QList<Parameter *> paramList = this->block->getParameters();

    // create and execute menu
    QMenu menu;
    QAction *actionPublic  = menu.addAction("Set Public");
    QAction *actionPrivate = menu.addAction("Set Private");
    QAction *action = menu.exec(event->screenPos());

    // action - public
    if (action == actionPublic && this->parameterIndex >= 0 && this->parameterIndex <= paramList.size()) {
        paramList.at(this->parameterIndex)->setPublic(true);
    }

    // action - private
    else if (action == actionPrivate && this->parameterIndex >= 0 && this->parameterIndex <= paramList.size()) {
        paramList.at(this->parameterIndex)->setPublic(false);
    }

}
