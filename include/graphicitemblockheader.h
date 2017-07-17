#ifndef GRAPHICITEMBLOCKHEADER_H
#define GRAPHICITEMBLOCKHEADER_H

#include "libblockdia.h"

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>

#include <block.h>


namespace bd {

class LIBBLOCKDIASHARED_EXPORT GraphicItemBlockHeader : public QGraphicsItem
{
public:
    GraphicItemBlockHeader(Block *block, QGraphicsItem *parent=0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getUsedWidth();
    int getUsedHeight();
    int minWidth;

private:
    Block *block;
    QRectF currentBoundingRect;
};

} // namespace bd

#endif // GRAPHICITEMBLOCKHEADER_H
