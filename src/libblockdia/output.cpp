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

libblockdia::Output *libblockdia::Output::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    Output *outp = Q_NULLPTR;

    // check for correct start tag
    if (xml->name().toString().toLower() == "output") {

        // check for name attribute
        QString name = "";
        QXmlStreamAttributes attr = xml->attributes();
        if (attr.hasAttribute("name")) name = attr.value("name").toString().trimmed();

        // create new input
        outp = new Output(name, parent);
    }

    // finish parsing current element
    xml->skipCurrentElement();

    return outp;
}
