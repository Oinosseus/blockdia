#include "parameterint.h"
#include <limits.h>

libblockdia::ParameterInt::ParameterInt(const QString &name, QObject *parent) : Parameter(name, parent)
{
    this->_minimum = INT_MIN;
    this->_maximum = INT_MAX;
}

int libblockdia::ParameterInt::minimum()
{
    return this->_minimum;
}

void libblockdia::ParameterInt::setMinimum(int min)
{
    if (this->_minimum != min) {
        this->_minimum = min;
        emit somethingHasChanged();
    }
}

int libblockdia::ParameterInt::maximum()
{
    return this->_maximum;
}

int libblockdia::ParameterInt::value()
{
    return this->_value;
}

bool libblockdia::ParameterInt::setValue(int value)
{
    bool ret = true;

    // clip at minimum
    if (value < this->_minimum) {
        value = this->_minimum;
        ret = false;
    }

    // clip at maximum
    if (value > this->_maximum) {
        value = this->_maximum;
        ret = false;
    }

    // set new value
    if (this->_value != value) {
        this->_value = value;
        emit somethingHasChanged();
    }

    return ret;
}

bool libblockdia::ParameterInt::setValue(QString value)
{
    bool ret = true;
    int intval = value.toInt(&ret);
    ret &= this->setValue(intval);
    return ret;
}

QString libblockdia::ParameterInt::strValue()
{
    return QString::number(this->_value);
}

QString libblockdia::ParameterInt::allowedValues()
{
    return QString::number(this->_minimum) + " .. " + QString::number(this->_maximum);
}

void libblockdia::ParameterInt::setMaximum(int max)
{
    if (this->_maximum != max) {
        this->_maximum = max;
        emit somethingHasChanged();
    }
}
