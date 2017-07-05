#ifndef BDBLOCK_H
#define BDBLOCK_H

#include <QObject>
#include <QString>
#include <QList>
#include <QColor>
#include <bdconstraint.h>

#include "libblockdia_global.h"

class LIBBLOCKDIASHARED_EXPORT BDBlock : public QObject
{
    Q_OBJECT
public:
    explicit BDBlock(QObject *parent = 0);


    // ------------------------------------------------------------------------
    //                                Properties
    // ------------------------------------------------------------------------

    QString typeId();
    void setTypeId(const QString &id);

    QString typeName();
    void setTypeName(const QString &name);

    QString instanceId();
    void setInstanceId(const QString &id);

    QString instanceName();
    void setInstanceName(const QString &name);

    QColor color();
    void setColor(QColor color);



    // ------------------------------------------------------------------------
    //                                   Methods
    // ------------------------------------------------------------------------

    void addConstraint(BDConstraint *cnstrnt);
    BDConstraint *getConstraint(const QString name);



signals:
    void signalSomethingChanged();

public slots:

private:
    QString _TypeId;
    QString _TypeName;
    QString _InstanceId;
    QString _InstanceName;
    QColor  _Color;
    QList<BDConstraint *> constraintsList;
};

#endif // BDBLOCK_H
