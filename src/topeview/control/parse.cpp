#include "parse.h"


#define LONG_ADDR_LEN   16  //长地址
#define SHORT_ADDR_LEN  4   //短地址
#define END_INFO_LEN    2   //请求类型

Parse::Parse(QObject *parent) :
    QObject(parent)
{
}

NodeInfos* Parse::parse(QString str)
{


    if(str.endsWith("#")){

        str=str.left(str.lastIndexOf("#"));
        //return NULL;
    }

    str=str.right(str.length());

    //str=str.left(str.lastIndexOf("#"));

    int len=str.size();

    NodeInfos*n=new NodeInfos;

    switch (len) {
    //短地址请求
    case LONG_ADDR_LEN+SHORT_ADDR_LEN+END_INFO_LEN:

        n->longAddr=str.left(LONG_ADDR_LEN);
        n->pShortAddr=str.left(LONG_ADDR_LEN+SHORT_ADDR_LEN).right(SHORT_ADDR_LEN);
        //n->shortAddr=NULL;
        break;

     //请求响应
    case SHORT_ADDR_LEN+LONG_ADDR_LEN+SHORT_ADDR_LEN:

        n->longAddr=str.left(SHORT_ADDR_LEN+LONG_ADDR_LEN).right(LONG_ADDR_LEN);
        n->pShortAddr=str.left(SHORT_ADDR_LEN);
        n->shortAddr=str.right(SHORT_ADDR_LEN);
        break;
    default:
        n=NULL;
        break;
    }

    return n;

}
