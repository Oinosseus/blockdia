#ifndef GRAPHICITEMBLOCKHEADER_H
#define GRAPHICITEMBLOCKHEADER_H

#include "libglobals.h"

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QFont>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>

#include <block.h>


namespace libblockdia {

class LIBBLOCKDIASHARED_EXPORT GraphicItemBlockHeader : public QGraphicsItem
{
public:
    GraphicItemBlockHeader(Block *block, QGraphicsItem *parent=0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal getUsedWidth();
    qreal getUsedHeight();
    qreal minWidth;
    qreal paddingH;
    qreal paddingV;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    Block *block;
    QRectF currentBoundingRect;
    QFont fontInstanceName;
    QFont fontTypeName;
    QFont fontId;
    bool isMouseHovered;
};

} // namespace bd

#endif // GRAPHICITEMBLOCKHEADER_H
