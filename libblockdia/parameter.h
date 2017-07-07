#ifndef BDPARAMETER_H
#define BDPARAMETER_H

#include <QObject>
#include <QString>

#include "libblockdia_global.h"

namespace bd {

/**
 * @brief Common base class (interface) for paramerters.
 */
class LIBBLOCKDIASHARED_EXPORT Parameter : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Constructing a parameter
     * @param parent
     */
    explicit Parameter(QObject *parent = 0);

    /**
     * @brief The name of the parameter
     * It is recommended, that every parameter within
     * has a unique name within a certain block.
     * @return The name of the parameter.
     */
    QString name();

    /**
     * @brief Assigning a new name for the parameter.
     * @see Parameter::name()
     * @param name The new name
     */
    void setName(QString name);

    /**
     * @brief Parameters can be defined as public or private.
     * @return Parameters can be defined as public or private.
     */
    bool isPublic();

    /**
     * @brief Parameters can be defined as public or private.
     * @param isPublic Defines if this parameter is public.
     */
    void setPublic(bool isPublic);

    /**
     * @brief The current value as a QString.
     * @return The current value as a QString
     */
    virtual QString strValue() = 0;

    /**
     * @brief Setting a new value.
     * @param value The new value.
     * @return False if the value is outside the allowed range.
     */
    virtual bool setValue(QString value) = 0;

    /**
     * @brief An information about the allowed values for this parameter.
     * This is used as informational message.
     * For example enums can return a string that lists all available enum items,
     * or integers can return a string with the allowed range (min..max).
     * @return An information about the allowed values for this parameter.
     */
    virtual QString allowedValues() = 0;

signals:
    /**
     * @brief This signal is emitted whenever a value has changed.
     */
    void somethingHasChanged();

private:
    QString _name;
    bool _isPublic;
};

} // namespace bd

#endif // BDPARAMETER_H
