#include "block.h"
#include <QDebug>

libblockdia::Block::Block(QObject *parent) : QObject(parent)
{
    // set default params
    this->_TypeId       = "";
    this->_TypeName     = "";
    this->_InstanceId   = "";
    this->_InstanceName = "";
    this->_Color        = QColor("#fff");
    this->giBlock       = new GraphicItemBlock(this);
    connect(this, SIGNAL(signalSomethingChanged()), this, SLOT(slotSomethingChanged()));
}



QString libblockdia::Block::typeId()
{
    return this->_TypeId;
}

void libblockdia::Block::setTypeId(const QString &id)
{
    if (id != this->_TypeId) {
        this->_TypeId = id;
        emit signalSomethingChanged();
    }
}

QString libblockdia::Block::typeName()
{
    return this->_TypeName;
}

void libblockdia::Block::setTypeName(const QString &name)
{
    if (name != this->_TypeName) {
        this->_TypeName = name;
        emit signalSomethingChanged();
    }
}


QString libblockdia::Block::instanceId()
{
    return this->_InstanceId;
}

void libblockdia::Block::setInstanceId(const QString &id)
{
    if (id != this->_InstanceId) {
        this->_InstanceId = id;
        emit signalSomethingChanged();
    }
}

QString libblockdia::Block::instanceName()
{
    return this->_InstanceName;
}

void libblockdia::Block::setInstanceName(const QString &name)
{
    if (name != this->_InstanceName) {
        this->_InstanceName = name;
        emit signalSomethingChanged();
    }
}

QColor libblockdia::Block::color()
{
    return this->_Color;
}

void libblockdia::Block::setColor(QColor color)
{
    this->_Color = color;
}

QList<libblockdia::Parameter *> libblockdia::Block::getParameters()
{
    return this->parametersList;
}

libblockdia::Parameter *libblockdia::Block::getParameter(const QString name)
{
    Parameter *ret = NULL;

    // find parameter by name
    for (int i = 0; i < this->parametersList.size(); ++i) {
        if (this->parametersList.at(i)->name() == name) {
            ret = this->parametersList.at(i);
            break;
        }
    }

    return ret;
}

QList<libblockdia::Input *> libblockdia::Block::getInputs()
{
    return this->inputsList;
}

libblockdia::Input *libblockdia::Block::getInput(const QString name)
{
    Input *ret = NULL;

    // find input by name
    for (int i = 0; i < this->inputsList.size(); ++i) {
        if (this->inputsList.at(i)->name() == name) {
            ret = this->inputsList.at(i);
            break;
        }
    }

    return ret;
}

QList<libblockdia::Output *> libblockdia::Block::getOutputs()
{
    return this->outputsList;
}

libblockdia::Output *libblockdia::Block::getOutput(const QString name)
{
    Output *ret = NULL;

    // find input by name
    for (int i = 0; i < this->outputsList.size(); ++i) {
        if (this->outputsList.at(i)->name() == name) {
            ret = this->outputsList.at(i);
            break;
        }
    }

    return ret;
}

QGraphicsItem *libblockdia::Block::getGraphicsItem()
{
    return this->giBlock;
}

void libblockdia::Block::slotSomethingChanged()
{
    this->giBlock->updateData();
}

