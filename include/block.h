#ifndef BDBLOCK_H
#define BDBLOCK_H

#include "libglobals.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QColor>
#include <QGraphicsItem>

#include <parameter.h>
#include <input.h>
#include <output.h>
#include <graphicitemblock.h>

namespace libblockdia {

// forward declarations
class GraphicItemBlock;
class Parameter;
class Input;
class Output;

/**
 * @brief Data storage class for a block representation.
 */
class LIBBLOCKDIASHARED_EXPORT Block : public QObject
{
    friend class Parameter;
    friend class Input;
    friend class Output;

    Q_OBJECT
public:

    /**
     * @brief Construct a BDBlock
     * @param parent The Qt parent pointer.
     */
    explicit Block(QObject *parent = 0);

    // ------------------------------------------------------------------------
    //                                Properties
    // ------------------------------------------------------------------------

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
    QString typeId();

    /**
     * @brief Setting the BDBlock::typeId property
     * @param The new BDBlock::typeId
     */
    void setTypeId(const QString &id);

    /**
     * @brief The longer version of the BDBlock::typeId
     * This is the same as the BDBlock::typeId but as a longer representation.
     * @return
     */
    QString typeName();

    /**
     * @brief Setting the BDBlock::typeName property.
     * @param The new BDBlock::typeName
     */
    void setTypeName(const QString &name);

    /**
     * @brief Distinguishing different block instances of same type.
     *
     * This is a unique Id for block instances of the same type.
     * The instanceId is the short cut of BDBlock::instanceName.
     * Only the combination of BDBlock::typeId and BDBlock::instanceId is unique.
     * The instanceId can be an arbitrary string.
     * @return The instanceId of the block
     */
    QString instanceId();

    /**
     * @brief Setting the BDBlock::instanceId
     * @param The new instanceId
     */
    void setInstanceId(const QString &id);

    /**
     * @brief The longer version of the BDBlock::instanceId
     * This is the same as the BDBlock::instanceId but as a longer representation.
     * @return
     */
    QString instanceName();

    /**
     * @brief Setting the BDBlock::instanceName property.
     * @param The new BDBlock::instanceName
     */
    void setInstanceName(const QString &name);

    /**
     * @brief The color of the block.
     * This is used as background color for the BDGraphicItemBlock.
     * @return The color of the block.
     */
    QColor color();

    /**
     * @brief Setting a new block color
     * @see BDBlock::color
     * @param color The new color for the block.
     */
    void setColor(QColor color);

    /**
     * @brief Retrieving a list of all parameters.
     * @return The list of parameters.
     */
    QList<Parameter *> getParameters();

    /**
     * @brief Get a certain parameter
     * @param name The name of the parameter.
     * @return Returns a pointer to the parameter or NULL if no the parameter could be found.
     */
    Parameter *getParameter(const QString name);

    /**
     * @brief Retrieving a list of all inputs.
     * @return The list of inputs.
     */
    QList<Input *> getInputs();

    /**
     * @brief Get a certain input
     * @param name The name of the input.
     * @return Returns a pointer to the input or NULL if the input could not be found.
     */
    Input *getInput(const QString name);

    /**
     * @brief Retrieving a list of all outputs.
     * @return The list of outputs.
     */
    QList<Output *> getOutputs();

    /**
     * @brief Get a certain output
     * @param name The name of the output.
     * @return Returns a pointer to the output or NULL if the output could not be found.
     */
    Output *getOutput(const QString name);

    /**
     * @brief Get the corresponding QGraphicsItem object
     * @return The corresponding QGraphicsItem object
     */
    QGraphicsItem *getGraphicsItem();



signals:

    /**
     * @brief Is emitted when any contained data has been changed.
     */
    void signalSomethingChanged();

public slots:

private:
    QString _TypeId;
    QString _TypeName;
    QString _InstanceId;
    QString _InstanceName;
    QColor  _Color;
    QList<Parameter *> parametersList;
    QList<Input *> inputsList;
    QList<Output *> outputsList;
    GraphicItemBlock *giBlock;

private slots:
    void slotSomethingChanged();
};

} // namespace bd

#endif // BDBLOCK_H
