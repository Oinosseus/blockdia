#include "parameter.h"

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
