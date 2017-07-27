#include "graphicitemblock.h"

#include <QBrush>
#include <QColor>
#include <QFontMetrics>
#include <QDebug>


libblockdia::GraphicItemBlock::GraphicItemBlock(Block *block, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->block = block;

    this->giBlockHead = Q_NULLPTR;
    this->giParamsPublic = QList<GraphicItemTextBox *>();
    this->updateBlockData();
}

QRectF libblockdia::GraphicItemBlock::boundingRect() const
{
    QRectF r = this->childrenBoundingRect();
    return this->currentBoundingRect;
}


void libblockdia::GraphicItemBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);

//    // background 0-cross
//    QRectF r = this->childrenBoundingRect();
//    r.setX(r.x() - 50);
//    r.setY(r.y() - 50);
//    r.setWidth(r.width() + 100);
//    r.setHeight(r.height() + 100);

//    painter->setPen(Qt::red);
//    painter->drawRect(r);
//    painter->drawLine(-200, 0, 200, 0);
//    painter->drawLine(0, -200, 0, 200);
}

void libblockdia::GraphicItemBlock::updateBlockData()
{
    this->prepareGeometryChange();

    qreal widthMaximum = 0;
    qreal widthInputs = 0;
    qreal widthOutputs = 0;
    qreal heightMaximum = 0;
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
    this->giBlockHead->setY(this->giBlockHead->getUsedHeight()/2.0);


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
            gitb->setY(gitb->y() + gitb->getUsedHeight()/2.0);
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

        // input - create new textbox
        giInp = new GraphicItemTextBox(this);
        giInp->bgColor = this->backgroundInputs;
        this->giInputs.append(giInp);

        // input - write text into textbox
        if (i < this->block->getInputs().size()) {
            inp = this->block->getInputs().at(i);
            giInp->setText(inp->name(), GraphicItemTextBox::Align::Left);
        }

        // input update height, width
        giInp->setY(giInp->y() + giInp->getUsedHeight()/2.0);
        giInp->setY(giInp->y() + heightMaximum);
        if (giInp->getUsedWidth() > widthInputs) widthInputs = giInp->getUsedWidth();

        // output - create new textbox
        giOutp = new GraphicItemTextBox(this);
        giOutp->bgColor = this->backgroundOutputs;
        this->giOutputs.append(giOutp);

        // output - write text into textbox
        if (i < this->block->getOutputs().size()) {
            outp = this->block->getOutputs().at(i);
            giOutp->setText(outp->name(), GraphicItemTextBox::Align::Right);
        }

        // output - update height, width
        giOutp->setY(giOutp->y() + giOutp->getUsedHeight()/2.0);
        giOutp->setY(giOutp->y() + heightMaximum);
        if (giOutp->getUsedWidth() > widthOutputs) widthOutputs = giOutp->getUsedWidth();

        // set new height
        int h = 0;
        if (giOutp->getUsedHeight() > h) h = giOutp->getUsedHeight();
        if (giInp->getUsedHeight() > h)  h = giInp->getUsedHeight();
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
            gitb->setY(gitb->y() + gitb->getUsedHeight()/2.0);
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
    this->giBlockHead->setY(this->giBlockHead->y() - heightMaximum/2.0);
    this->giBlockHead->minWidth = widthMaximum;

    // update private parameters
    for (int i=0; i < this->giParamsPrivate.size(); ++i) {
        gitb = this->giParamsPrivate.at(i);
        gitb->minWidth = widthMaximum;
        gitb->setY(gitb->y() - heightMaximum/2.0);
    }

    // stretch i/o width
    if ((widthInputs + widthOutputs) < widthMaximum) {
        int w = widthMaximum - widthInputs - widthOutputs;
        widthInputs += w/2.0;
        widthOutputs += w/2.0;
    }

    // update inputs
    for (int i=0; i < this->giInputs.size(); ++i) {
        gitb = this->giInputs.at(i);
        gitb->minWidth = widthInputs;
        gitb->setY(gitb->y() - heightMaximum/2.0);
        gitb->setX((widthInputs - widthMaximum) / 2.0);
    }

    // update outputs
    for (int i=0; i < this->giOutputs.size(); ++i) {
        gitb = this->giOutputs.at(i);
        gitb->minWidth = widthOutputs;
        gitb->setY(gitb->y() - heightMaximum/2.0);
        gitb->setX((widthMaximum - widthOutputs) / 2.0);
    }

    // update public parameters
    for (int i=0; i < this->giParamsPublic.size(); ++i) {
        gitb = this->giParamsPublic.at(i);
        gitb->minWidth = widthMaximum;
        gitb->setY(gitb->y() - heightMaximum/2.0);
    }

    this->currentBoundingRect.setWidth(widthMaximum);
    this->currentBoundingRect.setHeight(heightMaximum);
    this->currentBoundingRect.setY(this->giBlockHead->y());
    this->currentBoundingRect.setX(this->giBlockHead->x());
}
