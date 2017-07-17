#include "parameter.h"

bd::Parameter::Parameter(Block *parent, const QString &name) : QObject(parent)
{
    this->parent = parent;
    this->_name = name;
    this->_isPublic = false;

    // add parameter to block
    this->parent->parametersList.append(this);
    emit this->parent->signalSomethingChanged();
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
