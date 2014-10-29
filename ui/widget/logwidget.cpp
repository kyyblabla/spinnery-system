#include "logwidget.h"
#include "ui_logwidget.h"

#include <QDebug>

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::on_listWidget_itemSelectionChanged()
{

    int selectIndex=ui->listWidget->currentRow();

    if(selectIndex!=-1){

        emit this->selectIndexChange(selectIndex);

    }

}
