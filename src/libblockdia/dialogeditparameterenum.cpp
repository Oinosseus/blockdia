#include "dialogeditparameterenum.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QStringList>

libblockdia::DialogEditParameterEnum::DialogEditParameterEnum(ParameterEnum *param, QWidget *parent) : QDialog(parent)
{
    // setup configuration
    this->param = param;
    this->setSizeGripEnabled(true);
    connect(this, SIGNAL(accepted()), this, SLOT(slotWriteData()));

    // load values from block
    this->lineEditName.setText(this->param->name());
    this->checkPublic.setChecked(this->param->isPublic());
    this->lineEditDefault.setText(this->param->strDefaultValue());

    // load enum items from block
    QStringList enumitems = this->param->enumItems();
    for (int i=0; i < enumitems.size(); ++i) {
        this->textEditEnumItems.appendPlainText(enumitems.at(i));
    }

    // create layout
    QGridLayout *layoutGrid = new QGridLayout();
    int gridRowCount = 0;

    // add header row
    layoutGrid->setColumnStretch(0, 0);
    layoutGrid->setColumnStretch(1, 1);
    layoutGrid->setRowStretch(gridRowCount, 0);
    ++gridRowCount;

    // add name edit
    layoutGrid->addWidget(new QLabel("Name"), gridRowCount, 0, Qt::AlignRight);
    layoutGrid->addWidget(&this->lineEditName, gridRowCount, 1);
    layoutGrid->setRowStretch(gridRowCount, 10);
    ++gridRowCount;

    // add public edit
    layoutGrid->addWidget(new QLabel("Public"), gridRowCount, 0, Qt::AlignRight);
    layoutGrid->addWidget(&this->checkPublic, gridRowCount, 1);
    layoutGrid->setRowStretch(gridRowCount, 10);
    ++gridRowCount;

    // add default edit
    layoutGrid->addWidget(new QLabel("Default"), gridRowCount, 0, Qt::AlignRight);
    layoutGrid->addWidget(&this->lineEditDefault, gridRowCount, 1);
    layoutGrid->setRowStretch(gridRowCount, 10);
    ++gridRowCount;

    // add enum items edit
    layoutGrid->addWidget(new QLabel("Items"), gridRowCount, 0 , Qt::AlignRight);
    layoutGrid->addWidget(&this->textEditEnumItems, gridRowCount, 1);
    layoutGrid->setRowStretch(gridRowCount, 10);
    ++gridRowCount;

    // buttons
    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));

    // setup main layout
    QVBoxLayout *layoutMain = new QVBoxLayout();
    this->setLayout(layoutMain);
    layoutMain->addLayout(layoutGrid, 1);
//    layoutMain->addStretch(1);
    layoutMain->addWidget(btnBox);

}

void libblockdia::DialogEditParameterEnum::slotWriteData()
{
    this->param->setName(this->lineEditName.text().trimmed());
    this->param->setPublic(this->checkPublic.isChecked());

    // enum items
    QStringList items = this->textEditEnumItems.toPlainText().split("\n");
    this->param->setEnumItems(items);

    // default value
    this->param->setDefaultValue(this->lineEditDefault.text().trimmed());
}
