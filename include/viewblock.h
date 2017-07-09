#ifndef BDVIEWBLOCK_H
#define BDVIEWBLOCK_H

#include "libblockdia.h"

#include <QObject>
#include <QGraphicsView>

#include <block.h>

namespace bd {

class LIBBLOCKDIASHARED_EXPORT ViewBlock : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewBlock(QWidget *parent = 0);

signals:

public slots:
};

} // namespace bd

#endif // BDVIEWBLOCK_H
