#ifndef DIALOGEDITINPUT_H
#define DIALOGEDITINPUT_H

#include <QDialog>
#include <QLineEdit>

#include <input.h>

namespace libblockdia {

class DialogEditInput : public QDialog
{
    Q_OBJECT
public:
    explicit DialogEditInput(Input *input, QWidget *parent = nullptr);

signals:

public slots:

private:
    Input *input;
    QLineEdit lineEditName;

private slots:
    void slotWriteData();
};

} // namespace libblockdia


#endif // DIALOGEDITINPUT_H
