#include "block.h"

#include <QDebug>
#include <QMetaClassInfo>
#include <QObjectList>
#include <QXmlStreamReader>

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
    Parameter *ret = Q_NULLPTR;

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
    Input *ret = Q_NULLPTR;

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

libblockdia::Block *libblockdia::Block::parseBlockDef(QIODevice *dev, libblockdia::Block *block)
{
    QXmlStreamReader xml(dev);

    while (!xml.atEnd()) {

        if (xml.readNextStartElement()) {

            // no block definition found
            if (xml.name() != "BlockDef") {
                qWarning() << "parseBlockDef: unknown root element:" << xml.name();
                xml.skipCurrentElement();
            } else {

                // parse different versions
                if (xml.attributes().value("version") == "1") {
                    if (!block) block = new Block();
                    parseBlockDefVersion1(&xml, block);
                    break;
                }

                // unknwon version
                else {
                    qWarning() << "parseBlockDef: unsupported version:" << xml.attributes().value("version");
                    xml.skipCurrentElement();
                }
            }
        }
    }

    return block;
}

void libblockdia::Block::childEvent(QChildEvent *e)
{
    Q_UNUSED(e)

    // catch child add/delete event
    // delayed timer ensures that child is add/deleted completely
    // when calling the timer slot function
    QTimer::singleShot(0, this, SLOT(slotUpdateChildObjects()));
}

void libblockdia::Block::parseBlockDefVersion1(QXmlStreamReader *xml, libblockdia::Block *block)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "BlockDef");

    // read block definitions
    while (xml->readNextStartElement()) {

        // read type name
        if (xml->name() == "TypeName") {
            QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
            block->setTypeName(t);
        }

        // read type id
        else if (xml->name() == "TypeId") {
            QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
            block->setTypeId(t);
        }

        // read color
        else if (xml->name() == "Color") {
            QString t = xml->readElementText(QXmlStreamReader::SkipChildElements);
            block->setColor(QColor(t));
        }

        // check for inputs
        else if (xml->name() == "Inputs") {
            Input::parseBlockDef(xml, block);
        }

        // check for outputs
        else if (xml->name() == "Outputs") {
            Output::parseBlockDef(xml, block);
        }

        // check for parameters
        else if (xml->name() == "Parameters") {
            Parameter::parseBlockDef(xml, block);
        }

        // unknown tag
        else {
            xml->skipCurrentElement();
        }
    }
}

void libblockdia::Block::slotSomethingChanged()
{
    this->giBlock->updateData();
}

void libblockdia::Block::slotUpdateChildObjects()
{
    bool emitSomethignChanged = false;
    QObjectList listChildren = this->children();


    // ------------------------------------------------------------------------
    //                               Find New Children
    // ------------------------------------------------------------------------

    for (int i=0; i < listChildren.size(); ++i) {
        // get liblock dia meta data
        QString childClass = listChildren.at(i)->metaObject()->className();
        QString childSuperClass = listChildren.at(i)->metaObject()->superClass()->className();

        // check for new parameters
        if (childSuperClass == "libblockdia::Parameter") {
            Parameter *child = (Parameter *) listChildren.at(i);
            if (this->parametersList.count(child) == 0) {
                this->parametersList.append(child);
                connect(child, SIGNAL(somethingHasChanged()), this, SLOT(slotSomethingChanged()));
                emitSomethignChanged = true;
            }
        }

        // check for new inputs
        else if (childClass == "libblockdia::Input") {
            Input *child = (Input *) listChildren.at(i);
            if (this->inputsList.count(child) == 0) {
                this->inputsList.append(child);
                connect(child, SIGNAL(somethingHasChanged()), this, SLOT(slotSomethingChanged()));
                emitSomethignChanged = true;
            }
        }

        // check for new outputs
        else if (childClass == "libblockdia::Output") {
            Output *child = (Output *) listChildren.at(i);
            if (this->outputsList.count(child) == 0) {
                this->outputsList.append(child);
                connect(child, SIGNAL(somethingHasChanged()), this, SLOT(slotSomethingChanged()));
                emitSomethignChanged = true;
            }
        }
    }



    // ------------------------------------------------------------------------
    //                           Delete Lost Children
    // ------------------------------------------------------------------------

    for (int i=0; i < this->parametersList.size(); ++i) {
        if (!listChildren.contains(this->parametersList.at(i))) {
            this->parametersList.removeAt(i);
            emitSomethignChanged = true;
        }
    }

    for (int i=0; i < this->inputsList.size(); ++i) {
        if (!listChildren.contains(this->inputsList.at(i))) {
            this->inputsList.removeAt(i);
            emitSomethignChanged = true;
        }
    }

    for (int i=0; i < this->outputsList.size(); ++i) {
        if (!listChildren.contains(this->outputsList.at(i))) {
            this->outputsList.removeAt(i);
            emitSomethignChanged = true;
        }
    }


    // emit singal
    if (emitSomethignChanged) {
        emit signalSomethingChanged();
    }
}
