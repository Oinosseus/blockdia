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



    // ------------------------------------------------------------------------
    //                                  Fonts
    // ------------------------------------------------------------------------

    // font default
    QFont fontDefault = QFont();
    QFontMetrics fmDefault = QFontMetrics(fontDefault);

    // font instance name
    QFont fontInstanceName = fontDefault;
    fontInstanceName.setPointSize(fontInstanceName.pointSize() + 1);
    fontInstanceName.setBold(true);
    fontInstanceName.setItalic(false);
    QFontMetrics fmInstanceName = QFontMetrics(fontInstanceName);
    int widthInstanceName   = fmInstanceName.width(this->block->instanceName());
    int ascentInstanceName  = fmInstanceName.ascent();
    int descentInstanceName = fmInstanceName.descent();

    // font type name
    QFont fontTypeName = fontDefault;
    fontTypeName.setBold(false);
    fontTypeName.setItalic(false);
    QFontMetrics fmTypeName = QFontMetrics(fontTypeName);
    int widthTypeName   = fmTypeName.width(this->block->typeName());
    int ascentTypeName  = fmTypeName.ascent();
    int descentTypeName = fmTypeName.descent();

    // font type + instance id
    QFont fontId = fontDefault;
    fontId.setPointSize(fontId.pointSize() - 3);
    fontId.setBold(false);
    fontId.setItalic(true);
    QFontMetrics fmId = QFontMetrics(fontId);
    int widthId   = fmId.width(this->block->typeId() + this->block->instanceId());
//    int ascentId  = fmId.ascent();
//    int descentId = fmId.descent();



    // ------------------------------------------------------------------------
    //                           Width/Height Calculations
    // ------------------------------------------------------------------------

    // for block header
    int yBaselineInstanceName = 5 + ascentInstanceName;
    int yBaselineTypeName     = yBaselineInstanceName + descentInstanceName + ascentTypeName;
    int yBlockHeader          = yBaselineTypeName + descentTypeName + 5;
    int widthHeader2nLine = widthTypeName + 10 + widthId;

    // block constraints
    int widthConstraints = 0;
    for (int i=0; i < this->block->getConstraints().size(); ++i) {
        BDConstraint *cnstrnt = this->block->getConstraints().at(i);
        QString s = cnstrnt->name() + " = " + cnstrnt->strValue();
        int w = fmDefault.width(s);
        if (w > widthConstraints) widthConstraints = w;
    }

    // overall block width
    int overallWidth = 0;
    if (widthInstanceName > overallWidth) overallWidth = widthInstanceName;
    if (widthHeader2nLine > overallWidth) overallWidth = widthHeader2nLine;
    if (widthConstraints  > overallWidth) overallWidth = widthConstraints;
    int overallLeft   = -10 - overallWidth / 2;
    overallWidth += 20;




    // ------------------------------------------------------------------------
    //                                 Drawing
    // ------------------------------------------------------------------------

    int overallHeight = 0;

    // draw header
    painter->setPen(Qt::black);
    painter->fillRect(QRectF(overallLeft, 0, overallWidth, yBlockHeader), QBrush(this->block->color()));
    painter->drawRect(overallLeft, 0, overallWidth, yBlockHeader);
    painter->setFont(fontInstanceName);
    painter->drawText(-widthInstanceName/2, yBaselineInstanceName, this->block->instanceName());
    painter->setFont(fontTypeName);
    painter->drawText(-widthHeader2nLine/2, yBaselineTypeName, this->block->typeName());
    painter->setFont(fontId);
    painter->drawText(widthHeader2nLine/2 - widthId, yBaselineTypeName, this->block->typeId() + this->block->instanceId());
    overallHeight = yBlockHeader;

    // draw constraints
    painter->setFont(fontDefault);
    for (int i=0; i < this->block->getConstraints().size(); ++i) {
        BDConstraint *cnstrnt = this->block->getConstraints().at(i);
        QString s = cnstrnt->name() + " = " + cnstrnt->strValue();
        int w = fmDefault.width(s);
        int nextHeight = overallHeight + 5 + fmDefault.ascent() + fmDefault.descent() + 5;
        painter->fillRect(QRectF(overallLeft, overallHeight, overallWidth, nextHeight - overallHeight), QBrush(this->backgroundConstraint));
        painter->drawRect(overallLeft, overallHeight, overallWidth, nextHeight - overallHeight);
        painter->drawText(-w/2, overallHeight + 5 + fmDefault.ascent(), s);
        overallHeight = nextHeight;
    }


    // Remember Bounding Rect
    this->currentBoundingRect = QRectF(overallLeft, 0, overallWidth, overallHeight);
}
