#ifndef DIALOGEDITINPUT_H
#define DIALOGEDITINPUT_H

#include <QDialog>
#include <QLineEdit>

#include <blockinput.h>

namespace libblockdia {

class DialogEditInput : public QDialog
{
    Q_OBJECT
public:
    explicit DialogEditInput(BlockInput *input, QWidget *parent = nullptr);

signals:

public slots:

private:
    BlockInput *input;
    QLineEdit lineEditName;

private slots:
    void slotWriteData();
};

} // namespace libblockdia


#endif // DIALOGEDITINPUT_H
