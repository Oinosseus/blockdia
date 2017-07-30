#ifndef GRAPHICITEMINPUT_H
#define GRAPHICITEMINPUT_H

#include "libglobals.h"
#include "block.h"

namespace libblockdia {

class LIBBLOCKDIASHARED_EXPORT GraphicItemInput : public GraphicItemTextBox
{
public:
    GraphicItemInput(Block *block, int inputIndex, QGraphicsItem *parent=0);

    /**
     * @details Updates the displayed data
     */
    void updateData();

    /**
     * @details Updates the displayed data
     * @param inputIndex The index of the Input in the list of inputs of the Block
     */
    void updateData(int inputIndex);

private:
    int inputIndex;
    Block *block;
};

} // namespace libblockdia

#endif // GRAPHICITEMINPUT_H
