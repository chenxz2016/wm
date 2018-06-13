#ifndef ABSTRACTITEMDATA_H
#define ABSTRACTITEMDATA_H

#include <QDateTime>
#include <QPixmap>
#include <QVariant>

class QMenu;

class AbstractItemData
{
public:
    AbstractItemData(const AbstractItemData &data);
    virtual ~AbstractItemData();

    void setData(int role,const QVariant &data);
    QVariant data(int role)const;

    virtual bool isExist(int data_type);

    QString name()const;

    QString iconPath()const;

    QPixmap iconPixmap()const;

    QDateTime dateTime()const;

    QString lastMessage()const;

    int onlineStatus()const;

    int settingStatus()const;

    int itemType()const;

    QString petName()const;

    QString signment()const;

    int vipStatus()const;

    int videoStatus()const;

    QString spaceAction()const;

    int level()const;

    QVariant lightAction(int index)const;

    QString coverPath()const;

    QPixmap coverPixmap()const;

protected:
    AbstractItemData();
    AbstractItemData(const QList<int> &list);

protected:
    class AbstractItemDataPrivate *p_d;

};

#endif // ABSTRACTITEMDATA_H
