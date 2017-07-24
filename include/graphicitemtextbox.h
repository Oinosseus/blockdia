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
    enum struct Align {Center, Left, Right};

    GraphicItemTextBox(QGraphicsItem *parent=0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setText(const QString &text, Align align);
    int getUsedWidth();
    int getUsedHeight();
    int minWidth;
    QColor bgColor;



private:
    QRectF currentBoundingRect;
    QString text;
    QFont font;
    int padding;
    Align algn;
};

} // namespace bd

#endif // GRAPHICITEMTEXTBOX_H
