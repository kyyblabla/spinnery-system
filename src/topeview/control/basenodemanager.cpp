#include "basenodemanager.h"
#include "../widget/graphwidget.h"
#include "parse.h"

#include <QDebug>


BaseNodeManager::BaseNodeManager(GraphWidget *graphWidget)
{
    this->graphWidget=graphWidget;
}

QList<QString> BaseNodeManager::getNodeInfoList()
{
    QList<QString> list;

    foreach (NodeInfos*nodeInfo, this->nodeList) {

        QString info;

        if(nodeInfo->shortAddr==NULL){

            info=nodeInfo->longAddr+nodeInfo->pShortAddr+"00";

        }else{

            info=nodeInfo->pShortAddr+nodeInfo->longAddr+nodeInfo->shortAddr;
        }

        list.append(info);


    }
    return list;

}


void BaseNodeManager::addNode(NodeInfos *info)
{

    if(info==NULL){
        return;
    }

    //没有短地址,即节点请求短地址,或者添加的节点根节点
    if(info->shortAddr==NULL||info->type!=0){

        //根据该节点的长地址尝试从节点列表中获取重复节点
        NodeInfos*nodeInfoByNodeLongId=getNodeInfoByNodeLongId(info->longAddr);
        //当前地址节点列表中没有该节点
        if(nodeInfoByNodeLongId==NULL){
            nodeList.append(info);
        }
        //该短地址节点已经存在，需要修改节点信息
        else{
            //修改父节点地址
            nodeInfoByNodeLongId->pShortAddr=info->pShortAddr;
            //修改短节点地址
            nodeInfoByNodeLongId->shortAddr=info->shortAddr;
        }

    }
    //请求短地址成功
    else{

        //查找父节点信息
        NodeInfos*pnodeInfo=getNodeInfoByNodeShortId(info->pShortAddr);

        //查找到需要添加的节点
        NodeInfos*cnodeInfo=getNodeInfoByNodeLongId(info->longAddr);

        //父节点不存在，或本条信息表示的节点不存在，直接跳出
        if(pnodeInfo==NULL&&cnodeInfo==NULL){
            return;
        }

        if(cnodeInfo==NULL){
            nodeList.append(info);
        }else{
            //指定欲修改节点的短地址
            cnodeInfo->shortAddr=info->shortAddr;
            cnodeInfo->pShortAddr=info->pShortAddr;
        }
    }

    //更新节点显示状态
    this->updateNodeShows();

}

void BaseNodeManager::parseAndAddNode(QString text)
{
    //解析出节点信息
    NodeInfos*info= Parse::parse(text);

    //在view中添加节点
    addNode(info);

}


NodeInfos *BaseNodeManager::getNodeInfoByNodeShortId(QString id)
{

    foreach (NodeInfos*nodeInfo, this->nodeList) {

        if(strequals(nodeInfo->shortAddr,id)){
            return nodeInfo;
        }

    }
    return NULL;


}

NodeInfos *BaseNodeManager::getNodeInfoByNodeLongId(QString id)
{

    foreach (NodeInfos*nodeInfo, this->nodeList) {

        if(strequals(nodeInfo->longAddr,id)){
            return nodeInfo;
        }

    }
    return NULL;

}

void BaseNodeManager::updateNodeShows()
{
    foreach (NodeInfos*nodeInfo, this->nodeList) {

        //以节点长地址作为节点唯一标示
        //更新或增加节点
        graphWidget->addOrUpdateNode(nodeInfo->longAddr,nodeInfo->shortAddr);

        //没有短地址,或则为跟节点
        if(nodeInfo->shortAddr==NULL||nodeInfo->type!=0){

        }
        //存在短地址
        else{
            //获取父节点
            NodeInfos*pNodeInfo=getNodeInfoByNodeShortId(nodeInfo->pShortAddr);

            //找到父节点
            if(pNodeInfo!=NULL){

                //添加节点之间的连线
                graphWidget->addOrUpdateEdge(pNodeInfo->longAddr,nodeInfo->longAddr);
            }

        }
    }

}

bool BaseNodeManager::strequals(QString st1, QString st2)
{
    return st1.compare(st2)==0;
}
