#ifndef DIALOGEDITPARAMETERENUM_H
#define DIALOGEDITPARAMETERENUM_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QPlainTextEdit>

#include <parameterenum.h>

namespace libblockdia {

class DialogEditParameterEnum : public QDialog
{
    Q_OBJECT
public:
    explicit DialogEditParameterEnum(ParameterEnum *param, QWidget *parent = nullptr);

signals:

public slots:

private:
    ParameterEnum *param;
    QLineEdit lineEditName;
    QCheckBox checkPublic;
    QLineEdit lineEditDefault;
    QPlainTextEdit textEditEnumItems;

private slots:
    void slotWriteData();
};

} // namespace libblockdia


#endif // DIALOGEDITPARAMETERENUM_H
