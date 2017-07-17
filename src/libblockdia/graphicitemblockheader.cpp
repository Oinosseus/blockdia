#include "graphicitemblockheader.h"

#include <QFont>
#include <QFontMetrics>
#include <QColor>
#include <QBrush>

bd::GraphicItemBlockHeader::GraphicItemBlockHeader(Block *block, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->block = block;
    this->minWidth = 0;
}

QRectF bd::GraphicItemBlockHeader::boundingRect() const
{
    return this->currentBoundingRect;
}

void bd::GraphicItemBlockHeader::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    int padding = 5;



    // ------------------------------------------------------------------------
    //                                  Fonts
    // ------------------------------------------------------------------------

    // font default
    QFont fontDefault = QFont();

    // font instance name
    QFont fontInstanceName = fontDefault;
    fontInstanceName.setPointSize(fontInstanceName.pointSize() + 1);
    fontInstanceName.setBold(true);
    fontInstanceName.setItalic(false);
    QFontMetrics fmInstanceName = QFontMetrics(fontInstanceName);
    int widthInstanceName   = fmInstanceName.width(this->block->instanceName());

    // font type name
    QFont fontTypeName = fontDefault;
    fontTypeName.setBold(false);
    fontTypeName.setItalic(false);
    QFontMetrics fmTypeName = QFontMetrics(fontTypeName);
    int widthTypeName   = fmTypeName.width(this->block->typeName());

    // font type + instance id
    QFont fontId = fontDefault;
    fontId.setPointSize(fontId.pointSize() - 3);
    fontId.setBold(false);
    fontId.setItalic(true);
    QFontMetrics fmId = QFontMetrics(fontId);
    int widthId   = fmId.width(this->block->typeId() + this->block->instanceId());



    // ------------------------------------------------------------------------
    //                           Width/Height Calculations
    // ------------------------------------------------------------------------

    // overall height
    int overallHeight = 0;
    overallHeight += fmInstanceName.height();
    overallHeight += padding;
    overallHeight += (fmId.height() > fmTypeName.height()) ? fmId.height() : fmTypeName.height();

    // overall width
    int widthHeader2nLine = widthTypeName + 2*padding + widthId;
    int overallWidth = 0;
    if (widthInstanceName > overallWidth) overallWidth = widthInstanceName;
    if (widthHeader2nLine > overallWidth) overallWidth = widthHeader2nLine;
    if (this->minWidth    > overallWidth) overallWidth = this->minWidth;



    // ------------------------------------------------------------------------
    //                                 Drawing
    // ------------------------------------------------------------------------

    painter->setPen(Qt::black);

    // draw box
    this->currentBoundingRect = QRectF( - overallWidth/2 - padding, - overallHeight/2 - padding, overallWidth + 2*padding, overallHeight + 2*padding);
    painter->fillRect(this->currentBoundingRect, QBrush(this->block->color()));
    painter->drawRect(this->currentBoundingRect);

    // draw instance name
    painter->setFont(fontInstanceName);
    painter->drawText(-widthInstanceName/2, fmInstanceName.ascent() - overallHeight/2, this->block->instanceName());

    // draw type name
    painter->setFont(fontTypeName);
    painter->drawText(-widthHeader2nLine/2, fmInstanceName.height() + padding + fmTypeName.ascent() - overallHeight/2, this->block->typeName());

    // draw typeId + instacneId
    painter->setFont(fontId);
    painter->drawText(widthHeader2nLine/2 - widthId, fmInstanceName.height() + padding + fmId.height() - overallHeight/2, this->block->typeId() + this->block->instanceId());

}

int bd::GraphicItemBlockHeader::getUsedWidth()
{

}

int bd::GraphicItemBlockHeader::getUsedHeight()
{

}
