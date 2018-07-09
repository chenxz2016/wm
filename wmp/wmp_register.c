/* ************************************************************************
 *       Filename:  wmp_register.c
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
#include"wmp_register.h"


/* Create wmp_message_t instance. */
wmp_req_register_t *create_wmp_req_register()
{
	wmp_req_register_t *p_wmp_req_register = (wmp_req_register_t *)malloc(sizeof(wmp_req_register_t *));
	memset(p_wmp_req_register,0,sizeof(wmp_req_register_t));
	return p_wmp_req_register;
}

/* Delete wmp_message_t instance. */
void delete_wmp_req_register(wmp_req_register_t **p_req_wmp_register)
{
	if(p_req_wmp_register && (*p_req_wmp_register))
	{
		free(*p_req_wmp_register);
		(*p_req_wmp_register) = NULL;
	}
}


/* Parser wmp_message_t. */
wmp_req_register_t *parser_wmp_req_register(const char *package,uint32_t pack_len)
{
	if(!package || pack_len<WMP_REQ_REGISTER_MIN_LENGTH)
	{
#ifdef WMP_DEBUG
		printf("[WMP] parser wmp_req_register_t failed.\n");
#endif
		return NULL;
	}
	
	uint32_t index = 0;
    wmp_req_register_t *p_wmp_req_register = create_wmp_req_register();
	p_wmp_req_register->attr = ntohs(*(uint16_t *)(package+index));
	index+=2;
	memcpy(p_wmp_req_register->phone_num,package+index,WMP_REQ_REGISTER_PHONE_NUM_LENGTH);
	index+=WMP_REQ_REGISTER_PHONE_NUM_LENGTH;
	memcpy(p_wmp_req_register->email_addr,package+index,WMP_REQ_REGISTER_EMAIL_LENGTH);
	index+=WMP_REQ_REGISTER_EMAIL_LENGTH;
	return p_wmp_req_register;	
}


/* Package wmp_message_t. */
uint32_t package_wmp_req_register(char *package,const wmp_req_register_t *p_wmp_req_register)
{
	if(!package || !p_wmp_req_register)
	{
#ifdef WMP_DEBUG
		printf("[WMP] package wmp_req_register_t failed.\n");
#endif
		return 0;
	}

    uint32_t index = 0;
	*(uint16_t *)(package+index) = htons(p_wmp_req_register->attr);
	index+=2;
	memcpy(package+index,p_wmp_req_register->phone_num,WMP_REQ_REGISTER_PHONE_NUM_LENGTH);
	index+=WMP_REQ_REGISTER_PHONE_NUM_LENGTH;
	memcpy(package+index,p_wmp_req_register->email_addr,WMP_REQ_REGISTER_EMAIL_LENGTH);
	index+=WMP_REQ_REGISTER_EMAIL_LENGTH;
	return index;
}


/* Print wmp_message_t. */
void print_wmp_req_register(const wmp_req_register_t *p_wmp_req_register)
{
	if(!p_wmp_req_register)
	{
#ifdef WMP_DEBUG
		printf("[WMP] wmp_req_register_t is null.\n");
#endif
		return ;
	}

	printf("***************************WM-req_reigster Protocol Start**********************\n");
	printf("attr:%d;phone_num:%s;email_addr:%s\n",p_wmp_req_register->attr,\
			p_wmp_req_register->phone_num,p_wmp_req_register->email_addr);
	printf("***************************WM-req_register Protocol End************************\n");
}



/* Copy a new wmp_message_t instance. */
wmp_req_register_t *copy_wmp_req_register(const wmp_req_register_t *p_wmp_req_register)
{
    wmp_req_register_t *c_wmp_req_register = create_wmp_req_register();

    memcpy(c_wmp_req_register,p_wmp_req_register,sizeof(wmp_req_register_t));

    return c_wmp_req_register;
}


/* Create wmp_message_t instance. */
wmp_register_t *create_wmp_register()
{
	wmp_register_t *p_wmp_register = (wmp_register_t *)malloc(sizeof(wmp_register_t));
	memset(p_wmp_register,0,sizeof(wmp_register_t));
	return p_wmp_register;
}


/* Delete wmp_message_t instance. */
void delete_wmp_register(wmp_register_t **p_wmp_register)
{
	if(p_wmp_register && (*p_wmp_register))
	{
		free(*p_wmp_register);
		(*p_wmp_register) = NULL;
	}
}


/* Parser wmp_message_t instance. */
wmp_register_t *parser_wmp_register(const char *package,uint32_t pack_len)
{
	if(!package || pack_len<WMP_REGISTER_LENGTH)
	{
#ifdef WMP_DEBUG
		printf("[WMP] parser wmp_register_t failed.\n");
#endif
		return NULL;
	}

	uint32_t index = 0;
    wmp_register_t *p_wmp_register = create_wmp_register();
	p_wmp_register->attr = ntohs(*(uint16_t *)(package+index));
	index+=2;
	p_wmp_register->user_id = ntohl(*(uint32_t *)(package+index));
	index+=4;
	memcpy(p_wmp_register->identify_code,package+index,WMP_REGISTER_IDENTIFY_CODE_LENGTH);
	index+=WMP_REGISTER_IDENTIFY_CODE_LENGTH;
	return p_wmp_register;	
}


/* Package wmp_message_t instance. */
uint32_t package_wmp_register(char *package,const wmp_register_t *p_wmp_register)
{
	if(!package || !p_wmp_register)
	{
#ifdef WMP_DEBUG
		printf("[WMP] package wmp_register_t failed.\n");
#endif
		return 0;
	}

	uint32_t index = 0;
	*(uint16_t *)(package+index) = htons(p_wmp_register->attr);
	index+=2;
	*(uint32_t *)(package+index) = htonl(p_wmp_register->user_id);
	index+=4;
	memcpy(package+index,p_wmp_register->identify_code,WMP_REGISTER_IDENTIFY_CODE_LENGTH);
	index+=WMP_REGISTER_IDENTIFY_CODE_LENGTH;
	return index;	
}


/* Print wmp_message_t. */
void print_wmp_register(const wmp_register_t *p_wmp_register)
{
	if(!p_wmp_register)
	{
#ifdef WMP_DEBUG
		printf("[WMP] wmp_register_t is null.\n");
#endif
		return ;
	}

    printf("*****************************wm_reigster_start*****************************\n");
	printf("attr:%d;user_id:%d;identify_code:%s\n",p_wmp_register->attr,\
			p_wmp_register->user_id,p_wmp_register->identify_code);
    printf("******************************wm_reigster_end******************************\n");
}


/* Copy a new wmp_message_t instance. */
wmp_register_t *copy_wmp_register(const wmp_register_t *p_wmp_register)
{
    wmp_register_t *c_wmp_register = create_wmp_register();

    memcpy(c_wmp_register,p_wmp_register,sizeof(wmp_register_t));

    return c_wmp_register;
}
