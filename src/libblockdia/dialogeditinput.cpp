#include "dialogeditinput.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

libblockdia::DialogEditInput::DialogEditInput(libblockdia::Input *input, QWidget *parent) : QDialog(parent)
{
    // setup configuration
    this->input = input;
    this->setSizeGripEnabled(true);
    connect(this, SIGNAL(accepted()), this, SLOT(slotWriteData()));

    // load values from block
    this->lineEditName.setText(this->input->name());

    // edit layout
    QHBoxLayout *layoutEdit = new QHBoxLayout();
    layoutEdit->addWidget(new QLabel("Name"), 0);
    layoutEdit->addWidget(&this->lineEditName, 1);

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
    layoutMain->addLayout(layoutEdit, 1);
    layoutMain->addStretch(1);
    layoutMain->addLayout(layoutButtons);

}

void libblockdia::DialogEditInput::slotWriteData()
{
    this->input->setName(this->lineEditName.text().trimmed());
}