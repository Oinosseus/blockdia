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
}

void bd::GraphicItemBlock::updateBlockData()
{
    int widthMaximum = 0;
    int heightCounter = 50;
    GraphicItemTextBox *gitb;

    // creeate new header
    if (this->giBlockHead != Q_NULLPTR) {
        delete this->giBlockHead;
    }
    this->giBlockHead = new GraphicItemBlockHeader(this->block, this);

    // clear list
    while (this->giParamsPublic.size() > 0) {
        GraphicItemTextBox *tb = this->giParamsPublic.takeLast();
        delete tb;
    }

    // public parameters
    for (int i=0; i < this->block->getParameters().size(); ++i) {
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

    // apply minimum width to public parameters
    for (int i=0; i < this->giParamsPublic.size(); ++i) {
        gitb = this->giParamsPublic.at(i);
        gitb->minWidth = widthMaximum;
        gitb->setY(gitb->y() - heightCounter/2);
    }
}
