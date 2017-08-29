#ifndef DIALOGEDITOUTPUT_H
#define DIALOGEDITOUTPUT_H

#include <QDialog>
#include <QLineEdit>

#include <blockoutput.h>

namespace libblockdia {

class DialogEditOutput : public QDialog
{
    Q_OBJECT
public:
    explicit DialogEditOutput(BlockOutput *output, QWidget *parent = nullptr);

signals:

public slots:

private:
    BlockOutput *output;
    QLineEdit lineEditName;

private slots:
    void slotWriteData();
};

} // namespace libblockdia


#endif // DIALOGEDITOUTPUT_H
