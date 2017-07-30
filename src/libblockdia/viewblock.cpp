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
    param = new ParameterInt("Parameter 1", myBlock);
    param->setValue(-27);
    param->setPublic(false);
    param = new ParameterInt("Parameter two", myBlock);
    param->setValue(32768);
    param->setPublic(true);
    param = new ParameterInt("Parameter3", myBlock);
    param->setValue("123");
    param->setPublic(true);

    // add inputs
    new Input("Input1", myBlock);
    new Input("Input Two", myBlock);
    new Input("Input 3", myBlock);

    // add outputs
    new Output("Out1", myBlock);
    new Output("Out 2", myBlock);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myBlock->getGraphicsItem());

    this->setScene(scene);
    this->show();
}
