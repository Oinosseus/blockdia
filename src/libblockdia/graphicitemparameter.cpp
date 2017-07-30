#include "graphicitemparameter.h"

#include <QList>

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
    }

    // update text
    GraphicItemTextBox::updateData(txt);
}

void libblockdia::GraphicItemParameter::updateData(int parameterIndex)
{
    this->parameterIndex = parameterIndex;
    this->updateData();
}
