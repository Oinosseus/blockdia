#ifndef INPUT_H
#define INPUT_H

#include "libglobals.h"

#include <QObject>

namespace  libblockdia {

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
     * @details Constructing an Input
     * @param name The name for the input
     */
    explicit Input(const QString &name, QObject *parent = 0);

    /**
     * @details The name of the input
     * It is recommended, that every input
     * has a unique name within a certain block.
     * @return The name of the input.
     */
    QString name();

    /**
     * @details Assigning a new name for the input.
     * @see Input::name()
     * @param name The new name
     */
    void setName(QString name);


signals:
    /**
     * @details This signal is emitted whenever something has changed.
     */
    void somethingHasChanged();

public slots:

private:
    QString _name;
};

} // namespace bd

#endif // INPUT_H
