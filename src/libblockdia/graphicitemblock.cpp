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
    int heightCounter = 0;
    GraphicItemTextBox *gitb;

    // ------------------------------------------------------------------------
    //                           Create Sub GraphicIterms
    // ------------------------------------------------------------------------

    // creeate new header
    if (this->giBlockHead != Q_NULLPTR) {
        delete this->giBlockHead;
    }
    this->giBlockHead = new GraphicItemBlockHeader(this->block, this);
    heightCounter += this->giBlockHead->getUsedHeight();

    // create public parameters
    while (this->giParamsPublic.size() > 0) { // clear current list
        GraphicItemTextBox *tb = this->giParamsPublic.takeLast();
        delete tb;
    }
    for (int i=0; i < this->block->getParameters().size(); ++i) { // create new list
        Parameter *param = this->block->getParameters().at(i);
            if (param->isPublic()) {
            gitb = new GraphicItemTextBox(param->name(), this);
            this->giParamsPublic.append(gitb);
            gitb->setY(heightCounter);
            heightCounter += gitb->getUsedHeight();

            // update maximum width
            if (gitb->getUsedWidth() > widthMaximum) widthMaximum = gitb->getUsedWidth();
        }
    }

    // ------------------------------------------------------------------------
    //                             Update Positon
    // ------------------------------------------------------------------------

//    // update header
//    this->giBlockHead->setY(this->giBlockHead->y() - heightCounter/2);

//    // update public parameters
//    for (int i=0; i < this->giParamsPublic.size(); ++i) {
//        gitb = this->giParamsPublic.at(i);
//        gitb->minWidth = widthMaximum;
//        gitb->setY(gitb->y() - heightCounter/2);
//    }
}
