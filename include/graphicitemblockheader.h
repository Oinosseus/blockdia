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
#include <graphicitemtextbox.h>


namespace libblockdia {

/**
 * @brief A QGraphicsItem that shows the header of a Block
 */
class LIBBLOCKDIASHARED_EXPORT GraphicItemBlockHeader : public QGraphicsItem
{

public:

    /**
     * @param parent The QGraphicsItem parent object.
     */
    GraphicItemBlockHeader(Block *block, QGraphicsItem *parent=0);

    /**
     * @return The current bounding rect
     */
    QRectF boundingRect() const;

    /**
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @return The actual needed width for the text box (regardless of requested minimal width)
     */
    qreal actualNeededWidth();

    /**
     * @return The actual needed height for the text box (regardless of requested minimal height)
     */
    qreal actualNeededHeight();

    /**
     * @details Updates the displayed data
     * @param block Data is updated from the Block object
     */
    void setData();

    /**
     * @param minWidth Setting a minimal requested width for the text box
     */
    void setMinWidth(qreal minWidth);



    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:

    // private functions
    void calculateDimensions();

    // storing status
    Block *_block;
    QRectF currentBoundingRect;
    bool isMouseHovered;
    qreal minWidth;
    qreal paddingH;
    qreal paddingV;
    qreal _actualNeededWidth;
    qreal _actaulNeededHeight;
    QFont fontInstanceName;
    QFont fontTypeName;
    QFont fontId;
    QColor bgColor;

    // instance name
    QString textInstanceName;
    qreal xInstanceName;
    qreal yInstanceName;

    // type name
    QString textTypeName;
    qreal xTypeName;
    qreal yTypeName;

    // id
    QString textIds;
    qreal xIds;
    qreal yIds;

};

} // namespace bd

#endif // GRAPHICITEMBLOCKHEADER_H
