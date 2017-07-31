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

// forward declarations
//class GraphicItemTextBox;

/**
 * @brief A QGraphicsItem that shows the header of a Block
 */
class LIBBLOCKDIASHARED_EXPORT GraphicItemBlockHeader : public GraphicItemTextBox
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
     * @details Updates the displayed data
     */
    void updateData();

    /**
     * @param minWidth Setting a minimal requested width for the text box
     */
    void setMinWidth(qreal minWidth);


private:

    // private functions
    void calculateDimensions();

    // storing status
    Block *_block;
    QRectF currentBoundingRect;
    qreal minWidth;
    qreal paddingH;
    qreal paddingV;
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
