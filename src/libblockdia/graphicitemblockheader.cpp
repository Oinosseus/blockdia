#include "graphicitemblockheader.h"

#include <QFont>
#include <QFontMetrics>
#include <QColor>
#include <QBrush>
#include <QAction>
#include <QMenu>

#include <parameterint.h>
#include <input.h>
#include <output.h>

libblockdia::GraphicItemBlockHeader::GraphicItemBlockHeader(Block *block, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->_block = block;
    this->minWidth = 0;
    this->paddingH = 10;
    this->paddingV = 5;
    this->isMouseHovered = false;

    // font instance name
    this->fontInstanceName.setPointSize(fontInstanceName.pointSize() + 1);
    this->fontInstanceName.setBold(true);
    this->fontInstanceName.setItalic(false);

    // font type name
    this->fontTypeName.setBold(false);
    this->fontTypeName.setItalic(false);

    // font type + instance id
    this->fontId.setPointSize(fontId.pointSize() - 3);
    this->fontId.setBold(false);
    this->fontId.setItalic(true);

    // configurations
    this->setAcceptHoverEvents(true);

    // update
    this->updateData();
}

QRectF libblockdia::GraphicItemBlockHeader::boundingRect() const
{
    return this->currentBoundingRect;
}

void libblockdia::GraphicItemBlockHeader::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // setup painter
    painter->setPen(Qt::black);

    // draw box
    painter->fillRect(this->currentBoundingRect, QBrush(this->bgColor));
    painter->setPen((this->isMouseHovered) ? QColor(Qt::red) : QColor(Qt::black));
    painter->drawRect(this->currentBoundingRect);

    // draw instance name
    painter->setFont(fontInstanceName);
    painter->drawText(this->xInstanceName, this->yInstanceName, this->textInstanceName);

    // draw type name
    painter->setFont(fontTypeName);
    painter->drawText(this->xTypeName, this->yTypeName, this->textTypeName);

    // draw typeId + instacneId
    painter->setFont(fontId);
    painter->drawText(this->xIds, this->yIds, this->textIds);

}

qreal libblockdia::GraphicItemBlockHeader::actualNeededWidth()
{
    return this->_actualNeededWidth;
}

qreal libblockdia::GraphicItemBlockHeader::actualNeededHeight()
{
    return this->_actaulNeededHeight;
}

void libblockdia::GraphicItemBlockHeader::updateData()
{
    this->prepareGeometryChange();
    this->textInstanceName = this->_block->instanceName();
    this->textTypeName = this->_block->typeName();
    this->textIds = this->_block->typeId() + this->_block->instanceId();
    this->bgColor = this->_block->color();
    this->calculateDimensions();
}

void libblockdia::GraphicItemBlockHeader::setMinWidth(qreal minWidth)
{
    this->prepareGeometryChange();
    this->minWidth = minWidth;
    this->calculateDimensions();
}

void libblockdia::GraphicItemBlockHeader::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->prepareGeometryChange();
    this->isMouseHovered = true;
}

void libblockdia::GraphicItemBlockHeader::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->prepareGeometryChange();
    this->isMouseHovered = false;
}

void libblockdia::GraphicItemBlockHeader::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    // create and execute menu
    QMenu menu;
    QAction *actionNewParam  = menu.addAction("Add Integer Parameter");
    QAction *actionNewInput  = menu.addAction("Add Input");
    QAction *actionNewOutput = menu.addAction("Add Output");
    QAction *action = menu.exec(event->screenPos());

    // action - new parameter
    if (action == actionNewParam) {
        new ParameterInt(this->_block, "new param*");

    // action - new input
    } else if (action == actionNewInput) {
        new Input(this->_block, "new input");

    // action - new output
    } else if (action == actionNewOutput) {
        new Output(this->_block, "new output");

    }
}

void libblockdia::GraphicItemBlockHeader::calculateDimensions()
{
    QFontMetrics fmInstanceName = QFontMetrics(this->fontInstanceName);
    QFontMetrics fmTypeName = QFontMetrics(this->fontTypeName);
    QFontMetrics fmId = QFontMetrics(this->fontId);

    // calculate text widths
    qreal widthInstanceName = fmInstanceName.width(this->textInstanceName);
    qreal widthTypeName   = fmTypeName.width(this->textTypeName);
    qreal widthId   = fmId.width(this->textIds);
    qreal widthTypeId = widthTypeName + this->paddingH + widthId;
    qreal widthTextMax = (widthInstanceName > widthTypeId) ? widthInstanceName : widthTypeId;

    // set text x positions
    this->xInstanceName = - widthInstanceName / 2.0;
    this->xTypeName = - widthTypeId / 2.0;
    this->xIds = - widthTypeId / 2.0 + widthTypeName + this->paddingH;

    // calculate text heights
    qreal heightTextMax = 0;
    heightTextMax += fmInstanceName.height();
    heightTextMax += this->paddingV;
    heightTextMax += (fmId.height() > fmTypeName.height()) ? fmId.height() : fmTypeName.height();

    // set text y positions
    this->yInstanceName = fmInstanceName.ascent() - heightTextMax / 2.0;
    this->yTypeName = fmTypeName.ascent() - heightTextMax / 2.0 + fmInstanceName.height() + this->paddingV;
    this->yIds = fmId.ascent() - heightTextMax / 2.0 + fmInstanceName.height() + this->paddingV;

    // calculate new bounding rect
    this->_actualNeededWidth = widthTextMax + 2.0 * this->paddingH;
    this->_actaulNeededHeight = heightTextMax + 2.0 * this->paddingV;
    qreal w = (this->minWidth > this->_actualNeededWidth) ? this->minWidth : this->_actualNeededWidth;
    this->currentBoundingRect.setX(- w / 2.0);
    this->currentBoundingRect.setWidth(w);
    this->currentBoundingRect.setY(- this->_actaulNeededHeight / 2.0);
    this->currentBoundingRect.setHeight(this->_actaulNeededHeight);
}
