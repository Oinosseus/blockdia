#include "graphiciteminput.h"
#include <QList>

libblockdia::GraphicItemInput::GraphicItemInput(Block *block, int inputIndex, QGraphicsItem *parent) : GraphicItemTextBox(parent)
{
    this->block = block;
    this->inputIndex = inputIndex;
    this->setBgColor(QColor("#eef"));
}

void libblockdia::GraphicItemInput::updateData()
{
    QString txt;
    QList<Input *> inputsList = this->block->getInputs();

    // get input data
    if (this->inputIndex >= 0 && this->inputIndex < inputsList.size()) {
        txt = inputsList.at(this->inputIndex)->name();
    }

    // update
    GraphicItemTextBox::updateData(txt, GraphicItemTextBox::Align::Left);
}

void libblockdia::GraphicItemInput::updateData(int inputIndex)
{
    this->inputIndex = inputIndex;
    this->updateData();
}
