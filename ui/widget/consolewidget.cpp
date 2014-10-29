#include "consolewidget.h"
#include "ui_consolewidget.h"


ConsoleWidget::ConsoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleWidget)
{
    ui->setupUi(this);

}

ConsoleWidget::~ConsoleWidget()
{
    delete ui;
}

void ConsoleWidget::getMessage(QString msg)
{
    ui->textEdit_2->append(msg);

}

void ConsoleWidget::on_pushButton_send_clicked()
{

    QString addr=ui->lineEdit_addr->text();
    QString text=ui->plainTextEdit->document()->toPlainText();

    if(!text.trimmed().isEmpty()){

        text="<root>"+text+"</root>";

        emit this->senMessage(addr,text);
    }
}

void ConsoleWidget::on_pushButton_add_k_v_clicked()
{
    QString key=ui->lineEdit->text();
    QString val=ui->lineEdit_2->text();

    QString line = key="<"+key+">"+val+"</"+key+">";

    ui->plainTextEdit->appendPlainText(line);

}
