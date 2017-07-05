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
    QString name();
    void setName(QString name);
    QString strValue();

signals:

public slots:

private:
    QString _Name;
};

#endif // BDCONSTRAINTBASE_H
