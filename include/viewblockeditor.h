#ifndef BDVIEWBLOCKEDITOR_H
#define BDVIEWBLOCKEDITOR_H

#include "libglobals.h"
#include "block.h"

#include <QObject>
#include <QGraphicsView>

namespace libblockdia {

class LIBBLOCKDIASHARED_EXPORT ViewBlockEditor : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewBlockEditor(Block *block, QWidget *parent = 0);
    Block *block();


signals:

public slots:

private:
    Block *_block;
    QGraphicsItem *giTest;
    int testCounter;
};

} // namespace bd

#endif // BDVIEWBLOCKEDITOR_H
