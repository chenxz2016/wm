/* ************************************************************************
 *       Filename:  wmp_group.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_group.h"
#include<malloc.h>
#include<string.h>

#define WMP_GroupParamLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return NULL;

#define WMP_GroupLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return WMP_GROUP_PARSER_FAILED;


/* ***********************************************************************************
 * Allocate wmp_group_cet_t.
 *
 * @retval:	p_wmp_group_cet		wmp_group_cet_t pointer.
 *
 * ***********************************************************************************/
wmp_group_cet_t *allocate_wmp_group_cet()
{
	wmp_group_cet_t *p_wmp_group_cet = (wmp_group_cet_t *)malloc(sizeof(wmp_group_cet_t));
	memset(p_wmp_group_cet,0,sizeof(wmp_group_cet_t));
	return p_wmp_group_cet;
}

/* ***********************************************************************************
 * Deallocate wmp_group_cet_t.
 *
 * @param:	p_wmp_group_cet		wmp_group_cet_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_cet(wmp_group_cet_t **p_wmp_group_cet)
{
	if(p_wmp_group_cet && (*p_wmp_group_cet))
	{
		free((*p_wmp_group_cet));
		(*p_wmp_group_cet) = NULL;
	}
}


/* ***********************************************************************************
 * Allocate wmp_group_dsv_t.
 *
 * @retval:	p_wmp_group_dsv		wmp_group_dsv_t pointer.
 *
 * ***********************************************************************************/
wmp_group_dsv_t *allocate_wmp_group_dsv()
{
	wmp_group_dsv_t *p_wmp_group_dsv = (wmp_group_dsv_t *)malloc(sizeof(wmp_group_dsv_t));
	memset(p_wmp_group_dsv,0,sizeof(wmp_group_dsv_t));
	return p_wmp_group_dsv;
}

/* ***********************************************************************************
 * Deallocate wmp_group_dsv_t.
 *
 * @param:	p_wmp_group_dsv		wmp_group_dsv_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_dsv(wmp_group_dsv_t **p_wmp_group_dsv)
{
	if(p_wmp_group_dsv && (*p_wmp_group_dsv))
	{
		free((*p_wmp_group_dsv));
		(*p_wmp_group_dsv) = NULL;
	}
}


/* ***********************************************************************************
 * Allocate wmp_group_jon_t.
 *
 * @retval:	p_wmp_group_jon		wmp_group_jon_t pointer.
 *
 * ***********************************************************************************/
wmp_group_jon_t *allocate_wmp_group_jon()
{
	wmp_group_jon_t *p_wmp_group_jon = (wmp_group_jon_t *)malloc(sizeof(wmp_group_jon_t));
	memset(p_wmp_group_jon,0,sizeof(wmp_group_jon_t));
	return p_wmp_group_jon;
}

/* ***********************************************************************************
 * Deallocate wmp_group_jon_t.
 *
 * @param:	p_wmp_group_jon		wmp_group_jon_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_jon(wmp_group_jon_t **p_wmp_group_jon)
{
	if(p_wmp_group_jon && (*p_wmp_group_jon))
	{
		free((*p_wmp_group_jon));
		(*p_wmp_group_jon) = NULL;
	}
}

/* ***********************************************************************************
 * Allocate wmp_group_ext_t.
 *
 * @retval:	p_wmp_group_ext		wmp_group_ext_t pointer.
 *
 * ***********************************************************************************/
wmp_group_ext_t *allocate_wmp_group_ext()
{
	wmp_group_ext_t *p_wmp_group_ext = (wmp_group_ext_t *)malloc(sizeof(wmp_group_ext_t));
	memset(p_wmp_group_ext,0,sizeof(wmp_group_ext_t));
	return p_wmp_group_ext;	
}

/* ***********************************************************************************
 * Deallocate wmp_group_ext_t.
 *
 * @param:	p_wmp_group_ext		wmp_group_ext_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_ext(wmp_group_ext_t **p_wmp_group_ext)
{
	if(p_wmp_group_ext && (*p_wmp_group_ext))
	{
		free((*p_wmp_group_ext));
		(*p_wmp_group_ext) = NULL;
	}
}

/* ***********************************************************************************
 * Allocate wmp_group_set_t.
 *
 * @param:	num					wmp_group_set_t property numbers.
 *
 * @retval:	p_wmp_group_set		wmp_group_set_t pointer.
 *
 * ***********************************************************************************/
wmp_group_set_t *allocate_wmp_group_set(uint16_t num)
{
	wmp_group_set_t *p_wmp_group_set = (wmp_group_set_t *)malloc(sizeof(wmp_group_set_t));
	memset(p_wmp_group_set,0,sizeof(wmp_group_set_t));
	if(num)
	{
		p_wmp_group_set->property.property_num = num;
		p_wmp_group_set->property.properties = (wmp_group_property_t *)malloc(sizeof(wmp_group_property_t)*num);
		memset(p_wmp_group_set->property.properties,0,sizeof(wmp_group_property_t)*num);
	}
	return p_wmp_group_set;
}

/* ***********************************************************************************
 * Deallocate wmp_group_set_t.
 *
 * @param:	p_wmp_group_set		wmp_group_set_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_set(wmp_group_set_t **p_wmp_group_set)
{
	if(p_wmp_group_set && (*p_wmp_group_set) && (*p_wmp_group_set)->property.properties)
	{
		free((*p_wmp_group_set)->property.properties);
		(*p_wmp_group_set)->property.properties = NULL;
		free((*p_wmp_group_set));
		(*p_wmp_group_set) = NULL;
		return ;
	}
	if(p_wmp_group_set && (*p_wmp_group_set))
	{
		free((*p_wmp_group_set));
		(*p_wmp_group_set) = NULL;
	}
}

/* ***********************************************************************************
 * Set wmp_group_set_t property numbers.
 *
 * @param:	num					wmp_group_set_t property numbers.
 * @param:	p_wmp_group_set		wmp_group_set_t pointer.
 *
 * ***********************************************************************************/
void set_wmp_group_property_num(wmp_group_set_t *p_wmp_group_set,uint16_t num)
{
	if(!num || !p_wmp_group_set)
		return ;
	
	if(p_wmp_group_set->property.properties)
		free(p_wmp_group_set->property.properties);
	
	p_wmp_group_set->property.property_num = num;
	p_wmp_group_set->property.properties = (wmp_group_property_t *)malloc(sizeof(wmp_group_property_t)*num);
	memset(p_wmp_group_set->property.properties,0,sizeof(wmp_group_property_t)*num);
}


/* ***********************************************************************************
 * Allocate wmp_group_msg_t.
 *
 * @param:	msg_len				wmp_group_msg_t message length.
 *
 * @retval:	p_wmp_group_msg		wmp_group_msg_t pointer.
 *
 * ***********************************************************************************/
wmp_group_msg_t *allocate_wmp_group_msg(uint16_t msg_len)
{
	wmp_group_msg_t *p_wmp_group_msg = (wmp_group_msg_t *)malloc(sizeof(wmp_group_msg_t));
	memset(p_wmp_group_msg,0,sizeof(wmp_group_msg_t));
	if(msg_len)
	{
		p_wmp_group_msg->msg = (char *)malloc(msg_len);
		memset(p_wmp_group_msg->msg,0,msg_len);
		p_wmp_group_msg->msg_len = msg_len;
	}
	return p_wmp_group_msg;
}

/* ***********************************************************************************
 * Deallocate wmp_group_msg_t.
 *
 * @param:	p_wmp_group_msg		wmp_group_msg_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_msg(wmp_group_msg_t **p_wmp_group_msg)
{
	if(p_wmp_group_msg && (*p_wmp_group_msg) && (*p_wmp_group_msg)->msg)
	{
		free((*p_wmp_group_msg)->msg);
		(*p_wmp_group_msg)->msg = NULL;
		free((*p_wmp_group_msg));
		(*p_wmp_group_msg) = NULL;
		return ;
	}
	if(p_wmp_group_msg && (*p_wmp_group_msg))
	{
		free((*p_wmp_group_msg));
		(*p_wmp_group_msg) = NULL;
	}
}

/* ***********************************************************************************
 * Set wmp_group_msg_t property numbers.
 *
 * @param:	msg_len				wmp_group_msg_t message length.
 * @param:	p_wmp_group_msg		wmp_group_msg_t pointer.
 *
 * ***********************************************************************************/
void set_wmp_group_msg_len(wmp_group_msg_t *p_wmp_group_msg,uint16_t msg_len)
{
	if(!msg_len || !p_wmp_group_msg)
		return ;
	
	if(p_wmp_group_msg->msg)
		free(p_wmp_group_msg->msg);
	
	p_wmp_group_msg->msg = (char *)malloc(msg_len);
	memset(p_wmp_group_msg->msg,0,msg_len);
	p_wmp_group_msg->msg_len = msg_len;
}

/* ***********************************************************************************
 * Allocate wmp_group_fle_t.
 *
 * @param:	file_len			wmp_group_fle_t current file block length.
 *
 * @retval:	p_wmp_group_fle		wmp_group_fle_t pointer.
 *
 * ***********************************************************************************/
wmp_group_fle_t *allocate_wmp_group_fle(uint16_t file_len)
{
	wmp_group_fle_t *p_wmp_group_fle = (wmp_group_fle_t *)malloc(sizeof(wmp_group_fle_t));
	memset(p_wmp_group_fle,0,sizeof(wmp_group_fle_t));
	if(file_len)
	{
		p_wmp_group_fle->file_len = file_len;
		p_wmp_group_fle->file = (char *)malloc(file_len);
		memset(p_wmp_group_fle->file,0,file_len);
	}
	return p_wmp_group_fle;
}

/* ***********************************************************************************
 * Deallocate wmp_group_msg_t.
 *
 * @param:	p_wmp_group_msg		wmp_group_msg_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_fle(wmp_group_fle_t **p_wmp_group_fle)
{
	if(p_wmp_group_fle && (*p_wmp_group_fle))
	{
		free(*p_wmp_group_fle);
		(*p_wmp_group_fle) = NULL;
	}
}

/* ***********************************************************************************
 * Set wmp_group_fle_t property numbers.
 *
 * @param:	file_len			wmp_group_fle_t current file block length.
 * @param:	p_wmp_group_fle		wmp_group_fle_t pointer.
 *
 * ***********************************************************************************/
void set_wmp_group_fle_len(wmp_group_fle_t *p_wmp_group_fle,uint16_t file_len)
{
	if(!file_len || !p_wmp_group_fle)
		return ;
	
	if(p_wmp_group_fle->file)
		free(p_wmp_group_fle->file);
	
	p_wmp_group_fle->file = (char *)malloc(file_len);
	memset(p_wmp_group_fle->file,0,file_len);
	p_wmp_group_fle->file_len = file_len;
}

/* ***********************************************************************************
 * Allocate wmp_group_ntc_t.
 *
 * @param:	notice_len			wmp_group_ntc_t notice length.
 *
 * @retval:	p_wmp_group_ntc		wmp_group_ntc_t pointer.
 *
 * ***********************************************************************************/
wmp_group_ntc_t *allocate_wmp_group_ntc(uint16_t notice_len)
{
	wmp_group_ntc_t *p_wmp_group_ntc = (wmp_group_ntc_t *)malloc(sizeof(wmp_group_ntc_t));
	memset(p_wmp_group_ntc,0,sizeof(wmp_group_ntc_t));
	if(notice_len)
	{
		p_wmp_group_ntc->notice_len = notice_len;
		p_wmp_group_ntc->notice = (char *)malloc(notice_len);
		memset(p_wmp_group_ntc->notice,0,notice_len);
	}
	return p_wmp_group_ntc;
}

/* ***********************************************************************************
 * Deallocate wmp_group_ntc_t.
 *
 * @param:	p_wmp_group_ntc		wmp_group_ntc_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_ntc(wmp_group_ntc_t **p_wmp_group_ntc)
{
	if(p_wmp_group_ntc && (*p_wmp_group_ntc) && (*p_wmp_group_ntc)->notice)
	{
		free((*p_wmp_group_ntc)->notice);
		(*p_wmp_group_ntc)->notice = NULL;
		free(*p_wmp_group_ntc);
		(*p_wmp_group_ntc) = NULL;
		return ;
	}
	if(p_wmp_group_ntc && (*p_wmp_group_ntc))
	{
		free(*p_wmp_group_ntc);
		(*p_wmp_group_ntc) = NULL;
	}
}

/* ***********************************************************************************
 * Set wmp_group_ntc_t property numbers.
 *
 * @param:	notice_len			wmp_group_ntc_t notice length.
 * @param:	p_wmp_group_ntc		wmp_group_ntc_t pointer.
 *
 * ***********************************************************************************/
void set_wmp_group_ntc_len(wmp_group_ntc_t *p_wmp_group_ntc,uint16_t notice_len)
{
	if(!notice_len || !p_wmp_group_ntc)
		return ;
	
	if(p_wmp_group_ntc->notice)
		free(p_wmp_group_ntc->notice);
	
	p_wmp_group_ntc->notice = (char *)malloc(notice_len);
	memset(p_wmp_group_ntc->notice,0,notice_len);
	p_wmp_group_ntc->notice_len = notice_len;
}

/* ***********************************************************************************
 * Allocate wmp_group_ivt_t.
 *
 * @retval:	p_wmp_group_ivt		wmp_group_ivt_t pointer.
 *
 * ***********************************************************************************/
wmp_group_ivt_t *allocate_wmp_group_ivt()
{
	wmp_group_ivt_t *p_wmp_group_ivt = (wmp_group_ivt_t *)malloc(sizeof(wmp_group_ivt_t));
	memset(p_wmp_group_ivt,0,sizeof(wmp_group_ivt_t));
	return p_wmp_group_ivt;
}

/* ***********************************************************************************
 * Deallocate wmp_group_ivt_t.
 *
 * @param:	p_wmp_group_ivt		wmp_group_ivt_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group_ivt(wmp_group_ivt_t **p_wmp_group_ivt)
{
	if(p_wmp_group_ivt && (*p_wmp_group_ivt))
	{
		free(*p_wmp_group_ivt);
		(*p_wmp_group_ivt) = NULL;
	}
}


/* ***********************************************************************************
 * Allocate wmp_group_t.
 *
 * @retval:	p_wmp_group		wmp_group_t pointer.
 *
 * ***********************************************************************************/
wmp_group_t *allocate_wmp_group()
{
	wmp_group_t *p_wmp_group = (wmp_group_t *)malloc(sizeof(wmp_group_t));
	memset(p_wmp_group,0,sizeof(wmp_group_t));
	return p_wmp_group;
}

/* ***********************************************************************************
 * Deallocate wmp_group_t.
 *
 * @param:	p_wmp_group			wmp_group_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_group(wmp_group_t **p_wmp_group)
{
	if(p_wmp_group && (*p_wmp_group) && (*p_wmp_group)->param)
	{
		switch((*p_wmp_group)->id)
		{
			case WMP_GROUP_CET_ID:
				deallocate_wmp_group_cet((wmp_group_cet_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_DSV_ID:
				deallocate_wmp_group_dsv((wmp_group_dsv_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_JON_ID:
				deallocate_wmp_group_jon((wmp_group_jon_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_EXT_ID:
				deallocate_wmp_group_ext((wmp_group_ext_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_SET_ID:
				deallocate_wmp_group_set((wmp_group_set_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_MSG_ID:
				deallocate_wmp_group_msg((wmp_group_msg_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_FLE_ID:
				deallocate_wmp_group_fle((wmp_group_fle_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_NTC_ID:
				deallocate_wmp_group_ntc((wmp_group_ntc_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_IVT_ID:
				deallocate_wmp_group_ivt((wmp_group_ivt_t **)&((*p_wmp_group)->param));
				break;
		}
		free(*p_wmp_group);
		(*p_wmp_group) = NULL;
		return ;
	}
	
	if(p_wmp_group && (*p_wmp_group))
	{
		free(*p_wmp_group);
		*p_wmp_group = NULL;
	}
}

/* ***********************************************************************************
 * Parser wmp_group_parameter_t.
 *
 * @param:	p_wmp_group		wmp_group_t pointer.
 * @param:	package			protocol package.
 * @param:	pack_len		protocol package length.
 *
 * @retval:	index			wmp_group_parameter_t length.
 *
 * ***********************************************************************************/
static int parser_wmp_group_parameter(wmp_group_t *p_wmp_group,const char *package,uint32_t pack_len)
{
	uint32_t index = 0;
	wmp_group_ivt_t *p_wmp_group_ivt = 0;
	wmp_group_ntc_t *p_wmp_group_ntc = 0;
	wmp_group_fle_t *p_wmp_group_fle = 0;
	wmp_group_msg_t *p_wmp_group_msg = 0;
	wmp_group_set_t *p_wmp_group_set = 0;
	wmp_group_ext_t *p_wmp_group_ext = 0;
	wmp_group_jon_t *p_wmp_group_jon = 0;
	wmp_group_dsv_t *p_wmp_group_dsv = 0;
	wmp_group_cet_t *p_wmp_group_cet = 0;
	
	switch(p_wmp_group->id)
	{
		case WMP_GROUP_CET_ID:
			WMP_GroupLenCheck(index,6,pack_len)
			p_wmp_group_cet = allocate_wmp_group_cet();
			p_wmp_group_cet->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_cet->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_cet->result = *(uint8_t *)(package+index);
			index++;
			break;
		case WMP_GROUP_DSV_ID:
			WMP_GroupLenCheck(index,10,pack_len)
			p_wmp_group_dsv = allocate_wmp_group_dsv();
			p_wmp_group_dsv->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_dsv->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_dsv->result = *(uint8_t *)(package+index);
			index++;
			break;
		case WMP_GROUP_JON_ID:
			WMP_GroupLenCheck(index,7,pack_len)
			p_wmp_group_jon = allocate_wmp_group_jon();
			p_wmp_group_jon->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_jon->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_jon->result = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_jon->msg_len = *(uint8_t *)(package+index);
			index++;
			WMP_GroupLenCheck(index,p_wmp_group_jon->msg_len,pack_len)
			memcpy(p_wmp_group_jon->msg,package+index,p_wmp_group_jon->msg_len);
			index++;
			
			break;
		case WMP_GROUP_EXT_ID:
			WMP_GroupLenCheck(index,6,pack_len)
			p_wmp_group_ext = allocate_wmp_group_ext();
			p_wmp_group_ext->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_ext->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_ext->result = *(uint8_t *)(package+index);
			index++;
			break;
		case WMP_GROUP_SET_ID:
			WMP_GroupLenCheck(index,8,pack_len)
			p_wmp_group_set = allocate_wmp_group_set(0);
			p_wmp_group_set->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_set->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_set->result = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_set->property.property_num = ntohs(*(uint16_t *)(package+index));
			index+=2;
			set_wmp_group_property_num(p_wmp_group_set,p_wmp_group_set->property.property_num);
			for(uint16_t i=0;i<p_wmp_group_set->property.property_num;i++)
			{
				WMP_GroupLenCheck(index,3,pack_len)
				p_wmp_group_set->property.properties[i].id = ntohs(*(uint16_t *)(package+index));
				index++;
                p_wmp_group_set->property.properties[i].data_len = *(uint8_t *)(package+index);
                index++;
				WMP_GroupLenCheck(index,p_wmp_group_set->property.properties[i].data_len,pack_len)
				memcpy(p_wmp_group_set->property.properties[i].data,package+index,\
						p_wmp_group_set->property.properties[i].data_len);
				index+=p_wmp_group_set->property.properties[i].data_len;
			}
			break;
		case WMP_GROUP_MSG_ID:
			WMP_GroupLenCheck(index,8,pack_len)
			p_wmp_group_msg = allocate_wmp_group_msg(0);
			p_wmp_group_msg->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_msg->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_msg->result = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_msg->msg_len = ntohs(*(uint16_t *)(package+index));
			index+=2;
			WMP_GroupLenCheck(index,p_wmp_group_msg->msg_len,pack_len)
			memcpy(p_wmp_group_msg->msg,package+index,p_wmp_group_msg->msg_len);
			index+=p_wmp_group_msg->msg_len;
			break;
		case WMP_GROUP_FLE_ID:
			WMP_GroupLenCheck(index,11,pack_len)
			p_wmp_group_fle = allocate_wmp_group_fle(0);
			p_wmp_group_fle->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_fle->block = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_fle->sequence = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_fle->filename_len = *(uint8_t *)(package+index);
			index++;
			memcpy(p_wmp_group_fle->filename,package+index,p_wmp_group_fle->filename_len);
			index+=p_wmp_group_fle->filename_len;
			p_wmp_group_fle->file_len = ntohs(*(uint16_t *)(package+index));
			index+=2;
			WMP_GroupLenCheck(index,p_wmp_group_fle->file_len,pack_len)
			memcpy(p_wmp_group_fle->file,package+index,p_wmp_group_fle->file_len);
			index+=p_wmp_group_fle->file_len;
			break;
		case WMP_GROUP_NTC_ID:
			WMP_GroupLenCheck(index,3,pack_len)
			p_wmp_group_ntc = allocate_wmp_group_ntc(0);
			p_wmp_group_ntc->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_ntc->notice_len = ntohs(*(uint16_t *)(package+index));
			index+=2;
			set_wmp_group_ntc_len(p_wmp_group_ntc,p_wmp_group_ntc->notice_len);
			WMP_GroupLenCheck(index,p_wmp_group_ntc->notice_len,pack_len)
			memcpy(p_wmp_group_ntc->notice,package+index,p_wmp_group_ntc->notice_len);
			index+=p_wmp_group_ntc->notice_len;
			break;
		case WMP_GROUP_IVT_ID:
			WMP_GroupLenCheck(index,9,pack_len)
			p_wmp_group_ivt = allocate_wmp_group_ivt();
			p_wmp_group_ivt->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_ivt->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_ivt->invite_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			break;
	}
	return WMP_GROUP_PARSER_SUCCESS;
}

/* ***********************************************************************************
 * Parser wmp_group_t.
 *
 * @param:	package			protocol package.
 * @param:	pack_len		protocol package length.
 *
 * @retval:	p_wmp_group		wmp_group_t pointer.
 *
 * ***********************************************************************************/
wmp_group_t *parser_wmp_group(const char *package,uint32_t pack_len)
{
	uint32_t index = 0;
	WMP_GroupParamLenCheck(index,14,pack_len)
	
	wmp_group_t *p_wmp_group = allocate_wmp_group();
	
	p_wmp_group->src = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_group->src);
	
	p_wmp_group->dst = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_group->dst);
	
	p_wmp_group->id = ntohs(*(uint16_t *)(package+index));
	index+=sizeof(p_wmp_group->id);
	
	int ret = parser_wmp_group_parameter(p_wmp_group,package,pack_len-index);
	if(ret!=WMP_GROUP_PARSER_SUCCESS)
	{
		deallocate_wmp_group(&p_wmp_group);
		return NULL;
	}
	
	return p_wmp_group;
}

/* ***********************************************************************************
 * Package wmp_group_parameter_t.
 *
 * @param:	p_wmp_group		wmp_group_t pointer.
 * @param:	package			protocol package.
 *
 * @retval:	index			protocol package length.
 *
 * ***********************************************************************************/
static uint32_t package_wmp_group_parameter(wmp_group_t *p_wmp_group,char *package)
{
	uint32_t index = 0;
	wmp_group_ivt_t *p_wmp_group_ivt = NULL;
	wmp_group_ntc_t *p_wmp_group_ntc = NULL;
	wmp_group_fle_t *p_wmp_group_fle = NULL;
	wmp_group_msg_t *p_wmp_group_msg = NULL;
	wmp_group_set_t *p_wmp_group_set = NULL;
	wmp_group_ext_t *p_wmp_group_ext = NULL;
	wmp_group_jon_t *p_wmp_group_jon = NULL;
	wmp_group_dsv_t *p_wmp_group_dsv = NULL;
	wmp_group_cet_t *p_wmp_group_cet = NULL;
	
	switch(p_wmp_group->id)
	{
		case WMP_GROUP_CET_ID:
			p_wmp_group_cet = (wmp_group_cet_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_cet->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_cet->group_id);
			index+=4;
			*(uint8_t *)(package+index) = p_wmp_group_cet->result;
			index++;
			break;
		case WMP_GROUP_DSV_ID:
			p_wmp_group_dsv = (wmp_group_dsv_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_dsv->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_dsv->group_id);
			index+=4;
			*(uint8_t *)(package+index) = p_wmp_group_dsv->result;
			index++;
			break;
		case WMP_GROUP_JON_ID:
			p_wmp_group_jon = (wmp_group_jon_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_jon->attr;
			index++;
			*(uint32_t *)(package+index)= htonl(p_wmp_group_jon->group_id );
			index+=4;
			*(uint8_t *)(package+index) = p_wmp_group_jon->result;
			index++;
			*(uint8_t *)(package+index) = p_wmp_group_jon->msg_len;
			index++;
			memcpy(package+index,p_wmp_group_jon->msg,p_wmp_group_jon->msg_len);
			index+=p_wmp_group_jon->msg_len;
			
			break;
		case WMP_GROUP_EXT_ID:
			p_wmp_group_ext = (wmp_group_ext_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_ext->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_ext->group_id);
			index+=4;
			*(uint8_t *)(package+index) = p_wmp_group_ext->result;
			index++;
			break;
		case WMP_GROUP_SET_ID:
			p_wmp_group_set = (wmp_group_set_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_set->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_set->group_id);
			index+=4;
			*(uint8_t *)(package+index) = p_wmp_group_set->result;
			index++;
			*(uint16_t *)(package+index) = htons(p_wmp_group_set->property.property_num);
			index+=2;
			
			for(uint16_t i=0;i<p_wmp_group_set->property.property_num;i++)
			{
				*(uint16_t *)(package+index) = htons(p_wmp_group_set->property.properties[i].id);
				index++;
				*(uint16_t *)(package+index) = htons(p_wmp_group_set->property.properties[i].data_len);
				index+=2;
				memcpy(package+index,p_wmp_group_set->property.properties[i].data,\
					   p_wmp_group_set->property.properties[i].data_len);
					   
				index+=p_wmp_group_set->property.properties[i].data_len;
			}
			break;
		case WMP_GROUP_MSG_ID:
			p_wmp_group_msg = (wmp_group_msg_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_msg->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_msg->group_id);
			index+=4;
			*(uint8_t *)(package+index) = p_wmp_group_msg->result;
			index++;
			*(uint16_t *)(package+index) = htons(p_wmp_group_msg->msg_len);
			index+=2;
			memcpy(package+index,p_wmp_group_msg->msg,p_wmp_group_msg->msg_len);
			index+=p_wmp_group_msg->msg_len;
			break;
		case WMP_GROUP_FLE_ID:
			p_wmp_group_fle = (wmp_group_fle_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_fle->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_fle->block);
			index+=4;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_fle->sequence);
			index+=4;
			*(uint8_t *)(package+index) = p_wmp_group_fle->filename_len;
			index++;
			memcpy(package+index,p_wmp_group_fle->filename,p_wmp_group_fle->filename_len);
			index+=p_wmp_group_fle->filename_len;
			*(uint16_t *)(package+index) = ntohs(p_wmp_group_fle->file_len);
			index+=2;
			memcpy(package+index,p_wmp_group_fle->file,p_wmp_group_fle->file_len);
			index+=p_wmp_group_fle->file_len;
			break;
		case WMP_GROUP_NTC_ID:
			p_wmp_group_ntc = (wmp_group_ntc_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_ntc->attr;
			index++;
			*(uint16_t *)(package+index) = htons(p_wmp_group_ntc->notice_len);
			index+=2;
			memcpy(package+index,p_wmp_group_ntc->notice,p_wmp_group_ntc->notice_len);
			index+=p_wmp_group_ntc->notice_len;
			break;
		case WMP_GROUP_IVT_ID:
			p_wmp_group_ivt = (wmp_group_ivt_t *)p_wmp_group->param;
			*(uint8_t *)(package+index) = p_wmp_group_ivt->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_ivt->group_id);
			index+=4;
			*(uint32_t *)(package+index) = htonl(p_wmp_group_ivt->invite_id);
			index+=4;
			break;
		default:
			break;
	}
	return index;
}

/* ***********************************************************************************
 * Package wmp_group_t.
 *
 * @param:	p_wmp_group		wmp_group_t pointer.
 * @param:	package			protocol package.
 *
 * @retval:	index			protocol package length.
 *
 * ***********************************************************************************/
uint32_t package_wmp_group(char *package,wmp_group_t *p_wmp_group)
{
	uint32_t index = 0;
	
	*(uint32_t *)(package+index) = htonl(p_wmp_group->src);
	index+=sizeof(p_wmp_group->src);
	
	*(uint32_t *)(package+index) = htonl(p_wmp_group->dst);
	index+=sizeof(p_wmp_group->dst);
	
    *(uint16_t *)(package+index) = htons(p_wmp_group->id);
	index+=sizeof(p_wmp_group->id);
	
	index += package_wmp_group_parameter(p_wmp_group,package);
	
	return index;
}

static void print_wmp_group_property_data(const char *data,uint16_t data_len)
{
	printf("property data:\n");
	for(uint16_t i=0;i<data_len;i++)
		printf("%02x ",data[i]);
	printf("\n");
}

static void print_wmp_group_property(const wmp_group_set_property_t *property)
{
	printf("set property.\n");
	for(uint16_t i=0;i<property->property_num;i++)
	{
		printf("index[%d] id:%d;data_len:%d;\n",i,property->properties->id,\
				property->properties->data_len);
		print_wmp_group_property_data(property->properties->data,property->properties->data_len);
	}
}

/* ***********************************************************************************
 * Print wmp_group_t.
 *
 * @param:	p_wmp_group		wmp_group_t pointer.
 *
 * ***********************************************************************************/
void print_wmp_group(const wmp_group_t *p_wmp_group)
{
	if(!p_wmp_group)
	{
#ifdef WMP_DEBUG
		printf("wmp_group_t is null.\n");
#endif
		return ;
	}
	printf("***************************WM-group Protocol Start**********************\n");
	printf("src:%d;dst:%d;id:%d;",p_wmp_group->src,p_wmp_group->dst,p_wmp_group->id);

	wmp_group_ivt_t *p_wmp_group_ivt = NULL;
	wmp_group_ntc_t *p_wmp_group_ntc = NULL;
	wmp_group_fle_t *p_wmp_group_fle = NULL;
	wmp_group_msg_t *p_wmp_group_msg = NULL;
	wmp_group_set_t *p_wmp_group_set = NULL;
	wmp_group_ext_t *p_wmp_group_ext = NULL;
	wmp_group_jon_t *p_wmp_group_jon = NULL;
	wmp_group_dsv_t *p_wmp_group_dsv = NULL;
	wmp_group_cet_t *p_wmp_group_cet = NULL;
	switch(p_wmp_group->id)
	{
		
		case WMP_GROUP_CET_ID:
			p_wmp_group_cet = (wmp_group_cet_t *)p_wmp_group->param;
			if(!p_wmp_group_cet)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("create parameter.\n");
			printf("attr:%02x;group_id:%d;result:%d\n",p_wmp_group_cet->attr,\
					p_wmp_group_cet->group_id,p_wmp_group_cet->result);
			break;
		case WMP_GROUP_DSV_ID:
			p_wmp_group_dsv = (wmp_group_dsv_t *)p_wmp_group->param;
			if(!p_wmp_group_dsv)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("dissolve parameter.\n");
			printf("attr:%02x;group_id:%d;result:%d\n",p_wmp_group_dsv->attr,\
					p_wmp_group_dsv->group_id,p_wmp_group_dsv->result);
			break;
		case WMP_GROUP_JON_ID:
			p_wmp_group_jon = (wmp_group_jon_t *)p_wmp_group->param;
			if(!p_wmp_group_jon)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("join parameter.\n");
			printf("attr:%02x;group_id:%d;result:%d;msg_len:%d;msg:%s;\n",p_wmp_group_jon->attr,\
					p_wmp_group_jon->group_id,p_wmp_group_jon->result,p_wmp_group_jon->msg_len,\
					p_wmp_group_jon->msg);
			break;
		case WMP_GROUP_EXT_ID:
			p_wmp_group_ext = (wmp_group_ext_t *)p_wmp_group->param;
			if(!p_wmp_group_ext)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("exit parameter.\n");
			printf("attr:%02x;group_id:%d;result:%d\n",p_wmp_group_ext->attr,\
					p_wmp_group_ext->group_id,p_wmp_group_ext->result);
			break;
		case WMP_GROUP_SET_ID:
			p_wmp_group_set = (wmp_group_set_t *)p_wmp_group->param;
			if(!p_wmp_group_set)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("set parameter.\n");
			printf("attr:%02x;group_id:%d;result:%d,num:%d;",p_wmp_group_set->attr,\
					p_wmp_group_set->group_id,p_wmp_group_set->result,p_wmp_group_set->property.property_num);
			
			print_wmp_group_property(&(p_wmp_group_set->property));

			break;
		case WMP_GROUP_MSG_ID:
			p_wmp_group_msg = (wmp_group_msg_t *)p_wmp_group->param;
			if(!p_wmp_group_msg)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("message parameter.\n");
			printf("attr:%02x;group_id:%d;result:%d;msg_len:%d;msg:%s;\n",p_wmp_group_msg->attr,\
					p_wmp_group_msg->group_id,p_wmp_group_msg->result,p_wmp_group_msg->msg_len,\
					p_wmp_group_msg->msg);
			break;
		case WMP_GROUP_FLE_ID:
			p_wmp_group_fle = (wmp_group_fle_t *)p_wmp_group->param;
			if(!p_wmp_group_fle)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("file parameter.\n");
			printf("attr:%02x;block:%d;sequence:%d;filename_len:%d;filename:%s;file_len:%d;\n",\
					p_wmp_group_fle->attr,p_wmp_group_fle->block,p_wmp_group_fle->sequence,\
					p_wmp_group_fle->filename_len,p_wmp_group_fle->filename,p_wmp_group_fle->file_len);
			break;
		case WMP_GROUP_NTC_ID:
			p_wmp_group_ntc = (wmp_group_ntc_t *)p_wmp_group->param;
			if(!p_wmp_group_ntc)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("notice parameter.\n");
			printf("attr:%02x;notice_len:%d;notice:%s;\n",p_wmp_group_ntc->attr,\
					p_wmp_group_ntc->notice_len,p_wmp_group_ntc->notice);
			break;
		case WMP_GROUP_IVT_ID:
			p_wmp_group_ivt = (wmp_group_ivt_t *)p_wmp_group->param;
			if(!p_wmp_group_ivt)
			{
				printf("parameter is null.\n");
				break;
			}
			printf("invite parameter.\n");
			printf("attr:%02x;group_id:%d;invite_id:%d;\n",p_wmp_group_ivt->attr,\
					p_wmp_group_ivt->group_id,p_wmp_group_ivt->invite_id);
			break;
		default:
			printf("unknown parameter.\n");
			break;
	}
	
	printf("***************************WM-group Protocol End***********************\n");
}



