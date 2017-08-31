#ifndef BDVIEWPROCESSEDITOR_H
#define BDVIEWPROCESSEDITOR_H

#include "libglobals.h"
#include "block.h"

#include <QObject>
#include <QGraphicsView>
#include <QWheelEvent>

namespace libblockdia {

class LIBBLOCKDIASHARED_EXPORT ViewProcessEditor : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewProcessEditor(QWidget *parent = 0);


signals:

public slots:

private:
    void wheelEvent(QWheelEvent *e);
};

} // namespace bd

#endif // BDVIEWPROCESSEDITOR_H
