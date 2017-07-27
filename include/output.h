#ifndef OUTPUT_H
#define OUTPUT_H

#include "libglobals.h"

#include <QObject>

#include <block.h>

namespace  libblockdia {

/**
 * @brief Output for blocks.
 * Output objects represent inputs for Blocks.
 * Output objects can be connected to multiple inputs.
 */
class LIBBLOCKDIASHARED_EXPORT Output : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Constructing an Output
     * @param block The parent block, this output belongs to.
     * @param name The name for the output
     */
    explicit Output(Block *block, const QString &name);

    /**
     * @brief The name of the output
     * It is recommended, that every output
     * has a unique name within a certain block.
     * @return The name of the output.
     */
    QString name();

    /**
     * @brief Assigning a new name for the output.
     * @see Output::name()
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

#endif // OUTPUT_H
