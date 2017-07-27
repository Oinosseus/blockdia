#include "output.h"

libblockdia::Output::Output(Block *block, const QString &name) : QObject(block)
{
    this->parent = block;
    this->_name = name;

    // add this output to the outputs list of the block
    this->parent->outputsList.append(this);
    emit this->parent->signalSomethingChanged();
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
