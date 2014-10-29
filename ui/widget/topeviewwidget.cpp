#include "topeviewwidget.h"
#include "ui_topeviewwidget.h"

#include "src/topeview/control/basenodemanager.h"
#include "src/topeview/control/parse.h"
#include "src/topeview/widget/graphwidget.h"

TopeViewWidget::TopeViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopeViewWidget)
{
    ui->setupUi(this);

    this->graphWidget=new GraphWidget;

    ui->widget->layout()->addWidget(graphWidget);

    //绑定节点点击事件
    connect(graphWidget,SIGNAL(itemSelect(QString)),this,SLOT(doNodeItemClick(QString)));


    this->nodeManager=new BaseNodeManager(graphWidget);


    //添加节点的两种方式

    //-------------------------------------
    //方式一 ：
    //以 NodeInfos 对象添加
    for(int i=0;i<10;i++){

        NodeInfos*node=new NodeInfos;
        //构造短地址，短地址用来指明节点之间的子父依赖关系
        node->shortAddr=QString("000")+QString::number(i);

        //长地址用来标示节点 id
        node->longAddr=QString("000000000000000")+QString::number(i);

        //父节点短地址
        node->pShortAddr=(i==0)?QString::number(0):QString::number(qrand()%i);
        node->pShortAddr=QString("000")+node->pShortAddr;

        //节点类型，0 标示一般子节点，1标示根节点
        if(i==0){
            node->type=1;
        }

        nodeManager->addNode(node);

    }

    //-------------------------------------
    //方式二 ：
    //义字符串形式添加节点,这个可以再关联通信时直接使用该方式将从通信接口中得到的数据进行添加
    nodeManager->parseAndAddNode("00001234567890ABCDEF0001");
    nodeManager->parseAndAddNode("00002234567890ABCDEF0002");

}

TopeViewWidget::~TopeViewWidget()
{
    delete ui;
}

QList<QString> TopeViewWidget::getNodeList()
{
    return this->nodeManager->getNodeInfoList();
}

//缩小
void TopeViewWidget::on_pushButton_2_clicked()
{
    graphWidget->zoomOut();
}

//放大
void TopeViewWidget::on_pushButton_clicked()
{
    graphWidget->zoomIn();
}

void TopeViewWidget::doNodeItemClick(QString itemId)
{
    //根据长地址获取节点信息
    NodeInfos *nodeInfo=this->nodeManager->getNodeInfoByNodeLongId(itemId);
    if(nodeInfo!=NULL){

        ui->label_long_addr->setText(tr("Long Addr:")+nodeInfo->longAddr);

        ui->label_short_addr->setText(tr("Short Addr:")+nodeInfo->shortAddr);

        ui->label_p_s_addr->setText(tr("Parent Addr:")+nodeInfo->pShortAddr);

    }


}

