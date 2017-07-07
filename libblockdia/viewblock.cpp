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
    cnstrnt = new ParameterInt();
    cnstrnt->setName("Constraint1");
    cnstrnt->setValue(-27);
    myBlock->addConstraint(cnstrnt);
    cnstrnt = new ParameterInt();
    cnstrnt->setName("Constraint2");
    cnstrnt->setValue(32768);
    myBlock->addConstraint(cnstrnt);
    cnstrnt = new ParameterInt();
    cnstrnt->setName("Constraint3");
    cnstrnt->setValue("123");
    myBlock->addConstraint(cnstrnt);

    GraphicItemBlock *myBlockGItem = new GraphicItemBlock(myBlock);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myBlockGItem);

    this->setScene(scene);
    this->show();
}
