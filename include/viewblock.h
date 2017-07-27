#ifndef BDVIEWBLOCK_H
#define BDVIEWBLOCK_H

#include "libglobals.h"

#include <QObject>
#include <QGraphicsView>

namespace libblockdia {

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
