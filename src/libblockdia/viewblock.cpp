#include "viewblock.h"

#include <QGraphicsScene>
#include <QDebug>

#include <block.h>
#include <parameterint.h>
#include <input.h>
#include <output.h>

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
    ParameterInt *param;
    param = new ParameterInt(myBlock, "Parameter 1");
    param->setValue(-27);
    param->setPublic(false);
    param = new ParameterInt(myBlock, "Parameter two");
    param->setValue(32768);
    param->setPublic(true);
    param = new ParameterInt(myBlock, "Parameter3");
    param->setValue("123");
    param->setPublic(true);

    // add inputs
//    new Input(myBlock, "Input1");
//    new Input(myBlock, "Input Two");
//    new Input(myBlock, "Input 3");

    // add outputs
//    new Output(myBlock, "Out1");
//    new Output(myBlock, "Out 2");

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myBlock->getGraphicsItem());

    this->setScene(scene);
    this->show();
}
