#include "graphicitemparameter.h"

#include <QList>
#include <QMenu>

libblockdia::GraphicItemParameter::GraphicItemParameter(Block *block, int parameterIndex, QGraphicsItem *parent) : GraphicItemTextBox(parent)
{
    this->block = block;
    this->_parameterIndex = parameterIndex;
    this->setBgColor(QColor("#ffe"));
    this->isMouseHoverable = this->_parameterIndex >= 0 && this->_parameterIndex < this->block->getParameters().size();
    this->updateData();
}

void libblockdia::GraphicItemParameter::updateData()
{
    QString txt;
    QList<BlockParameter *> paramList = this->block->getParameters();

    // get parameter data
    if (this->_parameterIndex >= 0 && this->_parameterIndex <= paramList.size()) {
        txt = paramList.at(this->_parameterIndex)->name();
        txt += " = ";
        txt += paramList.at(this->_parameterIndex)->strValue();
    }

    // update text
    GraphicItemTextBox::updateData(txt);
}

void libblockdia::GraphicItemParameter::updateData(int parameterIndex)
{
    this->_parameterIndex = parameterIndex;
    this->isMouseHoverable = this->_parameterIndex >= 0 && this->_parameterIndex < this->block->getParameters().size();
    this->updateData();
}

int libblockdia::GraphicItemParameter::parameterIndex()
{
    return this->_parameterIndex;
}
