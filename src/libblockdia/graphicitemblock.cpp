#include "graphicitemblock.h"

#include <QBrush>
#include <QColor>
#include <QFontMetrics>
#include <QDebug>
#include <QAction>

#include <blockparameterint.h>
#include <blockinput.h>
#include <blockoutput.h>
#include <dialogeditheader.h>
#include <dialogeditinput.h>
#include <dialogeditoutput.h>
#include <dialogeditparameterint.h>
#include <dialogeditparameterstr.h>
#include <dialogeditparameterenum.h>

libblockdia::GraphicItemBlock::GraphicItemBlock(Block *block, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->block = block;
    this->isMouseHovered = false;
    this->giBlockHead = Q_NULLPTR;
    this->updateData();
    this->setAcceptHoverEvents(true);
}

QRectF libblockdia::GraphicItemBlock::boundingRect() const
{
    if (this->isMouseHovered) {
        return this->currentBoundingRectHighlighted;
    } else {
        return this->currentBoundingRect;
    }
}


void libblockdia::GraphicItemBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);

    // paint highlight border if hovered
    if (this->isMouseHovered) {
        painter->fillRect(this->currentBoundingRectHighlighted, QColor("#444"));
    }

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
    QList<BlockInput *> blockInputList = this->block->getInputs();
    QList<BlockOutput *> blockOutputsList = this->block->getOutputs();
    QList<BlockParameter *> blockParameters = this->block->getParameters();
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
    this->currentBoundingRectHighlighted = this->currentBoundingRect;
    this->currentBoundingRectHighlighted.adjust(-4, -5, 5, 4);
}

void libblockdia::GraphicItemBlock::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    Q_UNUSED(e);
    this->prepareGeometryChange();
    this->isMouseHovered = true;
}

void libblockdia::GraphicItemBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    Q_UNUSED(e);
    this->prepareGeometryChange();
    this->isMouseHovered = false;
}

void libblockdia::GraphicItemBlock::contextMenuEvent(QGraphicsSceneContextMenuEvent *e)
{
    BlockParameter *param = Q_NULLPTR;
    BlockInput *input = Q_NULLPTR;
    BlockOutput *output = Q_NULLPTR;


    // ------------------------------------------------------------------------
    //                          Find Child Item Objects
    // ------------------------------------------------------------------------

    // check if parameter is clicked
    if (param == Q_NULLPTR && input == Q_NULLPTR && output == Q_NULLPTR) {
        for (int i=0; i < this->giParamsPrivate.size(); ++i) {
            GraphicItemParameter *item = this->giParamsPrivate.at(i);
            if (item->isMouseHovered()) {
                int idx = item->parameterIndex();
                if (idx >= 0) {
                    QList<BlockParameter *> listParams = this->block->getParameters();
                    if (idx < listParams.size()) {
                        param = listParams.at(idx);
                        break;
                    }
                }
            }
        }
    }
    if (param == Q_NULLPTR && input == Q_NULLPTR && output == Q_NULLPTR) {
        for (int i=0; i < this->giParamsPublic.size(); ++i) {
            GraphicItemParameter *item = this->giParamsPublic.at(i);
            if (item->isMouseHovered()) {
                int idx = item->parameterIndex();
                if (idx >= 0) {
                    QList<BlockParameter *> listParams = this->block->getParameters();
                    if (idx < listParams.size()) {
                        param = listParams.at(idx);
                        break;
                    }
                }
            }
        }
    }

    // check if input is clicked
    if (param == Q_NULLPTR && input == Q_NULLPTR && output == Q_NULLPTR) {
        for (int i=0; i < this->giInOuts.size(); ++i) {
            QPair<GraphicItemInput *, GraphicItemOutput *> p = this->giInOuts.at(i);
            if (p.first->isMouseHovered()) {
                int idx = p.first->inputIndex();
                if (idx >= 0) {
                    QList<BlockInput *> l = this->block->getInputs();
                    if (idx < l.size()) {
                        input = l.at(idx);
                        break;
                    }
                }
            } else if (p.second->isMouseHovered()) {
                int idx = p.second->outputIndex();
                if (idx >= 0) {
                    QList<BlockOutput *> l = this->block->getOutputs();
                    if (idx < l.size()) {
                        output = l.at(idx);
                        break;
                    }
                }
            }
        }
    }


    // ------------------------------------------------------------------------
    //                               Create Menu
    // ------------------------------------------------------------------------

    // create menu - parameter add
    QMenu menuAddParam("Add Parameter");
    QAction *actionParameterAddInt  = menuAddParam.addAction("Integer Parameter");
    QAction *actionParameterAddStr  = menuAddParam.addAction("String Parameter");
    QAction *actionParameterAddEnum = menuAddParam.addAction("Enum arameter");

    // create menu - main
    QMenu menu;
    QAction *actionBlockHeader = menu.addAction("Edit Block Header");

    // add inputs/outputs/params
    menu.addSeparator();
    QAction *actionInputAdd = menu.addAction("Add Input");
    QAction *actionOutputAdd = menu.addAction("Add Output");
    menu.addMenu(&menuAddParam);

    // parameter menu
    QAction *actionParameterDelete = Q_NULLPTR;
    QAction *actionParameterEdit = Q_NULLPTR;
    QAction *actionParameterPublic = Q_NULLPTR;
    QAction *actionParameterPrivate = Q_NULLPTR;
    if (param != Q_NULLPTR) {
        QMenu *menuSub = new QMenu(param->name());
        menu.addSeparator();
        menu.addMenu(menuSub);
        if (param->isPublic()) actionParameterPrivate = menuSub->addAction("Set Private Parameter");
        else actionParameterPublic = menuSub->addAction("Set Public Paramerer");
        actionParameterEdit = menuSub->addAction("Edit Parameter");
        actionParameterDelete = menuSub->addAction("Delete Parameter");
    }

    // input menu
    QAction *actionInputDelete = Q_NULLPTR;
    QAction *actionInputEdit = Q_NULLPTR;
    if (input != Q_NULLPTR) {
        QMenu *menuSub = new QMenu(input->name());
        menu.addSeparator();
        menu.addMenu(menuSub);
        actionInputEdit = menuSub->addAction("Edit Input");
        actionInputDelete = menuSub->addAction("Delete Input");
    }

    // output menu
    QAction *actionOutputDelete = Q_NULLPTR;
    QAction *actionOutputEdit = Q_NULLPTR;
    if (output != Q_NULLPTR) {
        QMenu *menuSub = new QMenu(output->name());
        menu.addSeparator();
        menu.addMenu(menuSub);
        actionOutputEdit = menuSub->addAction("Edit Output");
        actionOutputDelete = menuSub->addAction("Delete Output");
    }


    // ------------------------------------------------------------------------
    //                               Execute Menu
    // ------------------------------------------------------------------------

    // execute menu
    QAction *action = menu.exec(e->screenPos());

    // no action
    if (action == Q_NULLPTR) {
        // do nothing
    }

    // edit block header
    else if (action == actionBlockHeader) {
        DialogEditHeader dialog(this->block);
        dialog.exec();
    }

    // add pramter int
    else if (action == actionParameterAddInt) {
        new BlockParameterInt("new parameter", this->block);
    }

    // add pramter str
    else if (action == actionParameterAddStr) {
        new BlockParameterStr("new parameter", this->block);
    }

    // add pramter enum
    else if (action == actionParameterAddEnum) {
        new BlockParameterEnum("new parameter", this->block);
    }

    // edit parameter
    else if (action == actionParameterEdit) {
        QString paramType = param->metaObject()->className();
        if (paramType == "libblockdia::ParameterInt") {
            DialogEditParameterInt dialog((BlockParameterInt *) param);
            dialog.exec();
        } else if (paramType == "libblockdia::ParameterStr") {
            DialogEditParameterStr dialog((BlockParameterStr *) param);
            dialog.exec();
        } else if (paramType == "libblockdia::ParameterEnum") {
            DialogEditParameterEnum dialog((BlockParameterEnum *) param);
            dialog.exec();
        }
    }

    // delete parameter
    else if (action == actionParameterDelete) {
        param->deleteLater();
    }

    // set parameter private
    else if (action == actionParameterPrivate) {
        param->setPublic(false);
    }

    // set parameter public
    else if (action == actionParameterPublic) {
        param->setPublic(true);
    }

    // add input
    else if (action == actionInputAdd) {
        new BlockInput("new input", this->block);
    }

    // edit input
    else if (action == actionInputEdit) {
        DialogEditInput dialog(input);
        dialog.exec();
    }

    // delete input
    else if (action == actionInputDelete) {
        input->deleteLater();
    }

    // add output
    else if (action == actionOutputAdd) {
        new BlockOutput("new output", this->block);
    }

    // edit output
    else if (action == actionOutputEdit) {
        DialogEditOutput dialog(output);
        dialog.exec();
    }

    // delete output
    else if (action == actionOutputDelete) {
        output->deleteLater();
    }
}
