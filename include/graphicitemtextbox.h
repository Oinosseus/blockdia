#ifndef GRAPHICITEMTEXTBOX_H
#define GRAPHICITEMTEXTBOX_H

#include "libglobals.h"

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>

namespace libblockdia {

/**
 * @brief A rectangle containing a text inside.
 */
class LIBBLOCKDIASHARED_EXPORT GraphicItemTextBox : public QGraphicsItem
{
    friend class GraphicItemBlockHeader;

public:

    /**
     * @brief Text alignement within the rectable.
     */
    enum struct Align {Center, Left, Right};

    /**
     * @param parent The QGraphicsItem parent object.
     */
    GraphicItemTextBox(QGraphicsItem *parent=0);

    /**
     * @return The current bounding rect of the QGraphicsItem
     */
    virtual QRectF boundingRect() const;

    /**
     * @param painter
     * @param option
     * @param widget
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @param text Setting a new text for the graphics item
     * @param align The text alignement
     */
    virtual void updateData(const QString &text, Align align = Align::Center);

    /**
     * @return The actual needed width for the text box (regardless of requested minimal width)
     */
    qreal actualNeededWidth();

    /**
     * @return The actual needed height for the text box (regardless of requested minimal height)
     */
    qreal actualNeededHeight();

    /**
     * @param minWidth Setting a minimal requested width for the text box
     */
    virtual void setMinWidth(qreal minWidth);

    /**
     * @param bgColor Setting a new background color
     */
    void setBgColor(QColor bgColor);

    /**
     * @return True if the item is currently hovered by mouse
     */
    bool isMouseHovered();




private:
    void calculateDimensions();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    QColor bgColor;
    QString text;
    QFont font;
    int padding;
    Align algn;
    QRectF currentBoundingRect;
    qreal _actualNeededWidth;
    qreal _actaulNeededHeight;
    qreal minWidth;
    bool _isMouseHovered;
};

} // namespace bd

#endif // GRAPHICITEMTEXTBOX_H
