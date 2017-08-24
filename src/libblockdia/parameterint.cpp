#include "parameterint.h"
#include <limits.h>

libblockdia::ParameterInt::ParameterInt(const QString &name, QObject *parent) : Parameter(name, parent)
{
    this->_minimum = INT_MIN;
    this->_maximum = INT_MAX;
    this->_value = this->_minimum;
    this->_defaultValue = this->_value;
}

int libblockdia::ParameterInt::minimum()
{
    return this->_minimum;
}

void libblockdia::ParameterInt::setMinimum(int min)
{
    if (this->_minimum != min) {
        this->_minimum = min;
        this->setValue(this->_value); // update for limit adjust
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

QString libblockdia::ParameterInt::strDefaultValue()
{
    return QString::number(this->_defaultValue);
}

int libblockdia::ParameterInt::defaultValue()
{
    return this->_defaultValue;
}

bool libblockdia::ParameterInt::setDefaultValue(QString value)
{
    bool ok;
    int ivalue = value.toInt(&ok);
    ok &= this->setDefaultValue(ivalue);
    return ok;
}

bool libblockdia::ParameterInt::setDefaultValue(int value)
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

libblockdia::ParameterInt *libblockdia::ParameterInt::parseBlockDef(QXmlStreamReader *xml, QObject *parent)
{
    // ctreate parameter
    ParameterInt *param = new ParameterInt(xml->attributes().value("name").toString(), parent);

    while (xml->readNextStartElement()) {

        // read min
        if (xml->name() == "Min") {
            QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
            bool ok;
            int i = t.toInt(&ok);
            if (ok) param->setMinimum(i);
        }

        // read max
        else if (xml->name() == "Max") {
            QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
            bool ok;
            int i = t.toInt(&ok);
            if (ok) param->setMaximum(i);
        }

        else {
            xml->skipCurrentElement();
        }
    }

    return param;
}

bool libblockdia::ParameterInt::exportBlockDef(QXmlStreamWriter *xml)
{
    xml->writeStartElement("ParameterInt");

    // parameter attributes
    xml->writeAttribute("name", this->name());
    if (this->isPublic()) xml->writeAttribute("isPublic", "true");
    xml->writeAttribute("default", this->strDefaultValue());

    // specific sub elements
    xml->writeTextElement("Min", QString::number(this->minimum()));
    xml->writeTextElement("Max", QString::number(this->maximum()));

    xml->writeEndElement();
    return xml->hasError();
}

void libblockdia::ParameterInt::setMaximum(int max)
{
    if (this->_maximum != max) {
        this->_maximum = max;
        this->setValue(this->_value); // update for limit adjust
        emit somethingHasChanged();
    }
}
