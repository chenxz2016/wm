#include "abstractitemdata.h"

#include <QMenu>

class AbstractItemDataPrivate
{
public:
    AbstractItemDataPrivate()
        :m_ref(1)
        ,m_onlineStatus(0)
        ,m_settingStatus(0)
        ,m_itemType(0)
        ,m_vipStatus(0)
        ,m_videoStatus(0)
        ,m_level(0)
    {}
    virtual ~AbstractItemDataPrivate(){}
    int m_ref;
    QList<int> m_data_type_list;
    QString m_name;
    QString m_iconPath;
    QPixmap m_iconPixmap;
    QDateTime m_dateTime;
    QString m_lastMessage;
    int m_onlineStatus;
    int m_settingStatus;
    int m_itemType;
    QString m_petName;
    QString m_sigment;
    int m_vipStatus;
    int m_videoStatus;
    QString m_spaceAction;
    int m_level;
    QMap<int,QVariant> m_lightActionMap;
    QString m_coverPath;
    QPixmap m_coverPixmap;
    QMap<int,QVariant> m_dataMap;
};

AbstractItemData::AbstractItemData(const QList<int> &list)
{
    p_d = new AbstractItemDataPrivate;
    p_d->m_data_type_list = list;
}

AbstractItemData::AbstractItemData(const AbstractItemData &data)
{
    if(data.p_d->m_ref)
    {}
}

AbstractItemData::~AbstractItemData()
{
    p_d->m_ref--;
    if(!p_d->m_ref)
        delete p_d;
}

void AbstractItemData::setData(int role, const QVariant &data)
{
    p_d->m_dataMap[role] = data;
}

QVariant AbstractItemData::data(int role) const
{
    return p_d->m_dataMap[role];
}

bool AbstractItemData::isExist(int data_type)
{
    if(p_d->m_lightActionMap.contains(data_type))
        return true;
    return false;
}

QString AbstractItemData::name() const
{
    return p_d->m_name;
}

QString AbstractItemData::iconPath() const
{
    return p_d->m_iconPath;
}

QPixmap AbstractItemData::iconPixmap() const
{
    return p_d->m_iconPixmap;
}

QDateTime AbstractItemData::dateTime() const
{
    return p_d->m_dateTime;
}

QString AbstractItemData::lastMessage() const
{
    return p_d->m_lastMessage;
}

int AbstractItemData::onlineStatus() const
{
    return p_d->m_onlineStatus;
}

int AbstractItemData::settingStatus() const
{
    return p_d->m_settingStatus;
}

int AbstractItemData::itemType() const
{
    return p_d->m_itemType;
}

QString AbstractItemData::petName() const
{
    return p_d->m_petName;
}

QString AbstractItemData::signment() const
{
    return p_d->m_sigment;
}

int AbstractItemData::vipStatus() const
{
    return p_d->m_vipStatus;
}

int AbstractItemData::videoStatus() const
{
    return p_d->m_videoStatus;
}

QString AbstractItemData::spaceAction() const
{
    return p_d->m_spaceAction;
}

int AbstractItemData::level() const
{
    return p_d->m_level;
}

QVariant AbstractItemData::lightAction(int index) const
{
    return p_d->m_lightActionMap[index];
}

QString AbstractItemData::coverPath() const
{
    return p_d->m_coverPath;
}

QPixmap AbstractItemData::coverPixmap() const
{
    return p_d->m_coverPixmap;
}

AbstractItemData::AbstractItemData()
{
    p_d = new AbstractItemDataPrivate;
}

