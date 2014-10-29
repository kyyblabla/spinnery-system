#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>

class QPixmap;

namespace Ui {
class ExitDialog;
}

class ExitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExitDialog(QWidget *parent = 0);
    ~ExitDialog();
    void paintEvent(QPaintEvent *event);
private:
    Ui::ExitDialog *ui;
    QPixmap back;
};

#endif // EXITDIALOG_H
