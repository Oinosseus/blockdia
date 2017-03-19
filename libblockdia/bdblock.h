#ifndef BDBLOCK_H
#define BDBLOCK_H

#include <QObject>
#include "libblockdia_global.h"

/**
 * @brief The BDBlock class
 *
 * It defines the central API for blocks.
 * Blocks have properties
 * It is possible to connect blocks together by inputs and outputs.
 */
class LIBBLOCKDIASHARED_EXPORT BDBlock : public QObject
{
    Q_OBJECT
public:
    explicit BDBlock(QObject *parent = 0);

signals:

public slots:
};

#endif // BDBLOCK_H
