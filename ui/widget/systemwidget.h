#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QWidget>

namespace Ui {
class SystemWidget;
}

class SystemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemWidget(QWidget *parent = 0);
    ~SystemWidget();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::SystemWidget *ui;
};

#endif // SYSTEMWIDGET_H
