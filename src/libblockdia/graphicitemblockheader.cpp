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
    this->block = block;
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
}

QRectF libblockdia::GraphicItemBlockHeader::boundingRect() const
{
    return this->currentBoundingRect;
}

void libblockdia::GraphicItemBlockHeader::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QFontMetrics fmInstanceName = QFontMetrics(this->fontInstanceName);
    QFontMetrics fmTypeName = QFontMetrics(this->fontTypeName);
    QFontMetrics fmId = QFontMetrics(this->fontId);

    qreal widthInstanceName = fmInstanceName.width(this->block->instanceName());
    qreal widthTypeName   = fmTypeName.width(this->block->typeName());
    qreal widthId   = fmId.width(this->block->typeId() + this->block->instanceId());
    qreal widthTypeId = widthTypeName + this->paddingH + widthId;
    qreal width = (widthInstanceName > widthTypeId) ? widthInstanceName : widthTypeId;

    // determine width of the textbox
    qreal boxHeight = this->getUsedHeight();
    qreal boxWidth = this->getUsedWidth();
    if (this->minWidth > boxWidth) boxWidth = this->minWidth;

    // set new bounding rect
    this->currentBoundingRect = QRectF ( - boxWidth/2.0, - boxHeight/2.0, boxWidth, boxHeight);

    // setup painter
    painter->setPen(Qt::black);

    // draw box
    painter->fillRect(this->currentBoundingRect, QBrush(this->block->color()));
    painter->setPen((this->isMouseHovered) ? QColor(Qt::red) : QColor(Qt::black));
    painter->drawRect(this->currentBoundingRect);

    // draw instance name
    painter->setFont(fontInstanceName);
    painter->drawText(-widthInstanceName/2.0, fmInstanceName.ascent() - boxHeight/2.0 + this->paddingV, this->block->instanceName());

    // draw type name
    painter->setFont(fontTypeName);
    painter->drawText(-widthTypeId/2.0, fmInstanceName.height() + this->paddingV + fmTypeName.ascent() - boxHeight/2.0 + this->paddingV, this->block->typeName());

    // draw typeId + instacneId
    painter->setFont(fontId);
    painter->drawText(widthTypeId/2.0 - widthId, fmInstanceName.height() + this->paddingV + fmId.height() - boxHeight/2.0 + this->paddingV, this->block->typeId() + this->block->instanceId());

}

qreal libblockdia::GraphicItemBlockHeader::getUsedWidth()
{
    QFontMetrics fmInstanceName = QFontMetrics(this->fontInstanceName);
    QFontMetrics fmTypeName = QFontMetrics(this->fontTypeName);
    QFontMetrics fmId = QFontMetrics(this->fontId);

    qreal widthInstanceName = fmInstanceName.width(this->block->instanceName());
    qreal widthTypeName   = fmTypeName.width(this->block->typeName());
    qreal widthId   = fmId.width(this->block->typeId() + this->block->instanceId());
    qreal widthTypeId = widthTypeName + this->paddingH + widthId;
    qreal width = (widthInstanceName > widthTypeId) ? widthInstanceName : widthTypeId;

    return width + 2.0 * this->paddingH;
}

qreal libblockdia::GraphicItemBlockHeader::getUsedHeight()
{
    QFontMetrics fmInstanceName = QFontMetrics(this->fontInstanceName);
    QFontMetrics fmTypeName = QFontMetrics(this->fontTypeName);
    QFontMetrics fmId = QFontMetrics(this->fontId);

    qreal height = 0;
    height += fmInstanceName.height();
    height += this->paddingV;
    height += (fmId.height() > fmTypeName.height()) ? fmId.height() : fmTypeName.height();

    return height + 2.0 * this->paddingV;
}

void libblockdia::GraphicItemBlockHeader::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->isMouseHovered = true;
    this->update();
}

void libblockdia::GraphicItemBlockHeader::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->isMouseHovered = false;
    this->update();
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
        new ParameterInt(this->block, "new param*");

    // action - new input
    } else if (action == actionNewInput) {
        new Input(this->block, "new input");

    // action - new output
    } else if (action == actionNewOutput) {
        new Output(this->block, "new output");

    }
}
