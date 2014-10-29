#ifndef PARSE_H
#define PARSE_H

#include <QObject>

/**上传的数据信息
 * @brief The Infos class
 */
class NodeInfos{

public:
    NodeInfos()
    {
        type=0;
    }
    QString longAddr;  //长地址
    QString pShortAddr; //父节点短地址
    QString shortAddr;  //短地址
    int type;
};

class Parse : public QObject
{
    Q_OBJECT
public:
    explicit Parse(QObject *parent = 0);
    //解析
    static NodeInfos *parse(QString str);
signals:

public slots:

};

#endif // PARSE_H
