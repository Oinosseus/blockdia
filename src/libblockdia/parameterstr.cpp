#include "parameterstr.h"

libblockdia::ParameterStr::ParameterStr(const QString &name, QObject *parent) : Parameter(name, parent)
{
    this->_value = "";
    this->_defaultValue = "";
}

QString libblockdia::ParameterStr::strDefaultValue()
{
    return this->_defaultValue;
}

bool libblockdia::ParameterStr::setDefaultValue(QString value)
{
    this->_defaultValue = value;
    return true;
}

bool libblockdia::ParameterStr::setValue(QString value)
{
    this->_value = value;
    return true;
}

QString libblockdia::ParameterStr::strValue()
{
    return this->_value;
}

QString libblockdia::ParameterStr::allowedValues()
{
    return QString("arbitrary string");
}

libblockdia::ParameterStr *libblockdia::ParameterStr::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    ParameterStr *param = new ParameterStr(xml->attributes().value("name").toString(), parent);
    xml->skipCurrentElement();
    return param;
}

bool libblockdia::ParameterStr::exportBlockDef(QXmlStreamWriter *xml)
{
    xml->writeStartElement("ParameterStr");

    // parameter attributes
    xml->writeAttribute("name", this->name());
    if (this->isPublic()) xml->writeAttribute("isPublic", "true");
    xml->writeAttribute("default", this->strDefaultValue());

    xml->writeEndElement();
    return xml->hasError();
}
