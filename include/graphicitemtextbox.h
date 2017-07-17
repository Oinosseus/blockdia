#ifndef GRAPHICITEMTEXTBOX_H
#define GRAPHICITEMTEXTBOX_H

#include "libblockdia.h"

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>

#include <parameter.h>


namespace bd {

class LIBBLOCKDIASHARED_EXPORT GraphicItemTextBox : public QGraphicsItem
{
public:
    GraphicItemTextBox(QString text, QGraphicsItem *parent=0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setText(const QString &text);
    int getUsedWidth();
    int getUsedHeight();
    int minWidth;


private:
    QRectF currentBoundingRect;
    QString text;
    QFont font;
    QColor bgColor;
    int padding;
};

} // namespace bd

#endif // GRAPHICITEMTEXTBOX_H
