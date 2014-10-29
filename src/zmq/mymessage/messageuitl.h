#ifndef MESSAGEUITL_H
#define MESSAGEUITL_H


#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomAttr>
#include <QtXml/QDomDocument>
#include <QtXml/QDomProcessingInstruction>

#include <QObject>

class MessageUitl : public QObject
{
    Q_OBJECT
public:
    explicit MessageUitl(QObject *parent = 0);

    static QString conetxt(QDomDocument*doc);

    static QDomDocument*parse(QString xmlContent);

    static QString getStrByTagName(QDomDocument*doc, QString tageName, QString attrName);

    static QList<QString> getStrByTagName(QDomDocument*doc, QString ptageName,QString ctageName,QString attrName);

    static int addValue(QDomDocument*doc, QString tagName, QString attrName, QString value);

    static int addValues(QDomDocument*doc, QString ptagName,  QString ctagName,QString attrName, QList<QString> values);

    static int removeValue(QDomDocument*doc, QString tagName, QString attrName);
private:
    static QDomNode getNodeByTagName(QDomDocument*doc, QString tagName);
signals:

public slots:

};

#endif // MESSAGEUITL_H
