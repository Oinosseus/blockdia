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
#include <graphicitemblockheader.h>
#include <graphicitemtextbox.h>

namespace bd {

class LIBBLOCKDIASHARED_EXPORT GraphicItemBlock : public QGraphicsItem
{
public:
    explicit GraphicItemBlock(Block *block, QGraphicsItem *parent=Q_NULLPTR);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QColor backgroundParameter = QColor("#ffd");
    QColor backgroundInputs     = QColor("#fdd");
    QColor backgroundOutputs    = QColor("#ddf");
    void updateBlockData();

private:
    Block *block;
    QRectF currentBoundingRect;
    GraphicItemBlockHeader *giBlockHead;
    QList<GraphicItemTextBox *> giParamsPrivate;
    QList<GraphicItemTextBox *> giInputs;
    QList<GraphicItemTextBox *> giOutputs;
    QList<GraphicItemTextBox *> giParamsPublic;
};

} // namespace bd

#endif // BDGRAPHICSITEMBLOCK_H
