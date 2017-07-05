#include "bdviewblock.h"
#include <QGraphicsScene>
#include <bdgraphicitemblock.h>
#include <bdconstraintint.h>

BDViewBlock::BDViewBlock(QWidget *parent) : QGraphicsView(parent)
{

    // create a test block
    BDBlock *myBlock = new BDBlock();
    myBlock->setTypeName("Compensated Calibration");
    myBlock->setTypeId("Cal1");
    myBlock->setInstanceName("Pressure Temp. Compensation");
    myBlock->setInstanceId("I1");
    myBlock->setColor(QColor("#00aa00"));

    BDGraphicItemBlock *myBlockGItem = new BDGraphicItemBlock(myBlock);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myBlockGItem);

    this->setScene(scene);
    this->show();
}
