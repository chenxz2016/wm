/* ************************************************************************
 *       Filename:  wmp_session.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_session.h"
#include<malloc.h>
#include<string.h>

#define WMP_SessionParamLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return WMP_PARSER_SESSION_FAILED;


/* **********************************************************************************************
 *	Allocate a wmp_session_cet_t structure.
 *
 *	@retval:	p_wm_session		The pointer to wmp_session_cet_t structure.
 *
 * **********************************************************************************************/
wmp_session_cet_t *allocate_wmp_session_cet()
{
	wmp_session_cet_t *p_wmp_session = (wmp_session_cet_t *)malloc(sizeof(wmp_session_cet_t));
	memset(p_wmp_session,0,sizeof(wmp_session_cet_t));
	return p_wmp_session;
}

/* **********************************************************************************************
 *	Deallocate a wmp_session_cet_t structure.
 *
 *	@param:	p_wm_session_cet	The pointer to wmp_session_cet_t structure.
 *
 * **********************************************************************************************/
void deallocate_wmp_session_cet(wmp_session_cet_t **p_wmp_session_cet)
{
	if(p_wmp_session_cet && (*p_wmp_session_cet))
	{
		free(*p_wmp_session_cet);
		(*p_wmp_session_cet) = NULL;
	}
}

/* **********************************************************************************************
 *	Copy a wmp_session_cet_t a new instance.
 *
 *	@param:	p_wm_session_cet	The pointer to wmp_session_cet_t structure.
 *  @retval:c_wm_session_cet    The pointer of new instance.
 *
 * **********************************************************************************************/
wmp_session_cet_t *copy_wmp_session_cet(wmp_session_cet_t *p_wmp_session_cet)
{
    wmp_session_cet_t *c_wmp_session_cet = allocate_wmp_session_cet();

    memcpy(c_wmp_session_cet,p_wmp_session_cet,sizeof(wmp_session_cet_t));

    return c_wmp_session_cet;
}

/* **********************************************************************************************
 *	Allocate a wmp_session_dsv_t structure.
 *
 *	@param:	p_wm_session_dsv	The pointer to wmp_session_dsv_t structure.
 *
 * **********************************************************************************************/
wmp_session_dsv_t *allocate_wmp_session_dsv()
{
	wmp_session_dsv_t *p_wmp_session_dsv = (wmp_session_dsv_t *)malloc(sizeof(wmp_session_dsv_t));
	memset(p_wmp_session_dsv,0,sizeof(wmp_session_dsv_t));
	return p_wmp_session_dsv;
}

/* **********************************************************************************************
 *	Deallocate a wmp_session_dsv_t structure.
 *
 *	@param:	p_wm_session_dsv	The pointer to wmp_session_dsv_t structure.
 *
 * **********************************************************************************************/
void deallocate_wmp_session_dsv(wmp_session_dsv_t **p_wmp_session_dsv)
{
	if(p_wmp_session_dsv && (*p_wmp_session_dsv))
	{
		free(*p_wmp_session_dsv);
		(*p_wmp_session_dsv) = NULL;
	}
}

/* **********************************************************************************************
 *	Copy a wmp_session_dsv_t a new instance.
 *
 *	@param:	p_wm_session_dsv	The pointer to wmp_session_dsv_t structure.
 *  @retval:c_wm_session_dsv    The pointer of new instance.
 *
 * **********************************************************************************************/
wmp_session_dsv_t *copy_wmp_session_dsv(wmp_session_dsv_t *p_wmp_session_dsv)
{
    wmp_session_dsv_t *c_wmp_session_dsv = allocate_wmp_session_dsv();

    memcpy(c_wmp_session_dsv,p_wmp_session_dsv,sizeof(wmp_session_dsv_t));

    return c_wmp_session_dsv;
}


/* **********************************************************************************************
 *	Allocate a wmp_session_ext_t structure.
 *
 *	@retval:	p_wm_session_ext	The pointer to wmp_session_ext_t structure.
 *
 * **********************************************************************************************/
wmp_session_ext_t *allocate_wmp_session_ext()
{
	wmp_session_ext_t *p_wmp_session_ext = (wmp_session_ext_t *)malloc(sizeof(wmp_session_ext_t));
	memset(p_wmp_session_ext,0,sizeof(wmp_session_ext_t));
	return p_wmp_session_ext;
}

/* **********************************************************************************************
 *	Deallocate a wmp_session_ext_t structure.
 *
 *	@param:	p_wm_session_ext	The pointer to wmp_session_ext_t structure.
 *
 * **********************************************************************************************/
void deallocate_wmp_session_ext(wmp_session_ext_t **p_wmp_session_ext)
{
	if(p_wmp_session_ext && (*p_wmp_session_ext))
	{
		free(*p_wmp_session_ext);
		(*p_wmp_session_ext) = NULL;
	}	
}

/* **********************************************************************************************
 *	Copy a wmp_session_ext_t a new instance.
 *
 *	@param:	p_wm_session_ext	The pointer to wmp_session_ext_t structure.
 *  @retval:c_wm_session_ext    The pointer of new instance.
 *
 * **********************************************************************************************/
wmp_session_ext_t *copy_wmp_session_ext(wmp_session_ext_t *p_wmp_session_ext)
{
    wmp_session_ext_t *c_wmp_session_ext = allocate_wmp_session_ext();

    memcpy(c_wmp_session_ext,p_wmp_session_ext,sizeof(wmp_session_ext_t));

    return c_wmp_session_ext;
}

/* **********************************************************************************************
 *	Allocate a wmp_session_msg_t structure.
 *
 *	@param:		msg_len				Message length.
 *
 *	@retval:	p_wm_session_msg	The pointer to wmp_session_msg_t structure.
 *
 * **********************************************************************************************/
wmp_session_msg_t *allocate_wmp_session_msg(uint16_t msg_len)
{
	wmp_session_msg_t *p_wmp_session_msg = (wmp_session_msg_t *)malloc(sizeof(wmp_session_msg_t));
	memset(p_wmp_session_msg,0,sizeof(wmp_session_msg_t));
	if(msg_len)
	{
		p_wmp_session_msg->msg_len = msg_len;
		p_wmp_session_msg->msg = (char *)malloc(msg_len);
		memset(p_wmp_session_msg->msg,0,msg_len);
	}
	return p_wmp_session_msg;
}

/* **********************************************************************************************
 *	Deallocate a wmp_session_msg_t structure.
 *
 *	@param:	p_wm_session_msg	The pointer to wmp_session_msg_t structure.
 *
 * **********************************************************************************************/
void deallocate_wmp_session_msg(wmp_session_msg_t **p_wmp_session_msg)
{
	if(p_wmp_session_msg && (*p_wmp_session_msg) && ((*p_wmp_session_msg))->msg)
	{
		free((*p_wmp_session_msg)->msg);
		(*p_wmp_session_msg)->msg = NULL;
		free(*p_wmp_session_msg);
		(*p_wmp_session_msg) = NULL;
		return ;
	}
	if(p_wmp_session_msg && (*p_wmp_session_msg))
	{
		free(*p_wmp_session_msg);
		(*p_wmp_session_msg) = NULL;		
	}
}

/* **********************************************************************************************
 *	Set wmp_session_msg_t message length.
 *
 *	@param:	p_wm_session_msg	The pointer to wmp_session_msg_t structure.
 *	@param:	msg_len				message length.
 *
 * **********************************************************************************************/
void set_wmp_session_msg_len(wmp_session_msg_t *p_wmp_session_msg,uint16_t msg_len)
{
	if(!p_wmp_session_msg || !msg_len)
		return ;
	
	if(p_wmp_session_msg->msg)
		free(p_wmp_session_msg->msg);
	
	p_wmp_session_msg->msg_len = msg_len;
	p_wmp_session_msg->msg = (char *)malloc(msg_len);
	memset(p_wmp_session_msg->msg,0,p_wmp_session_msg->msg_len);
}

/* **********************************************************************************************
 *	Copy wmp_session_msg_t a new instance.
 *
 *	@param:	p_wm_session_msg	The pointer to wmp_session_msg_t structure.
 *  @retval:c_wm_session_msg    The pointer of new instance.
 *
 * **********************************************************************************************/
wmp_session_msg_t *copy_wmp_session_msg(wmp_session_msg_t *p_wmp_session_msg)
{
    wmp_session_msg_t *c_wmp_session_msg = allocate_wmp_session_msg(p_wmp_session_msg->msg_len);

    c_wmp_session_msg->attr = p_wmp_session_msg->attr;
    c_wmp_session_msg->session_id = p_wmp_session_msg->session_id;
    memcpy(c_wmp_session_msg->msg,p_wmp_session_msg->msg,p_wmp_session_msg->msg_len);

    return c_wmp_session_msg;
}

/* **********************************************************************************************
 *	Allocate a wmp_session_fle_t structure.
 *
 *	@param:		file_len			File data length.
 *
 *	@retval:	p_wm_session_fle	The pointer to wmp_session_msg_t structure.
 *
 * **********************************************************************************************/
wmp_session_fle_t *allocate_wmp_session_fle(uint16_t file_len)
{
	wmp_session_fle_t *p_wmp_session_fle = (wmp_session_fle_t *)malloc(sizeof(wmp_session_fle_t));
	memset(p_wmp_session_fle,0,sizeof(wmp_session_fle_t));
	if(file_len)
	{
		p_wmp_session_fle->file_len = file_len;
		p_wmp_session_fle->file = (char *)malloc(file_len);
		memset(p_wmp_session_fle->file,0,file_len);
	}
	return p_wmp_session_fle;
}

/* **********************************************************************************************
 *	Deallocate a wmp_session_fle_t structure.
 *
 *	@param:		p_wmp_session_fle		The pointer of wmp_session_file_t pointer.
 *
 * **********************************************************************************************/
void deallocate_wmp_session_fle(wmp_session_fle_t **p_wmp_session_fle)
{
	if(p_wmp_session_fle && (*p_wmp_session_fle) && (*p_wmp_session_fle)->file)
	{
		free((*p_wmp_session_fle)->file);
		(*p_wmp_session_fle)->file = NULL;
		free(*p_wmp_session_fle);
		(*p_wmp_session_fle) = NULL;
		return ;		
	}
	if(p_wmp_session_fle && (*p_wmp_session_fle))
	{
		free(*p_wmp_session_fle);
		(*p_wmp_session_fle) = NULL;		
	}
}

/* **********************************************************************************************
 *	Set wmp_session_fle_t structure.
 *
 *	@param:		p_wmp_session_fle		The pointer of wmp_session_file_t pointer.
 *	@param:		file_len				File data length.
 *
 * **********************************************************************************************/
void set_wmp_session_fle_len(wmp_session_fle_t *p_wmp_session_fle,uint16_t file_len)
{
	if(!p_wmp_session_fle || !file_len)
		return ;
	
	if(p_wmp_session_fle->file)
		free(p_wmp_session_fle->file);
	
	p_wmp_session_fle->file_len = file_len;
	p_wmp_session_fle->file = (char *)malloc(file_len);
	memset(p_wmp_session_fle->file,0,file_len);
}

/* **********************************************************************************************
 *	Copy wmp_session_fle_t a new instance.
 *
 *	@param:		p_wmp_session_fle		The pointer of wmp_session_file_t pointer.
 *  @retval:    c_wmp_session_fle       The pointer of new instance.
 *
 * **********************************************************************************************/
wmp_session_fle_t *copy_wmp_session_fle(wmp_session_fle_t *p_wmp_session_fle)
{
    wmp_session_fle_t *c_wmp_session_fle = allocate_wmp_session_fle(p_wmp_session_fle->file_len);

    c_wmp_session_fle->attr = p_wmp_session_fle->attr;
    c_wmp_session_fle->session_id = p_wmp_session_fle->session_id;
    c_wmp_session_fle->block = p_wmp_session_fle->block;
    c_wmp_session_fle->sequence = p_wmp_session_fle->sequence;
    c_wmp_session_fle->filename_len = p_wmp_session_fle->filename_len;
    memcpy(c_wmp_session_fle->filename,p_wmp_session_fle->filename,p_wmp_session_fle->filename_len);
    memcpy(c_wmp_session_fle->file,p_wmp_session_fle->file,p_wmp_session_fle->file_len);

    return c_wmp_session_fle;
}


/* **********************************************************************************************
 *	Allocate wmp_session_ivt_t structure.
 *
 *	@param:		p_wmp_session_ivt	wmp_session_ivt_t pointer.
 *
 * **********************************************************************************************/
wmp_session_ivt_t *allocate_wmp_session_ivt()
{
	wmp_session_ivt_t *p_wmp_seesion_ivt = (wmp_session_ivt_t *)malloc(sizeof(wmp_session_ivt_t));
	memset(p_wmp_seesion_ivt,0,sizeof(wmp_session_ivt_t));
	return p_wmp_seesion_ivt;
}

/* **********************************************************************************************
 *	Deallocate wmp_session_ivt_t structure.
 *
 *	@param:		p_wmp_session_ivt	wmp_session_ivt_t pointer.
 *
 * **********************************************************************************************/
void deallocate_wmp_session_ivt(wmp_session_ivt_t **p_wmp_session_ivt)
{
	if(p_wmp_session_ivt && (*p_wmp_session_ivt))
	{
		free((*p_wmp_session_ivt));
		(*p_wmp_session_ivt) = NULL;
	}
}

/* **********************************************************************************************
 *	Copy wmp_session_ivt_t a new instance.
 *
 *	@param:		p_wmp_session_ivt	wmp_session_ivt_t pointer.
 *  @retval:    c_wmp_session_ivt   The pointer of new instance.
 *
 * **********************************************************************************************/
wmp_session_ivt_t *copy_wmp_session_ivt(wmp_session_ivt_t *p_wmp_session_ivt)
{
    wmp_session_ivt_t *c_wmp_session_ivt = allocate_wmp_session_ivt();

    memcpy(c_wmp_session_ivt,p_wmp_session_ivt,sizeof(wmp_session_ivt_t));

    return c_wmp_session_ivt;
}

/* **********************************************************************************************
 *	Allocate wmp_session_t structure.
 *
 *	@retval:		p_wmp_session		wmp_session_t pointer.
 *
 * **********************************************************************************************/
wmp_session_t *allocate_wmp_session()
{
	wmp_session_t *p_wmp_session = (wmp_session_t *)malloc(sizeof(wmp_session_t));
	memset(p_wmp_session,0,sizeof(wmp_session_t));
	return p_wmp_session;
}

/* **********************************************************************************************
 *	Deallocate wmp_session_t structure.
 *
 *	@param:		p_wmp_session		wmp_session_t pointer.
 *
 * **********************************************************************************************/
void deallocate_wmp_session(wmp_session_t **p_wmp_session)
{
	if(p_wmp_session && (*p_wmp_session) && (*p_wmp_session)->param)
	{
		free((*p_wmp_session)->param);
		(*p_wmp_session)->param = NULL;
		free((*p_wmp_session));
		(*p_wmp_session) = NULL;
		return ;
	}
	if(p_wmp_session && (*p_wmp_session))
	{
		free((*p_wmp_session));
		(*p_wmp_session) = NULL;		
	}
}

/* **********************************************************************************************
 *	Parser wmp_session_parameter_t structure.
 *
 *	@param:		package			package buffer.
 *	@param:		len				package buffer length.
 *	@param:		p_wmp_session	wmp_session_t pointer.
 *
 *	@retval:	index			wmp_session_t parameter length.
 *
 * **********************************************************************************************/
static int parser_wmp_session_parameter(const char *package,uint32_t len,wmp_session_t *p_wmp_session)
{
	uint32_t index = 0;
	wmp_session_cet_t *p_wmp_session_cet = NULL;
	wmp_session_dsv_t *p_wmp_session_dsv = NULL;
	wmp_session_ext_t *p_wmp_session_ext = NULL;
	wmp_session_msg_t *p_wmp_session_msg = NULL;
	wmp_session_fle_t *p_wmp_session_fle = NULL;
	wmp_session_ivt_t *p_wmp_session_ivt = NULL;
	switch(p_wmp_session->id)
	{
		case WMP_SESSION_CET_ID:
			WMP_SessionParamLenCheck(index,5,len)
			p_wmp_session_cet = allocate_wmp_session_cet();
			p_wmp_session_cet->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_cet->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session->param = (uint8_t *)p_wmp_session_cet;
			break;
		case WMP_SESSION_DSV_ID:
			WMP_SessionParamLenCheck(index,5,len)
			p_wmp_session_dsv = allocate_wmp_session_dsv();
			p_wmp_session_dsv->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_dsv->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session->param = (uint8_t *)p_wmp_session_dsv;
			break;
		case WMP_SESSION_EXT_ID:
			WMP_SessionParamLenCheck(index,5,len)
			p_wmp_session_ext = allocate_wmp_session_ext();
			p_wmp_session_ext->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_ext->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session->param = (uint8_t *)p_wmp_session_ext;
			break;
		case WMP_SESSION_MSG_ID:
			WMP_SessionParamLenCheck(index,7,len)
			
			p_wmp_session_msg = allocate_wmp_session_msg(0);
			p_wmp_session_msg->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_msg->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session_msg->msg_len = ntohs(*(uint16_t *)(package+index));
			index+=2;
			if((index+p_wmp_session_msg->msg_len)>len)
			{
				deallocate_wmp_session_msg(&p_wmp_session_msg);
				return WMP_PARSER_SESSION_FAILED;
			}
			p_wmp_session->param = (uint8_t *)p_wmp_session_msg;
			break;
		case WMP_SESSION_FLE_ID:
			WMP_SessionParamLenCheck(index,10,len)
			p_wmp_session_fle = allocate_wmp_session_fle(0);
			p_wmp_session_fle->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_fle->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session_fle->block = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session_fle->sequence = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session_fle->filename_len = *(uint8_t *)(package+index);
			index++;
			if((index+p_wmp_session_fle->filename_len)>len)
			{
				deallocate_wmp_session_fle(&p_wmp_session_fle);
				return WMP_PARSER_SESSION_FAILED;
			}
			memcpy(p_wmp_session_fle->filename,package+index,p_wmp_session_fle->filename_len);
			index+=p_wmp_session_fle->filename_len;
			p_wmp_session_fle->file_len = *(uint16_t *)(package+index);
			index+=2;
			if((index+p_wmp_session_fle->file_len)>len)
			{
				deallocate_wmp_session_fle(&p_wmp_session_fle);
				return WMP_PARSER_SESSION_FAILED;
			}
			memcpy(p_wmp_session_fle->file,package+index,p_wmp_session_fle->file_len);
			index+=p_wmp_session_fle->file_len;
			p_wmp_session->param = (uint8_t *)p_wmp_session_fle;
			break;
		case WMP_SESSION_IVT_ID:
			WMP_SessionParamLenCheck(index,9,len)
			p_wmp_session_ivt = allocate_wmp_session_ivt();
			p_wmp_session_ivt->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_ivt->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session_ivt->invite_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session->param = (uint8_t *)p_wmp_session_ivt;
			break;
	}
	return WMP_PARSER_SESSION_SUCCESS;
}

/* **********************************************************************************************
 *	Parser wmp_session_t structure.
 *
 *	@param:		package			package buffer.
 *	@param:		pack_len		package buffer length.
 *
 *	@retval:	p_wmp_session	wmp_session_t pointer.
 *
 * **********************************************************************************************/
wmp_session_t *parser_wmp_session(const char *package,uint32_t pack_len)
{
	uint32_t index=0;
	wmp_session_t *p_wmp_session = allocate_wmp_session();
	
	p_wmp_session->src = ntohl(*(uint32_t *)(package+index));
	index+=4;
	p_wmp_session->dst = ntohl(*(uint32_t *)(package+index));
	index+=4;
	p_wmp_session->id = ntohl(*(uint32_t *)(package+index));
	index+=4;
	
	int ret = parser_wmp_session_parameter(package,pack_len-index,p_wmp_session);
	if(ret!=WMP_PARSER_SESSION_SUCCESS)
	{
		deallocate_wmp_session(&p_wmp_session);
		return NULL;
	}
	return p_wmp_session;
}


/* **********************************************************************************************
 *	Package wmp_session_t parameter structure.
 *
 *	@param:		package			package buffer.
 *	@param:		p_wmp_session	wmp_session_t pointer.
 *
 *	@retval:	index			wmp_session_t parameter package length.
 *
 * **********************************************************************************************/
static int package_wmp_session_parameter(char *package,const wmp_session_t *p_wmp_session)
{
	uint32_t index = 0;
	wmp_session_cet_t *p_wmp_session_cet = NULL;
	wmp_session_dsv_t *p_wmp_session_dsv = NULL;
	wmp_session_ext_t *p_wmp_session_ext = NULL;
	wmp_session_msg_t *p_wmp_session_msg = NULL;
	wmp_session_fle_t *p_wmp_session_fle = NULL;
	wmp_session_ivt_t *p_wmp_session_ivt = NULL;
	switch(p_wmp_session->id)
	{
		case WMP_SESSION_CET_ID:
			p_wmp_session_cet = (wmp_session_cet_t *)p_wmp_session->param;
			*(uint8_t *)(package+index) = p_wmp_session_cet->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_cet->session_id);
			index+=4;
			break;
		case WMP_SESSION_DSV_ID:
			p_wmp_session_dsv = (wmp_session_dsv_t *)p_wmp_session->param;
			*(uint8_t *)(package+index) = p_wmp_session_dsv->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_dsv->session_id);
			index+=4;
			break;
		case WMP_SESSION_EXT_ID:
			p_wmp_session_ext = (wmp_session_ext_t *)p_wmp_session->param;
			*(uint8_t *)(package+index) = p_wmp_session_ext->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_ext->session_id);
			index+=4;
			break;
		case WMP_SESSION_MSG_ID:
			p_wmp_session_msg = (wmp_session_msg_t *)p_wmp_session->param;
			*(uint8_t *)(package+index) = p_wmp_session_msg->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_msg->session_id);
			index+=4;
			*(uint16_t *)(package+index) = htons(p_wmp_session_msg->msg_len);
			index+=2;
			memcpy(package+index,p_wmp_session_msg->msg,p_wmp_session_msg->msg_len);
			index+=p_wmp_session_msg->msg_len;
			break;
		case WMP_SESSION_FLE_ID:
			p_wmp_session_fle = (wmp_session_fle_t *)p_wmp_session->param;
			*(uint8_t *)(package+index) = p_wmp_session_fle->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_fle->session_id);
			index+=4;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_fle->block);
			index+=4;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_fle->sequence);
			index+=4;
			*(uint8_t *)(package+index) = p_wmp_session_fle->filename_len;
			index++;
			memcpy(package+index,p_wmp_session_fle->filename,p_wmp_session_fle->filename_len);
			index+=p_wmp_session_fle->filename_len;
			p_wmp_session_fle->file_len = *(uint16_t *)(package+index);
			index+=2;
			memcpy(package+index,p_wmp_session_fle->file,p_wmp_session_fle->file_len);
			index+=p_wmp_session_fle->file_len;
			break;
		case WMP_SESSION_IVT_ID:
			p_wmp_session_ivt = (wmp_session_ivt_t *)p_wmp_session->param;
			*(uint8_t *)(package+index) = p_wmp_session_ivt->attr;
			index++;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_ivt->session_id);
			index+=4;
			*(uint32_t *)(package+index) = htonl(p_wmp_session_ivt->invite_id);
			index+=4;
			break;
	}
	return WMP_PARSER_SESSION_SUCCESS;
}


/* **********************************************************************************************
 *	Package wmp_session_t structure.
 *
 *	@param:		package			package buffer.
 *	@param:		p_wmp_session	wmp_session_t pointer.
 *
 *	@retval:	index			wmp_session_t package length.
 *
 * **********************************************************************************************/
uint32_t package_wmp_session(char *package,const wmp_session_t *p_wmp_session)
{
	uint32_t index=0;
	
	*(uint32_t *)(package+index) = htonl(p_wmp_session->src);
	index+=4;

	*(uint32_t *)(package+index) = htonl(p_wmp_session->dst);
	index+=4;

	*(uint32_t *)(package+index) = htonl(p_wmp_session->id);
	index+=4;
	
	index += package_wmp_session_parameter(package,p_wmp_session);
	return index;	
}

/* **********************************************************************************************
 *	Print wmp_session_t structure.
 *
 *	@param:		p_wmp_session	wmp_session_t pointer.
 *
 * **********************************************************************************************/
void print_wmp_session(const wmp_session_t *p_wmp_session)
{
	if(!p_wmp_session)
	{
#ifdef WMP_DEBUG
		printf("[WMP] wmp_session_t is null.\n");
#endif
		return ;
	}

	printf("***************************WM-session Protocol Start**********************\n");

	printf("src:%d;dst:%d;id:%d;",p_wmp_session->src,p_wmp_session->dst,p_wmp_session->id);

	wmp_session_cet_t *p_wmp_session_cet = NULL;
	wmp_session_dsv_t *p_wmp_session_dsv = NULL;
	wmp_session_ext_t *p_wmp_session_ext = NULL;
	wmp_session_msg_t *p_wmp_session_msg = NULL;
	wmp_session_fle_t *p_wmp_session_fle = NULL;
	wmp_session_ivt_t *p_wmp_session_ivt = NULL;
	switch(p_wmp_session->id)
	{
		case WMP_SESSION_CET_ID:
			p_wmp_session_cet = (wmp_session_cet_t *)(p_wmp_session->param);
			if(!p_wmp_session_cet)
			{
#ifdef WMP_DEBUG
				printf("wmp_session_t parameter is null.\n");
#endif
				break;
			}
			printf("attr:%02x;session_id:%d;\n",p_wmp_session_cet->attr,\
					p_wmp_session_cet->session_id);
			break;
		case WMP_SESSION_DSV_ID:
			p_wmp_session_dsv = (wmp_session_dsv_t *)(p_wmp_session->param);
			if(!p_wmp_session_dsv)
			{
#ifdef WMP_DEBUG
				printf("wmp_session_t parameter is null.\n");
#endif
				break;
			}
			printf("attr:%02x;session_id:%d;\n",p_wmp_session_dsv->attr,\
					p_wmp_session_dsv->session_id);
			break;
		case WMP_SESSION_EXT_ID:
			p_wmp_session_ext = (wmp_session_ext_t *)(p_wmp_session->param);
			if(!p_wmp_session_ext)
			{
#ifdef WMP_DEBUG
				printf("wmp_session_t parameter is null.\n");
#endif
				break;
			}
			printf("attr:%02x;session_id:%d;\n",p_wmp_session_ext->attr,\
					p_wmp_session_ext->session_id);
			break;
		case WMP_SESSION_MSG_ID:
			p_wmp_session_msg = (wmp_session_msg_t *)(p_wmp_session->param);
			if(!p_wmp_session_msg)
			{
#ifdef WMP_DEBUG
				printf("wmp_session_t parameter is null.\n");
#endif
				break;
			}
			printf("attr:%02x;session_id:%d;msg_len:%d;msg:%s;\n",p_wmp_session_msg->attr,\
					p_wmp_session_msg->session_id,p_wmp_session_msg->msg_len,\
					p_wmp_session_msg->msg);
			break;
		case WMP_SESSION_FLE_ID:
			p_wmp_session_fle = (wmp_session_fle_t *)(p_wmp_session->param);
			if(!p_wmp_session_fle)
			{
#ifdef WMP_DEBUG
				printf("wmp_session_t parameter is null.\n");
#endif
				break;
			}
			printf("attr:%02x;session_id:%d;block:%d;sequence:%d;filename_len:%d;filename:%s;"
					"file_len:%d;\n",p_wmp_session_fle->attr,p_wmp_session_fle->session_id,\
					p_wmp_session_fle->block,p_wmp_session_fle->sequence,p_wmp_session_fle->filename_len,\
					p_wmp_session_fle->filename,p_wmp_session_fle->file_len);
			break;
		case WMP_SESSION_IVT_ID:
			p_wmp_session_ivt = (wmp_session_ivt_t *)(p_wmp_session->param);
			if(!p_wmp_session_ivt)
			{
#ifdef WMP_DEBUG
				printf("wmp_session_t parameter is null.\n");
#endif
				break;
			}
			printf("attr:%02x;session_id:%d;\n",p_wmp_session_ivt->attr,\
					p_wmp_session_ivt->session_id);
			break;
	}

	printf("***************************WM-session Protocol End***********************\n");
}


/* **********************************************************************************************
 *	Copy wmp_session_t a new instance.
 *
 *	@param:		p_wmp_session	wmp_session_t pointer.
 *  @retval:    c_wmp_session   The pointer of new instance.
 *
 * **********************************************************************************************/
wmp_session_t *copy_wmp_session(const wmp_session_t *p_wmp_session)
{
    wmp_session_t *c_wmp_session = allocate_wmp_session();

    c_wmp_session->src = p_wmp_session->src;
    c_wmp_session->dst = p_wmp_session->dst;
    c_wmp_session->id = p_wmp_session->id;

    switch(p_wmp_session->id)
    {
        case WMP_SESSION_CET_ID:
            c_wmp_session->param = copy_wmp_session_cet((wmp_session_cet_t *)p_wmp_session->param);
            break;
        case WMP_SESSION_DSV_ID:
            c_wmp_session->param = copy_wmp_session_dsv((wmp_session_dsv_t *)p_wmp_session->param);
            break;
        case WMP_SESSION_EXT_ID:
            c_wmp_session->param = copy_wmp_session_ext((wmp_session_ext_t *)p_wmp_session->param);
            break;
        case WMP_SESSION_MSG_ID:
            c_wmp_session->param = copy_wmp_session_msg((wmp_session_msg_t *)p_wmp_session->param);
            break;
        case WMP_SESSION_FLE_ID:
            c_wmp_session->param = copy_wmp_session_fle((wmp_session_fle_t *)p_wmp_session->param);
            break;
        case WMP_SESSION_IVT_ID:
            c_wmp_session->param = copy_wmp_session_ivt((wmp_session_ivt_t *)p_wmp_session->param);
            break;
        default:
            break;
    }

    return c_wmp_session;
}



