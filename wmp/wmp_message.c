/* ************************************************************************
 *       Filename:  wmp_message.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include<malloc.h>
#include<string.h>

#include"protocol_def.h"
#include"wmp_message.h"

/* Create wmp_message_t instance. */
wmp_message_t *create_wmp_message(uint32_t msg_len)
{
	wmp_message_t *p_wmp_msg = (wmp_message_t *)malloc(sizeof(wmp_message_t));
	memset(p_wmp_msg,0,sizeof(wmp_message_t));
    p_wmp_msg->msg_len = msg_len;

    if(msg_len)
    {
        p_wmp_msg->msg = (uint8_t *)malloc(msg_len);
        memset(p_wmp_msg->msg,0,msg_len);
    }
    return p_wmp_msg;
}

/* Delete wmp_message_t instance. */
void delete_wmp_message(wmp_message_t **p_wmp_msg)
{
    if((*p_wmp_msg))
	{
        if((*p_wmp_msg)->msg)
        {
            free(((*p_wmp_msg)->msg));
            (*p_wmp_msg)->msg = NULL;
        }
        free((*p_wmp_msg));
        (*p_wmp_msg) = NULL;
	}
}

/* Parser wmp_message_t. */
wmp_message_t *parser_wmp_message(const char *package,uint32_t pack_len)
{
	if(pack_len<WMP_MESSAGE_LENGTH)
		return NULL;
	
	uint32_t index = 0;
    wmp_message_t *p_wmp_msg = create_wmp_message(0);
	
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

/* Package wmp_message_t. */
uint32_t package_wmp_message(char *package,const wmp_message_t *p_wmp_msg)
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

/* Set wmp_message_t message length. */
void set_wmp_message_len(wmp_message_t *p_wmp_msg,uint32_t msg_len)
{
	if(p_wmp_msg)
	{
		if(p_wmp_msg->msg)
			free(p_wmp_msg->msg);

        p_wmp_msg->msg_len = msg_len;
		p_wmp_msg->msg = (uint8_t *)malloc(msg_len);
        memset(p_wmp_msg->msg,0,msg_len);
	}
}

/* Copy a new wmp_message_t instance. */
wmp_message_t *copy_wmp_message(const wmp_message_t *p_wmp_msg)
{
    wmp_message_t *c_wmp_msg = create_wmp_message(p_wmp_msg->msg_len);

    c_wmp_msg->attr = p_wmp_msg->attr;
    c_wmp_msg->result = p_wmp_msg->result;
    c_wmp_msg->src = p_wmp_msg->src;
    c_wmp_msg->dst = p_wmp_msg->dst;
    set_wmp_message_len(c_wmp_msg,p_wmp_msg->msg_len);
    memcpy(c_wmp_msg->msg,p_wmp_msg->msg,p_wmp_msg->msg_len);

    return c_wmp_msg;
}

