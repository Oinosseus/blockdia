#ifndef INPUT_H
#define INPUT_H

#include "libglobals.h"

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace  libblockdia {

/**
 * @brief Input for blocks.
 * Input objects represent inputs for Blocks.
 * Input objects can be connected to exactely one output.
 */
class LIBBLOCKDIASHARED_EXPORT BlockInput : public QObject
{
    Q_OBJECT
public:

    /**
     * @details Constructing an Input
     * @param name The name for the input
     */
    explicit BlockInput(const QString &name, QObject *parent = 0);

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

    /**
     * @details Parsing a XML stram for inputs
     * The XML stream is parsed from the current element for an inputs definition.
     * In every case the XML parser is set to after the current element (parent or next child).
     * @param xml The current xml parser
     * @param parent The parent Block object
     */
    static void parseBlockDef(QXmlStreamReader *xml, QObject *parent);

    /**
     * @details Exporting to an xml stream
     * @param xml The current xml writer
     * @return True on success
     */
    bool exportBlockDef(QXmlStreamWriter *xml);


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
