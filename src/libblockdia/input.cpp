#include "input.h"

libblockdia::Input::Input(Block *block, const QString &name) : QObject(block)
{
    this->parent = block;
    this->_name = name;

    // add this input to the inputs list of the block
    this->parent->inputsList.append(this);
    emit this->parent->signalSomethingChanged();
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
