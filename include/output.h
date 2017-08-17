#ifndef OUTPUT_H
#define OUTPUT_H

#include "libglobals.h"

#include <QObject>
#include <QXmlStreamReader>

namespace  libblockdia {

/**
 * @details Output for blocks.
 * Output objects represent inputs for Blocks.
 * Output objects can be connected to multiple inputs.
 */
class LIBBLOCKDIASHARED_EXPORT Output : public QObject
{
    Q_OBJECT
public:

    /**
     * @details Constructing an Output
     * The output is automatically attached to the parent block.
     * @param name The name for the output
     * @param parent The parent block, this output belongs to.
     */
    explicit Output(const QString &name, QObject *parent = 0);

    /**
     * @details The name of the output
     * It is recommended, that every output
     * has a unique name within a certain block.
     * @return The name of the output.
     */
    QString name();

    /**
     * @details Assigning a new name for the output.
     * @see Output::name()
     * @param name The new name
     */
    void setName(QString name);

    /**
     * @details Parsing a XML stram for an output
     * The XML stream is parsed from the current element for an output definition.
     * In every case the XML parser is set to after the current element (parent or next child).
     * @param xml The current xml parser
     * @param parent The parent Block object
     */
    static void parseBlockDef(QXmlStreamReader *xml, QObject *parent);


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

#endif // OUTPUT_H
