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
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    return true;
}

bool CSGroupProcess::syncSend(const QVariant &data)
{
    QMap<QString,QVariant> map = data.toMap();
    bool ok = true;
    quint32 groupID = map["group_id"].toString().toInt(&ok);
    if(groupID<1000)
        return false;

    quint32 opt = map["group_opt"].toString().toInt(&ok);

    /* 2 parameters, user id and user pwd. */
    wm_protocol_t *proto = allocate_wmp(1);

    proto->base.proto_type = p_service->protoType();
    proto->base.src = p_userID;
    proto->base.dst = CS_SERVICE_ID;
    p_service->localDevice(proto->base.device);

    proto->base.network = p_service->network();
    proto->base.time = p_service->time();

    p_service->protoVersion(proto->base.version);

    wmp_group_t *group = allocate_wmp_group();

    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(group);

    group->src = p_userID;
    group->dst = groupID;
    group->id = opt;

    switch(opt)
    {
    case WMP_GROUP_CET_ID:
    {
        wmp_group_cet_t *cet = allocate_wmp_group_cet();
        cet->attr = 0;
        cet->group_id = groupID;
        group->param = reinterpret_cast<uint8_t *>(cet);
        break;
    }
    case WMP_GROUP_DSV_ID:
    {
        wmp_group_dsv_t *dsv = allocate_wmp_group_dsv();
        group->param = reinterpret_cast<uint8_t *>(dsv);
        dsv->attr = 0;
        dsv->group_id = groupID;
        break;
    }
    case WMP_GROUP_JON_ID:
    {
        wmp_group_jon_t *jon = allocate_wmp_group_jon();
        group->param = reinterpret_cast<uint8_t *>(jon);
        jon->attr = 0;
        jon->group_id = groupID;
        QString msg = map["msg"].toString();
        jon->msg_len = msg.length();
        memcpy(jon->msg,msg.toStdString().c_str(),jon->msg_len);
        break;
    }
    case WMP_GROUP_EXT_ID:
    {
        wmp_group_ext_t *ext = allocate_wmp_group_ext();
        group->param = reinterpret_cast<uint8_t *>(ext);
        ext->attr = 0;
        ext->group_id = groupID;
        break;
    }
    case WMP_GROUP_SET_ID:
    {
        QList<QVariant> list = map["list"].toList();
        if(!list.count())
            break;

        wmp_group_set_t *set = allocate_wmp_group_set(list.count());
        group->param = reinterpret_cast<uint8_t *>(set);
        set->attr = 0;
        set->group_id = groupID;
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
        group->param = reinterpret_cast<uint8_t *>(msg);
        msg->attr = 0;
        msg->group_id = groupID;
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
        group->param = reinterpret_cast<uint8_t *>(ntc);
        ntc->attr = 0;
        memcpy(ntc->notice,notice.toStdString().c_str(),notice.length());
        break;
    }
    case WMP_GROUP_IVT_ID:
    {
        quint32 invite_id = map["invite_id"].toInt();
        wmp_group_ivt_t *ivt = allocate_wmp_group_ivt();
        group->param = reinterpret_cast<uint8_t *>(ivt);
        ivt->attr = 0;
        ivt->group_id = groupID;
        ivt->invite_id = invite_id;
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
