#ifndef DIALOGEDITPARAMETERINT_H
#define DIALOGEDITPARAMETERINT_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>

#include <blockparameterint.h>

namespace libblockdia {

class DialogEditParameterInt : public QDialog
{
    Q_OBJECT
public:
    explicit DialogEditParameterInt(BlockParameterInt *param, QWidget *parent = nullptr);

signals:

public slots:

private:
    BlockParameterInt *param;
    QLineEdit lineEditName;
    QCheckBox checkPublic;
    QLineEdit lineEditMin;
    QLineEdit lineEditMax;
    QLineEdit lineEditDefault;

private slots:
    void slotWriteData();
};

} // namespace libblockdia


#endif // DIALOGEDITPARAMETERINT_H
