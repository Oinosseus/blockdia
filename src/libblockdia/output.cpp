#include "output.h"

libblockdia::Output::Output(const QString &name, QObject *parent) : QObject(parent)
{
    this->_name = name;
}

QString libblockdia::Output::name()
{
    return this->_name;
}

void libblockdia::Output::setName(QString name)
{
    if (this->_name != name) {
        this->_name = name;
        emit somethingHasChanged();
    }
}

void libblockdia::Output::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "Outputs");

    while (xml->readNextStartElement()) {

        if (xml->name() == "Output") {
            QString name = "";
            QXmlStreamAttributes attr = xml->attributes();
            if (attr.hasAttribute("name")) name = attr.value("name").toString().trimmed();
            new Output(name, parent);
       }

        xml->skipCurrentElement();
    }
}

bool libblockdia::Output::exportBlockDef(QXmlStreamWriter *xml)
{
    xml->writeStartElement("Output");
    xml->writeAttribute("name", this->name());
    xml->writeEndElement();
    return xml->hasError();
}
