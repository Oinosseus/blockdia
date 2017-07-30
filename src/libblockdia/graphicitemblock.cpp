#include "graphicitemblock.h"

#include <QBrush>
#include <QColor>
#include <QFontMetrics>
#include <QDebug>


libblockdia::GraphicItemBlock::GraphicItemBlock(Block *block, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->block = block;

    this->giBlockHead = Q_NULLPTR;
    this->updateData();
}

QRectF libblockdia::GraphicItemBlock::boundingRect() const
{
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

void libblockdia::GraphicItemBlock::updateData()
{
    this->prepareGeometryChange();

    qreal widthMaximum = 0;
    qreal widthInputs = 0;
    qreal widthOutputs = 0;
    qreal heightMaximum = 0;

    // get block information
    QList<Input *> blockInputList = this->block->getInputs();
    QList<Output *> blockOutputsList = this->block->getOutputs();
    QList<Parameter *> blockParameters = this->block->getParameters();
    int countPublicParams = 0;
    int countPrivateParams = 0;
    for (int i=0; i < blockParameters.size(); ++i) {
        if (blockParameters.at(i)->isPublic()) {
            ++countPublicParams;
        } else {
            ++countPrivateParams;
        }
    }


    // ------------------------------------------------------------------------
    //                           Create Sub GraphicItems
    // ------------------------------------------------------------------------

    // create new header
    if (this->giBlockHead == Q_NULLPTR) {
        this->giBlockHead = new GraphicItemBlockHeader(this->block, this);
    }

    // update header
    this->giBlockHead->updateData();
    if (this->giBlockHead->actualNeededWidth() > widthMaximum) widthMaximum = this->giBlockHead->actualNeededWidth();
    this->giBlockHead->setY(heightMaximum + this->giBlockHead->boundingRect().height() / 2.0);
    heightMaximum += this->giBlockHead->boundingRect().height();

    // resize private parameters list
    while (this->giParamsPrivate.size() > countPrivateParams) delete this->giParamsPrivate.takeLast();
    while (this->giParamsPrivate.size() < countPrivateParams) this->giParamsPrivate.append(new GraphicItemParameter(this->block, -1, this));

    // update private parameters
    int idxParamPriv = 0;
    for (int i=0; i < blockParameters.size(); ++i) {
        if (!blockParameters.at(i)->isPublic()) {
            GraphicItemParameter *giParam = this->giParamsPrivate.at(idxParamPriv);
            giParam->updateData(i);
            if (giParam->actualNeededWidth() > widthMaximum) widthMaximum = giParam->actualNeededWidth();
            giParam->setY(heightMaximum + giParam->boundingRect().height()/2.0);
            heightMaximum += giParam->boundingRect().height();

            // update maximum width
            if (giParam->actualNeededWidth() > widthMaximum) widthMaximum = giParam->actualNeededWidth();

            ++idxParamPriv;
        }
    }

    // resize IO list
    while (this->giInOuts.size() > blockInputList.size() || this->giInOuts.size() > blockOutputsList.size()) {
        QPair<GraphicItemInput *, GraphicItemOutput *> p = this->giInOuts.takeLast();
        delete p.first;
        delete p.second;
    }
    while (this->giInOuts.size() < blockInputList.size() || this->giInOuts.size() < blockOutputsList.size()) {
        QPair<GraphicItemInput *, GraphicItemOutput *> p;
        p.first = new GraphicItemInput(this->block, -1, this);
        p.second = new GraphicItemOutput(this->block, -1, this);
        this->giInOuts.append(p);
    }

    // update inputs/output list
    for (int i = 0; i < this->giInOuts.size(); ++i) {
        QPair<GraphicItemInput *, GraphicItemOutput *> p = this->giInOuts.at(i);

        // create new input
        if (i <= blockInputList.size()) {
            p.first->updateData(i);
        } else {
            p.first->updateData();
        }

        // create new output
        if (i < blockOutputsList.size()) {
            p.second->updateData(i);
        } else {
            p.second->updateData();
        }

        // calculate width
        if (p.first->actualNeededWidth() > widthInputs) widthInputs = p.first->actualNeededWidth();
        if (p.second->actualNeededWidth() > widthOutputs) widthOutputs = p.second->actualNeededWidth();
        qreal w = widthInputs + widthOutputs;
        if (w > widthMaximum) widthMaximum = w;

        // calculate height
        p.first->setY(heightMaximum + p.first->boundingRect().height() / 2.0);
        p.second->setY(heightMaximum + p.second->boundingRect().height() / 2.0);
        heightMaximum += (p.first->boundingRect().height() > p.second->boundingRect().height()) ? p.first->boundingRect().height() : p.second->boundingRect().height();
    }

    // resize public parameters list
    while (this->giParamsPublic.size() > countPublicParams) delete this->giParamsPublic.takeLast();
    while (this->giParamsPublic.size() < countPublicParams) this->giParamsPublic.append(new GraphicItemParameter(this->block, 0, this));

    // update public parameters
    int idxParamPub = 0;
    for (int i=0; i < blockParameters.size(); ++i) {
        if (blockParameters.at(i)->isPublic()) {
            GraphicItemParameter *giParam = this->giParamsPublic.at(idxParamPub);
            giParam->updateData(i);
            if (giParam->actualNeededWidth() > widthMaximum) widthMaximum = giParam->actualNeededWidth();
            giParam->setY(heightMaximum + giParam->boundingRect().height()/2.0);
            heightMaximum += giParam->boundingRect().height();

            // update maximum width
            if (giParam->actualNeededWidth() > widthMaximum) widthMaximum = giParam->actualNeededWidth();

            ++idxParamPub;
        }
    }



    // ------------------------------------------------------------------------
    //                              Update Positons
    // ------------------------------------------------------------------------

    // header
    this->giBlockHead->setMinWidth(widthMaximum);
    this->giBlockHead->setX(0);
    this->giBlockHead->moveBy(0, - heightMaximum/2.0);

    // private parameters
    for (int i=0; i < this->giParamsPrivate.size(); ++i) {
        GraphicItemParameter *giParam = this->giParamsPrivate.at(i);
        giParam->setMinWidth(widthMaximum);
        giParam->moveBy(0, - heightMaximum/2.0);
    }

    // stretch i/o widths
    if ((widthInputs + widthOutputs) < widthMaximum) {
        int w = widthMaximum - widthInputs - widthOutputs;
        widthInputs += w/2.0;
        widthOutputs += w/2.0;
    }

    // In-/Outputs
    for (int i=0; i < this->giInOuts.size(); ++i) {
        QPair<GraphicItemInput *, GraphicItemOutput *> p = this->giInOuts.at(i);

        // update input
        p.first->setMinWidth(widthInputs);
        p.first->moveBy(0,  - heightMaximum/2.0);
        p.first->setX(- widthMaximum / 2.0 + p.first->boundingRect().width() / 2.0);

        // update output
        p.second->setMinWidth(widthOutputs);
        p.second->moveBy(0,  - heightMaximum/2.0);
        p.second->setX(widthMaximum / 2.0 - p.second->boundingRect().width() / 2.0);
    }

    // public parameters
    for (int i=0; i < this->giParamsPublic.size(); ++i) {
        GraphicItemParameter *giParam = this->giParamsPublic.at(i);
        giParam->setMinWidth(widthMaximum);
        giParam->moveBy(0, - heightMaximum/2.0);
    }

    // calculate new bounding rect
    this->currentBoundingRect = QRectF(- widthMaximum / 2.0, - heightMaximum / 2.0, widthMaximum, heightMaximum);
}
