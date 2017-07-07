#ifndef BDCONSTRAINTBASE_H
#define BDCONSTRAINTBASE_H

#include <QObject>
#include <QString>

#include "libblockdia_global.h"

namespace bd {

/**
 * @brief Interface for Constraints and Paramerters.
 */
class LIBBLOCKDIASHARED_EXPORT Constraint : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Constructing a parameter or constraint
     * @param parent
     */
    explicit Constraint(QObject *parent = 0);
    QString name();
    void setName(QString name);

    virtual QString strValue();
//    virtual int intValue() = 0;
//    virtual QString allowedValues() = 0;

signals:

public slots:

private:
    QString _Name;
};

} // namespace bd

#endif // BDCONSTRAINTBASE_H
