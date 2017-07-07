#include "output.h"

bd::Output::Output(Block *block) : QObject(block)
{
    this->parent = block;
    this->_name = "";

    // add this output to the outputs list of the block
    this->parent->outputsList.append(this);
}

QString bd::Output::name()
{
    return this->_name;
}

void bd::Output::setName(QString name)
{
    if (this->_name != name) {
        this->_name = name;
        emit somethingHasChanged();
    }
}
