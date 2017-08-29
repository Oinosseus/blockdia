#include "blockinput.h"
#include <QDebug>

libblockdia::BlockInput::BlockInput(const QString &name, QObject *parent) : QObject(parent)
{
    this->_name = name;
}

QString libblockdia::BlockInput::name()
{
    return this->_name;
}

void libblockdia::BlockInput::setName(QString name)
{
    if (this->_name != name) {
        this->_name = name;
        emit somethingHasChanged();
    }
}

void libblockdia::BlockInput::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "Inputs");

    while (xml->readNextStartElement()) {

        if (xml->name() == "Input") {
            QString name = "";
            QXmlStreamAttributes attr = xml->attributes();
            if (attr.hasAttribute("name")) name = attr.value("name").toString().trimmed();
            new BlockInput(name, parent);
        }

        xml->skipCurrentElement();
    }
}

bool libblockdia::BlockInput::exportBlockDef(QXmlStreamWriter *xml)
{
    xml->writeStartElement("Input");
    xml->writeAttribute("name", this->name());
    xml->writeEndElement();
    return xml->hasError();
}
