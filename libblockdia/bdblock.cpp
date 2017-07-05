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



/**
 * @brief A identification of similar block types.
 *
 * This is not a unique Id for each block instance.
 * The BDBlock::TypeId is the short cut of BDBlock::typeName.
 * Only the combination of BDBlock::typeId and BDBlock::instanceId is unique.
 * The BDBlock::typeId is the same for blocks of the same type.
 * The BDBlock::typeId can be an arbitrary string.
 * @return The BDBlock::typeId of the block
 */
QString BDBlock::typeId()
{
    return this->_TypeId;
}

/**
 * @brief Setting the BDBlock::typeId property
 * @param The new BDBlock::typeId
 */
void BDBlock::setTypeId(const QString &id)
{
    if (id != this->_TypeId) {
        this->_TypeId = id;
        emit signalSomethingChanged();
    }
}

/**
 * @brief The longer version of the BDBlock::typeId
 * This is the same as the BDBlock::typeId but as a longer representation.
 * @return
 */
QString BDBlock::typeName()
{
    return this->_TypeName;
}

/**
 * @brief Setting the BDBlock::typeName property.
 * @param The new BDBlock::typeName
 */
void BDBlock::setTypeName(const QString &name)
{
    if (name != this->_TypeName) {
        this->_TypeName = name;
        emit signalSomethingChanged();
    }
}


/**
 * @brief Distinguishing different block instances of same type.
 *
 * This is a unique Id for block instances of the same type.
 * The instanceId is the short cut of BDBlock::instanceName.
 * Only the combination of BDBlock::typeId and BDBlock::instanceId is unique.
 * The instanceId can be an arbitrary string.
 * @return The instanceId of the block
 */
QString BDBlock::instanceId()
{
    return this->_InstanceId;
}

/**
 * @brief Setting the BDBlock::instanceId
 * @param The new instanceId
 */
void BDBlock::setInstanceId(const QString &id)
{
    if (id != this->_InstanceId) {
        this->_InstanceId = id;
        emit signalSomethingChanged();
    }
}

/**
 * @brief The longer version of the BDBlock::instanceId
 * This is the same as the BDBlock::instanceId but as a longer representation.
 * @return
 */
QString BDBlock::instanceName()
{
    return this->_InstanceName;
}

/**
 * @brief Setting the BDBlock::instanceName property.
 * @param The new BDBlock::instanceName
 */
void BDBlock::setInstanceName(const QString &name)
{
    if (name != this->_InstanceName) {
        this->_InstanceName = name;
        emit signalSomethingChanged();
    }
}

/**
 * @brief The color of the block.
 * This is used as background color for the BDGraphicItemBlock.
 * @return The color of the block.
 */
QColor BDBlock::color()
{
    return this->_Color;
}

/**
 * @brief Setting a new block color
 * @see BDBlock::color
 * @param color The new color for the block.
 */
void BDBlock::setColor(QColor color)
{
    this->_Color = color;
}




/**
 * @brief BDBlock::addConstraint
 * @param cnstrnt The constraint that shall be added to this block.
 */
void BDBlock::addConstraint(BDConstraint *cnstrnt)
{
    this->constraintsList.append(cnstrnt);
}



/**
 * @brief BDBlock::getConstraint
 * @param name The name of the constraint.
 * @return Returns a pointer to BDConstraint or NULL if no constraint could be found.
 */
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
