#include "graphiciteminput.h"
#include <QList>

libblockdia::GraphicItemInput::GraphicItemInput(Block *block, int inputIndex, QGraphicsItem *parent) : GraphicItemTextBox(parent)
{
    this->block = block;
    this->_inputIndex = inputIndex;
    this->setBgColor(QColor("#eef"));
    this->isMouseHoverable = this->_inputIndex >= 0 && this->_inputIndex < this->block->getInputs().size();
}

void libblockdia::GraphicItemInput::updateData()
{
    QString txt;
    QList<Input *> inputsList = this->block->getInputs();

    // get input data
    if (this->_inputIndex >= 0 && this->_inputIndex < inputsList.size()) {
        txt = inputsList.at(this->_inputIndex)->name();
    }

    // update
    GraphicItemTextBox::updateData(txt, GraphicItemTextBox::Align::Left);
}

void libblockdia::GraphicItemInput::updateData(int inputIndex)
{
    this->_inputIndex = inputIndex;
    this->isMouseHoverable = this->_inputIndex >= 0 && this->_inputIndex < this->block->getInputs().size();
    this->updateData();
}

int libblockdia::GraphicItemInput::inputIndex()
{
    return this->_inputIndex;
}
