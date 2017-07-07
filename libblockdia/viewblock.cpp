#include "viewblock.h"
#include <QGraphicsScene>
#include <graphicitemblock.h>
#include <constraintint.h>
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
    Constraint *cnstrnt;
    cnstrnt = new ConstraintInt();
    cnstrnt->setName("Constraint1");
    myBlock->addConstraint(cnstrnt);
    cnstrnt = new ConstraintInt();
    cnstrnt->setName("Constraint2");
    myBlock->addConstraint(cnstrnt);
    cnstrnt = new ConstraintInt();
    cnstrnt->setName("Constraint3");
    myBlock->addConstraint(cnstrnt);

    GraphicItemBlock *myBlockGItem = new GraphicItemBlock(myBlock);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myBlockGItem);

    this->setScene(scene);
    this->show();
}
