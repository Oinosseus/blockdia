#include "blockparameterstr.h"
#include <QDebug>

libblockdia::BlockParameterStr::BlockParameterStr(const QString &name, QObject *parent) : BlockParameter(name, parent)
{
    this->_value = "";
    this->_defaultValue = "";
}

QString libblockdia::BlockParameterStr::strDefaultValue()
{
    return this->_defaultValue;
}

bool libblockdia::BlockParameterStr::setDefaultValue(QString value)
{
    this->_defaultValue = value;
    return true;
}

bool libblockdia::BlockParameterStr::setValue(QString value)
{
    this->_value = value;
    return true;
}

QString libblockdia::BlockParameterStr::strValue()
{
    return this->_value;
}

QString libblockdia::BlockParameterStr::allowedValues()
{
    return QString("arbitrary string");
}

bool libblockdia::BlockParameterStr::importParamDef(QXmlStreamReader *xml)
{
    xml->skipCurrentElement();
    return xml->hasError();
}

bool libblockdia::BlockParameterStr::exportParamDef(QXmlStreamWriter *xml)
{
    return xml->hasError();
}
