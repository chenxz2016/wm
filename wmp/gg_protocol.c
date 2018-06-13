/* ************************************************************************
 *       Filename:  gg_protocol.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"gg_protocol.h"
#include"protocol_crypt.h"
#include"crc32.h"
#include<malloc.h>
#include<string.h>

#define GGP_CheckLen(index,delt,len) \
	if((index+delt)>len) \
		return GGP_PARSER_FAILED;
	


/* ***********************************************************************************
 * Allocate gg_protocol_t.
 *
 * @param:	num		gg_protocol_t parameter numbers.
 *
 * @retval:	p_gg	The pointer of gg_protocol_t.
 *
 * ***********************************************************************************/
gg_protocol_t *allocate_ggp(uint16_t num)
{
	gg_protocol_t *p_gg = (gg_protocol_t *)malloc(sizeof(gg_protocol_t));
	memset(p_gg,0,sizeof(gg_protocol_t));
	if(num)
	{
		p_gg->param_num = num;
		p_gg->param = (gg_parameter_t *)malloc(sizeof(gg_parameter_t)*num);
		memset(p_gg->param,0,sizeof(gg_parameter_t)*num);
	}
	return p_gg;
}

/* ***********************************************************************************
 * Deallocate gg_protocol_t.
 *
 * @param:	p_gg		The pointer of gg_protocol_t  pointer.
 *
 * ***********************************************************************************/
void deallocate_ggp(gg_protocol_t **p_gg)
{
	if(p_gg && (*p_gg) && (*p_gg)->param)
	{
		for(uint16_t i=0;i<(*p_gg)->param_num;i++)
		{
			switch((*p_gg)->param[i].id)
			{
				case GGP_CONNECT_REQ_ID:
				case GGP_CONNECT_RSP_ID:
					deallocate_ggp_connect((gg_connect_t **)&((*p_gg)->param[i].data));
					break;
				case GGP_DISCONNECT_INFORM_ID:
					deallocate_ggp_disconnect((gg_disconnect_t **)&((*p_gg)->param[i].data));
					break;
				case GGP_BEAT_HEART_KEEPALIVE_ID:
					deallocate_ggp_beatheart((gg_beatheart_t **)&((*p_gg)->param[i].data));
					break;
				case GGP_UPDATE_ADD_REQ_ID:
				case GGP_UPDATE_ADD_RSP_ID:
				case GGP_UPDATE_DEL_REQ_ID:
				case GGP_UPDATE_DEL_RSP_ID:
					deallocate_ggp_update((gg_update_t **)&((*p_gg)->param[i].data));
					break;
				case GGP_TRANSACTION_BUSSINESS_REQ_ID:
				case GGP_TRANSACTION_BUSSINESS_RSP_ID:
					deallocate_ggp_tst((gg_transaction_t **)&((*p_gg)->param[i].data));
					break;
			}
		}

		free((*p_gg)->param);
		(*p_gg)->param = NULL;
		free(*p_gg);
		(*p_gg) = NULL;
		return ;
	}
	if(p_gg && (*p_gg))
	{
		free(*p_gg);
		(*p_gg) = NULL;
	}
}

/* ***********************************************************************************
 * Allocate gg_update_t.
 *
 * @param:	id_num		id number.
 *
 * @retval:	p_update	The pointer of gg_update_t.
 *
 * ***********************************************************************************/
gg_update_t *allocate_ggp_update(uint32_t id_num)
{
	gg_update_t *p_update = (gg_update_t *)malloc(sizeof(gg_update_t));
	memset(p_update,0,sizeof(gg_update_t));
	if(id_num)
	{
		p_update->id_list = (uint32_t *)malloc(sizeof(uint32_t)*id_num);
		p_update->id_num = id_num;
		memset(p_update->id_list,0,sizeof(uint32_t)*id_num);
	}
	return p_update;
}

/* ***********************************************************************************
 * Deallocate gg_update_t.
 *
 * @param:	p_update		The pointer of gg_update_t pointer.
 *
 * ***********************************************************************************/
void deallocate_ggp_update(gg_update_t **p_update)
{
	if(p_update && (*p_update) && (*p_update)->id_list)
	{
		free((*p_update)->id_list);
		(*p_update)->id_list = NULL;
		free(*p_update);
		(*p_update) = NULL;
		return ;
	}
	if(p_update && (*p_update))
	{
		free(*p_update);
		(*p_update) = NULL;
	}
}

/* ***********************************************************************************
 * Set gg_update_t id numbers.
 *
 * @param:	p_update		The pointer of gg_update_t pointer.
 * @param:	id_num			ID list numbers.
 *
 * ***********************************************************************************/
void set_ggp_update_num(gg_update_t *p_update,uint32_t id_num)
{
	if(!id_num || !p_update)
		return ;
	if(p_update->id_list)
		free(p_update->id_list);

	p_update->id_list = (uint32_t *)malloc(sizeof(uint32_t)*id_num);
	memset(p_update->id_list,0,sizeof(uint32_t)*id_num);
	p_update->id_num = id_num;
}

/* ***********************************************************************************
 * Allocate gg_connect_t.
 *
 * @retval:	p_gg_connect		The pointer of gg_disconnect_t pointer.
 *
 * ***********************************************************************************/
gg_connect_t *allocate_ggp_connect()
{
	gg_connect_t *p_gg_connect = (gg_connect_t *)malloc(sizeof(gg_connect_t));
	memset(p_gg_connect,0,sizeof(gg_connect_t));
	return p_gg_connect;
}

/* ***********************************************************************************
 * Deallocate gg_connect_t.
 *
 * @param:	p_gg_connect		The pointer of gg_connect_t pointer.
 *
 * ***********************************************************************************/
void deallocate_ggp_connect(gg_connect_t **p_connect)
{
	if(p_connect && (*p_connect))
	{
		free(*p_connect);
		(*p_connect)= NULL;
	}
}

/* ***********************************************************************************
 * Allocate gg_disconnect_t.
 *
 * @retval:	p_gg_disconnect		The pointer of gg_disconnect_t pointer.
 *
 * ***********************************************************************************/
gg_disconnect_t *allocate_ggp_disconnect()
{
	gg_disconnect_t *p_gg_disconnect = (gg_disconnect_t *)malloc(sizeof(gg_disconnect_t));
	memset(p_gg_disconnect,0,sizeof(gg_disconnect_t));
	return p_gg_disconnect;
}

/* ***********************************************************************************
 * Deallocate gg_disconnect_t.
 *
 * @param:	p_gg_disconnect		The pointer of gg_disconnect_t pointer.
 *
 * ***********************************************************************************/
void deallocate_ggp_disconnect(gg_disconnect_t **p_gg_disconnect)
{
	if(*p_gg_disconnect)
	{
		free(*p_gg_disconnect);
		*p_gg_disconnect = NULL;
	}
}

/* ***********************************************************************************
 * Allocate gg_beatheart_t.
 *
 * @retval:	p_gg_beatheart		gg_beatheart_t pointer.
 *
 * ***********************************************************************************/
gg_beatheart_t *allocate_ggp_beatheart()
{
	gg_beatheart_t *p_gg_beatheart = (gg_beatheart_t *)malloc(sizeof(gg_beatheart_t));
	memset(p_gg_beatheart,0,sizeof(gg_beatheart_t));
	return p_gg_beatheart;
}

/* ***********************************************************************************
 * Deallocate gg_beatheart_t.
 *
 * @param:	p_gg_beatheart		gg_transaction_t pointer.
 *
 * ***********************************************************************************/
void deallocate_ggp_beatheart(gg_beatheart_t **p_gg_beatheart)
{
	if(p_gg_beatheart && (*p_gg_beatheart))
	{
		free(*p_gg_beatheart);
		(*p_gg_beatheart) = NULL;
	}
}

/* ***********************************************************************************
 * Allocate gg_tansaction_t.
 *
 * @param:	len			The length of gg_transaction_t data.
 *
 * ***********************************************************************************/
gg_transaction_t *allocate_ggp_tst(uint32_t len)
{
	gg_transaction_t *p_gg_tst = (gg_transaction_t *)malloc(sizeof(gg_transaction_t));
	memset(p_gg_tst,0,sizeof(gg_transaction_t));

	if(len)
	{
		p_gg_tst->len = len;
		p_gg_tst->data = (char *)malloc(len);
		memset(p_gg_tst->data,0,len);
	}

	return p_gg_tst;
}

/* ***********************************************************************************
 * Deallocate gg_tansaction_t.
 *
 * @param:	p_gg_tst		the pointer of gg_transaction_t pointer.
 *
 * ***********************************************************************************/
void deallocate_ggp_tst(gg_transaction_t **p_gg_tst)
{
	if(p_gg_tst && (*p_gg_tst) && (*p_gg_tst)->data)
	{
		free((*p_gg_tst)->data);
		(*p_gg_tst)->data = NULL;
		free(*p_gg_tst);
		(*p_gg_tst) = NULL;
		return ;
	}
	if(p_gg_tst && (*p_gg_tst))
	{
		free(*p_gg_tst);
		(*p_gg_tst) = NULL;
	}
}

/* ***********************************************************************************
 * Set gg_tansaction_t data length.
 *
 * @param:	p			protocol package.
 *
 * @retval:	GGP_PARSER_FAILED
 * @retval:	GGP_PARSER_FAILED
 *
 * ***********************************************************************************/
void set_ggp_tst_len(gg_transaction_t *p_gg_tst,uint32_t len)
{
	if(!p_gg_tst || !len)
		return ;
	if(p_gg_tst->data)
		free(p_gg_tst->data);

	p_gg_tst->len = len;
	p_gg_tst->data = (char *)malloc(len);
	memset(p_gg_tst->data,0,len);
}

/* ***********************************************************************************
 * Check gg_protocol_t head and tail.
 *
 * @param:	p			protocol package.
 *
 * @retval:	GGP_PARSER_FAILED
 * @retval:	GGP_PARSER_FAILED
 *
 * ***********************************************************************************/
static int check_head_tail(const protocol_package *p)
{
	if(*(uint8_t *)p->data==GGP_HEAD_ID && *(uint8_t *)(p->data+p->length-1)==GGP_TAIL_ID)
		return GGP_PARSER_SUCCESS;
	return GGP_PARSER_FAILED;
}

/* ***********************************************************************************
 * Parser gg_protocol_t parameter.
 *
 * @param:	p			protocol package.
 * @param:	key			encrypt key.
 * @param:	key_len		encrypt key length.
 *
 * @retval:	p_gg		gg_protocol_t pointer.
 *
 * ***********************************************************************************/
static int parser_ggp_param(const char *buffer,uint32_t pack_len,gg_protocol_t *p_gg)
{
	uint32_t index = 0;
	gg_update_t *p_update = NULL;
	gg_connect_t *p_connect = NULL;
	gg_disconnect_t *p_disconnect = NULL;
	gg_beatheart_t *p_beatheart = NULL;
	gg_transaction_t *p_tst = NULL;

	set_ggp_param_num(p_gg,p_gg->param_num);

	for(uint32_t i=0;i<p_gg->param_num;i++)
	{
		p_gg->param[i].id = ntohs(*(uint16_t *)(buffer+index));
		index+=2;
		p_gg->param[i].attr = ntohs(*(uint16_t *)(buffer+index));
		index+=2;
		p_gg->param[i].length = ntohl(*(uint32_t *)(buffer+index));
		index+=4;
		switch(p_gg->param[i].id)
		{
			case GGP_UPDATE_ADD_REQ_ID:
			case GGP_UPDATE_DEL_REQ_ID:
				p_update = allocate_ggp_update(0);
				p_gg->param[i].data = (char *)p_update;
				p_update->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_update->type = ntohs(*(uint16_t *)(buffer+index));
				index+=2;
				p_update->id_num = ntohl(*(uint32_t *)(buffer+index));
				index+=4;

				set_ggp_update_num(p_update,p_update->id_num);

				GGP_CheckLen(index,p_update->id_num*4,pack_len)

				for(uint32_t i=0;i<p_update->id_num;i++)
				{
					p_update->id_list[i] = ntohl(*(uint32_t *)(buffer+index));
					index+=4;
				}
				break;
			case GGP_UPDATE_ADD_RSP_ID:
			case GGP_UPDATE_DEL_RSP_ID:
				GGP_CheckLen(index,5,pack_len)

				p_update = allocate_ggp_update(0);
				p_gg->param[i].data = (char *)p_update;
				p_update->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_update->result = *(uint8_t *)(buffer+index);
				index++;
				break;
			case GGP_CONNECT_REQ_ID:
				GGP_CheckLen(index,11,pack_len)
				p_connect = allocate_ggp_connect();
				p_gg->param[i].data = (char *)p_connect;
				p_connect->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_connect->open_ip = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_connect->open_port = ntohs(*(uint16_t *)(buffer+index));
				index+=2;
				p_connect->key_len = *(uint8_t *)(buffer+index);
				index++;
				GGP_CheckLen(index,p_connect->key_len,pack_len)

				memcpy(p_connect->key,buffer+index,p_connect->key_len);
				index+=p_connect->key_len;;
				break;
			case GGP_CONNECT_RSP_ID:
				GGP_CheckLen(index,5,pack_len)
				p_connect = allocate_ggp_connect();
				p_gg->param[i].data = (char *)p_connect;
				p_connect->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_connect->result = *(uint8_t *)(buffer+index);
				index++;
				break;
			case GGP_DISCONNECT_INFORM_ID:
				GGP_CheckLen(index,5,pack_len)
				p_disconnect = allocate_ggp_disconnect();
				p_gg->param[i].data = (char *)p_disconnect;
				p_disconnect->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_disconnect->reason= *(uint8_t *)(buffer+index);
				index++;
				break;
			case GGP_BEAT_HEART_KEEPALIVE_ID:
				GGP_CheckLen(index,5,pack_len)
				p_beatheart = allocate_ggp_beatheart();
				p_gg->param[i].data = (char *)p_beatheart;
				p_beatheart->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_beatheart->flag = *(uint8_t *)(buffer+index);
				index++;
				break;
			case GGP_TRANSACTION_BUSSINESS_REQ_ID:
				GGP_CheckLen(index,10,pack_len)
				p_tst = allocate_ggp_tst(0);
				p_gg->param[i].data = (char *)p_tst;
				p_tst->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_tst->id = ntohs(*(uint16_t *)(buffer+index));
				index+=2;
				p_tst->len = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				GGP_CheckLen(index,p_tst->len,pack_len)

				set_ggp_tst_len(p_tst,p_tst->len);
				memcpy(p_tst->data,buffer+index,p_tst->len);
				index+=p_tst->len;
				break;
			case GGP_TRANSACTION_BUSSINESS_RSP_ID:
				GGP_CheckLen(index,5,pack_len)
				p_tst = allocate_ggp_tst(0);
				p_gg->param[i].data = (char *)p_tst;
				p_tst->group_id = ntohl(*(uint32_t *)(buffer+index));
				index+=4;
				p_tst->result = *(uint8_t *)(buffer+index);
				index++;
				break;
			default:
				break;
		}
	}
	return GGP_PARSER_SUCCESS;
}


/* ***********************************************************************************
 * Parser gg_protocol_t parameter.
 *
 * @param:	p			protocol package.
 * @param:	key			encrypt key.
 * @param:	key_len		encrypt key length.
 *
 * @retval:	p_gg		gg_protocol_t pointer.
 *
 * ***********************************************************************************/
gg_protocol_t *parser_ggp(const protocol_package *package,const char *key,uint8_t key_len)
{
	volatile uint32_t index=0;
	char *crypt_ptr=NULL;
	uint32_t crypt_len=0;
	char buffer[1024]="";
	uint32_t len=sizeof(buffer);

	gg_protocol_t *p_gg = NULL;

	if(!package)
	{
#ifdef GGP_DEBUG
		printf("[GGP] package is null.\n");
#endif
		return NULL;
	}

	if(check_head_tail(package)==GGP_PARSER_FAILED)
	{
#ifdef GGP_DEBUG
		printf("[GGP] check and tail failed.\n");
#endif
		return NULL;
	}

	if(package->length<15)
	{
#ifdef GGP_DEBUG
		printf("[GGP] length is short.\n");
#endif
		return NULL;
	}

	p_gg = allocate_ggp(0);

	p_gg->head = *(uint8_t *)(package->data+index);
	index++;
	p_gg->tail = *(uint8_t *)(package->data+package->length-1);
	p_gg->attr = ntohs(*(uint16_t *)(package->data+index));
	index+=2;
	p_gg->crc_check = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	p_gg->sequence = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	p_gg->length = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	if(p_gg->length!=package->length)
	{
#ifdef GGP_DEBUG
		printf("[GGP] package length error, package length:%d,gg_protocol length:%d\n",package->length,p_gg->length);
#endif
		deallocate_ggp(&p_gg);
		return NULL;
	}

	if(GGP_CRC32Flag(p_gg))
	{
		uint32_t crc = crc32_check_char_buffer(package->data+index,package->length-index-1);
		if(crc!=p_gg->crc_check)
		{
#ifdef GGP_DEBUG
			printf("[GGP] crc32 check failed, crc:%d,real crc:%d\n",crc,p_gg->crc_check);
#endif
			deallocate_ggp(&p_gg);
			return NULL;
		}
	}
	if(GGP_CryptFlag(p_gg))
	{
		uint8_t crypt_alg = GGP_CryptAlg(p_gg);
		int ret = 0;
		if(crypt_alg!=P_CRYPT_CBC_ALG)
		{
#ifdef GGP_DEBUG
			printf("[GGP] algrithom error.\n");
#endif
			deallocate_ggp(&p_gg);
			return NULL;
		}

		ret = cbc_decrypt_char_buffer(package->data+index,package->length-index-1,\
									  buffer,(unsigned long *)&len,key,key_len);
		if(ret!=P_CRYPT_SUCCESS)
		{
#ifdef GCP_DEBUG
			printf("[GCP] parser failed, decrypt failed,ret:%d\n",ret);
#endif
			deallocate_ggp(&p_gg);
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
	p_gg->main_id = ntohs(*(uint16_t *)(crypt_ptr+index));
	index+=2;
	p_gg->src = ntohl(*(uint32_t *)(crypt_ptr+index));
	index+=4;
	p_gg->dst = ntohl(*(uint32_t *)(crypt_ptr+index));
	index+=4;
	p_gg->param_num = ntohs(*(uint16_t *)(crypt_ptr+index));
	index+=2;

	set_ggp_param_num(p_gg,p_gg->param_num);

	int ret = parser_ggp_param(crypt_ptr+index,crypt_len-index,p_gg);
	if(ret==GGP_PARSER_FAILED)
	{
#ifdef GGP_DEBUG
		printf("[GGP] parser parameter error.main_id:%d\n",p_gg->main_id);
#endif
		deallocate_ggp(&p_gg);
		return NULL;
	}
	
	return p_gg;
}

/* ***********************************************************************************
 * Package gg_protocol_t parameter.
 *
 * @param:	p_buffer	package buffer.
 * @param:	p_gg		gg_protocol_t pointer.
 *
 * @retval:	index		parameter size.
 *
 * ***********************************************************************************/
static uint32_t package_param(char *p_buffer,const gg_protocol_t *p_gg)
{
	uint32_t index = 0;
	gg_connect_t *p_gg_connect = NULL;
	gg_disconnect_t *p_gg_disconnect = NULL;
	gg_beatheart_t *p_gg_beatheart = NULL;
	gg_update_t *p_gg_update = NULL;
	gg_transaction_t *p_gg_tst = NULL;
	for(uint32_t i=0;i<p_gg->param_num;i++)
	{
		*(uint16_t *)(p_buffer+index) = htons(p_gg->param[i].id);
		index+=2;
		*(uint16_t *)(p_buffer+index) = htons(p_gg->param[i].attr);
		index+=2;
		*(uint32_t *)(p_buffer+index) = htonl(p_gg->param[i].length);
		index+=4;
		switch(p_gg->param[i].id)
		{
			case GGP_CONNECT_REQ_ID:
				p_gg_connect = (gg_connect_t *)(p_gg->param[i].data);
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_connect->group_id);
				index+=4;
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_connect->open_ip);
				index+=4;
				*(uint16_t *)(p_buffer+index) = htons(p_gg_connect->open_port);
				index+=2;
				*(uint8_t *)(p_buffer+index) = p_gg_connect->key_len;
				index++;
				memcpy(p_buffer+index,p_gg_connect->key,p_gg_connect->key_len);
				index+=p_gg_connect->key_len;
				break;
			case GGP_CONNECT_RSP_ID:
				p_gg_connect = (gg_connect_t *)(p_gg->param[i].data);
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_connect->group_id);
				index+=4;
				*(uint8_t *)(p_buffer+index) = p_gg_connect->result;
				index++;
				break;
			case GGP_DISCONNECT_INFORM_ID:
				p_gg_disconnect = (gg_disconnect_t *)(p_gg->param[i].data);
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_disconnect->group_id);
				index+=4;
				*(uint8_t *)(p_buffer+index) = p_gg_disconnect->reason;
				index++;
				break;
			case GGP_BEAT_HEART_KEEPALIVE_ID:
				p_gg_beatheart = (gg_beatheart_t *)(p_gg->param[i].data);
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_beatheart->group_id);
				index+=4;
				*(uint8_t *)(p_buffer+index) = p_gg_beatheart->flag;
				index++;
				break;
			case GGP_UPDATE_ADD_REQ_ID:
			case GGP_UPDATE_DEL_REQ_ID:
				p_gg_update = (gg_update_t *)(p_gg->param[i].data);
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_update->group_id);
				index+=4;
				*(uint16_t *)(p_buffer+index) = htons(p_gg_update->type);
				index+=2;
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_update->id_num);
				index+=4;
				for(uint32_t n=0;n<p_gg_update->id_num;n++)
				{
					*(uint32_t *)(p_buffer+index) = htonl(p_gg_update->id_list[n]);
					index+=4;
				}
				break;
			case GGP_UPDATE_ADD_RSP_ID:
			case GGP_UPDATE_DEL_RSP_ID:
				p_gg_update = (gg_update_t *)(p_gg->param[i].data);
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_update->group_id);
				index+=4;
				*(uint8_t *)(p_buffer+index) = p_gg_update->result;
				index++;
				break;
			case GGP_TRANSACTION_BUSSINESS_REQ_ID:
				p_gg_tst = (gg_transaction_t *)(p_gg->param[i].data);
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_tst->group_id);
				index+=4;
				*(uint16_t *)(p_buffer+index) = htons(p_gg_tst->id);
				index+=2;
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_tst->len);
				index+=4;
				memcpy(p_buffer+index,p_gg_tst->data,p_gg_tst->len);
				index+=p_gg_tst->len;
				break;
			case GGP_TRANSACTION_BUSSINESS_RSP_ID:
				p_gg_tst = (gg_transaction_t *)(p_gg->param[i].data);
				*(uint32_t *)(p_buffer+index) = htonl(p_gg_tst->group_id);
				index+=4;
				*(p_buffer+index) = p_gg_tst->result;
				index++;
			default:
				break;
		}
	}
	return index;
}

/* ***********************************************************************************
 * Package gg_protocol_t.
 *
 * @param:	p_gg		gg_protocol_t pointer.
 * @param:	key			encrypt key.
 * @param:	key_len		encrypt key length.
 *
 * @retval:	p			protocol package.
 *
 * ***********************************************************************************/
protocol_package *package_ggp(const gg_protocol_t *p_gg,const char *key,uint8_t key_len)
{
	char uc_buffer[1024]="";
	volatile uint32_t uc_index=0;
	char nc_buffer[1024]="";
	uint32_t nc_index=0;

	char crypt_buffer[1024]="";
	uint32_t crypt_len=0;

	uint32_t *crc_ptr = NULL;
	uint32_t *len_ptr = NULL;
	int ret;

	*(uint8_t *)(uc_buffer+uc_index) = GGP_HEAD_ID;
	uc_index++;
	*(uint16_t *)(uc_buffer+uc_index) = htons(p_gg->attr);
	uc_index+=2;

	crc_ptr = (uint32_t *)(uc_buffer+uc_index);
	uc_index+=4;
	*(uint32_t *)(uc_buffer+uc_index) = htonl(p_gg->sequence);
	uc_index+=4;
	len_ptr = (uint32_t *)(uc_buffer+uc_index);
	uc_index+=4;

	*(uint16_t *)(nc_buffer+nc_index) = htons(p_gg->main_id);
	nc_index+=2;
	*(uint32_t *)(nc_buffer+nc_index) = htonl(p_gg->src);
	nc_index+=4;
	*(uint32_t *)(nc_buffer+nc_index) = htonl(p_gg->dst);
	nc_index+=4;
	*(uint16_t *)(nc_buffer+nc_index) = htons(p_gg->param_num);
	nc_index+=2;

	nc_index += package_param(nc_buffer+nc_index,p_gg);

	if(GGP_CryptFlag(p_gg))
	{
		uint8_t crypt_alg = GGP_CryptAlg(p_gg);
		switch(crypt_alg)
		{
			case GGP_CRYPT_CBC_ALG:
				ret = cbc_encrypt_char_buffer(nc_buffer,nc_index,crypt_buffer,\
				  (unsigned long *)&crypt_len,key,key_len);
				if(ret!=P_CRYPT_SUCCESS)
				{
#ifdef GGP_DEBUG
					printf("[GGP] gg ecc encrypt failed,error:%d\n",ret);
#endif
					return NULL;
				}
				break;
			default:
				return NULL;
		}

		if(GGP_CRC32Flag(p_gg))
			*crc_ptr = htonl(crc32_check_char_buffer(crypt_buffer,crypt_len));
		
		*len_ptr = htonl(crypt_len+uc_index+1);
		protocol_package *p = allocate_package(crypt_len+uc_index+1);
		memcpy(p->data,uc_buffer,uc_index);
		memcpy(p->data+uc_index,crypt_buffer,crypt_len);
		*(uint8_t *)(p->data+uc_index+crypt_len) = GGP_TAIL_ID;
		return p;
	}
	else
	{
		if(GGP_CRC32Flag(p_gg))
			*crc_ptr = htonl(crc32_check_char_buffer(nc_buffer,nc_index));

		*len_ptr = htonl(nc_index+uc_index+1);
		protocol_package *p = allocate_package(nc_index+uc_index+1);
		memcpy(p->data,uc_buffer,uc_index);
		memcpy(p->data+uc_index,nc_buffer,nc_index);
		*(uint8_t *)(p->data+uc_index+nc_index) = GGP_TAIL_ID;
		return p;
	}
}

/* ***********************************************************************************
 * Set gg_protocol_t parameter numbers.
 *
 * @param:	p_gg		gg_protocol_t pointer.
 * @param:	num			copy number.
 *
 * ***********************************************************************************/
void set_ggp_param_num(gg_protocol_t *p_gg,uint16_t num)
{
	if(!p_gg || !num)
		return ;

	if(p_gg->param)
	{
		for(uint16_t i=0;i<p_gg->param_num;i++)
		{
			switch(p_gg->param[i].id)
			{
				case GGP_CONNECT_REQ_ID:
				case GGP_CONNECT_RSP_ID:
					deallocate_ggp_connect((gg_connect_t **)&(p_gg->param[i].data));
					break;
				case GGP_DISCONNECT_INFORM_ID:
					deallocate_ggp_disconnect((gg_disconnect_t **)&(p_gg->param[i].data));
					break;
				case GGP_BEAT_HEART_KEEPALIVE_ID:
					deallocate_ggp_beatheart((gg_beatheart_t **)&(p_gg->param[i].data));
					break;
				case GGP_UPDATE_ADD_REQ_ID:
				case GGP_UPDATE_DEL_REQ_ID:
				case GGP_UPDATE_ADD_RSP_ID:
				case GGP_UPDATE_DEL_RSP_ID:
					deallocate_ggp_update((gg_update_t **)&(p_gg->param[i].data));
					break;
				case GGP_TRANSACTION_BUSSINESS_REQ_ID:
				case GGP_TRANSACTION_BUSSINESS_RSP_ID:
					deallocate_ggp_tst((gg_transaction_t **)&(p_gg->param[i].data));
					break;
			}
		}
		free(p_gg->param);
	}
	p_gg->param_num = num;
	p_gg->param = (gg_parameter_t *)malloc(num*sizeof(gg_parameter_t));
	memset(p_gg->param,0,sizeof(gg_parameter_t)*num);
}

/* ***********************************************************************************
 * Copy gg_protocol_t parameter.
 *
 * @param:	p_gg		gg_protocol_t pointer.
 * @param:	flag		Copy flag.
 *						GGP_HEAD_FLAG
 *						GGP_COPY_PARAM_FLAG
 *		
 * @retval:	c_gg		Copy gg_protocol_t.
 *
 * ***********************************************************************************/
gg_protocol_t *copy_ggp(const gg_protocol_t *p_gg,int flag)
{
	gg_protocol_t *c_gg = allocate_ggp(p_gg->param_num);

	if((flag & GGP_COPY_HEAD_FLAG)==GGP_COPY_HEAD_FLAG)
	{
		memcpy(c_gg,p_gg,sizeof(gg_protocol_t));
		c_gg->param = 0;
	}

	if((flag & GGP_COPY_PARAM_FLAG)==GGP_COPY_PARAM_FLAG)
	{
		c_gg->param = (gg_parameter_t *)malloc(sizeof(gg_parameter_t)*p_gg->param_num);
		memcpy(c_gg->param,p_gg->param,sizeof(gg_parameter_t)*p_gg->param_num);
		for(uint16_t i=0;i<p_gg->param_num;i++)
		{
			//parameter copy ?
			c_gg->param[i].data = (char *)malloc(p_gg->param[i].length);
			memcpy(c_gg->param[i].data,p_gg->param[i].data,p_gg->param[i].length);
		}
	}

	return c_gg;
}

/* ***********************************************************************************
 * Print gg_protocol_t parameter.
 *
 * @param:	p_gg		gg_protocol_t pointer.
 *		
 * ***********************************************************************************/
static void print_ggp_param(const gg_protocol_t *p_gg)
{
	gg_connect_t *p_gg_connect = NULL;
	gg_disconnect_t *p_gg_disconnect = NULL;
	gg_beatheart_t *p_gg_beatheart = NULL;
	gg_update_t *p_gg_update = NULL;
	gg_transaction_t *p_gg_tst = NULL;

	printf("param_num:%d\n",p_gg->param_num);
	for(uint16_t i=0;i<p_gg->param_num;i++)
	{
		printf("param[%d]:\n",i);
		printf("id:%d\n",p_gg->param[i].id);
		printf("attr:%d\n",p_gg->param[i].attr);
		printf("length:%d\n",p_gg->param[i].length);
		switch(p_gg->param[i].id)
		{
			case GGP_CONNECT_REQ_ID:
				p_gg_connect = (gg_connect_t *)p_gg->param[i].data;
				if(!p_gg_connect)
				{
					printf("Parameter is null.\n");
					break;
				}
				printf("group_id:%d;open_ip:%d;open_port:%d;key_len:%d;key:",\
						p_gg_connect->group_id,p_gg_connect->open_ip,p_gg_connect->open_port,\
						p_gg_connect->key_len);
				for(uint8_t j=0;j<p_gg_connect->key_len;j++)
				{
					printf("%c",p_gg_connect->key[j]);
				}
				printf("\n");
				break;
			case GGP_CONNECT_RSP_ID:
				p_gg_connect = (gg_connect_t *)p_gg->param[i].data;
				if(!p_gg_connect)
				{
					printf("Parameter is null.\n");
					break;
				}
				printf("group_id:%d;result:%d\n",\
						p_gg_connect->group_id,p_gg_connect->result);
				printf("\n");
				break;
			case GGP_DISCONNECT_INFORM_ID:
				p_gg_disconnect = (gg_disconnect_t *)p_gg->param[i].data;
				if(!p_gg_disconnect)
				{
					printf("Parameter is null.\n");
					break;
				}
				printf("group_id:%d;reason:%d;\n",\
						p_gg_disconnect->group_id,p_gg_disconnect->reason);
				break;
			case GGP_BEAT_HEART_KEEPALIVE_ID:
				p_gg_beatheart = (gg_beatheart_t *)p_gg->param[i].data;
				if(!p_gg_beatheart)
				{
					printf("Parameter is null.\n");
					break;
				}
				printf("group_id:%d;flag:%d;\n",\
						p_gg_beatheart->group_id,p_gg_beatheart->flag);
				break;
			case GGP_UPDATE_ADD_REQ_ID:
			case GGP_UPDATE_DEL_REQ_ID:
				p_gg_update = (gg_update_t *)p_gg->param[i].data;
				if(!p_gg_update)
				{
					printf("Parameter is null.\n");
					break;
				}
				printf("group_id:%d;type:%d;id_num:%d;id_list:",\
						p_gg_update->group_id,p_gg_update->type,p_gg_update->id_num);
				for(uint32_t j=0;j<p_gg_update->id_num;j++)
				{
					printf("[j]:%d ",p_gg_update->id_list[j]);
				}
				printf("\n");
				break;
			case GGP_UPDATE_ADD_RSP_ID:
			case GGP_UPDATE_DEL_RSP_ID:
				p_gg_update = (gg_update_t *)p_gg->param[i].data;
				if(!p_gg_update)
				{
					printf("Parameter is null.\n");
					break;
				}
				printf("group_id:%d;result:%d;\n",\
						p_gg_update->group_id,p_gg_update->result);
				break;
			case GGP_TRANSACTION_BUSSINESS_REQ_ID:
				p_gg_tst = (gg_transaction_t *)p_gg->param[i].data;
				if(!p_gg_tst)
				{
					printf("Parameter is null.\n");
					break;
				}
				printf("group_id:%d;id:%d;len:%d;\n",\
						p_gg_tst->group_id,p_gg_tst->id,p_gg_tst->len);
				break;
			case GGP_TRANSACTION_BUSSINESS_RSP_ID:
				p_gg_tst = (gg_transaction_t *)p_gg->param[i].data;
				if(!p_gg_tst)
				{
					printf("Parameter is null.\n");
					break;
				}
				printf("group_id:%d;result:%d;\n",\
						p_gg_tst->group_id,p_gg_tst->result);
				break;
			default:
				printf("Invalid parameter id.\n");
				break;
		}
	}
}

/* ***********************************************************************************
 * Print gg_protocol_t.
 *
 * @param:	p_gg		gg_protocol_t pointer.
 *		
 * ***********************************************************************************/
void print_ggp(const gg_protocol_t *p_gg)
{
	if(!p_gg)
		return ;

	printf("***************************Group-Group Protocol Start**********************\n");
	printf("head:%c;tail:%c;attr:%d;crc_check:%d;sequence:%d;length:%d;main_id:%d;src:%d;dst:%d;\n",
			p_gg->head,p_gg->tail,p_gg->attr,p_gg->crc_check,p_gg->sequence,p_gg->length,
			p_gg->main_id,p_gg->src,p_gg->dst);

	print_ggp_param(p_gg);

	printf("***************************Group-Group Protocol End************************\n");
}




