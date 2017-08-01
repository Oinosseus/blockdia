#include "dialogeditheader.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

libblockdia::DialogEditHeader::DialogEditHeader(Block *block, QWidget *parent) : QDialog(parent)
{
    // setup configuration
    this->block = block;
    this->setSizeGripEnabled(true);
    connect(this, SIGNAL(accepted()), this, SLOT(slotWriteBlockData()));


    // ------------------------------------------------------------------------
    //                             Edit Grid
    // ------------------------------------------------------------------------

    // load values from block
    this->lineInstanceId.setText(this->block->instanceId());
    this->lineInstanceName.setText(this->block->instanceName());
    this->lineTypeId.setText(this->block->typeId());
    this->lineTypeName.setText(this->block->typeName());

    // create layout
    QGridLayout *layoutGrid = new QGridLayout();
    int gridRowCount = 0;

    // add header row
    layoutGrid->addWidget(new QLabel("ID"), gridRowCount, 1, Qt::AlignCenter);
    layoutGrid->addWidget(new QLabel("Name"), gridRowCount, 2, Qt::AlignCenter);
    layoutGrid->setColumnStretch(0, 0);
    layoutGrid->setColumnStretch(1, 1);
    layoutGrid->setColumnStretch(2, 3);
    layoutGrid->setRowStretch(gridRowCount, 0);
    ++gridRowCount;

    // add instance edits
    layoutGrid->addWidget(new QLabel("Instance"), gridRowCount, 0, Qt::AlignRight);
    layoutGrid->addWidget(&this->lineInstanceId, gridRowCount, 1);
    layoutGrid->addWidget(&this->lineInstanceName, gridRowCount, 2);
    layoutGrid->setRowStretch(gridRowCount, 10);
    ++gridRowCount;

    // add type edits
    layoutGrid->addWidget(new QLabel("Type"), gridRowCount, 0, Qt::AlignRight);
    layoutGrid->addWidget(&this->lineTypeId, gridRowCount, 1);
    layoutGrid->addWidget(&this->lineTypeName, gridRowCount, 2);
    layoutGrid->setRowStretch(gridRowCount, 10);
    ++gridRowCount;



    // ------------------------------------------------------------------------
    //                             Control Buttons
    // ------------------------------------------------------------------------

    // buttons
    QPushButton *btnOk = new QPushButton("Ok");
    btnOk->setDefault(true);
    connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()));
    QPushButton *btnCancel = new QPushButton("Cancel");
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

    // button layout
    QHBoxLayout *layoutButtons = new QHBoxLayout();
    layoutButtons->addStretch(1);
    layoutButtons->addWidget(btnOk);
    layoutButtons->addStretch(1);
    layoutButtons->addWidget(btnCancel);
    layoutButtons->addStretch(1);

    // setup main layout
    QVBoxLayout *layoutMain = new QVBoxLayout();
    this->setLayout(layoutMain);
    layoutMain->addLayout(layoutGrid, 1);
    layoutMain->addSpacing(50);
    layoutMain->addLayout(layoutButtons);

}

void libblockdia::DialogEditHeader::slotWriteBlockData()
{
    this->block->setInstanceId(this->lineInstanceId.text().trimmed());
    this->block->setInstanceName(this->lineInstanceName.text().trimmed());
    this->block->setTypeId(this->lineTypeId.text().trimmed());
    this->block->setTypeName(this->lineTypeName.text().trimmed());
}
