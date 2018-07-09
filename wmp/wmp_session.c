/* ************************************************************************
 *       Filename:  wmp_session.c
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
#include"wmp_session.h"

#define WMP_SessionParamLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return WMP_PARSER_SESSION_FAILED;


/* Create wmp_session_cet_t instance. */
wmp_session_cet_t *create_wmp_session_cet()
{
	wmp_session_cet_t *p_wmp_session = (wmp_session_cet_t *)malloc(sizeof(wmp_session_cet_t));
	memset(p_wmp_session,0,sizeof(wmp_session_cet_t));
	return p_wmp_session;
}


/* Delete wmp_session_cet_t instance. */
void delete_wmp_session_cet(wmp_session_cet_t **p_wmp_session_cet)
{
	if(p_wmp_session_cet && (*p_wmp_session_cet))
	{
		free(*p_wmp_session_cet);
		(*p_wmp_session_cet) = NULL;
	}
}


/* Copy a new wmp_session_cet_t instance. */
wmp_session_cet_t *copy_wmp_session_cet(const wmp_session_cet_t *p_wmp_session_cet)
{
    wmp_session_cet_t *c_wmp_session_cet = create_wmp_session_cet();

    memcpy(c_wmp_session_cet,p_wmp_session_cet,sizeof(wmp_session_cet_t));

    return c_wmp_session_cet;
}


/* Create wmp_session_dsv_t structure. */
wmp_session_dsv_t *create_wmp_session_dsv()
{
	wmp_session_dsv_t *p_wmp_session_dsv = (wmp_session_dsv_t *)malloc(sizeof(wmp_session_dsv_t));
	memset(p_wmp_session_dsv,0,sizeof(wmp_session_dsv_t));
	return p_wmp_session_dsv;
}


/* Delete wmp_session_dsv_t instance. */
void delete_wmp_session_dsv(wmp_session_dsv_t **p_wmp_session_dsv)
{
	if(p_wmp_session_dsv && (*p_wmp_session_dsv))
	{
		free(*p_wmp_session_dsv);
		(*p_wmp_session_dsv) = NULL;
	}
}

/* Copy a new wmp_session_dsv_t instance. */
wmp_session_dsv_t *copy_wmp_session_dsv(const wmp_session_dsv_t *p_wmp_session_dsv)
{
    wmp_session_dsv_t *c_wmp_session_dsv = create_wmp_session_dsv();

    memcpy(c_wmp_session_dsv,p_wmp_session_dsv,sizeof(wmp_session_dsv_t));

    return c_wmp_session_dsv;
}



/* Create wmp_session_ext_t instance. */
wmp_session_ext_t *create_wmp_session_ext()
{
	wmp_session_ext_t *p_wmp_session_ext = (wmp_session_ext_t *)malloc(sizeof(wmp_session_ext_t));
	memset(p_wmp_session_ext,0,sizeof(wmp_session_ext_t));
	return p_wmp_session_ext;
}


/* Delete wmp_session_ext_t structure. */
void delete_wmp_session_ext(wmp_session_ext_t **p_wmp_session_ext)
{
	if(p_wmp_session_ext && (*p_wmp_session_ext))
	{
		free(*p_wmp_session_ext);
		(*p_wmp_session_ext) = NULL;
	}	
}


/* Copy a new wmp_session_ext_t instance. */
wmp_session_ext_t *copy_wmp_session_ext(const wmp_session_ext_t *p_wmp_session_ext)
{
    wmp_session_ext_t *c_wmp_session_ext = create_wmp_session_ext();

    memcpy(c_wmp_session_ext,p_wmp_session_ext,sizeof(wmp_session_ext_t));

    return c_wmp_session_ext;
}


/* Create wmp_session_msg_t instance. */
wmp_session_msg_t *create_wmp_session_msg(uint16_t msg_len)
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

/* Delete wmp_session_msg_t structure. */
void delete_wmp_session_msg(wmp_session_msg_t **p_wmp_session_msg)
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


/* Set wmp_session_msg_t length. */
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


/* Copy wmp_session_msg_t a new instance. */
wmp_session_msg_t *copy_wmp_session_msg(wmp_session_msg_t *p_wmp_session_msg)
{
    wmp_session_msg_t *c_wmp_session_msg = create_wmp_session_msg(p_wmp_session_msg->msg_len);

    c_wmp_session_msg->attr = p_wmp_session_msg->attr;
    c_wmp_session_msg->session_id = p_wmp_session_msg->session_id;
    memcpy(c_wmp_session_msg->msg,p_wmp_session_msg->msg,p_wmp_session_msg->msg_len);

    return c_wmp_session_msg;
}

/* Create wmp_session_fle_t structure. */
wmp_session_fle_t *create_wmp_session_fle(uint16_t file_len)
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

/* Delete wmp_session_fle_t instance. */
void delete_wmp_session_fle(wmp_session_fle_t **p_wmp_session_fle)
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

/* Set wmp_session_fle_t file size. */
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


/* Copy a new wmp_session_fle_t instance. */
wmp_session_fle_t *copy_wmp_session_fle(const wmp_session_fle_t *p_wmp_session_fle)
{
    wmp_session_fle_t *c_wmp_session_fle = create_wmp_session_fle(p_wmp_session_fle->file_len);

    c_wmp_session_fle->attr = p_wmp_session_fle->attr;
    c_wmp_session_fle->session_id = p_wmp_session_fle->session_id;
    c_wmp_session_fle->block = p_wmp_session_fle->block;
    c_wmp_session_fle->sequence = p_wmp_session_fle->sequence;
    c_wmp_session_fle->filename_len = p_wmp_session_fle->filename_len;
    memcpy(c_wmp_session_fle->filename,p_wmp_session_fle->filename,p_wmp_session_fle->filename_len);
    memcpy(c_wmp_session_fle->file,p_wmp_session_fle->file,p_wmp_session_fle->file_len);

    return c_wmp_session_fle;
}


/* Create wmp_session_ivt_t instance. */
wmp_session_ivt_t *create_wmp_session_ivt()
{
	wmp_session_ivt_t *p_wmp_seesion_ivt = (wmp_session_ivt_t *)malloc(sizeof(wmp_session_ivt_t));
	memset(p_wmp_seesion_ivt,0,sizeof(wmp_session_ivt_t));
	return p_wmp_seesion_ivt;
}


/* Delete wmp_session_ivt_t instance. */
void delete_wmp_session_ivt(wmp_session_ivt_t **p_wmp_session_ivt)
{
	if(p_wmp_session_ivt && (*p_wmp_session_ivt))
	{
		free((*p_wmp_session_ivt));
		(*p_wmp_session_ivt) = NULL;
	}
}


/* Copy a new wmp_session_ivt_t instance. */
wmp_session_ivt_t *copy_wmp_session_ivt(const wmp_session_ivt_t *p_wmp_session_ivt)
{
    wmp_session_ivt_t *c_wmp_session_ivt = create_wmp_session_ivt();

    memcpy(c_wmp_session_ivt,p_wmp_session_ivt,sizeof(wmp_session_ivt_t));

    return c_wmp_session_ivt;
}



/* Create wmp_session_list_t instance. */
wmp_session_list_t *create_wmp_session_list(uint16_t session_num)
{
    wmp_session_list_t *p_wmp_session_list = (wmp_session_list_t *)malloc(sizeof(wmp_session_list_t));
    memset(p_wmp_session_list,0,sizeof(wmp_session_list_t));
    if(session_num)
    {
        p_wmp_session_list->session_num =session_num;
        p_wmp_session_list->session_list = (uint32_t *)malloc(session_num * sizeof(uint32_t));
        memset(p_wmp_session_list->session_list,0,session_num * sizeof(uint32_t));
    }

    return p_wmp_session_list;
}


/* Delete wmp_session_list_t structure. */
void delete_wmp_session_list(wmp_session_list_t **p_wmp_session_list)
{
    if((*p_wmp_session_list))
    {
        if((*p_wmp_session_list)->session_list)
        {
            free((*p_wmp_session_list)->session_list);
            (*p_wmp_session_list)->session_list = NULL;
        }
        free((*p_wmp_session_list));
        (*p_wmp_session_list) = NULL;
    }
}


/* Set wmp_session_list_t group number. */
void set_wmp_session_list_num(wmp_session_list_t *p_wmp_session_list,uint16_t session_num)
{
    if(p_wmp_session_list)
    {
        if(p_wmp_session_list->session_list)
        {
            free(p_wmp_session_list->session_list);
            p_wmp_session_list->session_list = NULL;
        }
        p_wmp_session_list->session_num =session_num;
        if(session_num)
        {
            p_wmp_session_list->session_list = (uint32_t *)malloc(session_num * sizeof(uint32_t));
            memset(p_wmp_session_list->session_list,0,session_num * sizeof(uint32_t));
        }
    }
}

/* Copy a new wmp_session_list_t instance. */
wmp_session_list_t * copy_wmp_session_list(const wmp_session_list_t *p_wmp_session_list)
{
    wmp_session_list_t *c_wmp_session_list = create_wmp_session_list(p_wmp_session_list->session_num);

    c_wmp_session_list->attr = p_wmp_session_list->attr;
    c_wmp_session_list->user_id = p_wmp_session_list->user_id;
    c_wmp_session_list->session_num = p_wmp_session_list->session_num;
    memcpy(c_wmp_session_list->session_list,p_wmp_session_list->session_list,p_wmp_session_list->session_num*sizeof(uint32_t));

    return c_wmp_session_list;
}



/* Create wmp_session_fetch_t instance. */
wmp_session_fetch_t *create_wmp_session_fetch(uint16_t property_num)
{
    wmp_session_fetch_t *p_wmp_session_fetch = (wmp_session_fetch_t *)malloc(sizeof(wmp_session_fetch_t));
    memset(p_wmp_session_fetch,0,sizeof(wmp_session_fetch_t));
    if(property_num)
    {
        p_wmp_session_fetch->property_num = property_num;
        p_wmp_session_fetch->properties = (wmp_session_property_t *)malloc(property_num*sizeof(wmp_session_property_t));
        memset(p_wmp_session_fetch->properties,0,property_num*sizeof(wmp_session_property_t));
    }

    return p_wmp_session_fetch;
}


/* Delete wmp_session_fetch_t structure. */
void delete_wmp_session_fetch(wmp_session_fetch_t **p_wmp_session_fetch)
{
    if((*p_wmp_session_fetch))
    {
        if((*p_wmp_session_fetch)->properties)
        {
            free((*p_wmp_session_fetch)->properties);
            (*p_wmp_session_fetch)->properties = NULL;
        }
        free((*p_wmp_session_fetch));
        (*p_wmp_session_fetch) = NULL;
    }
}


/* Set wmp_session_fetch_t group number. */
void set_wmp_session_fetch_num(wmp_session_fetch_t *p_wmp_group_fetch,uint16_t property_num)
{
    if(p_wmp_group_fetch)
    {
        if(p_wmp_group_fetch->properties)
        {
            free(p_wmp_group_fetch->properties);
            p_wmp_group_fetch->properties = NULL;
        }
        p_wmp_group_fetch->property_num = property_num;
        p_wmp_group_fetch->properties = (wmp_session_property_t *)malloc(property_num*sizeof(wmp_session_property_t));
        memset(p_wmp_group_fetch->properties,0,property_num*sizeof(wmp_session_fetch_t));
    }
}

/* Copy a new wmp_session_fetch_t instance. */
wmp_session_fetch_t * copy_wmp_session_fetch(const wmp_session_fetch_t *p_wmp_session_fetch)
{
    wmp_session_fetch_t *c_wmp_session_fetch = create_wmp_session_fetch(p_wmp_session_fetch->property_num);

    c_wmp_session_fetch->attr = p_wmp_session_fetch->attr;
    c_wmp_session_fetch->session_id = p_wmp_session_fetch->session_id;
    memcpy(c_wmp_session_fetch->properties,p_wmp_session_fetch->properties,\
           p_wmp_session_fetch->property_num*sizeof(wmp_session_fetch_t));

    return c_wmp_session_fetch;
}


/* Create wmp_session_t instance. */
wmp_session_t *create_wmp_session()
{
	wmp_session_t *p_wmp_session = (wmp_session_t *)malloc(sizeof(wmp_session_t));
	memset(p_wmp_session,0,sizeof(wmp_session_t));
	return p_wmp_session;
}

/*  Delete wmp_session_t instance. */
void delete_wmp_session(wmp_session_t **p_wmp_session)
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
    wmp_session_list_t *p_wmp_session_list = NULL;
    wmp_session_fetch_t *p_wmp_session_fetch = NULL;
	switch(p_wmp_session->id)
	{
		case WMP_SESSION_CET_ID:
			WMP_SessionParamLenCheck(index,5,len)
            p_wmp_session_cet = create_wmp_session_cet();
			p_wmp_session_cet->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_cet->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session->param = (uint8_t *)p_wmp_session_cet;
			break;
		case WMP_SESSION_DSV_ID:
			WMP_SessionParamLenCheck(index,5,len)
            p_wmp_session_dsv = create_wmp_session_dsv();
			p_wmp_session_dsv->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_dsv->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session->param = (uint8_t *)p_wmp_session_dsv;
			break;
		case WMP_SESSION_EXT_ID:
			WMP_SessionParamLenCheck(index,5,len)
            p_wmp_session_ext = create_wmp_session_ext();
			p_wmp_session_ext->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_ext->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session->param = (uint8_t *)p_wmp_session_ext;
			break;
		case WMP_SESSION_MSG_ID:
			WMP_SessionParamLenCheck(index,7,len)
			
            p_wmp_session_msg = create_wmp_session_msg(0);
			p_wmp_session_msg->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_msg->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session_msg->msg_len = ntohs(*(uint16_t *)(package+index));
			index+=2;
			if((index+p_wmp_session_msg->msg_len)>len)
			{
                delete_wmp_session_msg(&p_wmp_session_msg);
				return WMP_PARSER_SESSION_FAILED;
			}
			p_wmp_session->param = (uint8_t *)p_wmp_session_msg;
			break;
		case WMP_SESSION_FLE_ID:
			WMP_SessionParamLenCheck(index,10,len)
            p_wmp_session_fle = create_wmp_session_fle(0);
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
                delete_wmp_session_fle(&p_wmp_session_fle);
				return WMP_PARSER_SESSION_FAILED;
			}
			memcpy(p_wmp_session_fle->filename,package+index,p_wmp_session_fle->filename_len);
			index+=p_wmp_session_fle->filename_len;
			p_wmp_session_fle->file_len = *(uint16_t *)(package+index);
			index+=2;
			if((index+p_wmp_session_fle->file_len)>len)
			{
                delete_wmp_session_fle(&p_wmp_session_fle);
				return WMP_PARSER_SESSION_FAILED;
			}
			memcpy(p_wmp_session_fle->file,package+index,p_wmp_session_fle->file_len);
			index+=p_wmp_session_fle->file_len;
			p_wmp_session->param = (uint8_t *)p_wmp_session_fle;
			break;
		case WMP_SESSION_IVT_ID:
			WMP_SessionParamLenCheck(index,9,len)
            p_wmp_session_ivt = create_wmp_session_ivt();
			p_wmp_session_ivt->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_session_ivt->session_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session_ivt->invite_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_session->param = (uint8_t *)p_wmp_session_ivt;
			break;
        case WMP_SESSION_LIST_ID:
            WMP_SessionParamLenCheck(index,9,len)
            p_wmp_session_list = create_wmp_session_list(0);
            p_wmp_session_list->attr = *(uint8_t *)(package+index);
            index++;
            p_wmp_session_list->user_id = ntohl(*(uint32_t *)(package+index));
            index+=4;
            p_wmp_session_list->session_num = ntohs(*(uint16_t *)(package+index));
            index+=2;
            set_wmp_session_list_num(p_wmp_session_list,p_wmp_session_list->session_num);
            for(uint16_t i=0;i<p_wmp_session_list->session_num;i++)
            {
                p_wmp_session_list->session_list[i] = ntohl(*(uint32_t *)(package+index));
                index+=4;
            }
            p_wmp_session->param = (uint8_t *)p_wmp_session_list;
            break;
        case WMP_SESSION_FETCH_ID:
            WMP_SessionParamLenCheck(index,9,len)
            p_wmp_session_fetch = create_wmp_session_fetch(0);
            p_wmp_session_fetch->attr = *(uint8_t *)(package+index);
            index++;
            p_wmp_session_fetch->session_id = ntohl(*(uint32_t *)(package+index));
            index+=4;
            p_wmp_session_fetch->property_num = ntohs(*(uint16_t *)(package+index));
            index+=2;
            set_wmp_session_fetch_num(p_wmp_session_fetch,p_wmp_session_fetch->property_num);
            for(uint16_t i=0;i<p_wmp_session_fetch->property_num;i++)
            {
                p_wmp_session_fetch->properties[i].id = *(uint8_t *)(package+index);
                index++;
                p_wmp_session_fetch->properties[i].data_len = *(uint8_t *)(package+index);
                index++;
                memcpy(p_wmp_session_fetch->properties[i].data,package+index,p_wmp_session_fetch->properties[i].data_len);
                index+=p_wmp_session_fetch->properties[i].data_len;
            }
            p_wmp_session->param = (uint8_t *)p_wmp_session_fetch;
            break;
        default:
            break;
	}
	return WMP_PARSER_SESSION_SUCCESS;
}

/* Parser wmp_session_t instance. */
wmp_session_t *parser_wmp_session(const char *package,uint32_t pack_len)
{
	uint32_t index=0;
    wmp_session_t *p_wmp_session = create_wmp_session();
	
	p_wmp_session->src = ntohl(*(uint32_t *)(package+index));
	index+=4;
	p_wmp_session->dst = ntohl(*(uint32_t *)(package+index));
	index+=4;
	p_wmp_session->id = ntohl(*(uint32_t *)(package+index));
	index+=4;
	
	int ret = parser_wmp_session_parameter(package,pack_len-index,p_wmp_session);
	if(ret!=WMP_PARSER_SESSION_SUCCESS)
	{
        delete_wmp_session(&p_wmp_session);
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
    wmp_session_list_t *p_wmp_session_list = NULL;
    wmp_session_fetch_t *p_wmp_session_fetch = NULL;
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
        case WMP_SESSION_LIST_ID:
            p_wmp_session_list = (wmp_session_list_t *)p_wmp_session->param;
            *(uint8_t *)(package+index) = p_wmp_session_list->attr;
            index++;
            *(uint32_t *)(package+index) = htonl(p_wmp_session_list->user_id);
            index+=4;
            *(uint16_t *)(package+index) = htons(p_wmp_session_list->session_num);
            index+=2;
            for(uint32_t i=0;i<p_wmp_session_list->session_num;i++)
            {
                *(uint32_t *)(package+index) = htonl(p_wmp_session_list->session_list[i]);
                index+=4;
            }
            break;
        case WMP_SESSION_FETCH_ID:
            p_wmp_session_fetch = (wmp_session_fetch_t *)p_wmp_session->param;
            *(uint8_t *)(package+index) = p_wmp_session_fetch->attr;
            index++;
            *(uint32_t *)(package+index) = htonl(p_wmp_session_fetch->session_id);
            index+=4;
            *(uint16_t *)(package+index) = htons(p_wmp_session_fetch->property_num);
            index+=2;
            for(uint16_t i=0;i<p_wmp_session_list->session_num;i++)
            {
                *(uint8_t *)(package+index) = p_wmp_session_fetch->properties[i].id;
                index++;
                *(uint8_t *)(package+index) = p_wmp_session_fetch->properties[i].data_len;
                index++;
                memcpy(package+index,p_wmp_session_fetch->properties[i].data,
                       p_wmp_session_fetch->properties[i].data_len);
                index+=2;
            }
            break;
        default:
            break;
	}
	return WMP_PARSER_SESSION_SUCCESS;
}


/* Package wmp_session_t instance. */
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

/* Print wmp_session_t instance. */
void print_wmp_session(const wmp_session_t *p_wmp_session)
{
	if(!p_wmp_session)
	{
#ifdef WMP_DEBUG
		printf("[WMP] wmp_session_t is null.\n");
#endif
		return ;
	}

    printf("*****************************wm_session_start*****************************\n");

	printf("src:%d;dst:%d;id:%d;",p_wmp_session->src,p_wmp_session->dst,p_wmp_session->id);

	wmp_session_cet_t *p_wmp_session_cet = NULL;
	wmp_session_dsv_t *p_wmp_session_dsv = NULL;
	wmp_session_ext_t *p_wmp_session_ext = NULL;
	wmp_session_msg_t *p_wmp_session_msg = NULL;
	wmp_session_fle_t *p_wmp_session_fle = NULL;
	wmp_session_ivt_t *p_wmp_session_ivt = NULL;
    wmp_session_list_t *p_wmp_session_list = NULL;
    wmp_session_fetch_t *p_wmp_session_fetch = NULL;
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
        case WMP_SESSION_LIST_ID:
            p_wmp_session_list = (wmp_session_list_t *)(p_wmp_session->param);
            if(!p_wmp_session_list)
            {
#ifdef WMP_DEBUG
                printf("wmp_session_t parameter is null.\n");
#endif
                break;
            }
            printf("attr:%02x;user_id:%d;session_num:%d\n",p_wmp_session_list->attr,\
                    p_wmp_session_list->user_id,p_wmp_session_list->session_num);
            printf("session_list:\n");
            for(uint16_t i=0;i>p_wmp_session_list->session_num;i++)
                printf("list[%d]:%d ",i,p_wmp_session_list->session_list[i]);
            printf("\n");
            break;
        case WMP_SESSION_FETCH_ID:
            p_wmp_session_fetch = (wmp_session_fetch_t *)(p_wmp_session->param);
            if(!p_wmp_session_fetch)
            {
#ifdef WMP_DEBUG
                printf("wmp_session_t parameter is null.\n");
#endif
                break;
            }
            printf("attr:%02x;user_id:%d;property_num:%d\n",p_wmp_session_fetch->attr,\
                    p_wmp_session_fetch->session_id,p_wmp_session_fetch->property_num);
            break;
        default:
            break;
	}

    printf("******************************wm_session_end******************************\n");
}


/* Copy wmp_session_t a new instance. */
wmp_session_t *copy_wmp_session(const wmp_session_t *p_wmp_session)
{
    wmp_session_t *c_wmp_session = create_wmp_session();

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
        case WMP_SESSION_LIST_ID:
            c_wmp_session->param = copy_wmp_session_list((wmp_session_list_t *)p_wmp_session->param);
            break;
        case WMP_SESSION_FETCH_ID:
            c_wmp_session->param = copy_wmp_session_fetch((wmp_session_fetch_t *)p_wmp_session->param);
            break;
        default:
            break;
    }

    return c_wmp_session;
}

