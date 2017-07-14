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
    GraphicItemBlockHeader(Block *block);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int minWidth;

private:
    Block *block;
    QRectF currentBoundingRect;
};

} // namespace bd

#endif // GRAPHICITEMBLOCKHEADER_H
