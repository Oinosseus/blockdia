#include "graphicitemblock.h"
#include <QBrush>
#include <QColor>
#include <QFontMetrics>


bd::GraphicItemBlock::GraphicItemBlock(Block *block) : QGraphicsItem(NULL)
{
    this->block = block;
    this->currentBoundingRect = QRectF();
}

QRectF bd::GraphicItemBlock::boundingRect() const
{
    return this->currentBoundingRect;
}


void bd::GraphicItemBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    int padding = 5;



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
    int yBaselineInstanceName = padding + ascentInstanceName;
    int yBaselineTypeName     = yBaselineInstanceName + descentInstanceName + ascentTypeName;
    int yBlockHeader          = yBaselineTypeName + descentTypeName + padding;
    int widthHeader2nLine = widthTypeName + 2*padding + widthId;

    // block parameters
    int widthParameters = 0;
    for (int i=0; i < this->block->getParameters().size(); ++i) {
        Parameter *param = this->block->getParameters().at(i);
        QString s = param->name() + " = " + param->strValue();
        int w = fmDefault.width(s);
        if (w > widthParameters) widthParameters = w;
    }

    // block inputs
    int widthInputs = 0;
    for (int i=0; i < this->block->getInputs().size(); ++i) {
        Input *inp = this->block->getInputs().at(i);
        int w = fmDefault.width(inp->name());
        if (w > widthInputs) widthInputs = w;
    }

    // block outputs
    int widthOutputs = 0;
    for (int i=0; i < this->block->getOutputs().size(); ++i) {
        Output *outp = this->block->getOutputs().at(i);
        int w = fmDefault.width(outp->name());
        if (w > widthOutputs) widthOutputs = w;
    }


    // overall block width
    int overallWidth = 0;
    if (widthInstanceName > overallWidth) overallWidth = widthInstanceName;
    if (widthHeader2nLine > overallWidth) overallWidth = widthHeader2nLine;
    if (widthParameters   > overallWidth) overallWidth = widthParameters;
    if (widthInputs       > overallWidth) overallWidth = widthInputs;
    if (widthOutputs      > overallWidth) overallWidth = widthOutputs;
    int overallLeft   = -padding - overallWidth / 2;
    overallWidth += 2*padding;




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

    // draw non-public parameters
    painter->setFont(fontDefault);
    for (int i=0; i < this->block->getParameters().size(); ++i) {
        Parameter *param = this->block->getParameters().at(i);
        if (!param->isPublic()) {
            QString s = param->name() + " = " + param->strValue();
            int w = fmDefault.width(s);
            int nextHeight = overallHeight + padding + fmDefault.ascent() + fmDefault.descent() + padding;
            painter->fillRect(QRectF(overallLeft, overallHeight, overallWidth, nextHeight - overallHeight), QBrush(this->backgroundConstraint));
            painter->drawRect(overallLeft, overallHeight, overallWidth, nextHeight - overallHeight);
            painter->drawText(-w/2, overallHeight + padding + fmDefault.ascent(), s);
            overallHeight = nextHeight;
        }
    }

    // draw Inputs
    int currentInputHeight = overallHeight;
    painter->setFont(fontDefault);
    for (int i=0; i < this->block->getInputs().size(); ++i) {
        Input *inp = this->block->getInputs().at(i);
        int w = fmDefault.width(inp->name());
        int nextInputHeight = currentInputHeight + padding + fmDefault.ascent() + fmDefault.descent() + padding;
        painter->fillRect(QRectF(overallLeft, currentInputHeight, -overallLeft, nextInputHeight - currentInputHeight), QBrush(this->backgroundInputs));
        painter->drawRect(overallLeft, currentInputHeight, -overallLeft, nextInputHeight - currentInputHeight);
        painter->drawText(overallLeft + padding, currentInputHeight + padding + fmDefault.ascent(), inp->name());
        currentInputHeight = nextInputHeight;
    }

    // draw Outputs
    int currentOutputHeight = overallHeight;
    painter->setFont(fontDefault);
    for (int i=0; i < this->block->getOutputs().size(); ++i) {
        Output *outp = this->block->getOutputs().at(i);
        int w = fmDefault.width(outp->name());
        int nextOutputHeight = currentOutputHeight + padding + fmDefault.ascent() + fmDefault.descent() + padding;
        painter->fillRect(QRectF(0, currentOutputHeight, overallWidth + overallLeft, nextOutputHeight - currentOutputHeight), QBrush(this->backgroundOutputs));
        painter->drawRect(0, currentOutputHeight, overallWidth + overallLeft, nextOutputHeight - currentOutputHeight);
        painter->drawText(overallLeft + overallWidth - w - padding, currentOutputHeight + padding + fmDefault.ascent(), outp->name());
        currentOutputHeight = nextOutputHeight;
    }

    // set new overall height
    overallHeight = (currentInputHeight > currentOutputHeight) ? currentInputHeight : currentOutputHeight;

    // draw empty inputs
    if (currentInputHeight < overallHeight) {
        painter->fillRect(QRectF(overallLeft, currentInputHeight, -overallLeft, overallHeight - currentInputHeight), QBrush(this->backgroundInputs));
        painter->drawRect(overallLeft, currentInputHeight, -overallLeft, overallHeight - currentInputHeight);
    }

    // draw empty outputs
    if (currentOutputHeight < overallHeight) {
        painter->fillRect(QRectF(0, currentOutputHeight, overallWidth + overallLeft, overallHeight - currentOutputHeight), QBrush(this->backgroundOutputs));
        painter->drawRect(0, currentOutputHeight, overallWidth + overallLeft, overallHeight - currentOutputHeight);
    }

    // draw public parameters
    painter->setFont(fontDefault);
    for (int i=0; i < this->block->getParameters().size(); ++i) {
        Parameter *param = this->block->getParameters().at(i);
        if (param->isPublic()) {
            QString s = param->name() + " = " + param->strValue();
            int w = fmDefault.width(s);
            int nextHeight = overallHeight + padding + fmDefault.ascent() + fmDefault.descent() + padding;
            painter->fillRect(QRectF(overallLeft, overallHeight, overallWidth, nextHeight - overallHeight), QBrush(this->backgroundConstraint));
            painter->drawRect(overallLeft, overallHeight, overallWidth, nextHeight - overallHeight);
            painter->drawText(-w/2, overallHeight + padding + fmDefault.ascent(), s);
            overallHeight = nextHeight;
        }
    }

    // Remember Bounding Rect
    this->currentBoundingRect = QRectF(overallLeft, 0, overallWidth, overallHeight);
}
