#include "messageuitl.h"

#include <QDebug>

#define DEFAULT_TAG_NAME "ele"

MessageUitl::MessageUitl(QObject *parent) :
    QObject(parent)
{
}

QString MessageUitl::conetxt(QDomDocument *doc)
{
    return doc->toString();
}

QDomDocument *MessageUitl::parse(QString xmlContent)
{
    QDomDocument*doc=new QDomDocument;

    xmlContent=(xmlContent==NULL||xmlContent.trimmed().isEmpty())?"<root />":xmlContent;

    bool rc=doc->setContent(xmlContent);

    if(!rc){
        doc=new QDomDocument();
        doc->setContent(QString("<root />"));
    }

    return  doc;

}

QString MessageUitl::getStrByTagName(QDomDocument *doc, QString tageName, QString attrName)
{

    QDomNode e=getNodeByTagName(doc,tageName);


    if(e.isNull()){
        return "";
    }


    if(attrName!=NULL&&!attrName.trimmed().isEmpty()){

        return e.toElement().attribute(attrName);

    }else{

        return e.toElement().text();

    }

}

QList<QString> MessageUitl::getStrByTagName(QDomDocument *doc, QString ptageName, QString ctageName, QString attrName)
{

    QList<QString> list;

    QDomNode pnode=getNodeByTagName(doc,ptageName);

    if(!pnode.isNull()){

        QDomNodeList domList=pnode.toElement().elementsByTagName(ctageName);


        for(int i=0;i<domList.size();i++){

            QDomNode node=domList.at(i);

            if(node.isElement()){

                QString value;

                if(attrName==NULL||attrName.trimmed().isEmpty()){

                    value=node.toElement().text();
                }else{

                    value=node.toElement().attribute(attrName);
                }

                list.append(value);

            }

        }

    }

    return list;
}


int MessageUitl::addValue(QDomDocument *doc, QString tageName, QString attrName, QString value)
{

    QDomNode node=getNodeByTagName(doc,tageName);

    QDomElement ele;

    //cant find node with name tageName
    if(node.isNull()){

        ele=doc->createElement(tageName);
        doc->documentElement().appendChild(ele);

    }else{

        ele=node.toElement();

    }

    if(attrName==NULL||attrName.trimmed().isEmpty()){

        //node.setNodeValue(value);
        ele.removeChild(ele.childNodes().at(0));
        ele.appendChild(doc->createTextNode(value));

    }else{

        ele.setAttribute(attrName,value);

    }

    return 1;
}

int MessageUitl::addValues(QDomDocument *doc, QString ptagName, QString ctagName, QString attrName, QList<QString> values)
{


    QDomNode node=getNodeByTagName(doc,ptagName);

    QDomElement ele;

    //cant find node with name tageName
    if(node.isNull()){

        ele=doc->createElement(ptagName);
        doc->documentElement().appendChild(ele);

    }else{

        ele=node.toElement();

    }

    if(attrName==NULL||attrName.trimmed().isEmpty()){

        ele.setNodeValue("");

        foreach (QString str, values) {

            QDomElement cnode=doc->createElement(ctagName);
            cnode.appendChild(doc->createTextNode(str));
            ele.appendChild(cnode);
        }



    }else{

        ele.clear();

        foreach (QString str, values) {
            QDomElement cnode=doc->createElement(ctagName);
            cnode.setAttribute(attrName,str);
            ele.appendChild(cnode);
        }
    }

    return 1;

}

int MessageUitl::removeValue(QDomDocument *doc, QString tagName, QString attrName)
{

    QDomNode node=getNodeByTagName(doc,tagName);

    if(node.isNull()){
        return 0;
    }


    if(attrName==NULL){

        node.clear();

    }else{

        node.toElement().removeAttribute(attrName);

    }


    return 1;



}

QDomNode MessageUitl::getNodeByTagName(QDomDocument *doc, QString tagName)
{


    QDomNode node;

    QDomNodeList list=doc->elementsByTagName(tagName);

    if(list.size()>0){

        if(list.at(0).isElement()){

            node=list.at(0);
        }
    }

    return node;

}




