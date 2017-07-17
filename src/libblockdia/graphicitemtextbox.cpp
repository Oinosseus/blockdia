#include "graphicitemtextbox.h"

#include <QColor>
#include <QBrush>

bd::GraphicItemTextBox::GraphicItemTextBox(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->text = "";
    this->minWidth = 0;
    this->font = QFont();
    this->padding = 5;
    this->bgColor = QColor("#fdd");
    this->algn = Align::Center;
}

QRectF bd::GraphicItemTextBox::boundingRect() const
{
    return this->currentBoundingRect;
}

void bd::GraphicItemTextBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QFontMetrics fm = QFontMetrics(this->font);

    // determine width of the textbox
    int boxHeight = this->getUsedHeight();
    int boxWidth = this->getUsedWidth();
    if (this->minWidth > boxWidth) boxWidth = this->minWidth;

    // set new bounding rect
    this->currentBoundingRect = QRectF ( - boxWidth/2, - boxHeight/2, boxWidth, boxHeight);

    // setup painter
    painter->setPen(Qt::black);
    painter->setFont(this->font);

    // draw box
    painter->fillRect(this->currentBoundingRect, QBrush(this->bgColor));
    painter->drawRect(this->currentBoundingRect);

    // draw text
    if (this->algn == Align::Left) {
        painter->drawText(-boxWidth/2 + this->padding, fm.ascent() - boxHeight/2 + this->padding, this->text);
    } else if (this->algn == Align::Center) {
        painter->drawText(-fm.width(this->text)/2, fm.ascent() - boxHeight/2 + this->padding, this->text);
    } else if (this->algn == Align::Right) {
        painter->drawText(boxWidth/2 - fm.width(this->text) - this->padding, fm.ascent() - boxHeight/2 + this->padding, this->text);
    }
}

void bd::GraphicItemTextBox::setText(const QString &text, Align align)
{
    this->text = text;
    this->algn = align;
}

int bd::GraphicItemTextBox::getUsedWidth()
{
    QFontMetrics fm = QFontMetrics(this->font);
    return 2 * this->padding + fm.width(this->text);
}

int bd::GraphicItemTextBox::getUsedHeight()
{
    QFontMetrics fm = QFontMetrics(this->font);
    return 2 * this->padding + fm.height();
}
