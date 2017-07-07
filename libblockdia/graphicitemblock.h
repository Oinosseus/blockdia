#ifndef BDGRAPHICSITEMBLOCK_H
#define BDGRAPHICSITEMBLOCK_H

#include "libblockdia.h"

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsRectItem>
#include <QList>
#include <QString>
#include <block.h>

namespace bd {

class LIBBLOCKDIASHARED_EXPORT GraphicItemBlock : public QGraphicsItem
{
public:
    explicit GraphicItemBlock(Block *block);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QColor backgroundConstraint = QColor("#ffd");

private:
    Block *block;
    QRectF currentBoundingRect;
};

} // namespace bd

#endif // BDGRAPHICSITEMBLOCK_H
