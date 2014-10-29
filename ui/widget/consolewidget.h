#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>


class Message;

namespace Ui {
class ConsoleWidget;
}

class ConsoleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleWidget(QWidget *parent = 0);
    ~ConsoleWidget();
signals:
    void senMessage(QString addr,QString msg);

public slots:
    void getMessage(QString msg);

private slots:
    void on_pushButton_send_clicked();
    void on_pushButton_add_k_v_clicked();

private:
    Ui::ConsoleWidget *ui;

};

#endif // CONSOLEWIDGET_H
