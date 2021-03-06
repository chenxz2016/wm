#include "csuserprocess.h"
#include "clientservice.h"
#include "wmp_user.h"

#include <QTimer>
#include <QVector>
#include <QDebug>

static bool verify_team_info_fetch_full(quint16 team_num,const QVector<quint16> &vectors,QList<quint16> &list)
{
    if(!team_num || !vectors.count())
		return false;
	
	for(quint16 i=0;i<team_num;i++)
		list.append(i);
	
	foreach(quint16 i , vectors)
        list.removeAll(i);
		
	if(list.isEmpty())
		return true;
	
	return false;
}

class CSUserProcessPrivate
{
public:
    CSUserProcessPrivate(CSUserProcess *parent)
        :p(parent)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_USER_ID);
    }

    int timeout;
    CSUserProcess *p;
	
	quint16 teamNum;
	QVector<quint16> vectors;
	QVariant sendMeta;
	wm_protocol_t *cacheProto;
};

CSUserProcess::CSUserProcess(quint32 id,ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSUserProcessPrivate(this))
{
    p_d->init();
    setUserID(id);
}

CSUserProcess::~CSUserProcess()
{
    delete p_d;
}

bool CSUserProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    if(param_num!=1)
		return false;
	
	if(!param)
		return false;
	
    wmp_user_t *user = reinterpret_cast<wmp_user_t *>(param->data);
	if(!user)
		return false;
	
    if(user->dst != p_service->userID())
		return false;
	
	switch(user->id)
	{
    case WMP_USER_ADD_ID:
    {
        wmp_user_add_t *add = reinterpret_cast<wmp_user_add_t *>(user->param);
		resetPushData();
		appendPushData("opt",WM::CSUserID);
		appendPushData("src",user->src);
		appendPushData("user_id",user->id);
		appendPushData("user_add_attr",add->attr);
        appendPushData("msg",QString::fromLatin1(add->msg,add->msg_len));
		emit p_service->startUpdate(p_service);
        break;
    }
    case WMP_USER_DEL_ID:
    {
		wmp_user_del_t *del = reinterpret_cast<wmp_user_del_t *>(user->param);
		resetPushData();
		appendPushData("opt",WM::CSUserID);
		appendPushData("src",user->src);
		appendPushData("user_id",user->id);
        appendPushData("attr",del->attr);
		emit p_service->startUpdate(p_service);
        break;
    }
    case WMP_USER_SET_ID:
    {
        break;
    }
    case WMP_USER_MSG_ID:
    {
        wmp_user_msg_t *msg = reinterpret_cast<wmp_user_msg_t *>(user->param);
		resetPushData();
		appendPushData("opt",WM::CSUserID);
		appendPushData("src",user->src);
		appendPushData("user_id",user->id);
		appendPushData("attr",msg->attr);
        appendPushData("msg",QString::fromLatin1(msg->msg,msg->msg_len));
		emit p_service->startUpdate(p_service);
        break;
    }
	case WMP_USER_FRIEND_ID:
	{
        wmp_user_friend_t *friends = reinterpret_cast<wmp_user_friend_t *>(user->param);
        user->param = reinterpret_cast<uint8_t *>(friends);

		resetPushData();
        appendPushData("id",user->id);
		appendPushData("opt",WM::CSUserID);
		appendPushData("src",user->src);
		appendPushData("user_friend_attr",friends->attr);

		switch(friends->attr)
		{
			case WMP_USER_FRIEND_LIST_REQ:
				break;
			case WMP_USER_FRIEND_LIST_RSP:
			{
                appendPushData("team_name",QString::fromLatin1((char *)friends->team_name,friends->team_name_len));
				appendPushData("user_friend_team_index",friends->team_index);
				
				QList<QVariant> list;
                for(uint16_t i = 0;i<friends->friend_num;i++)
					list.append(friends->friend_list[i]);
				
				appendPushData("user_friend_list",list);
                qDebug() << "aaaaaaaaaaaaaa" ;
                break;
			}
			case WMP_USER_FRIEND_NUM_REQ:
				break;
			case WMP_USER_FRIEND_NUM_RSP:
				appendPushData("user_team_num",friends->team_num);
				break;
			default:
				break;
		}
		emit p_service->startUpdate(p_service);
		break;
	}
	case WMP_USER_FIND_ID:
	{
		break;
	}
	case WMP_USER_FETCH_ID:
	{
		break;
	}
    default:
        break;		
	}
	
    return true;
}

bool CSUserProcess::syncSend(const QVariant &data)
{
    QMap<QString,QVariant> map = data.toMap();
    quint32 id = map["id"].toInt();

    quint8 attr = map["attr"].toInt();
    if(!attr)
    {
        return false;
    }
	
    /* 2 parameters, user id and user pwd. */
    wm_protocol_t *proto = create_wmp(1);

	proto->head = WMP_HEAD_ID;
    proto->sequence = p_service->protoSequence();
    proto->tail = WMP_TAIL_ID;
	
    proto->base.proto_type = p_service->protoType();
	
    proto->base.src = p_service->userID();
    proto->base.dst = CS_SERVICE_ID;
    p_service->localDevice(proto->base.device);

    proto->base.network = p_service->network();
    proto->base.time = p_service->time();

    p_service->protoVersion(proto->base.version);

    wmp_user_t *user = create_wmp_user();
    proto->body.param_num = 1;
    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(user);

    user->src = p_service->userID();
    user->dst = map["dst"].toInt();
    user->id = id;

    switch(id)
    {
    case WMP_USER_ADD_ID:
    {
        wmp_user_add_t *add = create_wmp_user_add();
        user->param = reinterpret_cast<uint8_t *>(add);
        add->attr = map["attr"].toInt();
        QByteArray message = map["msg"].toByteArray();
        if(message.isEmpty())
        {
            delete_wmp(&proto);
            return false;
        }
        add->msg_len = message.length();
        memcpy(add->msg,message.data(),add->msg_len);
        break;
    }
    case WMP_USER_DEL_ID:
    {
        wmp_user_del_t *del = create_wmp_user_del();
        user->param = reinterpret_cast<uint8_t *>(del);
        del->attr = map["attr"].toInt();
        del->id = map["id"].toInt();
        break;
    }
    case WMP_USER_SET_ID:
    {
        QList<QVariant> list = map["list"].toList();
        wmp_user_set_t *set = create_wmp_user_set(list.count());
        user->param = reinterpret_cast<uint8_t *>(set);
        set->attr = map["attr"].toInt();
        for(uint16_t i = 0;i<set->property_num;i++)
        {
            QMap<QString,QVariant> m = list.at(i).toMap();
            QByteArray d = m["data"].toByteArray();
            set->property_list[i].id = m["id"].toInt();
            set->property_list[i].type = m["type"].toInt();
            set->property_list[i].len = d.length();
            memcpy(set->property_list[i].data,d.data(),d.length());
        }
        break;
    }
    case WMP_USER_MSG_ID:
    {
        QByteArray message = map["msg"].toByteArray();
        if(message.isEmpty())
        {
            delete_wmp(&proto);
            return false;
        }

        wmp_user_msg_t *msg = create_wmp_user_msg(message.length());
        user->param = reinterpret_cast<uint8_t *>(msg);
        msg->attr = map["attr"].toInt();
        memcpy(msg->msg,message.data(),message.length());
        break;
    }
	case WMP_USER_FRIEND_ID:
	{
        wmp_user_friend_t *friends = create_wmp_user_friend(0);
        user->param = reinterpret_cast<uint8_t *>(friends);
        friends->attr = map["user_friend_attr"].toInt();
        QTimer::singleShot(1000*20,this,SLOT(verifyFriendsNum()));
		break;
	}
    default:
        break;
    }

    bool ret = p_service->sendPackage(proto);
	//p_d->cacheProto = proto;
    if(!ret)
    {
        p_error = p_service->error();
        return false;
    }

    return true;
}

void CSUserProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSUserProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

int CSUserProcess::timeout() const
{
    return p_d->timeout;
}

void CSUserProcess::setTimeout(int timeout)
{
    p_d->timeout = timeout;
}

void CSUserProcess::verifyFriendsNum()
{
    QList<quint16> list;
    bool ret = verify_team_info_fetch_full(p_d->teamNum,p_d->vectors,list);
	if(!ret)
	{
		/* There is no any respond from server, resend request. */
		if(list.isEmpty())
		{
			static quint8 resend_time = 0;
			resend();
			resend_time++;
		}
		/* Did not receive party team from server, resend this team request. */
		else
		{
			
		}
	}
}

void CSUserProcess::resend()
{
	bool ret = p_service->sendPackage(p_d->cacheProto);
    if(!ret)
        p_error = p_service->error();
	
    QTimer::singleShot(1000*20,this,SLOT(verifyFriendsNum()));
}
