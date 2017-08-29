#include "blockoutput.h"

libblockdia::BlockOutput::BlockOutput(const QString &name, QObject *parent) : QObject(parent)
{
    this->_name = name;
}

QString libblockdia::BlockOutput::name()
{
    return this->_name;
}

void libblockdia::BlockOutput::setName(QString name)
{
    if (this->_name != name) {
        this->_name = name;
        emit somethingHasChanged();
    }
}

void libblockdia::BlockOutput::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "Outputs");

    while (xml->readNextStartElement()) {

        if (xml->name() == "Output") {
            QString name = "";
            QXmlStreamAttributes attr = xml->attributes();
            if (attr.hasAttribute("name")) name = attr.value("name").toString().trimmed();
            new BlockOutput(name, parent);
       }

       xml->skipCurrentElement();
    }
}

bool libblockdia::BlockOutput::exportBlockDef(QXmlStreamWriter *xml)
{
    xml->writeStartElement("Output");
    xml->writeAttribute("name", this->name());
    xml->writeEndElement();
    return xml->hasError();
}
