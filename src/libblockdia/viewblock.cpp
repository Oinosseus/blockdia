#include "viewblock.h"

#include <QGraphicsScene>
#include <QDebug>

#include <block.h>
#include <blockparameterint.h>
#include <blockinput.h>
#include <blockoutput.h>

libblockdia::ViewBlock::ViewBlock(QWidget *parent) : QGraphicsView(parent)
{

    // create a test block
    Block *myBlock = new libblockdia::Block();
    myBlock->setTypeName("Compensated Calibration");
    myBlock->setTypeId("Cal1");
    myBlock->setInstanceName("Pressure Temp. Compensation");
    myBlock->setInstanceId("I1");
    myBlock->setColor(QColor("#00aa00"));

    // add parameters
    BlockParameterInt *param;
    param = new BlockParameterInt("Parameter 1", myBlock);
    param->setValue(-27);
    param->setPublic(false);
    param = new BlockParameterInt("Parameter two", myBlock);
    param->setValue(32768);
    param->setPublic(true);
    param = new BlockParameterInt("Parameter3", myBlock);
    param->setValue("123");
    param->setPublic(true);

    // add inputs
    new BlockInput("Input1", myBlock);
    new BlockInput("Input Two", myBlock);
    new BlockInput("Input 3", myBlock);

    // add outputs
    new BlockOutput("Out1", myBlock);
    new BlockOutput("Out 2", myBlock);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myBlock->getGraphicsItem());

    this->setScene(scene);
    this->show();
}
