#include "bdblock.h"

BDBlock::BDBlock(QObject *parent) : QObject(parent)
{
    // set default params
    this->_TypeId       = "";
    this->_TypeName     = "";
    this->_InstanceId   = "";
    this->_InstanceName = "";
    this->_Color        = QColor("#fff");
}



QString BDBlock::typeId()
{
    return this->_TypeId;
}

void BDBlock::setTypeId(const QString &id)
{
    if (id != this->_TypeId) {
        this->_TypeId = id;
        emit signalSomethingChanged();
    }
}

QString BDBlock::typeName()
{
    return this->_TypeName;
}

void BDBlock::setTypeName(const QString &name)
{
    if (name != this->_TypeName) {
        this->_TypeName = name;
        emit signalSomethingChanged();
    }
}


QString BDBlock::instanceId()
{
    return this->_InstanceId;
}

void BDBlock::setInstanceId(const QString &id)
{
    if (id != this->_InstanceId) {
        this->_InstanceId = id;
        emit signalSomethingChanged();
    }
}

QString BDBlock::instanceName()
{
    return this->_InstanceName;
}

void BDBlock::setInstanceName(const QString &name)
{
    if (name != this->_InstanceName) {
        this->_InstanceName = name;
        emit signalSomethingChanged();
    }
}

QColor BDBlock::color()
{
    return this->_Color;
}

void BDBlock::setColor(QColor color)
{
    this->_Color = color;
}

void BDBlock::addConstraint(BDConstraint *cnstrnt)
{
    this->constraintsList.append(cnstrnt);
}

QList<BDConstraint *> BDBlock::getConstraints()
{
    return this->constraintsList;
}

BDConstraint *BDBlock::getConstraint(const QString name)
{
    BDConstraint *ret = NULL;

    // find constraint by name
    for (int i = 0; i < this->constraintsList.size(); ++i) {
        if (this->constraintsList.at(i)->Name == name) {
            ret = this->constraintsList.at(i);
            break;
        }
    }

    return ret;
}
