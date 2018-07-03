#include "csgroupprocess.h"
#include "clientservice.h"
#include "wmp_group.h"

class CSGroupProcessPrivate
{
public:
    CSGroupProcessPrivate(CSGroupProcess *parent)
        :p(parent)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_GROUP_ID);
    }

    CSGroupProcess *p;
};

CSGroupProcess::CSGroupProcess(quint32 id,ClientService *service)
    :AbstractCSProcess(service)
    ,p_d(new CSGroupProcessPrivate(this))
{
    p_d->init();
	setUserID(id);
}

CSGroupProcess::~CSGroupProcess()
{
    delete p_d;
}

bool CSGroupProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param_num)
    wmp_group_t *group = reinterpret_cast<wmp_group_t *>(param->data);

    switch(group->id)
    {
    case WMP_GROUP_CET_ID:
    {
        wmp_group_cet_t *cet = reinterpret_cast<wmp_group_cet_t *>(group->param);
        break;
    }
    case WMP_GROUP_DSV_ID:
    {
        wmp_group_dsv_t *dsv = reinterpret_cast<wmp_group_dsv_t *>(group->param);
        break;
    }
    case WMP_GROUP_JON_ID:
    {
        wmp_group_jon_t *jon = reinterpret_cast<wmp_group_jon_t *>(group->param);
        break;
    }
    case WMP_GROUP_EXT_ID:
    {
        wmp_group_ext_t *ext = reinterpret_cast<wmp_group_ext_t *>(group->param);
        break;
    }
    case WMP_GROUP_SET_ID:
    {
        wmp_group_set_t *set = reinterpret_cast<wmp_group_set_t *>(group->param);

        break;
    }
    case WMP_GROUP_MSG_ID:
    {
        wmp_group_msg_t *msg = reinterpret_cast<wmp_group_msg_t *>(group->param);
        break;
    }
    case WMP_GROUP_FLE_ID:
    {
        wmp_group_fle_t *fle = reinterpret_cast<wmp_group_fle_t *>(group->param);
        break;
    }
    case WMP_GROUP_NTC_ID:
    {
        wmp_group_ntc_t *ntc = reinterpret_cast<wmp_group_ntc_t *>(group->param);
        break;
    }
    case WMP_GROUP_IVT_ID:
    {
        wmp_group_ivt_t *ivt = reinterpret_cast<wmp_group_ivt_t *>(group->param);
        break;
    }
    case WMP_GROUP_LIST_ID:
    {
        wmp_group_list_t *group_list = reinterpret_cast<wmp_group_list_t *>(group->param);

        if(group_list->user_id != p_service->userID())
            break;

        QList<QVariant> list;
        for(quint16 i=0;i<group_list->group_num;i++)
            list.append(group_list->group_list[i]);

        appendPushData("opt",WM::CSGroupID);
        appendPushData("id",WMP_GROUP_LIST_ID);
        appendPushData("group_list",list);
        emit p_service->startUpdate(p_service);
        break;
    }
    case WMP_GROUP_FETCH_ID:
    {
        wmp_group_fetch_t *fetch = reinterpret_cast<wmp_group_fetch_t *>(group->param);

        if(fetch->group_id != p_service->userID())
            break;

        QList<QVariant> list;
        for(quint16 i=0;i<fetch->property_num;i++)
            list.append(fetch->properties[i].id);
        resetPushData();
        appendPushData("opt",WM::CSGroupID);
        appendPushData("id",WMP_GROUP_FETCH_ID);
        appendPushData("group_list",list);
        emit p_service->startUpdate(p_service);
        break;
    }
    default:
        break;
    }

    return true;
}

bool CSGroupProcess::syncSend(const QVariant &data)
{
    QMap<QString,QVariant> map = data.toMap();
    bool ok = true;
    quint32 dst = map["dst"].toInt();

    quint32 id = map["id"].toString().toInt(&ok);

    /* 2 parameters, user id and user pwd. */
    wm_protocol_t *proto = allocate_wmp(1);

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

    wmp_group_t *group = allocate_wmp_group();

    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(group);

    group->src = p_service->userID();
    group->dst = 0;
    group->id = id;

    switch(group->id)
    {
    case WMP_GROUP_CET_ID:
    {
        wmp_group_cet_t *cet = allocate_wmp_group_cet();
        group->param = cet;
        cet->attr = 0;
        cet->group_id = map["group_id"].toInt();
        break;
    }
    case WMP_GROUP_DSV_ID:
    {
        wmp_group_dsv_t *dsv = allocate_wmp_group_dsv();
        group->param = dsv;
        dsv->attr = 0;
        dsv->group_id = map["group_id"].toInt();
        break;
    }
    case WMP_GROUP_JON_ID:
    {
        wmp_group_jon_t *jon = allocate_wmp_group_jon();
        group->param = jon;
        jon->attr = 0;
        jon->group_id = map["group_id"].toInt();
        QString msg = map["msg"].toString();
        jon->msg_len = msg.length();
        memcpy(jon->msg,msg.toStdString().c_str(),jon->msg_len);
        break;
    }
    case WMP_GROUP_EXT_ID:
    {
        wmp_group_ext_t *ext = allocate_wmp_group_ext();
        group->param = ext;
        ext->attr = 0;
        ext->group_id = map["group_id"].toInt();
        break;
    }
    case WMP_GROUP_SET_ID:
    {
        QList<QVariant> list = map["list"].toList();
        if(!list.count())
            break;

        wmp_group_set_t *set = allocate_wmp_group_set(list.count());
        group->param = set;
        set->attr = 0;
        set->group_id = map["group_id"].toInt();
        for(uint16_t i = 0;i<set->property.property_num;i++)
        {
            QMap<QString,QVariant> map = list.at(i).toMap();
            set->property.properties->id = map["id"].toInt();
            QByteArray array = map["data"].toByteArray();
            memcpy(set->property.properties->data,array.data(),array.length());
            set->property.properties->data_len = array.length();
        }
        break;
    }
    case WMP_GROUP_MSG_ID:
    {
        QString message = map["msg"].toString();
        wmp_group_msg_t *msg = allocate_wmp_group_msg(message.length());
        group->param = msg;
        msg->attr = 0;
        msg->group_id = map["group_id"].toInt();
        memcpy(msg->msg,message.toStdString().c_str(),msg->msg_len);
        break;
    }
    case WMP_GROUP_FLE_ID:
    {
//        wmp_group_fle_t *fle;
        break;
    }
    case WMP_GROUP_NTC_ID:
    {
        QString notice = map["notice"].toString();
        wmp_group_ntc_t *ntc = allocate_wmp_group_ntc(notice.length());
        group->param = ntc;
        ntc->attr = 0;
        ntc->group_id = map["group_id"].toInt();
        memcpy(ntc->notice,notice.toStdString().c_str(),notice.length());
        break;
    }
    case WMP_GROUP_IVT_ID:
    {
        wmp_group_ivt_t *ivt = allocate_wmp_group_ivt();
        group->param = ivt;
        ivt->attr = 0;
        ivt->group_id = map["group_id"].toInt();
        ivt->invite_id = map["invite_id"].toInt();
        break;
    }
    case WMP_GROUP_LIST_ID:
    {
        wmp_group_list_t *group_list = allocate_wmp_group_list(0);
        group->param = group_list;
        group_list->attr = 0;
        group_list->user_id = p_service->userID();
        group_list->attr = map["attr"].toInt();
        break;
    }
    case WMP_GROUP_FETCH_ID:
    {
        wmp_group_fetch_t *fetch = allocate_wmp_group_fetch(0);
        group->param = fetch;
        fetch->attr = 0;
        fetch->group_id = p_service->userID();
        fetch->attr = map["attr"].toInt();
        break;
    }
    default:
        break;
    }

    bool ret = p_service->sendPackage(proto);
    if(!ret)
    {
        p_error = p_service->error();
        return false;
    }

    return true;
}

void CSGroupProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSGroupProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}
