#include "input.h"

bd::Input::Input(Block *block) : QObject(block)
{
    this->parent = block;
    this->_name = "";
}

QString bd::Input::name()
{
    return this->_name;
}

void bd::Input::setName(QString name)
{
    if (this->_name != name) {
        this->_name = name;
        emit somethingHasChanged();
    }
}
