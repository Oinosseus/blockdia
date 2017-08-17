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

void libblockdia::Parameter::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "Parameters");

    while (xml->readNextStartElement()) {

        Parameter *param = Q_NULLPTR;
        QXmlStreamAttributes atrr = xml->attributes();

       // create integer parameter
       if (xml->name() == "ParameterInt") {
           param = ParameterInt::parseBlockDef(xml, parent);
       }

       // create string parameter
       else if (xml->name() == "ParameterStr") {
           param = ParameterStr::parseBlockDef(xml, parent);
       }

       // unknown type
       else {
           xml->skipCurrentElement();
       }


       // set attribute
       if (param) {

           // public
           if (atrr.hasAttribute("isPublic")) {
                QString v = atrr.value("isPublic").toString().trimmed().toLower();
                param->setPublic(v == "yes" || v == "true" || v == "1");
           }

            // default
           if (atrr.hasAttribute("default")) {
                QString v = atrr.value("default").toString().trimmed().toLower();
                param->setDefaultValue(v);
           }
       }
    }
}
