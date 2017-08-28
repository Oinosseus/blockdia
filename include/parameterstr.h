#ifndef BDPARAMETERSTR_H
#define BDPARAMETERSTR_H

#include "libglobals.h"
#include <parameter.h>

namespace libblockdia {

/**
 * @brief A string parameter.
 */
class LIBBLOCKDIASHARED_EXPORT ParameterStr : public Parameter
{
    Q_OBJECT

public:

    /**
     * @details Constructing a parameter
     * @param parent The block this parameter belogns to.
     * @param name The name for the parameter
     */
    ParameterStr(const QString &name, QObject *parent = 0);

    /**
     * @return The default value as string representation
     */
    virtual QString strDefaultValue();

    /**
     * @param value Setting the default value from a string
     * @return False if the value could not be set
     */
    virtual bool setDefaultValue(QString value);

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
     * @details Parsing a XML stram for parameter definition.
     * @param xml The current xml parser
     * @return True if parsing was successful
     */
    bool importParamDef(QXmlStreamReader *xml);

    /**
     * @details Exporting to an xml stream
     * @param xml The current xml writer
     * @return True on success
     */
    bool exportParamDef(QXmlStreamWriter *xml);


private:
    QString _value;
    QString _defaultValue;

};

} // namespace bd

#endif // BDPARAMETERSTR_H
