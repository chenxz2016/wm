/* ************************************************************************
 *       Filename:  gnc_protocol.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"gnc_protocol.h"
#include<malloc.h>
#include<string.h>

#define GNCP_CheckParamLen(index,delt,len) \
	if((index+delt)>len)\
		return GNCP_PARSER_FAILED;


/* ***********************************************************************************
 * Allocate gnc_register_t.
 *
 * @retval:	p_register	The pointer of gnc_register_t.
 *
 * ***********************************************************************************/
gnc_register_t *allocate_gncp_register()
{
	gnc_register_t *p_register = (gnc_register_t *)malloc(sizeof(gnc_register_t));
	memset(p_register,0,sizeof(gnc_register_t));
	return p_register;
}

/* ***********************************************************************************
 * Deallocate gnc_register_t.
 *
 * @param:	p_register	The pointer of gnc_register_t.
 *
 * ***********************************************************************************/
void deallocate_gncp_register(gnc_register_t **p_register)
{
	if(p_register && (*p_register))
	{
		free(*p_register);
		(*p_register) = NULL;
	}
}

/* ***********************************************************************************
 * Allocate gnc_disconnect_t.
 *
 * @param:	p_disconnect	The pointer of gnc_disconnect_t.
 *
 * ***********************************************************************************/
gnc_disconnect_t *allocate_gncp_disconnect()
{
	gnc_disconnect_t *p_disconnect = malloc(sizeof(gnc_disconnect_t));
	memset(p_disconnect,0,sizeof(gnc_disconnect_t));
	return p_disconnect;
}

/* ***********************************************************************************
 * Deallocate gnc_disconnect_t.
 *
 * @param:	p_disconnect	The pointer of gnc_disconnect_t.
 *
 * ***********************************************************************************/
void deallocate_gncp_disconnect(gnc_disconnect_t **p_disconnect)
{
	if(p_disconnect && (*p_disconnect))
	{
		free(*p_disconnect);
		(*p_disconnect) = NULL;
	}
}

/* ***********************************************************************************
 * Allocate gnc_beatheart_t.
 *
 * @param:	p_beatheart		The pointer of gnc_beatheart_t.
 *
 * ***********************************************************************************/
gnc_beatheart_t *allocate_gncp_beatheart()
{
	gnc_beatheart_t *p_beatheart = (gnc_beatheart_t *)malloc(sizeof(gnc_beatheart_t));
	memset(p_beatheart,0,sizeof(gnc_beatheart_t));
	return p_beatheart;
}

/* ***********************************************************************************
 * Deallocate gnc_beatheart_t.
 *
 * @param:	p_beatheart		The pointer of gnc_beatheart_t.
 *
 * ***********************************************************************************/
void deallocate_gncp_beatheart(gnc_beatheart_t **p_beatheart)
{
	if(p_beatheart && (*p_beatheart))
	{
		free(*p_beatheart);
		(*p_beatheart) = NULL;
	}
}

/* ***********************************************************************************
 * Allocate gnc_update_t.
 *
 * @retval:	p_update		The pointer of gnc_beatheart_t.
 *
 * ***********************************************************************************/
gnc_update_t *allocate_gncp_update(uint16_t num)
{
	gnc_update_t *p_update = (gnc_update_t *)malloc(sizeof(gnc_update_t));
	memset(p_update,0,sizeof(gnc_update_t));
	if(num)
	{
		p_update->id_num = num;
		p_update->id_list = (uint32_t *)malloc(sizeof(uint32_t)*num);
		memset(p_update->id_list,0,sizeof(uint32_t)*num);
	}
	return p_update;
}

/* ***********************************************************************************
 * Deallocate gnc_update_t.
 *
 * @param:	p_update		The pointer of gnc_update_t pointer.
 *
 * ***********************************************************************************/
void deallocate_gncp_update(gnc_update_t **p_update)
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
 * Set gnc_update_t list number.
 *
 * @param:	p_update		The pointer of gnc_update_t pointer.
 * @param:	num				id list numbers.
 *
 * ***********************************************************************************/
void set_gncp_update_num(gnc_update_t *p_update,uint16_t num)
{
	if(!num || !p_update)
		return ;

	if(p_update->id_list)
		free(p_update->id_list);

	p_update->id_list = (uint32_t *)malloc(sizeof(uint32_t)*num);
	memset(p_update->id_list,0,sizeof(uint32_t)*num);
	p_update->id_num = num;
}

/* ***********************************************************************************
 * Set gnc_protocol_t list number.
 *
 * @retval:	p_gnc			The pointer of gnc_protocol_t.
 *
 * ***********************************************************************************/
gnc_protocol_t *allocate_gncp()
{
	gnc_protocol_t *p_gnc = (gnc_protocol_t *)malloc(sizeof(gnc_protocol_t));
	memset(p_gnc,0,sizeof(gnc_protocol_t));
	return p_gnc;
}

/* ***********************************************************************************
 * Deallocate gnc_protocol_t.
 *
 * @param:	p_gnc			The pointer of gnc_protocol_t.
 *
 * ***********************************************************************************/
void deallocate_gncp(gnc_protocol_t **p_gnc)
{
	if(p_gnc && (*p_gnc) && (*p_gnc)->data)
	{
		switch((*p_gnc)->type)
		{
			case GNCP_DISCONNECT_ID:
				deallocate_gncp_disconnect((gnc_disconnect_t **)&((*p_gnc)->data));
				break;
			case GNCP_BEAT_HEART_ID:
				deallocate_gncp_beatheart((gnc_beatheart_t **)&((*p_gnc)->data));
				break;
			case GNCP_REGISTER_ID:
				deallocate_gncp_register((gnc_register_t **)&((*p_gnc)->data));
				break;
			case GNCP_UPDATE_ID:
				deallocate_gncp_update((gnc_update_t **)&((*p_gnc)->data));
				break;
			default:
				free((*p_gnc)->data);
				break;
		}
		free(*p_gnc);
		(*p_gnc) = NULL;
		return ;
	}
	if(p_gnc && (*p_gnc))
	{
		free(*p_gnc);
		(*p_gnc) = NULL;
	}
}

/* ***********************************************************************************
 * Set gnc_protocol_t data length.
 *
 * @param:	p_gnc			The pointer of gnc_protocol_t.
 *
 * ***********************************************************************************/
void set_gncp_data_length(gnc_protocol_t *p_gnc,uint32_t length)
{
	if(!p_gnc || !length)
		return ;

	if(p_gnc->data)
	{
		switch(p_gnc->type)
		{
			case GNCP_DISCONNECT_ID:
				deallocate_gncp_disconnect((gnc_disconnect_t **)&(p_gnc->data));
				break;
			case GNCP_BEAT_HEART_ID:
				deallocate_gncp_beatheart((gnc_beatheart_t **)&(p_gnc->data));
				break;
			case GNCP_REGISTER_ID:
				deallocate_gncp_register((gnc_register_t **)&(p_gnc->data));
				break;
			case GNCP_UPDATE_ID:
				deallocate_gncp_update((gnc_update_t **)&(p_gnc->data));
				break;
			default:
				free(p_gnc->data);
				break;
		}
	}
	p_gnc->type = 65535;
	p_gnc->length = length;
	p_gnc->data = (char *)malloc(length);
	memset(p_gnc->data,0,length);
}

/* ***********************************************************************************
 * Check gnc_protocol_t package head and tail.
 *
 * @param:	p			protocol package.
 *
 * ***********************************************************************************/
static int check_head_tail(const protocol_package *p)
{
	if(*(uint8_t *)p->data==GNCP_HEAD_ID && *(uint8_t *)(p->data+p->length-1)==GNCP_TAIL_ID)
		return GNCP_PARSER_SUCCESS;
	return GNCP_PARSER_FAILED;
}

/* ***********************************************************************************
 * Parser gnc_protocol_t parameter.
 *
 * @param:	p			protocol package.
 * @param:	p_gnc		gnc_protocol_t pointer.
 *
 * @retval:	index		parameter index.
 *
 * ***********************************************************************************/
static int parser_gncp_param(const protocol_package *p,gnc_protocol_t *p_gnc)
{
	uint32_t index = GNCP_PARAM_INDEX;
	gnc_register_t *p_register = NULL;
	gnc_disconnect_t *p_disconnect = NULL;
	gnc_beatheart_t *p_beatheart = NULL;
	gnc_update_t *p_update = NULL;
	switch(p_gnc->type)
	{
		case GNCP_REGISTER_ID:
			GNCP_CheckParamLen(index,4,p_gnc->length)
			p_register = allocate_gncp_register();
			p_register->id = ntohl(*(uint32_t *)(p->data+index));
			index+=4;
			p_gnc->data = (char *)p_register;
			break;
		case GNCP_DISCONNECT_ID:
			GNCP_CheckParamLen(index,1,p_gnc->length)
			p_disconnect = allocate_gncp_disconnect();
			p_disconnect->reason = *(uint8_t *)(p->data+index);
			index++;
			p_gnc->data = (char *)p_disconnect;
			break;
		case GNCP_BEAT_HEART_ID:
			GNCP_CheckParamLen(index,1,p_gnc->length)
			p_beatheart = allocate_gncp_beatheart();
			p_beatheart->flag = *(uint8_t *)(p->data+index);
			index++;
			p_gnc->data = (char *)p_beatheart;
			break;
		case GNCP_UPDATE_ID:
			GNCP_CheckParamLen(index,7,p_gnc->length)
			p_update = allocate_gncp_update(0);
			p_update->flag = *(uint8_t *)(p->data+index);
			index++;
			p_update->type = ntohs(*(uint16_t *)(p->data+index));
			index+=2;
			p_update->id_num = ntohl(*(uint32_t *)(p->data+index));
			index+=4;
			GNCP_CheckParamLen(index,p_update->id_num*4,p_gnc->length)

			set_gncp_update_num(p_update,p_update->id_num);
			for(uint32_t i=0;i<p_update->id_num;i++)
			{
				p_update->id_list[i] = ntohl(*(uint32_t *)(p->data+index));
				index+=4;
			}
			p_gnc->data = (char *)p_update;
			break;
		default:
			return GNCP_PARSER_FAILED;
	}
	return GNCP_PARSER_SUCCESS;
}


/* ***********************************************************************************
 * Parser gnc_protocol_t.
 *
 * @param:	p			protocol package.
 *
 * @retval:	p_gnc		gnc_protocol_t pointer.
 *
 * ***********************************************************************************/
gnc_protocol_t *parser_gncp(const protocol_package *p)
{
	if(check_head_tail(p)==GNCP_PARSER_FAILED)
	{
#ifdef GNCP_DEBUG
		printf("[GNCP] parser parameter failed.\n");
#endif
		return NULL;
	}

	gnc_protocol_t *p_gnc = allocate_gncp();

	uint32_t index=0;
	p_gnc->head = *(uint8_t *)(p->data+index);
	index++;
	p_gnc->sequence = ntohl(*(uint32_t *)(p->data+index));
	index+=4;
	p_gnc->type = ntohs(*(uint16_t *)(p->data+index));
	index+=2;
	p_gnc->src = ntohl(*(uint32_t *)(p->data+index));
	index+=4;
	p_gnc->dst = ntohl(*(uint32_t *)(p->data+index));
	index+=4;
	p_gnc->length = ntohl(*(uint32_t *)(p->data+index));
	index+=4;

	if(parser_gncp_param(p,p_gnc)==GNCP_PARSER_FAILED)
	{
#ifdef GNCP_DEBUG
		printf("[GNCP] parser parameter failed.\n");
#endif
		deallocate_gncp(&p_gnc);
		return NULL;
	}
	
	return p_gnc;
}

/* ***********************************************************************************
 * Calculate gnc_protocol_t package length.
 *
 * @param:	p			protocol package pointer.
 * @param:	p_gnc		gnc_protocol_t pointer.
 *
 * @retval:	index		gnc_parameter_t data length.
 *
 * ***********************************************************************************/
static int package_gncp_data(char *buffer,const gnc_protocol_t *p_gnc)
{
	int index = 0;
	gnc_register_t *p_register = NULL;
	gnc_disconnect_t *p_disconnect = NULL;
	gnc_beatheart_t *p_beatheart = NULL;
	gnc_update_t *p_update = NULL;
	switch(p_gnc->type)
	{
		case GNCP_REGISTER_ID:
			p_register = (gnc_register_t *)p_gnc->data;
			*(uint32_t *)(buffer+index) = htonl(p_register->id);
			index+=4;
			break;
		case GNCP_DISCONNECT_ID:
			p_disconnect = (gnc_disconnect_t *)p_gnc->data;
			*(uint8_t *)(buffer+index) = p_disconnect->reason;
			index++;
			break;
		case GNCP_BEAT_HEART_ID:
			p_beatheart = (gnc_beatheart_t *)p_gnc->data;
			*(uint8_t *)(buffer+index) = p_beatheart->flag;
			index++;
			break;
		case GNCP_UPDATE_ID:
			p_update = (gnc_update_t *)p_gnc->data;
			*(uint8_t *)(buffer+index) = p_update->flag;
			index++;
			*(uint16_t *)(buffer+index) = htons(p_update->type);
			index+=2;
			*(uint32_t *)(buffer+index) = htonl(p_update->id_num);
			index+=4;
			for(uint32_t i=0;i<p_update->id_num;i++)
			{
				*(uint32_t *)(buffer+index) = htonl(p_update->id_list[i]);
				index+=4;
			}
			break;
		default:
			return GNCP_PACKAGE_FAILED;
	}

	return index;
}

/* ***********************************************************************************
 * Package gnc_protocol_t.
 *
 * @param:	p_gnc		gnc_protocol_t pointer.
 *
 * @retval:	p			gnc_protocol_t package.
 *
 * ***********************************************************************************/
protocol_package *package_gncp(const gnc_protocol_t *p_gnc)
{
	char buffer[4096]="";

	uint32_t index=0;
	uint32_t *len_ptr = NULL;
	*(uint8_t *)(buffer+index) = p_gnc->head;
	index++;

	*(uint32_t *)(buffer+index) = htonl(p_gnc->sequence);
	index+=4;
	*(uint16_t *)(buffer+index) = htons(p_gnc->type);
	index+=2;
	*(uint32_t *)(buffer+index) = htonl(p_gnc->src);
	index+=4;
	*(uint32_t *)(buffer+index) = htonl(p_gnc->dst);
	index+=4;
	//*(uint32_t *)(buffer+index) = htonl(p_gnc->length);
	len_ptr = (uint32_t *)(buffer+index);
	index+=4;

	index += package_gncp_data(buffer+index,p_gnc);

	*(uint8_t *)(buffer+index) = p_gnc->tail;
	index++;
	*len_ptr = htonl(index);

	protocol_package *p = allocate_package(index);
	memcpy(p->data,buffer,index);

	return p;
}


/* ***********************************************************************************
 * Copy gnc_protocol_t.
 *
 * @param:	p_gnc		gnc_protocol_t pointer.
 * @param:	flag		Copy flag.
 *
 * @retval:	c_gnc		copy gnc_protocol_t.
 *
 * ***********************************************************************************/
gnc_protocol_t *copy_gncp(gnc_protocol_t *p_gnc,int flag)
{
	gnc_protocol_t *c_gnc = allocate_gncp();

	if(flag & GNCP_COPY_HEAD_FLAG)
	{
		memcpy(c_gnc,p_gnc,sizeof(gnc_protocol_t));
		c_gnc->length = 0;
		c_gnc->data = 0;
	}

	if(flag & GNCP_COPY_DATA_FLAG)
	{
		switch(p_gnc->type)
		{
			case GNCP_DISCONNECT_ID:
				c_gnc->data = (char *)allocate_gncp_disconnect();
				memcpy(c_gnc->data,p_gnc->data,sizeof(gnc_disconnect_t));
				break;
			case GNCP_BEAT_HEART_ID:
				c_gnc->data = (char *)allocate_gncp_beatheart();
				memcpy(c_gnc->data,p_gnc->data,sizeof(gnc_beatheart_t));
				break;
			case GNCP_REGISTER_ID:
				c_gnc->data = (char *)allocate_gncp_register();
				memcpy(c_gnc->data,p_gnc->data,sizeof(gnc_register_t));
				break;
			case GNCP_UPDATE_ID:
				c_gnc->data = (char *)allocate_gncp_update(((gnc_update_t *)(p_gnc->data))->id_num);
				memcpy(c_gnc->data,p_gnc->data,sizeof(gnc_update_t));
				memcpy(((gnc_update_t *)(c_gnc->data))->id_list,\
						((gnc_update_t *)(p_gnc->data))->id_list,\
						((gnc_update_t *)(p_gnc->data))->id_num*sizeof(uint32_t));
				break;
		}
	}

	return c_gnc;
}

/* ***********************************************************************************
 * Print Hex.
 *
 * @param:	data		Data buffer.
 * @param:	length		Data length.
 *
 * ***********************************************************************************/
static void print_hex(const char *data,uint32_t length)
{
	for(uint32_t i=0;i<length;i++)
	{
		printf(" %02x",data[i]);
	}
	printf("\n");
}

/* ***********************************************************************************
 * Print Hex.
 *
 * @param:	p_gnc		gnc_protocol_t pointer.
 *
 * ***********************************************************************************/
static void print_gncp_data(const gnc_protocol_t *p_gnc)
{
	if(!p_gnc->data)
	{
		printf("data is null.\n");
		return ;
	}
	switch(p_gnc->type)
	{
		case GNCP_DISCONNECT_ID:
			printf("disconnect\n");
			printf("reason:%d\n",((gnc_disconnect_t *)p_gnc->data)->reason);
			break;
		case GNCP_BEAT_HEART_ID:
			printf("beat heart\n");
			printf("flag:%d\n",((gnc_beatheart_t *)p_gnc->data)->flag);
			break;
		case GNCP_REGISTER_ID:
			printf("register\n");
			printf("id:%d\n",((gnc_register_t *)p_gnc->data)->id);
			break;
		case GNCP_UPDATE_ID:
			printf("update\n");
			printf("flag:%d;type:%d;id_num:%d;id_list:\n",((gnc_update_t *)p_gnc->data)->flag,
					((gnc_update_t *)p_gnc->data)->type,((gnc_update_t *)p_gnc->data)->id_num);
			for(uint32_t i=0;i<((gnc_update_t *)p_gnc->data)->id_num;i++)
			{
				printf("[%d]:%d ",i,((gnc_update_t *)p_gnc->data)->id_list[i]);
			}
			printf("\n");
			break;
		default:
			print_hex(p_gnc->data,p_gnc->length);
			break;
	}
}

/* ***********************************************************************************
 * Print gnc_protocol_t.
 *
 * @param:	p_gnc		gnc_protocol_t pointer.
 * @param:	flag		Print flag.
 *
 * ***********************************************************************************/
void print_gncp(const gnc_protocol_t *p_gnc,int flag)
{
	if(!p_gnc)
		return ;

	printf("***************************NCore-Group Protocol Start**********************\n");
	printf("head:%c;tail%c;sequence:%d;src:%d;dst:%d;length:%d;\n",
			p_gnc->head,p_gnc->tail,p_gnc->sequence,p_gnc->src,p_gnc->dst,p_gnc->length);
	if(flag & GNCP_PRINT_DATA_FLAG)
		print_gncp_data(p_gnc);
	printf("***************************NCore-Group Protocol End************************\n");
}




