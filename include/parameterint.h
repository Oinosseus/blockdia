#ifndef BDPARAMETERINT_H
#define BDPARAMETERINT_H

#include "libglobals.h"
#include <parameter.h>

namespace libblockdia {

/**
 * @brief An integer parameter.
 * Integer parameters have an minimum and maximum allowed value.
 */
class LIBBLOCKDIASHARED_EXPORT ParameterInt : public Parameter
{
public:

    /**
     * @brief Constructing a parameter
     * @param parent The block this parameter belogns to.
     * @param name The name for the parameter
     */
    ParameterInt(const QString &name, QObject *parent = 0);

    /**
     * @brief The minimum allowed parameter value
     * By default the minimum is set to INT_MIN
     * @return The minimum allowed parameter value
     */
    int minimum();

    /**
     * @brief Setting the minim allowed parameter value
     * @param min The new minim parameter value
     */
    void setMinimum(int min);

    /**
     * @brief The maximum allowed parameter value
     * By default the maximum is set to INT_MAX
     * @return The maximum allowed parameter value
     */
    int maximum();

    /**
     * @brief Setting the maximum allowed parameter value
     * @param min The new maximum parameter value
     */
    void setMaximum(int max);

    /**
     * @brief The current parameter value
     * @return The current parameter value
     */
    int value();

    /**
     * @brief Setting a new value for this parameter.
     * The value will be clipped to the range defined by
     * minimum and maximum.
     * In case of clipping false is returned
     * @param value The new value
     * @return False if the new value could not be set aexactely.
     */
    virtual bool setValue(int value);

    /**
     * @brief Setting a new value from a string.
     * The string is interpreted as integer value.
     * @param value The new integer value as a string.
     * @return False if the new value could not be set aexactely.
     */
    virtual bool setValue(QString value);

    /**
     * @brief The current value as a QString.
     * @return The current value as a QString
     */
    QString strValue();

    /**
     * @brief An information about the allowed value range.
     * @return An information about the allowed values range.
     */
    QString allowedValues();


private:
    int _minimum;
    int _maximum;
    int _value;

};

} // namespace bd

#endif // BDPARAMETERINT_H
