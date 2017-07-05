#ifndef BDCONSTRAINTBASE_H
#define BDCONSTRAINTBASE_H

#include <QObject>
#include <QString>

#include "libblockdia_global.h"

class LIBBLOCKDIASHARED_EXPORT BDConstraint : public QObject
{
    Q_OBJECT
public:
    explicit BDConstraint(QObject *parent = 0);
    QString Name;

signals:

public slots:
};

#endif // BDCONSTRAINTBASE_H
