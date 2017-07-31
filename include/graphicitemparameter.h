#ifndef GRAPHICITEMPARAMETER_H
#define GRAPHICITEMPARAMETER_H

#include "libglobals.h"

#include <QGraphicsSceneContextMenuEvent>

#include "block.h"

namespace libblockdia {

class LIBBLOCKDIASHARED_EXPORT GraphicItemParameter : public GraphicItemTextBox
{
public:

    /**
     * @brief A QGraphicsItem that represents a parameter.
     * @param block The referenced block object
     * @param parameterIndex The index of the Parameter in the list of paramters of the Block
     * @param parent The Qt parent QGraphicsItem
     */
    GraphicItemParameter(Block *block, int _parameterIndex, QGraphicsItem *parent=0);

    /**
     * @details Updates the displayed data
     */
    void updateData();

    /**
     * @details Updates the displayed data
     * @param parameterIndex The index of the Parameter in the list of paramters of the Block
     */
    void updateData(int _parameterIndex);

    /**
     * @return The actual used index of the Parameter in the list of parameter of the corresponding Block.
     */
    int parameterIndex();



private:
    int _parameterIndex;
    Block *block;
};

} // namespace libblockdia

#endif // GRAPHICITEMPARAMETER_H
