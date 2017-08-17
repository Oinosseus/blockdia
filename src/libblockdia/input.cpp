#include "input.h"
#include <QDebug>

libblockdia::Input::Input(const QString &name, QObject *parent) : QObject(parent)
{
    this->_name = name;
}

QString libblockdia::Input::name()
{
    return this->_name;
}

void libblockdia::Input::setName(QString name)
{
    if (this->_name != name) {
        this->_name = name;
        emit somethingHasChanged();
    }
}

void libblockdia::Input::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "Inputs");

    while (xml->readNextStartElement()) {

        if (xml->name() == "Input") {
            QString name = "";
            QXmlStreamAttributes attr = xml->attributes();
            if (attr.hasAttribute("name")) name = attr.value("name").toString().trimmed();
            new Input(name, parent);
        }

        xml->skipCurrentElement();
    }
}
