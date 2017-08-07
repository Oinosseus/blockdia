#ifndef BDBLOCK_H
#define BDBLOCK_H

#include "libglobals.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QColor>
#include <QGraphicsItem>
#include <QChildEvent>
#include <QTimer>

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
    Q_OBJECT

public:

    /**
     * @details Construct a BDBlock
     * @param parent The Qt parent pointer.
     */
    explicit Block(QObject *parent = 0);

    // ------------------------------------------------------------------------
    //                                Properties
    // ------------------------------------------------------------------------

    /**
     * @details A identification of similar block types.
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
     * @param id Setting a new BDBlock::typeId property
     */
    void setTypeId(const QString &id);

    /**
     * @return This is the long representation of typeId()
     */
    QString typeName();

    /**
     * @param Setting a new BDBlock::typeName property
     */
    void setTypeName(const QString &name);

    /**
     * @details Distinguishing different block instances of same type.
     *
     * This is a unique Id for block instances of the same type.
     * The instanceId is the short cut of BDBlock::instanceName.
     * Only the combination of BDBlock::typeId and BDBlock::instanceId is unique.
     * The instanceId can be an arbitrary string.
     * @return The instanceId of the block
     */
    QString instanceId();

    /**
     * @param id Setting a new BDBlock::instanceId
     */
    void setInstanceId(const QString &id);

    /**
     * @return This is the long represenmtation of instanceId()
     */
    QString instanceName();

    /**
     * @param name Setting a new instanceName() property
     */
    void setInstanceName(const QString &name);

    /**
     * @return This is used as background color for the BDGraphicItemBlock.
     */
    QColor color();

    /**
     * @param color Setting a new block color
     */
    void setColor(QColor color);

    /**
     * @return A list of all parameters
     */
    QList<Parameter *> getParameters();

    /**
     * @details Get a certain parameter
     * @param name The name of the parameter.
     * @return Returns a pointer to the parameter or NULL if no the parameter could be found.
     */
    Parameter *getParameter(const QString name);

    /**
     * @return A list of all inputs
     */
    QList<Input *> getInputs();

    /**
     * @details Get a certain input
     * @param name The name of the input.
     * @return Returns a pointer to the input or NULL if the input could not be found.
     */
    Input *getInput(const QString name);

    /**
     * @return A list of all outputs
     */
    QList<Output *> getOutputs();

    /**
     * @details Get a certain output
     * @param name The name of the output.
     * @return Returns a pointer to the output or NULL if the output could not be found.
     */
    Output *getOutput(const QString name);

    /**
     * @return The corresponding QGraphicsItem object
     */
    QGraphicsItem *getGraphicsItem();



signals:

    /**
     * @details Is emitted when any contained data has been changed.
     */
    void signalSomethingChanged();

public slots:

private:
    void childEvent(QChildEvent *e);

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
    void slotUpdateChildObjects();
};

} // namespace bd

#endif // BDBLOCK_H
