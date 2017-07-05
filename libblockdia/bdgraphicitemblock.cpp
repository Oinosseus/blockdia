#include "bdgraphicitemblock.h"
#include <QBrush>
#include <QColor>
#include <QFontMetrics>


BDGraphicItemBlock::BDGraphicItemBlock(BDBlock *block) : QGraphicsItem(NULL)
{
    this->block = block;
    this->currentBoundingRect = QRectF();
}

QRectF BDGraphicItemBlock::boundingRect() const
{
    return this->currentBoundingRect;
}


void BDGraphicItemBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    ///////////////
    // Setup Fonts

    QFont fontDefault = QFont();

    // block instance name
    QFont fontInstanceName = fontDefault;
    fontInstanceName.setPointSize(fontInstanceName.pointSize() + 1);
    fontInstanceName.setBold(true);
    fontInstanceName.setItalic(false);
    QFontMetrics fmInstanceName = QFontMetrics(fontInstanceName);
    int widthInstanceName   = fmInstanceName.width(this->block->instanceName());
    int ascentInstanceName  = fmInstanceName.ascent();
    int descentInstanceName = fmInstanceName.descent();

    // type name
    QFont fontTypeName = fontDefault;
    fontTypeName.setBold(false);
    fontTypeName.setItalic(false);
    QFontMetrics fmTypeName = QFontMetrics(fontTypeName);
    int widthTypeName   = fmTypeName.width(this->block->typeName());
    int ascentTypeName  = fmTypeName.ascent();
    int descentTypeName = fmTypeName.descent();

    // type + instance id
    QFont fontId = fontDefault;
    fontId.setPointSize(fontId.pointSize() - 3);
    fontId.setBold(false);
    fontId.setItalic(true);
    QFontMetrics fmId = QFontMetrics(fontId);
    int widthId   = fmId.width(this->block->typeId() + this->block->instanceId());
//    int ascentId  = fmId.ascent();
//    int descentId = fmId.descent();


    ///////////////////////
    // Calcluate Positions

    // for block header
    int yBaselineInstanceName = 5 + ascentInstanceName;
    int yBaselineTypeName     = yBaselineInstanceName + descentInstanceName + ascentTypeName;
    int yBlockHeader          = yBaselineTypeName + descentTypeName + 5;
    int widthHeader2nLine = widthTypeName + 10 + widthId;

    // overall block width
    int widthOverall = 0;
    if (widthInstanceName > widthOverall) widthOverall = widthInstanceName;
    if (widthHeader2nLine > widthOverall) widthOverall = widthHeader2nLine;


    /////////////////////////
    // Draw Header Rectangle

    painter->setPen(Qt::black);
    painter->fillRect(QRectF(-10 - widthOverall/2, 0, 20 + widthOverall, yBlockHeader), QBrush(this->block->color()));
    painter->drawRect(-10 - widthOverall/2, 0, 20 + widthOverall, yBlockHeader);
    painter->setFont(fontInstanceName);
    painter->drawText(-widthInstanceName/2, yBaselineInstanceName, this->block->instanceName());
    painter->setFont(fontTypeName);
    painter->drawText(-widthHeader2nLine/2, yBaselineTypeName, this->block->typeName());
    painter->setFont(fontId);
    painter->drawText(widthHeader2nLine/2 - widthId, yBaselineTypeName, this->block->typeId() + this->block->instanceId());

    //////////////////////////
    // Remember Bounding Rect
    this->currentBoundingRect = QRectF(-10 - widthOverall/2, 0, 20 + widthOverall, yBlockHeader);
}
