#ifndef TOPEVIEWWIDGET_H
#define TOPEVIEWWIDGET_H

#include <QWidget>


class BaseNodeManager;
class GraphWidget;

namespace Ui {
class TopeViewWidget;
}

class TopeViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TopeViewWidget(QWidget *parent = 0);
    ~TopeViewWidget();
    QList<QString> getNodeList();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    //处理节点点击事件
    void doNodeItemClick(QString itemId);

private:
    Ui::TopeViewWidget *ui;
    BaseNodeManager*nodeManager;
    GraphWidget*graphWidget;
};

#endif // TOPEVIEWWIDGET_H
