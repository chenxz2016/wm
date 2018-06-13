/* ************************************************************************
 *       Filename:  wmp_message.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_message.h"
#include<malloc.h>
#include<string.h>



wmp_message_t *allocate_wmp_message()
{
	wmp_message_t *p_wmp_msg = (wmp_message_t *)malloc(sizeof(wmp_message_t));
	memset(p_wmp_msg,0,sizeof(wmp_message_t));
	return p_wmp_msg;
}

void deallocate_wmp_message(wmp_message_t **p_wmp_msg)
{
	if(*p_wmp_msg && (*p_wmp_msg)->msg)
	{
		free(((*p_wmp_msg)->msg));
		free(*p_wmp_msg);
		*p_wmp_msg = 0;
	}
	
	if(*p_wmp_msg)
	{
		free(*p_wmp_msg);
		*p_wmp_msg = 0;
	}
}


wmp_message_t *parser_wmp_message(const char *package,uint32_t pack_len)
{
	if(pack_len<WMP_MESSAGE_LENGTH)
		return NULL;
	
	uint32_t index = 0;
	wmp_message_t *p_wmp_msg = allocate_wmp_message();
	
	p_wmp_msg->attr = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_msg->attr);

	p_wmp_msg->result = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_msg->result);

	p_wmp_msg->src = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_msg->src);

	p_wmp_msg->dst = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_msg->dst);

	p_wmp_msg->msg_len = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_msg->msg_len);

	memcpy(p_wmp_msg->msg,package+index,p_wmp_msg->msg_len);
	index+=p_wmp_msg->msg_len;
	
	return p_wmp_msg;
}

uint32_t package_wmp_message(char *package,wmp_message_t *p_wmp_msg)
{
	uint32_t index = 0;
	
	*(uint8_t *)(package+index) = p_wmp_msg->attr;
	index+=sizeof(p_wmp_msg->attr);

	*(uint8_t *)(package+index) = p_wmp_msg->result;
	index+=sizeof(p_wmp_msg->result);

	*(uint32_t *)(package+index) = htonl(p_wmp_msg->src);
	index+=sizeof(p_wmp_msg->src);

	*(uint32_t *)(package+index) = htonl(p_wmp_msg->dst);
	index+=sizeof(p_wmp_msg->dst);

	*(uint32_t *)(package+index) = htonl(p_wmp_msg->msg_len);
	index+=sizeof(p_wmp_msg->msg_len);

	memcpy(package+index,p_wmp_msg->msg,p_wmp_msg->msg_len);
	index+=p_wmp_msg->msg_len;
	
	return index;
}

void set_wmp_message_len(wmp_message_t *p_wmp_msg,uint32_t msg_len)
{
	if(p_wmp_msg)
	{
		if(p_wmp_msg->msg)
			free(p_wmp_msg->msg);
		p_wmp_msg->msg = (uint8_t *)malloc(msg_len);
		p_wmp_msg->msg_len = msg_len;
	}
}



