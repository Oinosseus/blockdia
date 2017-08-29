#include "blockparameter.h"

#include <QDebug>
#include "blockparameterint.h"
#include "blockparameterstr.h"
#include "blockparameterenum.h"

libblockdia::BlockParameter::BlockParameter(const QString &name, QObject *parent) : QObject(parent)
{
    this->_name = name;
    this->_isPublic = false;
}

QString libblockdia::BlockParameter::name()
{
    return this->_name;
}

void libblockdia::BlockParameter::setName(QString name)
{
    bool emitSignal = this->_name != name;
    this->_name = name;
    if (emitSignal) emit somethingHasChanged();
}

bool libblockdia::BlockParameter::isPublic()
{
    return this->_isPublic;
}

void libblockdia::BlockParameter::setPublic(bool isPublic)
{
    bool emitSignal = this->_isPublic != isPublic;
    this->_isPublic = isPublic;
    if (emitSignal) emit somethingHasChanged();
}

void libblockdia::BlockParameter::importBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "Parameters");

    while (xml->readNextStartElement()) {

        QXmlStreamAttributes attr = xml->attributes();

        if (attr.hasAttribute("type")) {

            BlockParameter *param = Q_NULLPTR;
            QString type = attr.value("type").toString().trimmed();
            QString name = (attr.hasAttribute("name")) ? attr.value("name").toString() : "";

            // create parameter
            if (type == "int") {
                param = new BlockParameterInt(name, parent);
                param->importParamDef(xml);
            } else if (type == "enum") {
                param = new BlockParameterEnum(name, parent);
                param->importParamDef(xml);
            } else if (type == "str") {
                param = new BlockParameterStr(name, parent);
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

bool libblockdia::BlockParameter::exportBlockDef(QXmlStreamWriter *xml)
{
    // begin parameter export
    xml->writeStartElement("Parameter");

    // type attribute
    QString classname = this->metaObject()->className();
    if (classname == "libblockdia::BlockParameterInt") {
        xml->writeAttribute("type", "int");
    } else if (classname == "libblockdia::BlockParameterStr") {
        xml->writeAttribute("type", "str");
    } else if (classname == "libblockdia::BlockParameterEnum") {
        xml->writeAttribute("type", "enum");
    }

    // standard attributes
    xml->writeAttribute("name", this->name());
    if (this->isPublic()) xml->writeAttribute("isPublic", "yes");
    xml->writeAttribute("default", this->strDefaultValue());

    // export parameter specific data
    this->exportParamDef(xml);

    // finish the parameter export
    xml->writeEndElement();
    return xml->hasError();
}
