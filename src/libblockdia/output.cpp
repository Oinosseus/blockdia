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
