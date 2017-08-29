#ifndef DIALOGEDITPARAMETERSTR_H
#define DIALOGEDITPARAMETERSTR_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>

#include <blockparameterstr.h>

namespace libblockdia {

class DialogEditParameterStr : public QDialog
{
    Q_OBJECT
public:
    explicit DialogEditParameterStr(BlockParameterStr *param, QWidget *parent = nullptr);

signals:

public slots:

private:
    BlockParameterStr *param;
    QLineEdit lineEditName;
    QCheckBox checkPublic;
    QLineEdit lineEditDefault;

private slots:
    void slotWriteData();
};

} // namespace libblockdia


#endif // DIALOGEDITPARAMETERSTR_H
