#include "exitdialog.h"
#include "ui_exitdialog.h"

#include <QPixmap>
#include <QPainter>

ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(accept()));

    this->back.load(":/mainrs/main_back.png");
}

ExitDialog::~ExitDialog()
{
    delete ui;
}

void ExitDialog::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);

    QPainter p(this);

    p.drawPixmap(0,0,this->width(),this->height(),back,0,0,this->width(),this->height());


}
