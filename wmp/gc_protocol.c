/* ************************************************************************
 *       Filename:  gc_protocol.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"protocol_crypt.h"
#include"gc_protocol.h"
#include<string.h>
#include<malloc.h>

/* This is used to check len plus delt whether beyond length */
#define GC_Check_Length(len,delt,length)\
	if((len+delt)>length)\
		return GCP_PARSER_FAILED;


/* *********************************************************************************************
 *	Allocate gc_protocol_t structure.
 *
 *	@param:	 num		gc_protocol_t parameter numbers.
 *
 *	@retval: p_gc		The pointer to gc_protocol_t.
 *
 * *********************************************************************************************/
gc_protocol_t *allocate_gcp(uint16_t num)
{
	gc_protocol_t *p_gc = (gc_protocol_t *)malloc(sizeof(gc_protocol_t));
	memset(p_gc,0,sizeof(gc_protocol_t));
	p_gc->param_num = num;
	p_gc->param = 0;
	if(num)
	{
		p_gc->param_num = num;
		p_gc->param = malloc(sizeof(gc_parameter_t)*num);
		memset(p_gc->param,0,sizeof(gc_parameter_t)*num);
	}
	return p_gc;
}

/* *******************************************************************************************
 *	Deallocate gc_protocol_t structure.
 *
 *	@param:	p_gc		The pointer of gc_protocol_t's pointer needs to delete. *p_gc will be set 0,
 *					    if delete by this function.
 *
 * *******************************************************************************************/
void deallocate_gcp(gc_protocol_t **p_gc)
{
	gc_login_request_t *p_login_request = NULL;
	gc_login_on_t *p_login_on = NULL;
	gc_login_off_t *p_login_off = NULL;
	gc_login_register_t *p_login_register = NULL;
	gc_beat_heart_t *p_beat_heart = NULL;
	gc_request_groups_t *p_request_groups = NULL;
	gc_report_t *p_report = NULL;
	gc_subscribe_t *p_subscribe = NULL;

	if(p_gc && (*p_gc) && (*p_gc)->param)
	{
		for(int i=0;i<(*p_gc)->param_num;i++)
		{
			switch((*p_gc)->param[i].id)
			{
				case GCP_LOGIN_REQ_ID:
					deallocate_gcp_login_request((gc_login_request_t **)(&(*p_gc)->param[i].data));
					break;
				case GCP_LOGIN_ON_ID:
					deallocate_gcp_login_on((gc_login_on_t **)(&(*p_gc)->param[i].data));
					break;
				case GCP_LOGIN_OFF_ID:
					deallocate_gcp_login_off((gc_login_off_t **)(&(*p_gc)->param[i].data));
					break;
				case GCP_LOGIN_REGISTER_ID:
					deallocate_gcp_login_register((gc_login_register_t **)(&(*p_gc)->param[i].data));
					break;
				case GCP_BEAT_HEART_KEEPALIVE_ID:
					deallocate_gcp_beat_heart((gc_beat_heart_t **)(&(*p_gc)->param[i].data));
					break;
				case GCP_REQUEST_GROUP_ID:
				case GCP_REQUEST_ALL_GROUP_ID:
					deallocate_gcp_request_groups((gc_request_groups_t **)(&(*p_gc)->param[i].data));
					break;
				case GCP_REPORT_ERROR_ID:
				case GCP_REPORT_WARNING_ID:
					deallocate_gcp_report((gc_report_t **)(&(*p_gc)->param[i].data));
					break;
				case GCP_SUBSCRIBE_GROUP_ID:
				case GCP_CANCEL_SUBSCRIBE_GROUP_ID:
					deallocate_gcp_subscribe((gc_subscribe_t **)(&(*p_gc)->param[i].data));
					break;
			}
		}
		free((*p_gc)->param);
		(*p_gc)->param = NULL;
		free(*p_gc);
		(*p_gc) = NULL;
		return ;
	}

	if(p_gc && (*p_gc))
	{
		free(*p_gc);
		(*p_gc) = NULL;
	}
}

/* ******************************************************************************************
 *	Create a gc_login_on_t structure.
 *	@retval glo		The pointer of gc_protocol_t created. 
 *					The memory of gc_login_on_t will be set 0.
 * 
 * ******************************************************************************************/
gc_login_on_t *allocate_gcp_login_on()
{
	gc_login_on_t *p_login_on = (gc_login_on_t *)malloc(sizeof(gc_login_on_t));
	memset(p_login_on,0,sizeof(gc_login_on_t));
	return p_login_on;
}

/* *****************************************************************************************
 *	Delete a gc_login_on_t structure.
 *	@param glo		The pointer of gc_login_on_t's pointer needs to delete. *glo will be set 0,
 *					if deleted by this function.
 *
 * *****************************************************************************************/
void deallocate_gcp_login_on(gc_login_on_t **p_login_on)
{
	if(p_login_on && (*p_login_on))
	{
		free(*p_login_on);
		(*p_login_on) = NULL;
	}
}


/* ******************************************************************************************
 *	Create a gc_login_request_t structure.
 *	@retval req		The pointer of gc_login_request_t created. 
 *					The memory of gc_login_reqeust_t will be set 0.
 * 
 * ******************************************************************************************/
gc_login_request_t *allocate_gcp_login_request()
{
	gc_login_request_t *p_login_request = (gc_login_request_t *)malloc(sizeof(gc_login_request_t));
	memset(p_login_request,0,sizeof(gc_login_request_t));
	return p_login_request;
}

/* *****************************************************************************************
 *	Delete a gc_login_request_t structure.
 *	@param req		The pointer of gc_login_request_t's pointer needs to delete. *req will be set 0,
 *					if deleted by this function.
 *
 * *****************************************************************************************/
void deallocate_gcp_login_request(gc_login_request_t **p_login_request)
{
	if(p_login_request && (*p_login_request))
	{
		free(*p_login_request);
		(*p_login_request) = NULL;
	}
}


/* ******************************************************************************************
 *	Create a gc_login_off_t structure.
 *	@retval glo		The pointer of gc_login_off_t created. 
 *					The memory of gc_login_off_t will be set 0.
 * 
 * ******************************************************************************************/
gc_login_off_t *allocate_gcp_login_off()
{
	gc_login_off_t *p_login_off = (gc_login_off_t *)malloc(sizeof(gc_login_off_t));
	memset(p_login_off,0,sizeof(gc_login_off_t));
	return p_login_off;
}

/* *****************************************************************************************
 *	Delete a gc_login_off_t structure.
 *	@param glo		The pointer of gc_login_on_t's pointer needs to delete. *glo will be set 0,
 *					if deleted by this function.
 *
 * *****************************************************************************************/
void deallocate_gcp_login_off(gc_login_off_t **p_login_off)
{
	if(p_login_off && (p_login_off))
	{
		free(*p_login_off);
		(*p_login_off) = NULL;
	}
}

/* ******************************************************************************************
 *	Create a gc_login_register_t structure.
 *	@retval glr		The pointer of gc_register_t created. 
 *					The memory of gc_login_register_t will be set 0.
 * 
 * ******************************************************************************************/
gc_login_register_t *allocate_gcp_login_register()
{
	gc_login_register_t *p_login_register = (gc_login_register_t *)malloc(sizeof(gc_login_register_t));
	memset(p_login_register,0,sizeof(gc_login_register_t));
	return p_login_register;
}

/* *****************************************************************************************
 *	Delete a gc_login_register_t structure.
 *	@param glr		The pointer of gc_login_register_t's pointer needs to delete. *glr will be set 0,
 *					if deleted by this function.
 *
 * *****************************************************************************************/
void deallocate_gcp_login_register(gc_login_register_t **p_login_register)
{
	if(p_login_register && (*p_login_register))
	{
		free(*p_login_register);
		(p_login_register) = NULL;
	}
}

/* ******************************************************************************************
 *	Create a gc_beat_heart_t structure.
 *	@retval bh		The pointer of gc_beat_heart_t created. 
 *					The memory of gc_beat_heart_t will be set 0.
 * 
 * ******************************************************************************************/
gc_beat_heart_t *allocate_gcp_beat_heart()
{
	gc_beat_heart_t *p_beat_heart = (gc_beat_heart_t *)malloc(sizeof(gc_beat_heart_t));
	memset(p_beat_heart,0,sizeof(gc_beat_heart_t));
	return p_beat_heart;
}

/* *****************************************************************************************
 *	Delete a gc_beat_heart_t structure.
 *	@param bh		The pointer of gc_beat_heart_t's pointer needs to delete. *bh will be set 0,
 *					if deleted by this function.
 *
 * *****************************************************************************************/
void deallocate_gcp_beat_heart(gc_beat_heart_t **p_beat_heart)
{
	if(p_beat_heart && (*p_beat_heart))
	{
		free(*p_beat_heart);
		(*p_beat_heart) = NULL;
	}
}

/* ******************************************************************************************
 *	Create a gc_request_groups_t structure.
 *	@param	group_num	gourp info parameter number.
 *	@retval bh			The pointer of gc_request_groups_t created. 
 *						The memory of gc_request_groups_t will be set 0.
 * 
 * ******************************************************************************************/
gc_request_groups_t *allocate_gcp_request_groups(uint16_t num)
{
	gc_request_groups_t *p_request_groups = (gc_request_groups_t *)malloc(sizeof(gc_request_groups_t));
	memset(p_request_groups,0,sizeof(gc_request_groups_t));
	if(num)
	{
		p_request_groups->group_num = num;
		p_request_groups->groups_list = (gc_group_info_t *)malloc(sizeof(gc_group_info_t)*num);
		memset(p_request_groups->groups_list,0,sizeof(gc_group_info_t)*num);
	}
	return p_request_groups;
}

/* *****************************************************************************************
 *	Delete a gc_request_groups_t structure.
 *	@param req		The pointer of gc_request_groups_t's pointer needs to delete. *req will be set 0,
 *					if deleted by this function.
 *
 * *****************************************************************************************/
void deallocate_gcp_request_groups(gc_request_groups_t **p_request_groups)
{
	if(p_request_groups && (*p_request_groups) && (*p_request_groups)->groups_list)
	{
		free((*p_request_groups)->groups_list);
		(*p_request_groups)->groups_list = NULL;

		free(*p_request_groups);
		(*p_request_groups)=NULL;
		return ;
	}
	if(p_request_groups && (*p_request_groups))
	{
		free(*p_request_groups);
		(*p_request_groups)=NULL;
	}
}

/* ******************************************************************************************
 *	Set a gc_request_groups_t structure group info parameter numbers..
 *	@param	req			gc_request_groups_t needs to be set.
 *	@param	group_num	gourp info parameter number.
 * 
 * ******************************************************************************************/
void set_gcp_request_groups_num(gc_request_groups_t *p_request_groups,uint16_t num)
{
	if(!p_request_groups || !num)
		return ;

	if(p_request_groups->groups_list)
		free(p_request_groups->groups_list);

	p_request_groups->group_num = num;
	p_request_groups->groups_list = (gc_group_info_t *)malloc(sizeof(gc_group_info_t)*num);
	memset(p_request_groups->groups_list,0,sizeof(gc_group_info_t)*num);
}

/* *****************************************************************************************
 *	Create a gc_report_t structure.
 *	@retvalu rep	The pointer of gc_report_t structure reated. *rep will be set 0,
 *					The memory of gc_request_groups_t will be set 0.
 *
 * *****************************************************************************************/
gc_report_t *allocate_gcp_report()
{
	gc_report_t *p_report = (gc_report_t *)malloc(sizeof(gc_report_t));
	memset(p_report,0,sizeof(gc_report_t));
	return p_report;
}

/* *****************************************************************************************
 *	Delete a gc_report_t structure.
 *	@param rep		The pointer of gc_report_t's pointer needs to delete. *rep will be set 0,
 *					if deleted by this function.
 *
 * *****************************************************************************************/
void deallocate_gcp_report(gc_report_t **p_report)
{
	if(p_report && (*p_report))
	{
		free(*p_report);
		(*p_report) = NULL;
	}
}

/* *****************************************************************************************
 *	Create a gc_subscribe_t structure.
 *	@retvalu sub	The pointer of gc_subscribe_t structure reated. *rep will be set 0,
 *					The memory of gc_subscribe_t will be set 0.
 *
 * *****************************************************************************************/
gc_subscribe_t *allocate_gcp_subscribe()
{
	gc_subscribe_t *p_subscribe = (gc_subscribe_t *)malloc(sizeof(gc_subscribe_t));
	memset(p_subscribe,0,sizeof(gc_subscribe_t));
	return p_subscribe;
}

/* *****************************************************************************************
 *	Delete a gc_subscribe_t structure.
 *	@param sub		The pointer of gc_subscribe_t's pointer needs to delete. *sub will be set 0,
 *					if deleted by this function.
 *
 * *****************************************************************************************/
void deallocate_gcp_subscribe(gc_subscribe_t **p_subscribe)
{
	if(p_subscribe && (*p_subscribe))
	{
		free(*p_subscribe);
		(*p_subscribe) = NULL;
	}
}

/* *****************************************************************************************
 *	Set a gc_protocol_t structure parameter numbers.
 *	@param gc_p		The pointer of gc_protocol_t's pointer needs to be set.
 *	@param num		Parameter numbers.
 *
 * *****************************************************************************************/
void set_gcp_param_num(gc_protocol_t *p_gc,uint16_t num)
{
	if(!p_gc || !num)
		return ;

	if(p_gc->param)
	{
		for(int i=0;i<p_gc->param_num;i++)
		{
			switch(p_gc->param[i].id)
			{
				case GCP_LOGIN_REQ_ID:
					deallocate_gcp_login_request((gc_login_request_t **)(&(p_gc->param[i].data)));
					break;
				case GCP_LOGIN_ON_ID:
					deallocate_gcp_login_on((gc_login_on_t **)(&(p_gc->param[i].data)));
					break;
				case GCP_LOGIN_OFF_ID:
					deallocate_gcp_login_off((gc_login_off_t **)(&(p_gc->param[i].data)));
					break;
				case GCP_LOGIN_REGISTER_ID:
					deallocate_gcp_login_register((gc_login_register_t **)(&(p_gc->param[i].data)));
					break;
				case GCP_BEAT_HEART_KEEPALIVE_ID:
					deallocate_gcp_beat_heart((gc_beat_heart_t **)(&(p_gc->param[i].data)));
					break;
				case GCP_REQUEST_GROUP_ID:
				case GCP_REQUEST_ALL_GROUP_ID:
					deallocate_gcp_request_groups((gc_request_groups_t **)(&(p_gc->param[i].data)));
					break;
				case GCP_REPORT_ERROR_ID:
				case GCP_REPORT_WARNING_ID:
					deallocate_gcp_report((gc_report_t **)(&(p_gc->param[i].data)));
					break;
				case GCP_SUBSCRIBE_GROUP_ID:
				case GCP_CANCEL_SUBSCRIBE_GROUP_ID:
					deallocate_gcp_subscribe((gc_subscribe_t **)(&(p_gc->param[i].data)));
					break;
			}
		}
		free(p_gc->param);
	}

	p_gc->param_num = num;
	p_gc->param = (gc_parameter_t *)malloc(sizeof(gc_parameter_t)*num);
	memset(p_gc->param,0,sizeof(gc_parameter_t)*num);
}

/* *****************************************************************************************
 *	Check protocol_package head and tail flag.
 *	@param	package					The pointer of protocol_package.
 *	@retval GCP_PARSER_SUCCESS		The pointer of gc_protocol_t's pointer needs to be set.
 *	@retval GCP_PARSER_FAILED		Parameter numbers.
 *
 * *****************************************************************************************/
static int check_head_tail(const protocol_package *package)
{
	if(*(package->data)==GCP_HEAD_ID && *(package->data+package->length-1)==GCP_TAIL_ID)
		return GCP_PARSER_SUCCESS;
	return GCP_PARSER_FAILED;
}

/* *****************************************************************************************
 *	Check protocol_package head and tail flag.
 *	@param	gc_p					The pointer of gc_protocol_t.
 *	@param	buffer					The buffer of decrypted protocol package.
 *	@param	len						The length of decrypted protocol package.
 *
 *	@retval GCP_PARSER_FAILED		Function error.
 *	@retval index					If parser parameter successfuly, return the length of buffer.
 *
 * *****************************************************************************************/
static int parser_param(gc_protocol_t *p_gc,const char *buffer,uint32_t len)
{
	uint32_t index=0;
	for(int i=0;i<p_gc->param_num;i++)
	{
		GC_Check_Length(index,8,len)
		
		p_gc->param[i].id = ntohs(*(uint16_t *)(buffer+index));
		index+=2;
		p_gc->param[i].type = ntohs(*(uint16_t *)(buffer+index));
		index+=2;
		p_gc->param[i].length = ntohs(*(uint16_t *)(buffer+index));
		index+=2;
		gc_login_on_t *p_login_on = NULL;
		gc_login_off_t *p_login_off = NULL;
		gc_login_register_t *p_login_register = NULL;
		gc_beat_heart_t *p_beat_heart = NULL;
		gc_report_t *p_report = NULL;
		gc_subscribe_t *p_subscribe = NULL;
		gc_request_groups_t *p_request_groups = NULL;
		gc_login_request_t *p_login_request = NULL;
		switch(p_gc->param[i].id)
		{
			case GCP_LOGIN_REQ_ID:
				GC_Check_Length(index,5,len);

				p_login_request = allocate_gcp_login_request();
				p_gc->param[i].data = (char *)p_login_request;
				p_login_request->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_login_request->flag = *(uint8_t *)(buffer+index);
				index++;
				break;
			case GCP_LOGIN_ON_ID:
				if(GCP_AttrGC(p_gc)==GCP_CTG)
				{
					GC_Check_Length(index,5,len)
					p_login_on = allocate_gcp_login_on();
					p_gc->param[i].data = (char *)p_login_on;
					p_login_on->group_id = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					p_login_on->result = *(uint8_t *)(buffer+index);
					index++;
					break;
				}
				else if(GCP_AttrGC(p_gc)==GCP_GTC)
				{
					GC_Check_Length(index,16,len);
					p_login_on = allocate_gcp_login_on();
					p_gc->param[i].data = (char *)p_login_on;
					p_login_on->group_id = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					p_login_on->link_ip = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					p_login_on->link_port = ntohs(*(uint16_t *)(buffer+index));
					index+=2;
					p_login_on->open_ip = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					p_login_on->open_port = ntohs(*(uint16_t * )(buffer+index));
					index+=2;
					break;
				}
				return GCP_PARSER_FAILED;
			case GCP_LOGIN_OFF_ID:
				if(GCP_AttrGC(p_gc)==GCP_GTC)
				{
					GC_Check_Length(index,5,len);
					p_login_off = allocate_gcp_login_off();
					p_gc->param[i].data = (char *)p_login_off;
					p_login_off->group_id = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					p_login_off->reason = *(uint8_t *)(buffer+index);
					index++;
					break;
				}
				return GCP_PARSER_FAILED;
			case GCP_LOGIN_REGISTER_ID:
				if(GCP_AttrGC(p_gc)==GCP_CTG)
				{
					GC_Check_Length(index,5,len);
					p_login_register = allocate_gcp_login_register();
					p_gc->param[i].data = (char *)p_login_register;
					p_login_register->group_id = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					p_login_register->result = *(uint8_t *)(buffer+index);
					index++;
					if(p_login_register->result==GCP_LOGIN_REGISTER_SUCCESS_RESULT)
					{
						GC_Check_Length(index,1,len);
						p_login_register->key_len = *(uint8_t *)(buffer+index);
						index++;
						GC_Check_Length(index,p_login_register->key_len,len);
						memcpy(p_login_register->key,buffer+index,p_login_register->key_len);
						index+=p_login_register->key_len;
					}
					break;
				}
				else if(GCP_AttrGC(p_gc)==GCP_GTC)
				{
					GC_Check_Length(index,5,len);
					p_login_register = allocate_gcp_login_register();
					p_gc->param[i].data = (char *)p_login_register;
					p_login_register->group_id = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					p_login_register->key_len = *(uint8_t *)(buffer+index);
					index++;
					GC_Check_Length(index,p_login_register->key_len,len);
					memcpy(p_login_register->key,buffer+index,p_login_register->key_len);
					index+=p_login_register->key_len;
					break;
				}
				return GCP_PARSER_FAILED;
			case GCP_BEAT_HEART_KEEPALIVE_ID:
				GC_Check_Length(index,5,len);

				p_beat_heart = allocate_gcp_beat_heart();
				p_gc->param[i].data = (char *)p_beat_heart;
				p_beat_heart->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_beat_heart->flag = *(uint8_t *)(buffer+index);
				index++;
				break;
			case GCP_REPORT_WARNING_ID:
			case GCP_REPORT_ERROR_ID:
				GC_Check_Length(index,5,len);

				p_report = allocate_gcp_report();
				p_gc->param[i].data = (char *)p_report;
				p_report->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_report->reserve = *(uint8_t *)(buffer+index);
				index++;
				break;
			case GCP_REQUEST_GROUP_ID:
			case GCP_REQUEST_ALL_GROUP_ID:
				p_request_groups = allocate_gcp_request_groups(0);
				p_gc->param[i].data = (char *)p_request_groups;
				if(GCP_AttrGC(p_gc)==GCP_GTC)
				{
					GC_Check_Length(index,4,len);
					
					p_request_groups->group_id = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
				}
				else if(GCP_AttrGC(p_gc)==GCP_CTG)
				{
					GC_Check_Length(index,8,len);
					
					p_request_groups->group_id = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					p_request_groups->group_num = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
					GC_Check_Length(index,10*p_request_groups->group_num,len);
					
					set_gcp_request_groups_num(p_request_groups,p_request_groups->group_num);
					
					for(uint32_t j=0;j<p_request_groups->group_num;j++)
					{
						p_request_groups->groups_list[j].group_id = ntohl(*(uint32_t *)(buffer+index));
						index+=4;
						p_request_groups->groups_list[j].open_ip = ntohl(*(uint32_t *)(buffer+index));
						index+=4;
						p_request_groups->groups_list[j].open_port = ntohs(*(uint16_t *)(buffer+index));
						index+=2;
					}
				}
				break;
			case GCP_SUBSCRIBE_GROUP_ID:
			case GCP_CANCEL_SUBSCRIBE_GROUP_ID:
				GC_Check_Length(index,4,len);
				
				p_subscribe = allocate_gcp_subscribe();
				p_gc->param[i].data = (char *)p_subscribe;
				p_subscribe->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				break;
			default:
				break;
		}
	}

	return GCP_PARSER_SUCCESS;
}


/* *****************************************************************************************
 *	Parser group-center protocol package.
 *	@param	package					The pointer of protocol_package.
 *	@param	key						The key needs to decrypt.
 *	@param	key_len					The length of key.
 *	@retval GCP_PARSER_SUCCESS		Parser successfully.
 *	@retval GCP_PARSER_FAILED		Parser failed.
 *
 * *****************************************************************************************/
gc_protocol_t *parser_gcp(const protocol_package *package,const char *key,uint16_t key_len)
{
	if(!package)
	{
#ifdef GCP_DEBUG
		printf("[GCP] package is null.\n");
#endif
		return NULL;
	}

	if(check_head_tail(package)!=GCP_PARSER_SUCCESS)
	{
#ifdef GCP_DEBUG
		printf("Check head and tail.\n");
#endif
		return NULL;
	}

	if(package->length<15)
	{
#ifdef GGP_DEBUG
		printf("[GCP] length is short.\n");
#endif
		return NULL;
	}

	char *crypt_ptr = 0;
	uint32_t crypt_len=0;
	char buffer[1024]="";
	uint32_t len=sizeof(buffer);

	uint32_t index = 1;
	gc_protocol_t *p_gc = allocate_gcp(0);
	p_gc->attr = ntohs(*(uint16_t *)(package->data+index));
	index+=2;
	p_gc->crc_check = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	p_gc->sequence = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	p_gc->length = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	if(p_gc->length!=package->length)
	{
#ifdef GCP_DEBUG
		printf("[GCP] parser length failed,len:%d,index:%d\n",p_gc->length,index);
#endif
		deallocate_gcp(&p_gc);
		return NULL;
	}
	if(GCP_CRC32Flag(p_gc))
	{
		if(crc32_check_char_buffer(package->data+index,package->length-index-1)!=p_gc->crc_check)
		{
#ifdef GCP_DEBUG
			printf("[GCP] parser failed, crc32 check failed\n");
#endif
			deallocate_gcp(&p_gc);
			return NULL;
		}
	}
	if(GCP_CryptFlag(p_gc))
	{
		uint8_t crypt_alg = GCP_CryptAlg(p_gc);
		int ret = 0;
		switch(crypt_alg)
		{
			case GCP_CRYPT_ECC_ALG:
				ret = ecc_decrypt_char_buffer(package->data+index,package->length-index-1,\
											  buffer,(unsigned long *)&len,key,key_len);
				if(ret!=P_CRYPT_SUCCESS)
				{
#ifdef GCP_DEBUG
					printf("[GCP] parser failed, decrypt failed,ret:%d\n",ret);
#endif
					deallocate_gcp(&p_gc);
					return NULL;
				}
				break;
			case GCP_CRYPT_CBC_ALG:
				ret = cbc_decrypt_char_buffer(package->data+index,package->length-index-1,\
											  buffer,(unsigned long *)&len,key,key_len);
				if(ret!=P_CRYPT_SUCCESS)
				{
#ifdef GCP_DEBUG
					printf("[GCP] parser failed, decrypt failed,ret:%d\n",ret);
#endif
					deallocate_gcp(&p_gc);
					return NULL;
				}
				break;
			default:
				return NULL;
		}
		crypt_ptr = buffer;
		crypt_len = len;
		index=0;
	}
	else
	{
		crypt_ptr = package->data+index;
		crypt_len = package->length-1-index;
		index=0;
	}

	p_gc->main_id = ntohs(*(uint16_t *)(crypt_ptr+index));
	index+=2;
	p_gc->src = ntohl(*(uint32_t *)(crypt_ptr+index));
	index+=4;
	p_gc->dst = ntohl(*(uint32_t *)(crypt_ptr+index));
	index+=4;
	p_gc->param_num = ntohs(*(uint16_t *)(crypt_ptr+index));
	index+=2;

	set_gcp_param_num(p_gc,p_gc->param_num);
	
	if(parser_param(p_gc,crypt_ptr+index,crypt_len-index)!=GCP_PARSER_SUCCESS)
	{
#ifdef GCP_DEBUG
		printf("[GCP] parser parameters failed, main_id:%d\n",p_gc->main_id);
#endif
		deallocate_gcp(&p_gc);
		return 0;
	}

	return p_gc;
}

static uint16_t calculate_protocol_length(gc_protocol_t *p_gc)
{
	uint16_t len = GCP_PARAM_INDEX+1;
	for(int i=0;i<p_gc->param_num;i++)
	{
		len += 8;
		len += p_gc->param[i].length;
	}
	return len;	
}

static int package_param(const gc_protocol_t *p_gc,char *buffer)
{
	uint32_t index = 0;
	uint16_t *len_ptr = 0;
	for(uint16_t i=0;i<p_gc->param_num;i++)
	{
		*(uint16_t *)(buffer+index) = htons(p_gc->param[i].id);
		index+=2;
		*(uint16_t *)(buffer+index) = htons(p_gc->param[i].type);
		index+=2;
		len_ptr = (uint16_t *)(buffer+index);
		index+=2;

		gc_login_on_t *p_login_on=NULL;
		gc_login_off_t *p_login_off=NULL;
		gc_login_register_t *p_login_register=NULL;
		gc_beat_heart_t *p_beat_heart = NULL;
		gc_report_t *p_report = NULL;
		gc_subscribe_t *p_subscribe = NULL;
		gc_request_groups_t *p_request_groups = NULL;
		gc_login_request_t *p_login_request = NULL;

		switch(p_gc->param[i].id)
		{
			case GCP_LOGIN_REQ_ID:
				p_login_request = (gc_login_request_t *)p_gc->param[i].data;
				*(uint32_t *)(buffer+index) = htonl(p_login_request->group_id);
				index+=4;
				*(uint8_t *)(buffer+index) = p_login_request->flag;
				index++;
				*len_ptr = htons(5);
				break;
			case GCP_LOGIN_ON_ID:
				p_login_on = (gc_login_on_t *)p_gc->param[i].data;
				if(GCP_AttrGC(p_gc)==GCP_GTC)
				{
					*(uint32_t *)(buffer+index) = htonl(p_login_on->group_id);
					index+=4;
					*(uint32_t *)(buffer+index) = htonl(p_login_on->link_ip);
					index+=4;
					*(uint16_t *)(buffer+index) = htons(p_login_on->link_port);
					index+=2;
					*(uint32_t *)(buffer+index) = htonl(p_login_on->open_ip);
					index+=4;
					*(uint16_t *)(buffer+index) = htons(p_login_on->open_port);
					index+=2;
					*len_ptr = htons(16);
				}
				else if(GCP_AttrGC(p_gc)==GCP_CTG)
				{
					*(uint32_t *)(buffer+index) = htonl(p_login_on->group_id);
					index+=4;
					*(uint8_t *)(buffer+index) = p_login_on->result;
					index++;
					*len_ptr = htons(5);
				}
				break;
			case GCP_LOGIN_OFF_ID:
				p_login_off = (gc_login_off_t *)p_gc->param[i].data;
				*(uint32_t *)(buffer+index) = htonl(p_login_off->group_id);
				index+=4;
				*(uint8_t *)(buffer+index) = p_login_off->reason;
				index++;
				*len_ptr = htons(5);
				break;
			case GCP_LOGIN_REGISTER_ID:
				p_login_register = (gc_login_register_t *)p_gc->param[i].data;
				if(GCP_AttrGC(p_gc)==GCP_GTC)
				{
					*(uint32_t *)(buffer+index) = htonl(p_login_register->group_id);
					index+=4;
					*(uint8_t *)(buffer+index) = p_login_register->key_len;
					index++;
					memcpy(buffer+index,p_login_register->key,p_login_register->key_len);
					index+=p_login_register->key_len;
					*len_ptr = htons(4);
				}
				else if(GCP_AttrGC(p_gc)==GCP_CTG)
				{
					uint16_t len=5;
					*(uint32_t *)(buffer+index) = htonl(p_login_register->group_id);
					index+=4;
					*(uint8_t *)(buffer+index) = p_login_register->result;
					index++;
					if(p_login_register->result==GCP_LOGIN_REGISTER_SUCCESS_RESULT)
					{
						*(uint8_t *)(buffer+index) = p_login_register->key_len;
						index++;
						memcpy(buffer+index,p_login_register->key,p_login_register->key_len);
						index+=p_login_register->key_len;
						len=6+p_login_register->key_len;
					}
					*len_ptr = htons(len);
				}
				break;
			case GCP_BEAT_HEART_KEEPALIVE_ID:
				p_beat_heart = (gc_beat_heart_t *)p_gc->param[i].data;
				*(uint32_t *)(buffer+index) = htonl(p_beat_heart->group_id);
				index+=4;
				*(uint8_t *)(buffer+index) = p_beat_heart->flag;
				index++;
				*len_ptr = htons(5);
				break;
			case GCP_REPORT_ERROR_ID:
			case GCP_REPORT_WARNING_ID:
				p_report = (gc_report_t *)p_gc->param[i].data;
				*(uint32_t *)(buffer+index) = htonl(p_report->group_id);
				index+=4;
				*(uint8_t *)(buffer+index) = p_report->reserve;
				index++;
				*len_ptr = htons(5);
				break;
			case GCP_REQUEST_GROUP_ID:
			case GCP_REQUEST_ALL_GROUP_ID:
				p_request_groups = (gc_request_groups_t *)p_gc->param[i].data;
				if(GCP_AttrGC(p_gc)==GCP_GTC)
				{
					*(uint32_t *)(buffer+index) = htonl(p_request_groups->group_id);
					index+=4;
					*len_ptr = htons(4);
				}
				else if(GCP_AttrGC(p_gc)==GCP_CTG)
				{
					uint16_t len = 8;
					*(uint32_t *)(buffer+index) = htonl(p_request_groups->group_id);
					index+=4;
					*(uint32_t *)(buffer+index) = htonl(p_request_groups->group_num);
					index+=4;
					for(uint32_t j=0;j<p_request_groups->group_num;j++)
					{
						*(uint32_t *)(buffer+index) = htonl(p_request_groups->groups_list[j].group_id);
						index+=4;
						*(uint32_t *)(buffer+index) = htonl(p_request_groups->groups_list[j].open_ip);
						index+=4;
						*(uint16_t *)(buffer+index) = htons(p_request_groups->groups_list[j].open_port);
						index+=2;
						len+=10;
					}
					*len_ptr = htons(len);
				}
				break;
			case GCP_SUBSCRIBE_GROUP_ID:
			case GCP_CANCEL_SUBSCRIBE_GROUP_ID:
				p_subscribe = (gc_subscribe_t *)p_gc->param[i].data;
				*(uint32_t *)(buffer+index) = htonl(p_subscribe->group_id);
				index+=4;
				*len_ptr = htons(4);
				break;
		}
	}
	return index;
}

protocol_package *package_gcp(const gc_protocol_t *p_gc,const char *key,uint16_t key_len)
{
	uint32_t *crc_ptr = 0;
	uint32_t *len_ptr = 0;
	char uc_buffer[1024]="";
	uint32_t uc_index;
	char nc_buffer[1024]="";
	uint32_t nc_index = 0;
	char crypt_buffer[1024]="";
	uint32_t crypt_len = 0;
	int ret = 0;

	*(uint8_t *)(uc_buffer) = GCP_HEAD_ID;
	uc_index = 1;
	*(uint16_t *)(uc_buffer+uc_index) = htons(p_gc->attr);
	uc_index+=2;
	//*(uint32_t *)(uc_buffer+uc_index) = htonl(p_gc->crc_check);
	crc_ptr = (uint32_t *)(uc_buffer+uc_index);
	uc_index+=4;
	*(uint32_t *)(uc_buffer+uc_index) = htonl(p_gc->sequence);
	uc_index+=4;
	//*(uint32_t *)(uc_buffer+uc_index) = htonl(gc_p->length);
	len_ptr = (uint32_t *)(uc_buffer+uc_index);
	uc_index+=4;


	*(uint16_t *)(nc_buffer+nc_index) = htons(p_gc->main_id);
	nc_index+=2;
	*(uint32_t *)(nc_buffer+nc_index) = htonl(p_gc->src);
	nc_index+=4;
	*(uint32_t *)(nc_buffer+nc_index) = htonl(p_gc->dst);
	nc_index+=4;
	*(uint16_t *)(nc_buffer+nc_index) = htons(p_gc->param_num);
	nc_index+=2;
	
	nc_index += package_param(p_gc,nc_buffer+nc_index);

	if(GCP_CryptFlag(p_gc))
	{
		uint8_t crypt_alg = GCP_CryptAlg(p_gc);
		switch(crypt_alg)
		{
			case GCP_CRYPT_ECC_ALG:
				ret = ecc_encrypt_char_buffer(nc_buffer,nc_index,crypt_buffer,\
				  (unsigned long *)&crypt_len,key,key_len);
				if(ret!=P_CRYPT_SUCCESS)
				{
#ifdef GCP_DEBUG
					printf("[GCP] gc ecc encrypt failed,error:%d\n",ret);
#endif
					return NULL;
				}
				break;
			case GCP_CRYPT_CBC_ALG:
				ret = cbc_encrypt_char_buffer(nc_buffer,nc_index,crypt_buffer,\
				  (unsigned long *)&crypt_len,key,key_len);
				if(ret!=P_CRYPT_SUCCESS)
				{
#ifdef GCP_DEBUG
					printf("[GCP] gc cbc encrypt failed,error:%d\n",ret);
#endif
					return NULL;
				}
				break;
			default:
				return NULL;
		}

		if(GCP_CRC32Flag(p_gc))
			*crc_ptr = htonl(crc32_check_char_buffer(crypt_buffer,crypt_len));

		*len_ptr = htonl(crypt_len+uc_index+1);
		protocol_package *p = allocate_package(crypt_len+uc_index+1);
		memcpy(p->data,uc_buffer,uc_index);
		memcpy(p->data+uc_index,crypt_buffer,crypt_len);
		*(uint8_t *)(p->data+uc_index+crypt_len) = GCP_TAIL_ID;
		return p;
	}
	else
	{
		if(GCP_CRC32Flag(p_gc))
			*crc_ptr = htonl(crc32_check_char_buffer(nc_buffer,nc_index));

		*len_ptr = htonl(nc_index+uc_index+1);
		protocol_package *p = allocate_package(nc_index+uc_index+1);
		memcpy(p->data,uc_buffer,uc_index);
		memcpy(p->data+uc_index,nc_buffer,nc_index);
		*(uint8_t *)(p->data+uc_index+nc_index) = GCP_TAIL_ID;
		return p;
	}
}


gc_protocol_t *copy_gcp(gc_protocol_t *p_gc_src,int flag)
{
	gc_protocol_t *p_gc_dst = allocate_gcp(p_gc_src->param_num);
	
	if((flag & GCP_COPY_HEAD_FLAG) == GCP_COPY_HEAD_FLAG)
	{
		p_gc_dst->attr = p_gc_src->attr;
		p_gc_dst->crc_check = p_gc_src->crc_check;
		p_gc_dst->sequence = p_gc_src->sequence;
		p_gc_dst->length = p_gc_src->length;
		p_gc_dst->main_id = p_gc_src->main_id;
		p_gc_dst->src = p_gc_src->src;
		p_gc_dst->dst = p_gc_src->dst;
		p_gc_dst->param_num = 0;
		p_gc_dst->param = NULL;
	}
	if((flag & GCP_COPY_COPY_PARAM_FLAG) == GCP_COPY_COPY_PARAM_FLAG)
	{
		p_gc_dst->param_num = p_gc_src->param_num;
		for(int i=0;i<p_gc_src->param_num;i++)
		{
			p_gc_dst->param[i].id = p_gc_src->param[i].id;
			p_gc_dst->param[i].type = p_gc_src->param[i].type;
			p_gc_dst->param[i].length = p_gc_src->param[i].length;
			if(p_gc_src->param[i].data)
			{
				switch(p_gc_src->param[i].type)
				{
					case GCP_LOGIN_ON_ID:
						p_gc_dst->param[i].data = (char *)allocate_gcp_login_on();
						memcpy(p_gc_dst->param[i].data,p_gc_src->param[i].data,sizeof(gc_login_on_t));
						break;
					case GCP_LOGIN_OFF_ID:
						p_gc_dst->param[i].data = (char *)allocate_gcp_login_off();
						memcpy(p_gc_dst->param[i].data,p_gc_src->param[i].data,sizeof(gc_login_off_t));
						break;
					case GCP_LOGIN_REGISTER_ID:
						p_gc_dst->param[i].data = (char *)allocate_gcp_report();
						memcpy(p_gc_dst->param[i].data,p_gc_src->param[i].data,sizeof(gc_login_register_t));
						break;
					case GCP_BEAT_HEART_ID:
						p_gc_dst->param[i].data = (char *)allocate_gcp_beat_heart();
						memcpy(p_gc_dst->param[i].data,p_gc_src->param[i].data,sizeof(gc_beat_heart_t));
						break;
					case GCP_REPORT_ID:
						p_gc_dst->param[i].data = (char *)allocate_gcp_report();
						memcpy(p_gc_dst->param[i].data,p_gc_src->param[i].data,sizeof(gc_report_t));
						break;
				}
			}
		}
	}

	return p_gc_dst;
}

static void print_param(gc_parameter_t *param,int i)
{
	gc_login_on_t *p_login_on=NULL;
	gc_login_off_t *p_login_off=NULL;
	gc_login_register_t *p_login_register=NULL;
	gc_beat_heart_t *p_beat_heart=NULL;
	gc_report_t *p_report=NULL;
	gc_request_groups_t *p_request_groups = NULL;
	gc_group_info_t *p_group_info=NULL;

	printf("param[%d]\n",i);
	printf("id:%04x;",param[i].id);
	switch(param[i].type)
	{
		case GCP_TYPE_INT8_ID:
			printf("type:%d,Signed 8bit int;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%d;",*(int8_t *)param[i].data);
			break;
		case GCP_TYPE_UINT8_ID:
			printf("type:%d,Unsigned 8bit int;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%d;",*(int8_t *)param[i].data);
			break;
		case GCP_TYPE_INT16_ID:
			printf("type:%d,Signed 16bit int;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%hd;",*(int16_t *)param[i].data);
			break;
		case GCP_TYPE_UINT16_ID:
			printf("type:%d,Unsigned 16bit int;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%hu;",*(int16_t *)param[i].data);
			break;
		case GCP_TYPE_INT32_ID:
			printf("type:%d,Signed 32bit int;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%d;",*(int32_t *)param[i].data);
			break;
		case GCP_TYPE_UINT32_ID:
			printf("type:%d,Unsigned 32bit int;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%u;",*(uint32_t *)param[i].data);
			break;
		case GCP_TYPE_INT64_ID:
			printf("type:%d,Signed 64bit int;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%"PRId64";",*(int64_t *)param[i].data);
			break;
		case GCP_TYPE_UINT64_ID:
			printf("type:%d,Unsigned 64bit int;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%"PRIu64";",*(uint64_t *)param[i].data);
			break;
		case GCP_TYPE_BYTEARRAY_ID:
			printf("type:%d,Byte Array;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:[");
			for(int j=0;j<param[i].length;j++)
				printf("%x ",param[i].data[j]);
			printf("];");
			break;
		case GCP_TYPE_STRING_ID:
			printf("type:%d,String;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%s;",param[i].data);
			break;
		case GCP_TYPE_BCD_ID:
			printf("type:%d,BCD Code;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%s;",param[i].data);
			break;
		case GCP_TYPE_CUSTOM_ID:
			printf("type:%d,CUSTOM Code;",param[i].type);
			printf("length:%d;",param[i].length);
			switch(param[i].id)
			{
				case GCP_LOGIN_ON_ID:
					p_login_on=(gc_login_on_t *)param[i].data;
					printf("[login on]group_id:%d;\n",p_login_on->group_id);
					if(p_login_on->open_ip)
						printf("[login on]open_ip:%d;\n",p_login_on->open_ip);
					if(p_login_on->open_port)
						printf("[login on]open_port:%d;\n",p_login_on->open_port);
					if(p_login_on->link_ip)
						printf("[login on]link_ip:%d;\n",p_login_on->link_ip);
					if(p_login_on->link_port)
						printf("[login on]link_port:%d;\n",p_login_on->link_port);
					if(p_login_on->result)
						printf("[login on]result:%d;\n",p_login_on->result);
					break;
				case GCP_LOGIN_OFF_ID:
					p_login_off=(gc_login_off_t *)param[i].data;
					printf("[login off]group_id:%d;\n",p_login_off->group_id);
					printf("[login off]reason:%d;\n",p_login_off->reason);
					break;
				case GCP_LOGIN_REGISTER_ID:
					p_login_register=(gc_login_register_t *)param[i].data;
					printf("[login register]group_id:%d;\n",p_login_register->group_id);
					if(p_login_register->result)
						printf("[login register]result:%d;\n",p_login_register->result);
					if(p_login_register->key_len && p_login_register->key)
					{
						printf("[login register]key_len:%d;\n",p_login_register->key_len);
						printf("[login register]key:");
						for(uint8_t i=0;i<p_login_register->key_len;i++)
						{
							printf("%02x ",p_login_register->key[i]);
						}
						printf(";\n");
					}
					break;
				case GCP_REQUEST_GROUP_ID:
				case GCP_REQUEST_ALL_GROUP_ID:
					p_request_groups =(gc_request_groups_t *)param[i].data;
					printf("[request groups]group_id:%d;\n",p_request_groups->group_id);
					printf("[request groups]group_num:%d;\n",p_request_groups->group_num);
					for(uint16_t i=0;i<p_request_groups->group_num;i++)
					{
						printf("[request group][list(%d)]group_id:%d;open_ip:%d;open_port:%d\n",\
								i,p_request_groups->groups_list[i].group_id,p_request_groups->groups_list[i].open_ip,
								p_request_groups->groups_list[i].open_port);
					}
					break;
				case GCP_BEAT_HEART_KEEPALIVE_ID:
					p_beat_heart =(gc_beat_heart_t *)param[i].data;
					printf("[beat heart]group_id:%d;\n",p_beat_heart->group_id);
					printf("[beat heart]flag:%d;\n",p_beat_heart->flag);
					break;
				case GCP_REPORT_WARNING_ID:
					p_report=(gc_report_t *)param[i].data;
					printf("[report warning]warning:%d;\n",p_report->reserve);
					break;
				case GCP_REPORT_ERROR_ID:
					p_report=(gc_report_t *)param[i].data;
					printf("[report error]error:%d;\n",p_report->reserve);
					break;
			}
			break;
		default:
			printf("type:%d,Unknown type;",param[i].type);
			printf("length:%d;",param[i].length);
			printf("data:%s;",param[i].data);
			break;
	}
	printf("\n");
}

void print_gcp(gc_protocol_t *p_gc)
{
	if(!p_gc)
	{
		printf("gc_protocol is a null\n");
		return ;
	}
	printf("***********************Group Control Protocol Print Start**********************\n");
	printf("head:%02x;tail:%02x;attr:%d;sequence:%d;length:%d;main_id:%04x;src:%d;dst:%d\n",
			p_gc->head,p_gc->tail,p_gc->attr,p_gc->sequence,p_gc->length,p_gc->main_id,\
			p_gc->src,p_gc->dst);
	printf("parameter:\n");
	printf("param_num:%d\n",p_gc->param_num);
	for(int i=0;i<p_gc->param_num;i++)
	{
		printf("param num:%d\n",i);
		print_param(p_gc->param,i);
	}
	printf("***********************Group Control Protocol Print End************************\n");
}


