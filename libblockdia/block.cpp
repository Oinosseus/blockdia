#include "block.h"
#include <QDebug>

bd::Block::Block(QObject *parent) : QObject(parent)
{
    // set default params
    this->_TypeId       = "";
    this->_TypeName     = "";
    this->_InstanceId   = "";
    this->_InstanceName = "";
    this->_Color        = QColor("#fff");
}



QString bd::Block::typeId()
{
    return this->_TypeId;
}

void bd::Block::setTypeId(const QString &id)
{
    if (id != this->_TypeId) {
        this->_TypeId = id;
        emit signalSomethingChanged();
    }
}

QString bd::Block::typeName()
{
    return this->_TypeName;
}

void bd::Block::setTypeName(const QString &name)
{
    if (name != this->_TypeName) {
        this->_TypeName = name;
        emit signalSomethingChanged();
    }
}


QString bd::Block::instanceId()
{
    return this->_InstanceId;
}

void bd::Block::setInstanceId(const QString &id)
{
    if (id != this->_InstanceId) {
        this->_InstanceId = id;
        emit signalSomethingChanged();
    }
}

QString bd::Block::instanceName()
{
    return this->_InstanceName;
}

void bd::Block::setInstanceName(const QString &name)
{
    if (name != this->_InstanceName) {
        this->_InstanceName = name;
        emit signalSomethingChanged();
    }
}

QColor bd::Block::color()
{
    return this->_Color;
}

void bd::Block::setColor(QColor color)
{
    this->_Color = color;
}

void bd::Block::addConstraint(Constraint *cnstrnt)
{
    this->constraintsList.append(cnstrnt);
}

QList<bd::Constraint *> bd::Block::getConstraints()
{
    return this->constraintsList;
}

bd::Constraint *bd::Block::getConstraint(const QString name)
{
    Constraint *ret = NULL;

    // find constraint by name
    for (int i = 0; i < this->constraintsList.size(); ++i) {
        if (this->constraintsList.at(i)->name() == name) {
            ret = this->constraintsList.at(i);
            break;
        }
    }

    return ret;
}
