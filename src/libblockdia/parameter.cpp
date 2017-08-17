#include "parameter.h"

#include <QDebug>
#include "parameterint.h"
#include "parameterstr.h"

libblockdia::Parameter::Parameter(const QString &name, QObject *parent) : QObject(parent)
{
    this->_name = name;
    this->_isPublic = false;
}

QString libblockdia::Parameter::name()
{
    return this->_name;
}

void libblockdia::Parameter::setName(QString name)
{
    bool emitSignal = this->_name != name;
    this->_name = name;
    if (emitSignal) emit somethingHasChanged();
}

bool libblockdia::Parameter::isPublic()
{
    return this->_isPublic;
}

void libblockdia::Parameter::setPublic(bool isPublic)
{
    bool emitSignal = this->_isPublic != isPublic;
    this->_isPublic = isPublic;
    if (emitSignal) emit somethingHasChanged();
}

libblockdia::Parameter *libblockdia::Parameter::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Parameter *param = Q_NULLPTR;
    QString tagName = xml->name().toString().toLower();

    // ParamterInt
    if (tagName == "parameterint") {
        param = ParameterInt::parseBlockDef(xml, parent);
    }

    // ParamterStr
    if (tagName == "parameterstr") {
        param = ParameterStr::parseBlockDef(xml, parent);
    }

    // unknown type
    else {
        xml->skipCurrentElement();
    }

    return param;
}
