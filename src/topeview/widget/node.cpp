#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>


#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QAction>
#include <QMenu>
#include <QDebug>


int Node::Default_node_width=60;

//! [0]
Node::Node(GraphWidget *graphWidget)
    : graph(graphWidget),isHover(false)
{

    setCacheMode(DeviceCoordinateCache);

    setZValue(-1);

    //允许选择、发送状态改变事件、能够移动
    setFlags(ItemIsSelectable | ItemSendsGeometryChanges | ItemIsMovable);

    //允许接收鼠标悬停事件
    setAcceptsHoverEvents(true);


}
//! [0]

//! [1]
void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}
//! [1]

//! [2]
void Node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
    //! [2]

    //! [3]
    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
    foreach (QGraphicsItem *item, scene()->items()) {
        Node *node = qgraphicsitem_cast<Node *>(item);
        if (!node)
            continue;

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = 2.0 * (dx * dx + dy * dy);
        if (l > 0) {
            xvel += (dx * 100.0) / l;
            yvel += (dy * 100.0) / l;
        }
    }
    //! [3]

    //! [4]
    // Now subtract all forces pulling items together
    double weight = (edgeList.size() + 1) * Default_node_width;
    foreach (Edge *edge, edgeList) {

        QPointF vec;
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->destNode(), 0, 0);
        else
            vec = mapToItem(edge->sourceNode(), 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }
    //! [4]

    //! [5]
    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;
    //! [5]

    //! [6]
    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + Default_node_width/2), sceneRect.right() - Default_node_width/2));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + Default_node_width/2), sceneRect.bottom() - Default_node_width/2));
}
//! [6]

//! [7]
bool Node::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}
//! [7]

//! [8]
QRectF Node::boundingRect() const
{
    qreal adjust = 2;

    return QRectF( -Default_node_width/2 - adjust, -Default_node_width/2 - adjust-adjust-Default_node_width/2,
                   Default_node_width+3 + adjust, Default_node_width+3 + adjust+adjust+Default_node_width/2);
}
//! [8]

//! [9]
QPainterPath Node::shape() const
{
    QPainterPath path;

    path.addEllipse(-Default_node_width/2, -Default_node_width/2, Default_node_width, Default_node_width);

    return path;
}
//! [9]

//! [10]
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{


    painter->setPen(Qt::NoPen);


    //绘制阴影效果

     int offset=2;//阴影向下偏移量

     QRadialGradient gradientShadow(0,-offset, Default_node_width);

    gradientShadow.setCenter(0, -offset);
    gradientShadow.setColorAt(0, QColor(0,0,0,255));
    gradientShadow.setColorAt(1, QColor(0,0,0,0));
    painter->setBrush(gradientShadow);

    painter->drawEllipse(-(Default_node_width)/2, -(Default_node_width)/2+offset, Default_node_width, Default_node_width);


    QBrush brush;

    if (this->isHover) {
        //鼠标悬停颜色
        brush=QBrush(QColor(255, 127, 14));

    } else {

        brush=QBrush(QColor(23, 190, 207));

    }

    //绘制整体形状
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-Default_node_width/2, -Default_node_width/2, Default_node_width, Default_node_width);

    //绘制描述文字
    this->nodeInfo=(nodeInfo==NULL)?"":nodeInfo;

    QPen textPen(Qt::black);
    textPen.setStyle(Qt::SolidLine);

    //设置字体
    QFont f=painter->font();
    f.setPointSize(15);
    f.setPixelSize(15);
    f.setStretch(QFont::SemiExpanded);

    painter->setFont(f);
    painter->setPen(textPen);

    //计算字体高度，宽度，得出适合字体显示的矩形区域
    QFontMetrics mf =  painter->fontMetrics();

    QRectF textRect=mf.boundingRect(nodeInfo);

    int padding=3;


    textRect.adjust(-padding,-padding,padding,padding);
    textRect.translate(-textRect.center().x(),-Default_node_width/2-2*padding);

    painter->setBrush(Qt::NoBrush);

    //居中绘制文字
    painter->drawText(textRect,Qt::AlignHCenter,this->nodeInfo);


}
//! [10]

//! [11]
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {

    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
//! [11]

//! [12]
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->isHover=true;
    QGraphicsItem::hoverEnterEvent(event);

}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->isHover=false;
    QGraphicsItem::hoverLeaveEvent(event);
}



void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}


//! [12]
