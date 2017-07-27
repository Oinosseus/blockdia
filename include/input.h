#ifndef INPUT_H
#define INPUT_H

#include "libglobals.h"

#include <QObject>

#include <block.h>

namespace  libblockdia {

// forward declarations
class Block;

/**
 * @brief Input for blocks.
 * Input objects represent inputs for Blocks.
 * Input objects can be connected to exactely one output.
 */
class LIBBLOCKDIASHARED_EXPORT Input : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Constructing an Input
     * @param block The parent block, this input belongs to.
     * @param name The name for the input
     */
    explicit Input(Block *block, const QString &name);

    /**
     * @brief The name of the input
     * It is recommended, that every input
     * has a unique name within a certain block.
     * @return The name of the input.
     */
    QString name();

    /**
     * @brief Assigning a new name for the input.
     * @see Input::name()
     * @param name The new name
     */
    void setName(QString name);


signals:
    /**
     * @brief This signal is emitted whenever something has changed.
     */
    void somethingHasChanged();

public slots:

private:
    QString _name;
    Block *parent;
};

} // namespace bd

#endif // INPUT_H
