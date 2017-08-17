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
    QXmlStreamAttributes attr = xml->attributes();

    // ctreate parameter
    QString name = "";
    if (attr.hasAttribute("name")) name = attr.value("name").toString().trimmed();
    ParameterInt *param = new ParameterInt(name, parent);

    // check public
    if (attr.hasAttribute("isPublic")) {
        QString ispublic = attr.value("isPublic").toString().trimmed().toLower();
        param->setPublic(ispublic == "yes" || ispublic == "true" || ispublic == "1");
    }

    // read default
    if (attr.hasAttribute("default")) {
        QString def = attr.value("default").toString().trimmed();
        param->setDefaultValue(def);
    }

    // parse definitions
    if (!xml->isEndElement()) {
        while (xml->readNextStartElement()) {
            QString xmlTag = xml->name().toString().toLower();

            // read min
            if (xmlTag == "min") {
                QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
                bool ok;
                int i = t.toInt(&ok);
                if (ok) param->setMinimum(i);
            }

            // read max
            else if (xmlTag == "max") {
                QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
                bool ok;
                int i = t.toInt(&ok);
                if (ok) param->setMaximum(i);
            }

            else {
                xml->skipCurrentElement();
            }
        }
    }

    return param;
}

void libblockdia::ParameterInt::setMaximum(int max)
{
    if (this->_maximum != max) {
        this->_maximum = max;
        this->setValue(this->_value); // update for limit adjust
        emit somethingHasChanged();
    }
}
