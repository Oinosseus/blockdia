#include "graphicitemparameter.h"

#include <QList>
#include <QMenu>

libblockdia::GraphicItemParameter::GraphicItemParameter(Block *block, int parameterIndex, QGraphicsItem *parent) : GraphicItemTextBox(parent)
{
    this->block = block;
    this->_parameterIndex = parameterIndex;
    this->setBgColor(QColor("#ffe"));
}

void libblockdia::GraphicItemParameter::updateData()
{
    QString txt;
    QList<Parameter *> paramList = this->block->getParameters();

    // get parameter data
    if (this->_parameterIndex >= 0 && this->_parameterIndex <= paramList.size()) {
        txt = paramList.at(this->_parameterIndex)->name();
        txt += " = ";
        txt += paramList.at(this->_parameterIndex)->strValue();
        if (paramList.at(this->_parameterIndex)->isPublic()) txt += " (public)";
        else txt += " (private)";
    }

    // update text
    GraphicItemTextBox::updateData(txt);
}

void libblockdia::GraphicItemParameter::updateData(int parameterIndex)
{
    this->_parameterIndex = parameterIndex;
    this->updateData();
}

int libblockdia::GraphicItemParameter::parameterIndex()
{
    return this->_parameterIndex;
}
