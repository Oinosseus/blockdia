#include "graphicitemoutput.h"

libblockdia::GraphicItemOutput::GraphicItemOutput(Block *block, int outputIndex, QGraphicsItem *parent) : GraphicItemTextBox(parent)
{
    this->block = block;
    this->_outputIndex = outputIndex;
    this->setBgColor(QColor("#fee"));
    this->isMouseHoverable = this->_outputIndex >= 0 && this->_outputIndex < this->block->getOutputs().size();
}

void libblockdia::GraphicItemOutput::updateData()
{
    QString txt;
    QList<Output *> outputsList = this->block->getOutputs();

    // get output data
    if (this->_outputIndex >= 0 && this->_outputIndex < outputsList.size()) {
        txt = outputsList.at(this->_outputIndex)->name();
    }

    // update
    GraphicItemTextBox::updateData(txt, GraphicItemTextBox::Align::Right);
}

void libblockdia::GraphicItemOutput::updateData(int outputIndex)
{
    this->_outputIndex = outputIndex;
    this->isMouseHoverable = this->_outputIndex >= 0 && this->_outputIndex < this->block->getOutputs().size();
    this->updateData();
}

int libblockdia::GraphicItemOutput::outputIndex()
{
    return this->_outputIndex;
}
