#include "viewblockeditor.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

libblockdia::ViewBlockEditor::ViewBlockEditor(Block *block, QWidget *parent) : QGraphicsView(parent)
{
    this->block = block;

    QGraphicsScene *scene = new QGraphicsScene(this);
//    scene->setBackgroundBrush(QBrush(QColor("#fffcfc")));
//    scene->addItem(this->block->getGraphicsItem());

    this->testCounter = 0;
    this->giTest = new GraphicItemTextBox();
    scene->addItem(this->giTest);

    QTimer *timerTest = new QTimer(this);
    connect(timerTest, SIGNAL(timeout()), this, SLOT(slotTestTimeout()));
    timerTest->start(1000);

    // show center
//    scene->addLine(-100, 0, 100, 0, QPen(QColor("#f00")));
//    scene->addLine(0, -100, 0, 100, QPen(QColor("#f00")));

    this->setScene(scene);

    this->show();
}

void libblockdia::ViewBlockEditor::slotTestTimeout()
{
    GraphicItemTextBox * gitb = (GraphicItemTextBox *) this->giTest;

    if (this->testCounter == 0)
        gitb->setText("FooyBar", GraphicItemTextBox::Align::Center);
    if (this->testCounter == 1)
        gitb->setText("FoyoBar Long", GraphicItemTextBox::Align::Center);
    if (this->testCounter == 2)
        gitb->setText("IjIjIjIj", GraphicItemTextBox::Align::Center);
    if (this->testCounter == 3)
        gitb->setMinWidth(300);
    if (this->testCounter == 4)
        gitb->setText("IjIjIjIj", GraphicItemTextBox::Align::Left);
    if (this->testCounter == 5)
        gitb->setText("IjIjIjIj", GraphicItemTextBox::Align::Right);
    if (this->testCounter == 6)
        gitb->setMinWidth(100);
    if (this->testCounter == 7)
        gitb->setText("This is a long text - longer than the minimum specified width.", GraphicItemTextBox::Align::Center);
    if (this->testCounter == 8)
        gitb->setBgColor(QColor("#faa"));
    if (this->testCounter == 9)
        gitb->setBgColor(QColor("#afa"));
    if (this->testCounter == 10)
        gitb->setBgColor(QColor("#aaf"));

    ++this->testCounter;
}
