/* ************************************************************************
 *       Filename:  wm_protocol.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wm_protocol.h"
#include<malloc.h>
#include<string.h>

#include "wmp_beat_heart.h"
#include "wmp_file.h"
#include "wmp_group.h"
#include "wmp_login.h"
#include "wmp_message.h"
#include "wmp_register.h"
#include "wmp_session.h"
#include "wmp_sound.h"
#include "wmp_user.h"
#include "wmp_video.h"

#define WMP_CheckLen(index,delt,len) \
	if((index+delt)>len) \
		return WMP_PARSER_FAILED;

#define WMP_CheckPackLen(index,delt,len,p_wm) \
	if((index+delt)>len) \
	{\
		deallocate_wmp(&p_wm);\
		return NULL;\
	}


/* **********************************************************************************************
 *	Allocate a wm_protocol_t structure.
 *
 *	@param:		param_num		wm_protocol_t parameter numbers.
 *	@retval:	p_wm			The pointer to wm_protocol_t structure.
 *
 *	If param_num is 0, p_wm will not assign any wm_parameter_t.
 *
 * **********************************************************************************************/
wm_protocol_t *allocate_wmp(uint16_t param_num)
{
	wm_protocol_t *p_wm = (wm_protocol_t *)malloc(sizeof(wm_protocol_t));
	memset(p_wm,0,sizeof(wm_protocol_t));

	/* check param_num parameter. */
	if(param_num)
	{
		p_wm->body.param_num = param_num;
		p_wm->body.param = (wm_parameter_t *)malloc(sizeof(wm_parameter_t)*param_num);
		memset(p_wm->body.param,0,sizeof(wm_parameter_t)*param_num);
	}

	return p_wm;
}


/* **********************************************************************************************
 *	Free a wm_protocol_t structure.
 *
 *	@param:		p_wm			The pointer of the pointer to wm_protocol_t structure.
 *
 * **********************************************************************************************/
void deallocate_wmp(wm_protocol_t **p_wm)
{
	/* If p_wm contains parameters. */
	if(p_wm && (*p_wm) && (*p_wm)->body.param)
	{
		/* Free all parameter data. */
		for(uint16_t i=0;i<(*p_wm)->body.param_num;i++)
		{
			if((*p_wm)->body.param[i].data)
			{
				free((*p_wm)->body.param[i].data);
				(*p_wm)->body.param[i].data = NULL;
			}
		}

		/* Free parameters. */
		free((*p_wm)->body.param);
		(*p_wm)->body.param = NULL;

		/* Free wm_protocol_t. */
		free((*p_wm));
		(*p_wm) = NULL;
		return ;
	}

	/* If p_wm doesn't contian parameters. */
	if(p_wm && (*p_wm))
	{
		free((*p_wm));
		(*p_wm) = NULL;
	}
}


/* **********************************************************************************************
 *	Set wm_body_t parameter numbers.
 *
 *	@param:		p_wm_body		The pointer to wm_body_t structure.
 *	@param:		param_num		Parameter numbers.
 *
 * **********************************************************************************************/
void set_wmp_body_param_num(wm_body_t *p_wm_body,uint16_t num)
{
	/* Check parameters. */
	if(!p_wm_body || !num)
		return ;

	/* Free body parameter, if contians it. */
	if(p_wm_body->param)
	{
		/* Free every parameters data. */
		for(uint16_t i=0;i<p_wm_body->param_num;i++)
		{
			if(p_wm_body->param[i].data)
			{
				free(p_wm_body->param[i].data);
				p_wm_body->param[i].data = NULL;
			}
		}
		free(p_wm_body->param);
	}

	/* Reallocate parameters. */
	p_wm_body->param_num = num;
	p_wm_body->param = (wm_parameter_t *)malloc(sizeof(wm_parameter_t)*num);
	memset(p_wm_body->param,0,sizeof(wm_parameter_t)*num);
}

/* **********************************************************************************************
 *	Set wm_parameter_t data length.
 *
 *	@param:		p_wm_param		The pointer to wm_parameter_t structure.
 *	@param:		len				Parameter data length.
 *
 * **********************************************************************************************/
void set_wmp_param_len(wm_parameter_t *p_wm_param,uint16_t len)
{
	/* Check parameters. */
	if(!p_wm_param || !len)
		return ;

	/* Free parameter data. */
	if(p_wm_param->data)
		free(p_wm_param->data);

	/* Reallocate parameter data. */
	p_wm_param->length = len;
	p_wm_param->data = (char *)malloc(len);
	memset(p_wm_param->data,0,len);
}

/* **********************************************************************************************
 *	Check protocol_package for wm_protocol head and tail.
 *
 *	@param:		package		The pointer to wm_parameter_t structure.
 *	
 *	@retval: WMP_PARSER_SUCCESS		protocol_package head and tail is compatible for wm_protocol.
 *	@retval: WMP_PARSER_FAILED		protocol_package head and tail is not compatible for wm_protocol.
 *
 * **********************************************************************************************/
static int check_head_tail(const protocol_package *package)
{
	if(*(uint8_t *)package->data==WMP_HEAD_ID && *(uint8_t *)(package->data+package->length-1)==WMP_TAIL_ID)
		return WMP_PARSER_SUCCESS;
	return WMP_PARSER_FAILED;
}

/* **********************************************************************************************
 *	Parser wm_base_t.
 *
 *	@param:		package		Raw package data.
 *	@param:		pack_len	Raw package data length.
 *	@param:		p_wm_base	The pointer to wm_base_t structure.
 *	
 *	@retval: WMP_PARSER_SUCCESS		parser success.
 *	@retval: WMP_PARSER_FAILED		parser failed.
 *
 * **********************************************************************************************/
static int parser_wmp_base(const char *package,uint32_t pack_len,wm_base_t *p_base)
{
	uint32_t index = 0;

	/* Check length. */
	WMP_CheckLen(index,WMP_BASE_LENGTH,pack_len)

	/* Parser wm_base_t. */
	p_base->proto_type = ntohs(*(uint16_t *)(package+index));
	index+=2;
	p_base->src = ntohl(*(uint32_t *)(package+index));
	index+=4;
	p_base->dst = ntohl(*(uint32_t *)(package+index));
	index+=4;
	memcpy(p_base->device,package+index,24);
	index+=24;
	p_base->network = *(uint8_t *)(package+index);
	index++;
	p_base->time = ntohl(*(uint32_t *)(package+index));
	index+=4;
	memcpy(p_base->version,package+index,10);
	index+=10;
	return WMP_PARSER_SUCCESS;
}

/* **********************************************************************************************
 *	Parser wm_body_t.
 *
 *	@param:		package		Raw package data.
 *	@param:		pack_len	Raw package data length.
 *	@param:		p_wm_body	The pointer to wm_body_t structure.
 *	
 *	@retval: WMP_PARSER_SUCCESS		parser success.
 *	@retval: WMP_PARSER_FAILED		parser failed.
 *
 * **********************************************************************************************/
static int parser_wmp_body(const char *package,uint32_t pack_len,wm_body_t *p_wm_body)
{
	uint32_t index = 0;

	/* Check length for main_id and param_num. */
    WMP_CheckLen(index,4,pack_len)
	p_wm_body->param_num = ntohs(*(uint16_t *)(package+index));
	index+=2;

	/* Set wm_body_t parameter numbers. */
	set_wmp_body_param_num(p_wm_body,p_wm_body->param_num);

	for(uint16_t i=0;i<p_wm_body->param_num;i++)
	{
		/* Check length for attr and length. */
		WMP_CheckLen(index,6,pack_len)

		p_wm_body->param[i].attr = ntohl(*(uint32_t *)(package+index));
		index+=4;

        p_wm_body->param[i].main_id = ntohs(*(uint16_t *)(package+index));
        index+=2;

        p_wm_body->param[i].length = ntohl(*(uint32_t *)(package+index));
        index+=4;

        switch(p_wm_body->param[i].main_id)
        {
        case WMP_PROTO_LOGIN_KEY_ID:
        {
            wmp_login_key_t *key = parser_wmp_login_key(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)key;
            break;
        }
        case WMP_PROTO_LOGIN_ID:
        {
            wmp_login_t *login = parser_wmp_login(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)login;
            break;
        }
        case WMP_PROTO_BH_ID:
        {
            wmp_beat_heart_t *bh = parser_wmp_beat_heart(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)bh;
            break;
        }
        case WMP_PROTO_FILE_ID:
        {
            wmp_file_t *file = parser_wmp_file(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)file;
            break;
        }
        case WMP_PROTO_GROUP_ID:
        {
            wmp_group_t *group = parser_wmp_group(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)group;
            break;
        }
        case WMP_PROTO_MSG_ID:
        {
            wmp_message_t *msg = parser_wmp_message(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)msg;
            break;
        }
        case WMP_PROTO_REGISTER_ID:
        {
            wmp_register_t *reg = parser_wmp_register(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)reg;
            break;
        }
        case WMP_PROTO_SESSION_ID:
        {
            wmp_session_t *session = parser_wmp_session(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)session;
            break;
        }
        case WMP_PROTO_SOUND_ID:
        {
            wmp_sound_t *sound = parser_wmp_sound(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)sound;
            break;
        }
        case WMP_PROTO_VIDEO_ID:
        {
            wmp_video_t *video = parser_wmp_video(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)video;
            break;
        }
        case WMP_PROTO_USER_ID:
        {
            wmp_user_t *user = parser_wmp_user(package+index,pack_len-index);
            p_wm_body->param[i].data = (char *)user;
            break;
        }
        default:
            break;
        }
        index += p_wm_body->param[i].length;
	}
	return WMP_PARSER_SUCCESS;
}

/* **********************************************************************************************
 *	Parser wm_protocol_t.
 *
 *	@param:		package		The pointer to protocol_package.
 *	@param:		key			Encrypt key.
 *	@param:		key_len		Encrypt key length.
 *	
 *	@retval:	p_wm		Parsered wm_protocol_t pointer.
 *	@retval:	NULL		Parser failed.
 *
 * **********************************************************************************************/
wm_protocol_t *parser_wmp(const protocol_package *package,const char *key,const uint16_t key_len)
{
	if(check_head_tail(package)==WMP_PARSER_FAILED)
	{
#ifdef WMP_DEBUG
		printf("Check head and tail failed.\n");
#endif
		return NULL;
	}

	uint32_t index = 0;
	wm_protocol_t *p_wm = allocate_wmp(0);

	/* Check length for head, sequence, crc_check, attr and length. */
	WMP_CheckPackLen(index,WMP_BASE_INDEX,package->length,p_wm)

	p_wm->head = *(uint8_t *)(package->data+index);
	index++;
	p_wm->sequence = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	p_wm->crc_check = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	p_wm->attr = ntohl(*(uint32_t *)(package->data+index));
	index+=4;
	p_wm->length = ntohl(*(uint32_t *)(package->data+index));
	index+=4;

	if(WMP_CRC32Flag(p_wm))
	{
		uint32_t crc32 = crc32_check_char_buffer(package->data+index,package->length-index-1);
		if(crc32 != p_wm->crc_check)
		{
#ifdef WMP_DEBUG
			printf("CRC32 check failed,check crc32:%d, real crc32:%d\n",crc32,p_wm->crc_check);
#endif
			deallocate_wmp(&p_wm);
			return NULL;
		}
	}

	int ret = parser_wmp_base(package->data+index,package->length-index,&p_wm->base);
	if(ret!=WMP_PARSER_SUCCESS)
	{
#ifdef WMP_DEBUG
		printf("Parser base failed.\n");
#endif
		deallocate_wmp(&p_wm);
		return NULL;
	}

	index+=49;

	ret = parser_wmp_body(package->data+index,package->length-index,&p_wm->body);
	if(ret!=WMP_PARSER_SUCCESS)
	{
#ifdef WMP_DEBUG
		printf("Parser body failed.\n");
#endif
		deallocate_wmp(&p_wm);
		return NULL;
	}
	p_wm->tail = *(uint8_t *)(package->data+package->length-1);
	return p_wm;
}

/* **********************************************************************************************
 *	Package wm_base_t.
 *
 *	@param:		package		The buffer to write.
 *	@param:		p_wm_base	The pointer to wm_base_t.
 *	
 *	@retval:	index		The index of writing wm_base_t, it should be WMP_BASE_LENGTH.
 *
 * **********************************************************************************************/
static uint32_t package_wmp_base(char *package,const wm_base_t *p_wm_base)
{
	uint32_t index = 0;

	*(uint16_t *)(package+index) = htons(p_wm_base->proto_type);
	index+=2;

	*(uint32_t*)(package+index) = htonl(p_wm_base->src);
	index+=4;

	*(uint32_t *)(package+index) = htonl(p_wm_base->dst);
	index+=4;

	memcpy(package+index,p_wm_base->device,24);
	index+=24;

	*(uint8_t *)(package+index) = p_wm_base->network;
	index++;

	*(uint32_t *)(package+index) = htonl(p_wm_base->time);
	index+=4;

	memcpy(package+index,p_wm_base->version,10);
	index+=10;

	return index;
}

/* **********************************************************************************************
 *	Package wm_body_t.
 *
 *	@param:		package		The buffer to write.
 *	@param:		p_wm_body	The pointer to wm_body_t.
 *	
 *	@retval:	index		The index of writing wm_body_t.
 *
 * **********************************************************************************************/
static uint32_t package_wmp_body(char *package,const wm_body_t *p_wm_body)
{
	uint32_t index = 0;

	*(uint16_t *)(package+index) = htons(p_wm_body->param_num);
	index+=2;

    for(uint16_t i=0;i<p_wm_body->param_num;i++)
	{
		*(uint32_t *)(package+index) = htonl(p_wm_body->param[i].attr);
		index+=4;

        *(uint16_t *)(package+index) = htons(p_wm_body->param[i].main_id);
        index+=2;

        uint32_t *len_ptr = NULL;
        len_ptr = (uint32_t *)(package+index);
        index+=4;
        switch(p_wm_body->param[i].main_id)
        {
        case WMP_PROTO_LOGIN_KEY_ID:
        {
            wmp_login_key_t *key = (wmp_login_key_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_login_key(package+index,key);
            break;
        }
        case WMP_PROTO_LOGIN_ID:
        {
            wmp_login_t *login = (wmp_login_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_login(package+index,login);
            break;
        }
        case WMP_PROTO_BH_ID:
        {
            wmp_beat_heart_t *bh = (wmp_beat_heart_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_beat_heart(package+index,bh);
            break;
        }
        case WMP_PROTO_FILE_ID:
        {
            wmp_file_t *file = (wmp_file_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_file(package+index,file);
            break;
        }
        case WMP_PROTO_GROUP_ID:
        {
            wmp_group_t *group = (wmp_group_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_group(package+index,group);
            break;
        }
        case WMP_PROTO_MSG_ID:
        {
            wmp_message_t *msg = (wmp_message_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_message(package+index,msg);
            break;
        }
        case WMP_PROTO_REGISTER_ID:
        {
            wmp_register_t *reg = (wmp_register_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_register(package+index,reg);
            break;
        }
        case WMP_PROTO_SESSION_ID:
        {
            wmp_session_t *session = (wmp_session_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_session(package+index,session);
            break;
        }
        case WMP_PROTO_SOUND_ID:
        {
            wmp_sound_t *sound = (wmp_sound_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_sound(package+index,sound);
            break;
        }
        case WMP_PROTO_VIDEO_ID:
        {
            wmp_video_t *video = (wmp_video_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_video(package+index,video);
            break;
        }
        case WMP_PROTO_USER_ID:
        {
            wmp_user_t *user = (wmp_user_t *)p_wm_body->param[i].data;
            p_wm_body->param[i].length = package_wmp_user(package+index,user);
            break;
        }
        default:
            break;
        }

        (*len_ptr) = htonl(p_wm_body->param[i].length);
        index += p_wm_body->param[i].length;
	}
	return index;
}

/* **********************************************************************************************
 *	Package wm_protocol_t.
 *
 *	@param:		p_wm		The pointer to wm_protocol_t.
 *	@param:		key			Encrypt key.
 *	@param:		key_len		Encrypt key length.
 *	
 *	@retval:	pp			The pointer to protocol_package.
 *
 * **********************************************************************************************/
protocol_package *package_wmp(const wm_protocol_t *p_wm,const char *key,const uint16_t key_len)
{
    char buffer[5*1024]="";
	uint32_t index = 0;
	uint32_t *crc_ptr = NULL;
	uint32_t *len_ptr = NULL;

	*(uint8_t *)(buffer+index) = p_wm->head;
	index++;

	*(uint32_t *)(buffer+index) = htonl(p_wm->sequence);
	index+=4;

	*(uint32_t *)(buffer+index) = htonl(p_wm->crc_check);
	crc_ptr = (uint32_t *)(buffer+index);
	index+=4;

	*(uint32_t *)(buffer+index) = htonl(p_wm->attr);
	index+=4;

	*(uint32_t *)(buffer+index) = htonl(p_wm->length);
	len_ptr = (uint32_t *)(buffer+index);
	index+=4;

	index += package_wmp_base(buffer+index,&p_wm->base);

	index += package_wmp_body(buffer+index,&p_wm->body);
	
	*(uint8_t *)(buffer+index) = p_wm->tail;
	index++;

	if(WMP_CRC32Flag(p_wm))
	{
		*crc_ptr = htonl(crc32_check_char_buffer(buffer+17,index-18));
	}
	*len_ptr = htonl(index);

	protocol_package *package = allocate_package(index);
	memcpy(package->data,buffer,index);
	return package;
}

/* **********************************************************************************************
 *	Print wm_base_t.
 *
 *	@param:		p_wm_base	The pointer to wm_base_t.
 *
 * **********************************************************************************************/
static void print_wmp_base(const wm_base_t *p_wm_base)
{
	printf("wm_base_t:\n");
	printf("proto_type:%02x;src:%d;dst:%d;device:%s;network:%d;time:%d;version:%s;\n",
			p_wm_base->proto_type,p_wm_base->src,p_wm_base->dst,p_wm_base->device,
			p_wm_base->network,p_wm_base->time,p_wm_base->version);
}

/* **********************************************************************************************
 *	Print wm_body_t.
 *
 *	@param:		p_wm_body	The pointer to wm_body_t.
 *
 * **********************************************************************************************/
static void print_wmp_body(const wm_body_t *p_wm_body)
{
	printf("wm_body_t:\n");
    printf("param_num:%d;\n",p_wm_body->param_num);
	printf("wm_parameter_t:\n");
	for(uint16_t i=0;i<p_wm_body->param_num;i++)
	{
        printf("main_id:%d;index:%d;attr:%d;length:%d\n",\
                p_wm_body->param[i].main_id,i,p_wm_body->param[i].attr,p_wm_body->param[i].length);
	}
}

/* **********************************************************************************************
 *	Print wm_protocol_t.
 *
 *	@param:		p_wm		The pointer to wm_protocol_t.
 *
 * **********************************************************************************************/
void print_wmp(const wm_protocol_t *p_wm)
{
	if(!p_wm)
		return ;
	printf("**********************************wmp start********************************\n");

	printf("head:%02x;tail:%02x;sequence:%d;attr:%d;length:%d;\n",\
			p_wm->head,p_wm->tail,p_wm->sequence,p_wm->attr,p_wm->length);

	print_wmp_base(&p_wm->base);
	print_wmp_body(&p_wm->body);

	printf("***********************************wmp end*********************************\n");
}


/* **********************************************************************************************
 *	Copy wm_protocol_t a new instance.
 *
 *	@param:		p_wm		The pointer to wm_protocol_t.
 *  @retval:    c_wm        The pointer to new wm_protocol_t instance.
 *
 * **********************************************************************************************/
wm_protocol_t * copy_wmp(const wm_protocol_t *p_wm)
{
    wm_protocol_t *c_wm = allocate_wmp(p_wm->body.param_num);
    c_wm->head = p_wm->head;
    c_wm->sequence = p_wm->sequence;
    c_wm->crc_check = p_wm->crc_check;
    c_wm->attr = p_wm->attr;
    c_wm->length = p_wm->length;
    c_wm->tail = p_wm->tail;
    memcpy(&c_wm->base,&p_wm->base,sizeof(wm_base_t));
    c_wm->body.param_num = p_wm->body.param_num;
    for(uint16_t i=0;i<p_wm->body.param_num;i++)
    {
        c_wm->body.param[i].attr = p_wm->body.param[i].attr;
        c_wm->body.param[i].main_id = p_wm->body.param[i].main_id;
        c_wm->body.param[i].length = p_wm->body.param[i].length;
        switch(p_wm->body.param[i].main_id)
        {
        case WMP_PROTO_LOGIN_KEY_ID:
        {
            c_wm->body.param[i].data = copy_wmp_login_key((wmp_login_key_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_LOGIN_ID:
        {
            c_wm->body.param[i].data = copy_wmp_login((wmp_login_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_BH_ID:
        {
            c_wm->body.param[i].data = copy_wmp_beat_heart((wmp_beat_heart_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_FILE_ID:
        {
            c_wm->body.param[i].data = copy_wmp_file((wmp_file_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_GROUP_ID:
        {
            c_wm->body.param[i].data = copy_wmp_group((wmp_group_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_MSG_ID:
        {
            c_wm->body.param[i].data = copy_wmp_message((wmp_message_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_REGISTER_ID:
        {
            c_wm->body.param[i].data = copy_wmp_register((wmp_register_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_SESSION_ID:
        {
            c_wm->body.param[i].data = copy_wmp_session((wmp_session_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_SOUND_ID:
        {
            c_wm->body.param[i].data = copy_wmp_sound((wmp_sound_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_VIDEO_ID:
        {
            c_wm->body.param[i].data = copy_wmp_video((wmp_video_t *)p_wm->body.param[i].data);
            break;
        }
        case WMP_PROTO_USER_ID:
        {
            c_wm->body.param[i].data = copy_wmp_user((wmp_user_t *)p_wm->body.param[i].data);
            break;
        }
        default:
            break;
        }
    }

    return c_wm;
}


