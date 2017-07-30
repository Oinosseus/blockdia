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
