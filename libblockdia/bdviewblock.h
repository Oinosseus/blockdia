#ifndef BDVIEWBLOCK_H
#define BDVIEWBLOCK_H

#include "libblockdia_global.h"

#include <QObject>
#include <QGraphicsView>

#include <bdblock.h>

class LIBBLOCKDIASHARED_EXPORT BDViewBlock : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BDViewBlock(QWidget *parent = 0);

signals:

public slots:
};

#endif // BDVIEWBLOCK_H
