#include "viewblock.h"

#include <QGraphicsScene>
#include <QDebug>

#include <graphicitemblock.h>
#include <parameterint.h>
#include <input.h>
#include <output.h>

bd::ViewBlock::ViewBlock(QWidget *parent) : QGraphicsView(parent)
{

    // create a test block
    Block *myBlock = new Block();
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
    Input *inp;
    inp = new Input(myBlock, "Input1");
    inp = new Input(myBlock, "Input2");
    inp = new Input(myBlock, "Input3");

    // add outputs
    Output *outp;
    outp = new Output(myBlock, "Out1");

    GraphicItemBlock *myGitemTst= new GraphicItemBlock(myBlock);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myGitemTst);

    this->setScene(scene);
    this->show();
}
