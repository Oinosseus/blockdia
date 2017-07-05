#include "bdviewblock.h"
#include <QGraphicsScene>
#include <bdgraphicitemblock.h>
#include <bdconstraintint.h>
#include <QDebug>

BDViewBlock::BDViewBlock(QWidget *parent) : QGraphicsView(parent)
{

    // create a test block
    BDBlock *myBlock = new BDBlock();
    myBlock->setTypeName("Compensated Calibration");
    myBlock->setTypeId("Cal1");
    myBlock->setInstanceName("Pressure Temp. Compensation");
    myBlock->setInstanceId("I1");
    myBlock->setColor(QColor("#00aa00"));

    // add constraints
    BDConstraint *cnstrnt;
    cnstrnt = new BDConstraint();
    cnstrnt->setName("Constraint1");
    myBlock->addConstraint(cnstrnt);
    cnstrnt = new BDConstraint();
    cnstrnt->setName("Constraint2");
    myBlock->addConstraint(cnstrnt);
    cnstrnt = new BDConstraint();
    cnstrnt->setName("Constraint3");
    myBlock->addConstraint(cnstrnt);

    BDGraphicItemBlock *myBlockGItem = new BDGraphicItemBlock(myBlock);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
    scene->addItem(myBlockGItem);

    this->setScene(scene);
    this->show();
}
