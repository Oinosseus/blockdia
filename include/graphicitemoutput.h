#ifndef GRAPHICITEMOUTPUT_H
#define GRAPHICITEMOUTPUT_H

#include "libglobals.h"
#include "block.h"

namespace libblockdia {

class LIBBLOCKDIASHARED_EXPORT GraphicItemOutput : public GraphicItemTextBox
{
public:
    GraphicItemOutput(Block *block, int outputIndex, QGraphicsItem *parent=0);

    /**
     * @details Updates the displayed data
     */
    void updateData();

    /**
     * @details Updates the displayed data
     * @param outputIndex The index of the Input in the list of outputs of the Block
     */
    void updateData(int outputIndex);

private:
    Block *block;
    int outputIndex;
};

} // namespace libblockdia

#endif // GRAPHICITEMOUTPUT_H
