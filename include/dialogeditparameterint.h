#ifndef DIALOGEDITPARAMETERINT_H
#define DIALOGEDITPARAMETERINT_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>

#include <parameterint.h>

namespace libblockdia {

class DialogEditParameterInt : public QDialog
{
    Q_OBJECT
public:
    explicit DialogEditParameterInt(ParameterInt *param, QWidget *parent = nullptr);

signals:

public slots:

private:
    ParameterInt *param;
    QLineEdit lineEditName;
    QCheckBox checkPublic;
    QLineEdit lineEditMin;
    QLineEdit lineEditMax;

private slots:
    void slotWriteData();
};

} // namespace libblockdia


#endif // DIALOGEDITPARAMETERINT_H
