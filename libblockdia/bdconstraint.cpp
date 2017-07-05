#include "bdconstraint.h"

BDConstraint::BDConstraint(QObject *parent) : QObject(parent)
{
    this->_Name = "";
}

QString BDConstraint::name()
{
    return this->_Name;
}

void BDConstraint::setName(QString name)
{
    this->_Name = name;
}

QString BDConstraint::strValue()
{
    return "Dummy Value";
}
