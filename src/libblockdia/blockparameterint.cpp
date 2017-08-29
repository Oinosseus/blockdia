#include "blockparameterint.h"
#include <limits.h>
#include <QDebug>

libblockdia::BlockParameterInt::BlockParameterInt(const QString &name, QObject *parent) : BlockParameter(name, parent)
{
    this->_minimum = INT_MIN;
    this->_maximum = INT_MAX;
    this->_value = this->_minimum;
    this->_defaultValue = this->_value;
}

int libblockdia::BlockParameterInt::minimum()
{
    return this->_minimum;
}

void libblockdia::BlockParameterInt::setMinimum(int min)
{
    if (this->_minimum != min) {
        this->_minimum = min;
        this->setValue(this->_value); // update for limit adjust
        emit somethingHasChanged();
    }
}

int libblockdia::BlockParameterInt::maximum()
{
    return this->_maximum;
}

int libblockdia::BlockParameterInt::value()
{
    return this->_value;
}

QString libblockdia::BlockParameterInt::strDefaultValue()
{
    return QString::number(this->_defaultValue);
}

int libblockdia::BlockParameterInt::defaultValue()
{
    return this->_defaultValue;
}

bool libblockdia::BlockParameterInt::setDefaultValue(QString value)
{
    bool ok;
    int ivalue = value.toInt(&ok);
    ok &= this->setDefaultValue(ivalue);
    return ok;
}

bool libblockdia::BlockParameterInt::setDefaultValue(int value)
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
    if (this->_defaultValue != value) {
        this->_defaultValue = value;
        emit somethingHasChanged();
    }

    return ret;
}

bool libblockdia::BlockParameterInt::setValue(int value)
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

bool libblockdia::BlockParameterInt::setValue(QString value)
{
    bool ret = true;
    int intval = value.toInt(&ret);
    ret &= this->setValue(intval);
    return ret;
}

QString libblockdia::BlockParameterInt::strValue()
{
    return QString::number(this->_value);
}

QString libblockdia::BlockParameterInt::allowedValues()
{
    return QString::number(this->_minimum) + " .. " + QString::number(this->_maximum);
}

bool libblockdia::BlockParameterInt::importParamDef(QXmlStreamReader *xml)
{
    while (xml->readNextStartElement()) {

        // read min
        if (xml->name() == "Min") {
            QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
            bool ok;
            int i = t.toInt(&ok);
            if (ok) this->setMinimum(i);
        }

        // read max
        else if (xml->name() == "Max") {
            QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
            bool ok;
            int i = t.toInt(&ok);
            if (ok) this->setMaximum(i);
        }

        else {
            xml->skipCurrentElement();
            qWarning() << "ERROR Parsing XML: unknown element (at line" << xml->lineNumber() << ")";
        }

    }

    return xml->hasError();
}

bool libblockdia::BlockParameterInt::exportParamDef(QXmlStreamWriter *xml)
{
    // specific sub elements
    xml->writeTextElement("Min", QString::number(this->minimum()));
    xml->writeTextElement("Max", QString::number(this->maximum()));
    return xml->hasError();
}

void libblockdia::BlockParameterInt::setMaximum(int max)
{
    if (this->_maximum != max) {
        this->_maximum = max;
        this->setValue(this->_value); // update for limit adjust
        emit somethingHasChanged();
    }
}
