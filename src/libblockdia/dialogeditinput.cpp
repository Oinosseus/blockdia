#include "dialogeditinput.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

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
    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));

    // setup main layout
    QVBoxLayout *layoutMain = new QVBoxLayout();
    this->setLayout(layoutMain);
    layoutMain->addLayout(layoutEdit, 1);
    layoutMain->addStretch(1);
    layoutMain->addWidget(btnBox);

}

void libblockdia::DialogEditInput::slotWriteData()
{
    this->input->setName(this->lineEditName.text().trimmed());
}
