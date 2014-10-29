#ifndef BASENODEMANAGER_H
#define BASENODEMANAGER_H

#include <QObject>
#include <QList>

class GraphWidget;
class NodeInfos;

class BaseNodeManager : public QObject
{
    Q_OBJECT
public:

    BaseNodeManager(GraphWidget *graphWidget);
    QList<QString> getNodeInfoList();
public slots:

    //添加节点
    void addNode(NodeInfos*info);

    //根据字符串解析出节点信息并添加节点
    void parseAndAddNode(QString text);

    NodeInfos*getNodeInfoByNodeLongId(QString id);
private:
    QList<NodeInfos*> nodeList;
    GraphWidget *graphWidget;
    NodeInfos*getNodeInfoByNodeShortId(QString id);

    //更新节点信息
    void updateNodeShows();
    bool strequals(QString st1,QString st2);

};

#endif // BASENODEMANAGER_H
