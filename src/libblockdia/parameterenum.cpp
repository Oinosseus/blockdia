#include "parameterenum.h"
#include <limits.h>

libblockdia::ParameterEnum::ParameterEnum(const QString &name, QObject *parent) : Parameter(name, parent)
{
    this->_value = "";
    this->_defaultValue = this->_value;
}

QString libblockdia::ParameterEnum::strDefaultValue()
{
    return this->_defaultValue;
}

bool libblockdia::ParameterEnum::setDefaultValue(QString value)
{
    if (this->_enumItems.contains(value)) {
        this->_defaultValue = value;
        return true;
    } else {
        return false;
    }
}

bool libblockdia::ParameterEnum::setValue(QString value)
{
    if (this->_enumItems.contains(value)) {
        this->_value= value;
        return true;
    } else {
        return false;
    }
}

QString libblockdia::ParameterEnum::strValue()
{
    return this->_value;
}

QString libblockdia::ParameterEnum::allowedValues()
{
    QString values = "";
    for (int i=0; i < this->_enumItems.size(); ++i) {
        if (values.length() > 0) values+= ", ";
        values += this->_enumItems.at(i);
    }

    return values;
}

libblockdia::ParameterEnum *libblockdia::ParameterEnum::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    // ctreate parameter
    ParameterEnum *param = new ParameterEnum(xml->attributes().value("name").toString(), parent);

    while (xml->readNextStartElement()) {
        xml->skipCurrentElement();
    }

    return param;
}
