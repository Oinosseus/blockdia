#ifndef BDGRAPHICSITEMBLOCK_H
#define BDGRAPHICSITEMBLOCK_H

#include "libglobals.h"

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

#include <graphicitemblockheader.h>
#include <graphicitemtextbox.h>

namespace libblockdia {

// forward declarations
class GraphicItemBlockHeader;
class GraphicItemTextBox;

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
    GraphicItemBlockHeader *giBlockHead;
    QList<GraphicItemTextBox *> giParamsPrivate;
    QList<GraphicItemTextBox *> giInputs;
    QList<GraphicItemTextBox *> giOutputs;
    QList<GraphicItemTextBox *> giParamsPublic;
    QRectF currentBoundingRect;
};

} // namespace bd

#endif // BDGRAPHICSITEMBLOCK_H
