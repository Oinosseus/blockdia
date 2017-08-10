#include "input.h"

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

libblockdia::Input *libblockdia::Input::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Input *inp = Q_NULLPTR;

    // check for correct start tag
    if (xml->name().toString().toLower() == "input") {

        // check for name attribute
        QString name = "";
        QXmlStreamAttributes attr = xml->attributes();
        if (attr.hasAttribute("name")) name = attr.value("name").toString().trimmed();

        // create new input
        inp = new Input(name, parent);
    }

    // finish parsing current element
    xml->skipCurrentElement();

    return inp;
}
