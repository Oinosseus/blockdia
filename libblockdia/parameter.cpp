#include "parameter.h"

bd::Parameter::Parameter(QObject *parent) : QObject(parent)
{
    this->_name = "";
    this->_isPublic = false;
}

QString bd::Parameter::name()
{
    return this->_name;
}

void bd::Parameter::setName(QString name)
{
    bool emitSignal = this->_name != name;
    this->_name = name;
    if (emitSignal) emit somethingHasChanged();
}

bool bd::Parameter::isPublic()
{
    return this->_isPublic;
}

void bd::Parameter::setPublic(bool isPublic)
{
    bool emitSignal = this->_isPublic == isPublic;
    this->_isPublic = isPublic;
    if (emitSignal) emit somethingHasChanged();
}
