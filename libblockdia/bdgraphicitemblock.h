#ifndef BDGRAPHICSITEMBLOCK_H
#define BDGRAPHICSITEMBLOCK_H

#include "libblockdia_global.h"

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
#include <bdblock.h>

class LIBBLOCKDIASHARED_EXPORT BDGraphicItemBlock : public QGraphicsItem
{
public:
    explicit BDGraphicItemBlock(BDBlock *block);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void updateBlockInfos();

private:
    BDBlock *block;
    QString instanceName;
    QString typeName;
    QString tiId;
    QRectF  currentBoundingRect;
};

#endif // BDGRAPHICSITEMBLOCK_H
