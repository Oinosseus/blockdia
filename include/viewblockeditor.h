#ifndef BDVIEWBLOCKEDITOR_H
#define BDVIEWBLOCKEDITOR_H

#include "libblockdia.h"
#include "block.h"

#include <QObject>
#include <QGraphicsView>

namespace bd {

class LIBBLOCKDIASHARED_EXPORT ViewBlockEditor : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewBlockEditor(Block *block, QWidget *parent = 0);

signals:

public slots:

private:
    Block *block;
};

} // namespace bd

#endif // BDVIEWBLOCKEDITOR_H
