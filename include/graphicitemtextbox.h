#ifndef GRAPHICITEMTEXTBOX_H
#define GRAPHICITEMTEXTBOX_H

#include "libglobals.h"

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>

#include <parameter.h>


namespace libblockdia {

/**
 * @brief A rectangle containing a text inside.
 */
class LIBBLOCKDIASHARED_EXPORT GraphicItemTextBox : public QGraphicsItem
{
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
    QRectF boundingRect() const;

    /**
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @param text Setting a new text for the graphics item
     * @param align The text alignement
     */
    void setText(const QString &text, Align align = Align::Center);

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
    void setMinWidth(qreal minWidth);

    /**
     * @param bgColor Setting a new background color
     */
    void setBgColor(QColor bgColor);



private:
    void calculateDimensions();

    QColor bgColor;
    QString text;
    QFont font;
    int padding;
    Align algn;
    QRectF currentBoundingRect;
    qreal textWidth;
    qreal textHeight;
    qreal minWidth;
};

} // namespace bd

#endif // GRAPHICITEMTEXTBOX_H
