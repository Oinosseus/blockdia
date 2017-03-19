#ifndef BDVIEWBLOCK_H
#define BDVIEWBLOCK_H

#include <QObject>
#include <QWidget>
#include "libblockdia_global.h"

class LIBBLOCKDIASHARED_EXPORT BDViewBlock : public QWidget
{
    Q_OBJECT
public:
    explicit BDViewBlock(QWidget *parent = 0);

signals:

public slots:
};

#endif // BDVIEWBLOCK_H
