#include "constraint.h"

bd::Constraint::Constraint(QObject *parent) : QObject(parent)
{
    this->_Name = "";
}

QString bd::Constraint::name()
{
    return this->_Name;
}

void bd::Constraint::setName(QString name)
{
    this->_Name = name;
}

QString bd::Constraint::strValue()
{
    return "Dummy Value";
}
