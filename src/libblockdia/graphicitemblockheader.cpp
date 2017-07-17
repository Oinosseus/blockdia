#include "graphicitemblockheader.h"

#include <QFont>
#include <QFontMetrics>
#include <QColor>
#include <QBrush>

bd::GraphicItemBlockHeader::GraphicItemBlockHeader(Block *block, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->block = block;
    this->minWidth = 0;
    this->padding = 15;


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
}

QRectF bd::GraphicItemBlockHeader::boundingRect() const
{
    return this->currentBoundingRect;
}

void bd::GraphicItemBlockHeader::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QFontMetrics fmInstanceName = QFontMetrics(this->fontInstanceName);
    QFontMetrics fmTypeName = QFontMetrics(this->fontTypeName);
    QFontMetrics fmId = QFontMetrics(this->fontId);

    int widthInstanceName = fmInstanceName.width(this->block->instanceName());
    int widthTypeName   = fmTypeName.width(this->block->typeName());
    int widthId   = fmId.width(this->block->typeId() + this->block->instanceId());
    int widthTypeId = widthTypeName + this->padding + widthId;
    int width = (widthInstanceName > widthTypeId) ? widthInstanceName : widthTypeId;

    // determine width of the textbox
    int boxHeight = this->getUsedHeight();
    int boxWidth = this->getUsedWidth();
    if (this->minWidth > boxWidth) boxWidth = this->minWidth;

    // set new bounding rect
    this->currentBoundingRect = QRectF ( - boxWidth/2, - boxHeight/2, boxWidth, boxHeight);

    // setup painter
    painter->setPen(Qt::black);

    // draw box
    painter->fillRect(this->currentBoundingRect, QBrush(this->block->color()));
    painter->drawRect(this->currentBoundingRect);

    // draw instance name
    painter->setFont(fontInstanceName);
    painter->drawText(-widthInstanceName/2, fmInstanceName.ascent() - boxHeight/2 + this->padding, this->block->instanceName());

    // draw type name
    painter->setFont(fontTypeName);
    painter->drawText(-widthTypeId/2, fmInstanceName.height() + this->padding + fmTypeName.ascent() - boxHeight/2 + padding, this->block->typeName());

    // draw typeId + instacneId
    painter->setFont(fontId);
    painter->drawText(widthTypeId/2 - widthId, fmInstanceName.height() + this->padding + fmId.height() - boxHeight/2 + this->padding, this->block->typeId() + this->block->instanceId());

}

int bd::GraphicItemBlockHeader::getUsedWidth()
{
    QFontMetrics fmInstanceName = QFontMetrics(this->fontInstanceName);
    QFontMetrics fmTypeName = QFontMetrics(this->fontTypeName);
    QFontMetrics fmId = QFontMetrics(this->fontId);

    int widthInstanceName = fmInstanceName.width(this->block->instanceName());
    int widthTypeName   = fmTypeName.width(this->block->typeName());
    int widthId   = fmId.width(this->block->typeId() + this->block->instanceId());
    int widthTypeId = widthTypeName + this->padding + widthId;
    int width = (widthInstanceName > widthTypeId) ? widthInstanceName : widthTypeId;

    return width + 2 * this->padding;
}

int bd::GraphicItemBlockHeader::getUsedHeight()
{
    QFontMetrics fmInstanceName = QFontMetrics(this->fontInstanceName);
    QFontMetrics fmTypeName = QFontMetrics(this->fontTypeName);
    QFontMetrics fmId = QFontMetrics(this->fontId);

    int height = 0;
    height += fmInstanceName.height();
    height += padding;
    height += (fmId.height() > fmTypeName.height()) ? fmId.height() : fmTypeName.height();

    return height + 2 * this->padding;
}
