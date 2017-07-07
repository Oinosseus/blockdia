#include "parameterint.h"
#include <limits.h>

bd::ParameterInt::ParameterInt(QObject *parent)
{
    this->_minimum = INT_MIN;
    this->_maximum = INT_MAX;
}

int bd::ParameterInt::minimum()
{
    return this->_minimum;
}

void bd::ParameterInt::setMinimum(int min)
{
    if (this->_minimum != min) {
        this->_minimum = min;
        emit somethingHasChanged();
    }
}

int bd::ParameterInt::maximum()
{
    return this->_maximum;
}

int bd::ParameterInt::value()
{
    return this->_value;
}

bool bd::ParameterInt::setValue(int value)
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

bool bd::ParameterInt::setValue(QString value)
{
    bool ret = true;
    int intval = value.toInt(&ret);
    ret &= this->setValue(intval);
    return ret;
}

QString bd::ParameterInt::strValue()
{
    return QString::number(this->_value);
}

QString bd::ParameterInt::allowedValues()
{
    return QString::number(this->_minimum) + " .. " + QString::number(this->_maximum);
}

void bd::ParameterInt::setMaximum(int max)
{
    if (this->_maximum != max) {
        this->_maximum = max;
        emit somethingHasChanged();
    }
}
