#include "dialogeditparameterint.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDialogButtonBox>

libblockdia::DialogEditParameterInt::DialogEditParameterInt(ParameterInt *param, QWidget *parent) : QDialog(parent)
{
    // setup configuration
    this->param = param;
    this->setSizeGripEnabled(true);
    connect(this, SIGNAL(accepted()), this, SLOT(slotWriteData()));

    // load values from block
    this->lineEditName.setText(this->param->name());
    this->checkPublic.setChecked(this->param->isPublic());
    this->lineEditMax.setText(QString::number(this->param->maximum()));
    this->lineEditMin.setText(QString::number(this->param->minimum()));

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

    // add max edit
    layoutGrid->addWidget(new QLabel("Maximum"), gridRowCount, 0, Qt::AlignRight);
    layoutGrid->addWidget(&this->lineEditMax, gridRowCount, 1);
    layoutGrid->setRowStretch(gridRowCount, 10);
    ++gridRowCount;

    // add min edit
    layoutGrid->addWidget(new QLabel("Minimum"), gridRowCount, 0, Qt::AlignRight);
    layoutGrid->addWidget(&this->lineEditMin, gridRowCount, 1);
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
    layoutMain->addStretch(1);
    layoutMain->addWidget(btnBox);

}

void libblockdia::DialogEditParameterInt::slotWriteData()
{
    this->param->setName(this->lineEditName.text().trimmed());
    this->param->setPublic(this->checkPublic.isChecked());
    this->param->setMaximum(this->lineEditMax.text().trimmed().toInt());
    this->param->setMinimum(this->lineEditMin.text().trimmed().toInt());
}
