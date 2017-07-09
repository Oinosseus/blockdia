#include "input.h"

bd::Input::Input(Block *block, const QString &name) : QObject(block)
{
    this->parent = block;
    this->_name = name;

    // add this input to the inputs list of the block
    this->parent->inputsList.append(this);
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
