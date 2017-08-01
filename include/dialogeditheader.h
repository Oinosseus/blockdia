#ifndef DIALOGEDITHEADER_H
#define DIALOGEDITHEADER_H

#include <QDialog>
#include <QLineEdit>
#include <QColor>
#include <QPushButton>

#include <block.h>

namespace libblockdia {

class DialogEditHeader : public QDialog
{
    Q_OBJECT
public:
    explicit DialogEditHeader(Block *block, QWidget *parent = nullptr);

signals:

public slots:

private:
    Block *block;
    QLineEdit lineInstanceName;
    QLineEdit lineInstanceId;
    QLineEdit lineTypeName;
    QLineEdit lineTypeId;
    QColor colorEdit;
    QPushButton btnColor;

private slots:
    void slotWriteBlockData();
    void slotColorDialog();
};

} // namespace libblockdia


#endif // DIALOGEDITHEADER_H
