#include "graphicitemoutput.h"

libblockdia::GraphicItemOutput::GraphicItemOutput(Block *block, int outputIndex, QGraphicsItem *parent) : GraphicItemTextBox(parent)
{
    this->block = block;
    this->outputIndex = outputIndex;
    this->setBgColor(QColor("#fee"));
}

void libblockdia::GraphicItemOutput::updateData()
{
    QString txt;
    QList<Output *> outputsList = this->block->getOutputs();

    // get output data
    if (this->outputIndex >= 0 && this->outputIndex < outputsList.size()) {
        txt = outputsList.at(this->outputIndex)->name();
    }

    // update
    GraphicItemTextBox::updateData(txt, GraphicItemTextBox::Align::Right);
}

void libblockdia::GraphicItemOutput::updateData(int outputIndex)
{
    this->outputIndex = outputIndex;
    this->updateData();
}
