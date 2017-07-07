#include "viewblock.h"
#include <QGraphicsScene>
#include <graphicitemblock.h>
#include <parameterint.h>
#include <QDebug>

bd::ViewBlock::ViewBlock(QWidget *parent) : QGraphicsView(parent)
{

    // create a test block
    Block *myBlock = new Block();
    myBlock->setTypeName("Compensated Calibration");
    myBlock->setTypeId("Cal1");
    myBlock->setInstanceName("Pressure Temp. Compensation");
    myBlock->setInstanceId("I1");
    myBlock->setColor(QColor("#00aa00"));

    // add constraints
    ParameterInt *cnstrnt;
    cnstrnt = new ParameterInt(myBlock, "Constraint1");
    cnstrnt->setValue(-27);
    cnstrnt = new ParameterInt(myBlock, "Constraint2");
    cnstrnt->setValue(32768);
    cnstrnt = new ParameterInt(myBlock, "Constraint3");
    cnstrnt->setValue("123");

    GraphicItemBlock *myBlockGItem = new GraphicItemBlock(myBlock);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myBlockGItem);

    this->setScene(scene);
    this->show();
}
