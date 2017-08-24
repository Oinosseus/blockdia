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
    Q_OBJECT

public:

    /**
     * @details Constructing a parameter
     * @param parent The block this parameter belogns to.
     * @param name The name for the parameter
     */
    ParameterInt(const QString &name, QObject *parent = 0);

    /**
     * @details The minimum allowed parameter value
     * By default the minimum is set to INT_MIN
     * @return The minimum allowed parameter value
     */
    int minimum();

    /**
     * @details Setting the minim allowed parameter value
     * @param min The new minim parameter value
     */
    void setMinimum(int min);

    /**
     * @details The maximum allowed parameter value
     * By default the maximum is set to INT_MAX
     * @return The maximum allowed parameter value
     */
    int maximum();

    /**
     * @param min Setting a new maximum allowed parameter value
     */
    void setMaximum(int max);

    /**
     * @return The current parameter value
     */
    int value();

    /**
     * @return The default value as string representation
     */
    virtual QString strDefaultValue();

    /**
     * @return The default value
     */
    virtual int defaultValue();

    /**
     * @param value Setting the default value from a string
     * @return False if the value could not be set
     */
    virtual bool setDefaultValue(QString value);

    /**
     * @param value Setting the default value
     * @return False if the value could not be set
     */
    virtual bool setDefaultValue(int value);

    /**
     * @details Setting a new value for this parameter.
     * The value will be clipped to the range defined by
     * minimum and maximum.
     * In case of clipping false is returned
     * @param value The new value
     * @return False if the new value could not be set aexactely.
     */
    virtual bool setValue(int value);

    /**
     * @details Setting a new value from a string.
     * The string is interpreted as integer value.
     * @param value The new integer value as a string.
     * @return False if the new value could not be set aexactely.
     */
    virtual bool setValue(QString value);

    /**
     * @return The current value as a QString
     */
    QString strValue();

    /**
     * @return An information about the allowed values range.
     */
    QString allowedValues();

    /**
     * @details Parsing a XML stram for an parameter
     * The XML stream is parsed from the current element for an parameter definition.
     * In every case the XML parser is set to after the current element (parent or next child).
     * @param xml The current xml parser
     * @param parent The parent Block object
     * @return A new defined Output object or Q_NULLPTR
     */
    static ParameterInt *parseBlockDef(QXmlStreamReader *xml, QObject *parent);

    /**
     * @details Exporting to an xml stream
     * @param xml The current xml writer
     * @return True on success
     */
    bool exportBlockDef(QXmlStreamWriter *xml);

private:
    int _minimum;
    int _maximum;
    int _value;
    int _defaultValue;

};

} // namespace bd

#endif // BDPARAMETERINT_H
