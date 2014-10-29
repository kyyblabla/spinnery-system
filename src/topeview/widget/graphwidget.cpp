/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <QtGui>
#include <QDebug>
#include <QPixmap>
#include <QLayout>

#include <math.h>

static int Default_width=460;

static int Default_height=260;


//! [0]
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{

    //初始化场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    //设置场景
    setScene(scene);

    //缓存背景模式，提高绘制效率，防止闪屏
    setCacheMode(CacheBackground);

    setViewportUpdateMode(BoundingRectViewportUpdate);

    //设置抗锯齿，平滑图像或字体边缘
    setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);

    //允许节点位置动态调整
    setTransformationAnchor(AnchorUnderMouse);

    //允许上下文菜单
    setContextMenuPolicy(Qt::ActionsContextMenu);

    //允许拖拽滚屏
    setDragMode( QGraphicsView::ScrollHandDrag);

    setInteractive(true);

    setMinimumSize(Default_width, Default_height);

}
//! [1]

//! [2]
void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}
//! [2]




//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}
//! [5]

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{

}

void GraphWidget::drawForeground(QPainter *painter, const QRectF &rect)
{


}



//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::contextMenuEvent(QContextMenuEvent *event)
{

    QGraphicsView::contextMenuEvent(event);
    this->contentMenu->exec();

}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{

    QGraphicsView::mousePressEvent(event);

    foreach (QGraphicsItem *item, scene()->selectedItems()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item)){

            if(node->isSelected()){
                emit this->itemSelect(node->nodeId);
                break;
            }

        }
    }
}




//! [7]


void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}


Node *GraphWidget::getNodeById(QString nodeId)
{

    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item)){
            if(node->nodeId.compare(nodeId)==0){
                return node;
            }
        }
    }

    return NULL;

}

Edge *GraphWidget::getEdge(QString pid, QString cid)
{

    foreach (QGraphicsItem *item, scene()->items()) {
        if (Edge *edge = qgraphicsitem_cast<Edge *>(item)){
            bool e1=edge->sourceNode()->nodeId.compare(pid)==0;
            bool e2=edge->destNode()->nodeId.compare(cid)==0;

            if(e1&&e2){
                return edge;
            }

        }
    }

    return NULL;


}

void GraphWidget::addIcon()
{

}


void GraphWidget::addOrUpdateNode(QString cNodeId, QString nodetext)
{

    Node*cNode=getNodeById(cNodeId);

    if(cNode!=NULL){
        cNode->nodeInfo=nodetext;
        return;
    }

    cNode=new Node(this);

    cNode->nodeId=cNodeId;
    cNode->nodeInfo=nodetext;

    scene()->addItem(cNode);


}

void GraphWidget::addOrUpdateEdge(QString pId, QString cId)
{

    Node*pNode=getNodeById(pId);

    Node*cNode=getNodeById(cId);

    if(pNode==NULL||cNode==NULL){
        return;
    }

    //判断边是否存在,如果此条边已经存在，则不予添加
    if(getEdge(pNode->nodeId,cNode->nodeId)!=NULL){
        return;
    }

    int rx=pNode->pos().x()+Node::Default_node_width+qrand()%Node::Default_node_width;
    int ry=pNode->pos().x()+Node::Default_node_width+qrand()%Node::Default_node_width;

    cNode->setPos(rx,ry);

    Edge*edge=new Edge(pNode,cNode);
    scene()->addItem(edge);

    //itemMoved();


}


void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}


void GraphWidget::addChildNodes(QString pId, QString cId, QString nodetext)
{

    addOrUpdateNode(cId,nodetext);
    addOrUpdateEdge(pId,cId);

}

