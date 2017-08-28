#include "parameter.h"

#include <QDebug>
#include "parameterint.h"
#include "parameterstr.h"
#include "parameterenum.h"

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

        QXmlStreamAttributes attr = xml->attributes();

        if (attr.hasAttribute("type")) {

            Parameter *param = Q_NULLPTR;
            QString type = attr.value("type").toString().trimmed();
            QString name = (attr.hasAttribute("name")) ? attr.value("name").toString() : "";

            // create parameter
            if (type == "int") {
                param = new ParameterInt(name, parent);
                param->importParamDef(xml);
            } else if (type == "enum") {
                param = new ParameterEnum(name, parent);
                param->importParamDef(xml);
            } else if (type == "str") {
                param = new ParameterStr(name, parent);
                param->importParamDef(xml);
            } else {
                qWarning() << "ERROR Parsing XML: unknown parameter type (at line" << xml->lineNumber() << ")";
                xml->skipCurrentElement();
            }

            // set values for parameter
            if (param) {
                // public
                if (attr.hasAttribute("isPublic")) {
                     QString v = attr.value("isPublic").toString().trimmed().toLower();
                     param->setPublic(v == "yes" || v == "true" || v == "1");
                }

                 // default
                if (attr.hasAttribute("default")) {
                     QString v = attr.value("default").toString().trimmed();
                     param->setDefaultValue(v);
                }
            }
        }
    }
}
