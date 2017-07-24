#include "graphicitemblock.h"

#include <QBrush>
#include <QColor>
#include <QFontMetrics>
#include <QDebug>


bd::GraphicItemBlock::GraphicItemBlock(Block *block, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->block = block;
    this->currentBoundingRect = QRectF();

    this->giBlockHead = Q_NULLPTR;
    this->giParamsPublic = QList<GraphicItemTextBox *>();
    this->updateBlockData();
}

QRectF bd::GraphicItemBlock::boundingRect() const
{
    return this->currentBoundingRect;
}


void bd::GraphicItemBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);

    painter->setPen(Qt::red);
    painter->drawLine(-200, 0, 200, 0);
    painter->drawLine(0, -200, 0, 200);
}

void bd::GraphicItemBlock::updateBlockData()
{
    int widthMaximum = 0;
    int widthInputs = 0;
    int widthOutputs = 0;
    int heightMaximum = 0;
    GraphicItemTextBox *gitb;

    // ------------------------------------------------------------------------
    //                           Create Sub GraphicItems
    // ------------------------------------------------------------------------

    // create new header
    if (this->giBlockHead != Q_NULLPTR) {
        delete this->giBlockHead;
    }
    this->giBlockHead = new GraphicItemBlockHeader(this->block, this);
    if (this->giBlockHead->getUsedWidth() > widthMaximum) widthMaximum = this->giBlockHead->getUsedWidth();
    heightMaximum += this->giBlockHead->getUsedHeight();
    this->giBlockHead->setY(this->giBlockHead->getUsedHeight()/2);


    // clear private parameters
    while (this->giParamsPrivate.size() > 0) delete this->giParamsPrivate.takeLast();

    // create public parameters
    for (int i=0; i < this->block->getParameters().size(); ++i) { // create new list
        Parameter *param = this->block->getParameters().at(i);
        if (!param->isPublic()) {
            gitb = new GraphicItemTextBox(this);
            gitb->bgColor = this->backgroundParameter;
            this->giParamsPrivate.append(gitb);

            // update
            gitb->setText(param->name(), GraphicItemTextBox::Align::Center);

            // update height
            gitb->setY(gitb->y() + gitb->getUsedHeight()/2);
            gitb->setY(gitb->y() + heightMaximum);
            heightMaximum += gitb->getUsedHeight();

            // update maximum width
            if (gitb->getUsedWidth() > widthMaximum) widthMaximum = gitb->getUsedWidth();
        }
    }


    // clear inputs and outputs
    while (this->giInputs.size() > 0) delete this->giInputs.takeLast();
    while (this->giOutputs.size() > 0) delete this->giOutputs.takeLast();
    for (int i = 0; i < this->block->getInputs().size() || i < this->block->getOutputs().size(); ++i) {

        Input *inp = Q_NULLPTR;
        Output *outp = Q_NULLPTR;
        GraphicItemTextBox *giInp = Q_NULLPTR;
        GraphicItemTextBox *giOutp = Q_NULLPTR;

        // inputs
        if (i < this->block->getInputs().size()) {
            inp = this->block->getInputs().at(i);
            giInp = new GraphicItemTextBox(this);
            giInp->bgColor = this->backgroundInputs;
            this->giInputs.append(giInp);

            // update
            giInp->setText(inp->name(), GraphicItemTextBox::Align::Left);

            // update height
            giInp->setY(giInp->y() + giInp->getUsedHeight()/2);
            giInp->setY(giInp->y() + heightMaximum);

            // update width
            if (giInp->getUsedWidth() > widthInputs) widthInputs = giInp->getUsedWidth();
        }

        // outputs
        if (i < this->block->getOutputs().size()) {
            outp = this->block->getOutputs().at(i);
            giOutp = new GraphicItemTextBox(this);
            giOutp->bgColor = this->backgroundOutputs;
            this->giOutputs.append(giOutp);

            // update
            giOutp->setText(outp->name(), GraphicItemTextBox::Align::Right);

            // update height
            giOutp->setY(giOutp->y() + giOutp->getUsedHeight()/2);
            giOutp->setY(giOutp->y() + heightMaximum);

            // update width
            if (giOutp->getUsedWidth() > widthOutputs) widthOutputs = giOutp->getUsedWidth();
        }

        // set new height
        int h = 0;
        if (giOutp != Q_NULLPTR && giOutp->getUsedHeight() > h) h = giOutp->getUsedHeight();
        if (giInp != Q_NULLPTR  && giInp->getUsedHeight() > h)  h = giInp->getUsedHeight();
        heightMaximum += h;

        // set new width
        if ((widthInputs + widthOutputs) > widthMaximum) widthMaximum = widthInputs + widthOutputs;
    }


    // clear public parameters
    while (this->giParamsPublic.size() > 0) delete this->giParamsPublic.takeLast();

    // create public parameters
    for (int i=0; i < this->block->getParameters().size(); ++i) { // create new list
        Parameter *param = this->block->getParameters().at(i);
        if (param->isPublic()) {
            gitb = new GraphicItemTextBox(this);
            gitb->bgColor = this->backgroundParameter;
            this->giParamsPublic.append(gitb);

            // update
            gitb->setText(param->name(), GraphicItemTextBox::Align::Center);

            // update height
            gitb->setY(gitb->y() + gitb->getUsedHeight()/2);
            gitb->setY(gitb->y() + heightMaximum);
            heightMaximum += gitb->getUsedHeight();

            // update maximum width
            if (gitb->getUsedWidth() > widthMaximum) widthMaximum = gitb->getUsedWidth();
        }
    }




    // ------------------------------------------------------------------------
    //                             Update Positon
    // ------------------------------------------------------------------------

    // update header
    this->giBlockHead->setY(this->giBlockHead->y() - heightMaximum/2);
    this->giBlockHead->minWidth = widthMaximum;

    // update private parameters
    for (int i=0; i < this->giParamsPrivate.size(); ++i) {
        gitb = this->giParamsPrivate.at(i);
        gitb->minWidth = widthMaximum;
        gitb->setY(gitb->y() - heightMaximum/2);
    }

    // stretch i/o width
    if ((widthInputs + widthOutputs) < widthMaximum) {
        int w = widthMaximum - widthInputs - widthOutputs;
        widthInputs += w/2;
        widthOutputs += w/2;
    }

    // update inputs
    for (int i=0; i < this->giInputs.size(); ++i) {
        gitb = this->giInputs.at(i);
        gitb->minWidth = widthInputs;
        gitb->setY(gitb->y() - heightMaximum/2);
        gitb->setX((widthInputs - widthMaximum) / 2);
    }

    // update outputs
    for (int i=0; i < this->giOutputs.size(); ++i) {
        gitb = this->giOutputs.at(i);
        gitb->minWidth = widthOutputs;
        gitb->setY(gitb->y() - heightMaximum/2);
        gitb->setX((widthMaximum - widthOutputs) / 2);
    }

    // update public parameters
    for (int i=0; i < this->giParamsPublic.size(); ++i) {
        gitb = this->giParamsPublic.at(i);
        gitb->minWidth = widthMaximum;
        gitb->setY(gitb->y() - heightMaximum/2);
    }

}
