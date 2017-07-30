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
#include <QPair>
#include <QMenu>

#include <graphicitemblockheader.h>
#include <graphicitemtextbox.h>
#include <graphicitemparameter.h>
#include <graphiciteminput.h>
#include <graphicitemoutput.h>

namespace libblockdia {

// forward declarations
class GraphicItemBlockHeader;
class GraphicItemTextBox;
class GraphicItemParameter;
class GraphicItemInput;
class GraphicItemOutput;

class LIBBLOCKDIASHARED_EXPORT GraphicItemBlock : public QGraphicsItem
{
public:
    explicit GraphicItemBlock(Block *block, QGraphicsItem *parent=Q_NULLPTR);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void updateData();

private:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    Block *block;
    GraphicItemBlockHeader *giBlockHead;
    QList<GraphicItemParameter *> giParamsPrivate;
    QList<QPair<GraphicItemInput*, GraphicItemOutput*>> giInOuts;
    QList<GraphicItemParameter *> giParamsPublic;
    QRectF currentBoundingRect;
};

} // namespace bd

#endif // BDGRAPHICSITEMBLOCK_H
