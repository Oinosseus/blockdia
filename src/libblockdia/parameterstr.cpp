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
    QXmlStreamAttributes attr = xml->attributes();

    // ctreate parameter
    QString name = "";
    if (attr.hasAttribute("name")) name = attr.value("name").toString().trimmed();
    ParameterStr *param = new ParameterStr(name, parent);

    // check public
    if (attr.hasAttribute("isPublic")) {
        QString ispublic = attr.value("isPublic").toString().trimmed().toLower();
        param->setPublic(ispublic == "yes" || ispublic == "true" || ispublic == "1");
    }

    // read default
    if (attr.hasAttribute("default")) {
        QString def = attr.value("default").toString().trimmed();
        param->setDefaultValue(def);
    }

    // parse definitions
    xml->skipCurrentElement();

    return param;
}
