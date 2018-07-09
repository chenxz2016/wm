/* ************************************************************************
 *       Filename:  wmp_group.c
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
#include"wmp_group.h"


#define WMP_GroupParamLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return NULL;

#define WMP_GroupLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return WMP_GROUP_PARSER_FAILED;



/* Create wmp_group_cet_t instance. */
wmp_group_cet_t *create_wmp_group_cet()
{
	wmp_group_cet_t *p_wmp_group_cet = (wmp_group_cet_t *)malloc(sizeof(wmp_group_cet_t));
	memset(p_wmp_group_cet,0,sizeof(wmp_group_cet_t));
	return p_wmp_group_cet;
}

/* Delete wmp_group_cet_t structure. */
void delete_wmp_group_cet(wmp_group_cet_t **p_wmp_group_cet)
{
	if(p_wmp_group_cet && (*p_wmp_group_cet))
	{
		free((*p_wmp_group_cet));
		(*p_wmp_group_cet) = NULL;
	}
}

/* Copy a new wmp_group_cet_t instance. */
wmp_group_cet_t *copy_wmp_group_cet(const wmp_group_cet_t *p_wmp_group_cet)
{
    wmp_group_cet_t *c_wmp_group_cet = create_wmp_group_cet();

    memcpy(c_wmp_group_cet,p_wmp_group_cet,sizeof(wmp_group_cet_t));

    return c_wmp_group_cet;
}

/* Create wmp_group_dsv_t instance. */
wmp_group_dsv_t *create_wmp_group_dsv()
{
	wmp_group_dsv_t *p_wmp_group_dsv = (wmp_group_dsv_t *)malloc(sizeof(wmp_group_dsv_t));
	memset(p_wmp_group_dsv,0,sizeof(wmp_group_dsv_t));
	return p_wmp_group_dsv;
}


/* Delete wmp_group_dsv_t instance. */
void delete_wmp_group_dsv(wmp_group_dsv_t **p_wmp_group_dsv)
{
	if(p_wmp_group_dsv && (*p_wmp_group_dsv))
	{
		free((*p_wmp_group_dsv));
		(*p_wmp_group_dsv) = NULL;
	}
}

/* Copy a new wmp_group_dsv_t instance. */
wmp_group_dsv_t *copy_wmp_group_dsv(const wmp_group_dsv_t *p_wmp_group_dsv)
{
    wmp_group_dsv_t *c_wmp_group_dsv = create_wmp_group_dsv();

    memcpy(c_wmp_group_dsv,p_wmp_group_dsv,sizeof(wmp_group_dsv_t));

    return c_wmp_group_dsv;
}

/* Create wmp_group_jon_t instance. */
wmp_group_jon_t *create_wmp_group_jon()
{
	wmp_group_jon_t *p_wmp_group_jon = (wmp_group_jon_t *)malloc(sizeof(wmp_group_jon_t));
	memset(p_wmp_group_jon,0,sizeof(wmp_group_jon_t));
	return p_wmp_group_jon;
}


/* Delete wmp_group_jon_t instance. */
void delete_wmp_group_jon(wmp_group_jon_t **p_wmp_group_jon)
{
	if(p_wmp_group_jon && (*p_wmp_group_jon))
	{
		free((*p_wmp_group_jon));
		(*p_wmp_group_jon) = NULL;
	}
}

/* Copy a new wmp_group_jon_t instance. */
wmp_group_jon_t *copy_wmp_group_jon(const wmp_group_jon_t *p_wmp_group_jon)
{
    wmp_group_jon_t *c_wmp_group_jon = create_wmp_group_jon();

    memcpy(c_wmp_group_jon,p_wmp_group_jon,sizeof(wmp_group_jon_t));

    return c_wmp_group_jon;
}


/* Create wmp_group_ext_t instance. */
wmp_group_ext_t *create_wmp_group_ext()
{
	wmp_group_ext_t *p_wmp_group_ext = (wmp_group_ext_t *)malloc(sizeof(wmp_group_ext_t));
	memset(p_wmp_group_ext,0,sizeof(wmp_group_ext_t));
	return p_wmp_group_ext;	
}

/* Delete wmp_group_ext_t instance. */
void delete_wmp_group_ext(wmp_group_ext_t **p_wmp_group_ext)
{
	if(p_wmp_group_ext && (*p_wmp_group_ext))
	{
		free((*p_wmp_group_ext));
		(*p_wmp_group_ext) = NULL;
	}
}

/* Copy a new wmp_group_ext_t instance. */
wmp_group_ext_t *copy_wmp_group_ext(const wmp_group_ext_t *p_wmp_group_ext)
{
    wmp_group_ext_t *c_wmp_group_ext = create_wmp_group_ext();

    memcpy(c_wmp_group_ext,p_wmp_group_ext,sizeof(wmp_group_ext_t));

    return c_wmp_group_ext;
}


/* Create wmp_group_set_t instance. */
wmp_group_set_t *create_wmp_group_set(uint16_t num)
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


/* Delete wmp_group_set_t instance. */
void delete_wmp_group_set(wmp_group_set_t **p_wmp_group_set)
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


/* Set wmp_group_set_t property numbers. */
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


/* Copy a new wmp_group_set_t instance. */
wmp_group_set_t *copy_wmp_group_set(const wmp_group_set_t *p_wmp_group_set)
{
    wmp_group_set_t *c_wmp_group_set = create_wmp_group_set(p_wmp_group_set->property.property_num);

    c_wmp_group_set->attr = p_wmp_group_set->attr;
    c_wmp_group_set->group_id = p_wmp_group_set->group_id;
    c_wmp_group_set->result = p_wmp_group_set->result;
    memcpy(c_wmp_group_set->property.properties,c_wmp_group_set->property.properties,\
           c_wmp_group_set->property.property_num*sizeof(wmp_group_property_t));

    return c_wmp_group_set;
}



/* Create wmp_group_msg_t instance. */
wmp_group_msg_t *create_wmp_group_msg(uint16_t msg_len)
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


/* Delete wmp_group_msg_t structure. */
void delete_wmp_group_msg(wmp_group_msg_t **p_wmp_group_msg)
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


/* Set wmp_group_msg_t length. */
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


/* Copy a new wmp_group_msg_t instance. */
wmp_group_msg_t *copy_wmp_group_msg(const wmp_group_msg_t *p_wmp_group_msg)
{
    wmp_group_msg_t *c_wmp_group_msg = create_wmp_group_msg(p_wmp_group_msg->msg_len);

    c_wmp_group_msg->attr = p_wmp_group_msg->attr;
    c_wmp_group_msg->group_id = p_wmp_group_msg->group_id;
    c_wmp_group_msg->result = p_wmp_group_msg->result;
    c_wmp_group_msg->msg_len = p_wmp_group_msg->msg_len;
    memcpy(c_wmp_group_msg->msg,p_wmp_group_msg->msg,p_wmp_group_msg->msg_len);

    return c_wmp_group_msg;
}


/* Create wmp_group_fle_t instance. */
wmp_group_fle_t *create_wmp_group_fle(uint16_t file_len)
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


/* Delete wmp_group_fle_t. */
void delete_wmp_group_fle(wmp_group_fle_t **p_wmp_group_fle)
{
	if(p_wmp_group_fle && (*p_wmp_group_fle))
	{
		free(*p_wmp_group_fle);
		(*p_wmp_group_fle) = NULL;
	}
}


/* Set wmp_group_fle_t structure. */
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


/* Copy a new wmp_group_fle_t instance. */
wmp_group_fle_t *copy_wmp_group_fle(const wmp_group_fle_t *p_wmp_group_fle)
{
    wmp_group_fle_t *c_wmp_group_fle = create_wmp_group_fle(p_wmp_group_fle->file_len);

    c_wmp_group_fle->attr = p_wmp_group_fle->attr;
    c_wmp_group_fle->block = p_wmp_group_fle->block;
    c_wmp_group_fle->sequence = p_wmp_group_fle->sequence;
    c_wmp_group_fle->filename_len = p_wmp_group_fle->filename_len;
    memcpy(c_wmp_group_fle->filename,p_wmp_group_fle->filename,p_wmp_group_fle->filename_len);
    c_wmp_group_fle->file_len = p_wmp_group_fle->file_len;
    memcpy(c_wmp_group_fle->file,p_wmp_group_fle->file,p_wmp_group_fle->file_len);

    return c_wmp_group_fle;
}


/* Create wmp_group_ntc_t instance. */
wmp_group_ntc_t *create_wmp_group_ntc(uint16_t notice_len)
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


/* Delete wmp_group_ntc_t instance. */
void delete_wmp_group_ntc(wmp_group_ntc_t **p_wmp_group_ntc)
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


/* Set wmp_group_ntc_t notice length. */
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


/* Copy a new wmp_group_ntc_t instance. */
wmp_group_ntc_t *copy_wmp_group_ntc(const wmp_group_ntc_t *p_wmp_group_ntc)
{
    wmp_group_ntc_t *c_wmp_group_ntc = create_wmp_group_ntc(p_wmp_group_ntc->notice_len);

    c_wmp_group_ntc->attr = p_wmp_group_ntc->attr;
    c_wmp_group_ntc->group_id = p_wmp_group_ntc->group_id;
    c_wmp_group_ntc->notice_len = p_wmp_group_ntc->notice_len;
    memcpy(c_wmp_group_ntc->notice,p_wmp_group_ntc->notice,p_wmp_group_ntc->notice_len);

    return c_wmp_group_ntc;
}


/* Create wmp_group_ivt_t instance. */
wmp_group_ivt_t *create_wmp_group_ivt()
{
	wmp_group_ivt_t *p_wmp_group_ivt = (wmp_group_ivt_t *)malloc(sizeof(wmp_group_ivt_t));
	memset(p_wmp_group_ivt,0,sizeof(wmp_group_ivt_t));
	return p_wmp_group_ivt;
}


/* Delete wmp_group_ivt_t instance. */
void delete_wmp_group_ivt(wmp_group_ivt_t **p_wmp_group_ivt)
{
	if(p_wmp_group_ivt && (*p_wmp_group_ivt))
	{
		free(*p_wmp_group_ivt);
		(*p_wmp_group_ivt) = NULL;
	}
}


/* Copy a new wmp_group_ivt_t instance. */
wmp_group_ivt_t * copy_wmp_group_ivt(const wmp_group_ivt_t *p_wmp_group_ivt)
{
    wmp_group_ivt_t *c_wmp_group_ivt = create_wmp_group_ivt();
    memcpy(c_wmp_group_ivt,p_wmp_group_ivt,sizeof(wmp_group_ivt_t));
    return c_wmp_group_ivt;
}



/* Create wmp_group_fetch_t structure. */
wmp_group_list_t *create_wmp_group_list(uint16_t group_num)
{
    wmp_group_list_t *p_wmp_group_list = (wmp_group_list_t *)malloc(sizeof(wmp_group_list_t));

    memset(p_wmp_group_list,0,sizeof(wmp_group_list_t));
    if(group_num)
    {
        p_wmp_group_list->group_list = (uint32_t *)malloc(group_num * sizeof(uint32_t));
        memset(p_wmp_group_list->group_list,0,p_wmp_group_list->group_num * sizeof(uint32_t));
    }

    return p_wmp_group_list;
}


/* Delete wmp_group_list_t instance. */
void delete_wmp_group_list(wmp_group_list_t **p_wmp_group_list)
{
    if((*p_wmp_group_list))
    {
        if((*p_wmp_group_list)->group_list)
        {
            free((*p_wmp_group_list)->group_list);
            (*p_wmp_group_list)->group_list = NULL;
        }
        free((*p_wmp_group_list));
        (*p_wmp_group_list) = NULL;
    }
}


/* Set wmp_group_list_t group number. */
void set_wmp_group_list_num(wmp_group_list_t *p_wmp_group_list,uint16_t group_num)
{
    if(p_wmp_group_list)
    {
        if(p_wmp_group_list->group_list)
            free(p_wmp_group_list->group_list);

        p_wmp_group_list->group_num = group_num;
        p_wmp_group_list->group_list = (uint32_t *)malloc(group_num * sizeof(uint32_t));
        memset(p_wmp_group_list->group_list,0,p_wmp_group_list->group_num * sizeof(uint32_t));
    }
}



/* Copy a new wmp_group_list_t instance. */
wmp_group_list_t * copy_wmp_group_list(const wmp_group_list_t *p_wmp_group_list)
{
    wmp_group_list_t * c_wmp_group_list = create_wmp_group_list(p_wmp_group_list->group_num);;

    c_wmp_group_list->attr = p_wmp_group_list->attr;
    c_wmp_group_list->user_id = p_wmp_group_list->user_id;
    c_wmp_group_list->group_num = p_wmp_group_list->group_num;
    memcpy(c_wmp_group_list->group_list,p_wmp_group_list->group_list,\
           c_wmp_group_list->group_num * sizeof(uint32_t));

    return c_wmp_group_list;
}



/* Create wmp_group_fetch_t structure. */
wmp_group_fetch_t *create_wmp_group_fetch(uint16_t property_num)
{
    wmp_group_fetch_t *p_wmp_group_fetch = (wmp_group_fetch_t *)malloc(property_num * sizeof(wmp_group_fetch_t));
    memset(p_wmp_group_fetch,0,sizeof(wmp_group_fetch_t));
    p_wmp_group_fetch->property_num = property_num;
    if(property_num)
    {
        p_wmp_group_fetch->properties = (wmp_group_property_t *)malloc(property_num * sizeof(wmp_group_property_t));
        memset(p_wmp_group_fetch->properties,0,property_num * sizeof(wmp_group_property_t));
    }

    return p_wmp_group_fetch;
}


/* Delete wmp_group_fetch_t structure. */
void delete_wmp_group_fetch(wmp_group_fetch_t **p_wmp_group_fetch)
{
    if((*p_wmp_group_fetch))
    {
        if((*p_wmp_group_fetch)->properties)
        {
            free((*p_wmp_group_fetch)->properties);
            (*p_wmp_group_fetch)->properties = NULL;
        }
        free((*p_wmp_group_fetch));
        (*p_wmp_group_fetch) = NULL;
    }
}


/* Set wmp_group_fetch_t group number. */
void set_wmp_group_fetch_num(wmp_group_fetch_t *p_wmp_group_fetch,uint16_t property_num)
{
    if(p_wmp_group_fetch)
    {
        if(p_wmp_group_fetch->properties)
        {
            free(p_wmp_group_fetch->properties);
            p_wmp_group_fetch->properties = NULL;
        }
        p_wmp_group_fetch->property_num = property_num;
        p_wmp_group_fetch->properties = (wmp_group_property_t *)malloc(property_num * sizeof(wmp_group_property_t));
        memset(p_wmp_group_fetch->properties,0,property_num * sizeof(wmp_group_property_t));
    }
}


/* Copy a new wmp_group_fetch_t instance. */
wmp_group_fetch_t * copy_wmp_group_fetch(const wmp_group_fetch_t *p_wmp_group_fetch)
{
    wmp_group_fetch_t *c_wmp_group_fetch = create_wmp_group_fetch(p_wmp_group_fetch->property_num);

    c_wmp_group_fetch->attr = p_wmp_group_fetch->attr;
    c_wmp_group_fetch->group_id = p_wmp_group_fetch->group_id;

    memcpy(c_wmp_group_fetch->properties,p_wmp_group_fetch->properties,\
           p_wmp_group_fetch->property_num*sizeof(wmp_group_fetch_t));

    return c_wmp_group_fetch;
}


/* Create wmp_group_t instance. */
wmp_group_t *create_wmp_group()
{
	wmp_group_t *p_wmp_group = (wmp_group_t *)malloc(sizeof(wmp_group_t));
	memset(p_wmp_group,0,sizeof(wmp_group_t));
	return p_wmp_group;
}

/* Delete wmp_group_t instance. */
void delete_wmp_group(wmp_group_t **p_wmp_group)
{
	if(p_wmp_group && (*p_wmp_group) && (*p_wmp_group)->param)
	{
		switch((*p_wmp_group)->id)
		{
			case WMP_GROUP_CET_ID:
                delete_wmp_group_cet((wmp_group_cet_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_DSV_ID:
                delete_wmp_group_dsv((wmp_group_dsv_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_JON_ID:
                delete_wmp_group_jon((wmp_group_jon_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_EXT_ID:
                delete_wmp_group_ext((wmp_group_ext_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_SET_ID:
                delete_wmp_group_set((wmp_group_set_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_MSG_ID:
                delete_wmp_group_msg((wmp_group_msg_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_FLE_ID:
                delete_wmp_group_fle((wmp_group_fle_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_NTC_ID:
                delete_wmp_group_ntc((wmp_group_ntc_t **)&((*p_wmp_group)->param));
				break;
			case WMP_GROUP_IVT_ID:
                delete_wmp_group_ivt((wmp_group_ivt_t **)&((*p_wmp_group)->param));
				break;
            case WMP_GROUP_FETCH_ID:
                delete_wmp_group_fetch((wmp_group_fetch_t **)&((*p_wmp_group)->param));
                break;
            default:
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
    wmp_group_fetch_t *p_wmp_group_fetch = 0;
    wmp_group_list_t *p_wmp_group_list = 0;
	
	switch(p_wmp_group->id)
	{
		case WMP_GROUP_CET_ID:
			WMP_GroupLenCheck(index,6,pack_len)
            p_wmp_group_cet = create_wmp_group_cet();
            p_wmp_group->param = p_wmp_group_cet;
			p_wmp_group_cet->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_cet->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_cet->result = *(uint8_t *)(package+index);
			index++;
			break;
		case WMP_GROUP_DSV_ID:
			WMP_GroupLenCheck(index,10,pack_len)
            p_wmp_group_dsv = create_wmp_group_dsv();
            p_wmp_group->param = p_wmp_group_dsv;
			p_wmp_group_dsv->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_dsv->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_dsv->result = *(uint8_t *)(package+index);
			index++;
			break;
		case WMP_GROUP_JON_ID:
			WMP_GroupLenCheck(index,7,pack_len)
            p_wmp_group_jon = create_wmp_group_jon();
            p_wmp_group->param = p_wmp_group_jon;
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
            p_wmp_group_ext = create_wmp_group_ext();
            p_wmp_group->param = p_wmp_group_ext;
			p_wmp_group_ext->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_ext->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_ext->result = *(uint8_t *)(package+index);
			index++;
			break;
		case WMP_GROUP_SET_ID:
			WMP_GroupLenCheck(index,8,pack_len)
            p_wmp_group_set = create_wmp_group_set(0);
            p_wmp_group->param = p_wmp_group_set;
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
            p_wmp_group_msg = create_wmp_group_msg(0);
            p_wmp_group->param = p_wmp_group_msg;
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
            p_wmp_group_fle = create_wmp_group_fle(0);
            p_wmp_group->param = p_wmp_group_fle;
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
            p_wmp_group_ntc = create_wmp_group_ntc(0);
            p_wmp_group->param = p_wmp_group_ntc;
			p_wmp_group_ntc->attr = *(uint8_t *)(package+index);
			index++;
            p_wmp_group_ntc->group_id = ntohl(*(uint32_t *)(package+index));
            index+=4;
			p_wmp_group_ntc->notice_len = ntohs(*(uint16_t *)(package+index));
			index+=2;
			set_wmp_group_ntc_len(p_wmp_group_ntc,p_wmp_group_ntc->notice_len);
			WMP_GroupLenCheck(index,p_wmp_group_ntc->notice_len,pack_len)
			memcpy(p_wmp_group_ntc->notice,package+index,p_wmp_group_ntc->notice_len);
			index+=p_wmp_group_ntc->notice_len;
			break;
		case WMP_GROUP_IVT_ID:
			WMP_GroupLenCheck(index,9,pack_len)
            p_wmp_group_ivt = create_wmp_group_ivt();
            p_wmp_group->param = p_wmp_group_ivt;
			p_wmp_group_ivt->attr = *(uint8_t *)(package+index);
			index++;
			p_wmp_group_ivt->group_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			p_wmp_group_ivt->invite_id = ntohl(*(uint32_t *)(package+index));
			index+=4;
			break;
        case WMP_GROUP_LIST_ID:
            p_wmp_group_list = create_wmp_group_list(0);
            p_wmp_group->param = p_wmp_group_list;
            p_wmp_group_list->attr = *(uint8_t *)(package+index);
            index++;
            p_wmp_group_list->user_id = ntohl(*(uint32_t *)(package+index));
            index+=4;
            if(p_wmp_group_list->attr == WMP_GROUP_LIST_RSP)
            {
                p_wmp_group_list->group_num = ntohs(*(uint16_t *)(package+index));
                index+=2;
                set_wmp_group_list_num(p_wmp_group_list,p_wmp_group_list->group_num);
                for(uint16_t i=0;i<p_wmp_group_list->group_num;i++)
                {
                    p_wmp_group_list->group_list[i] = ntohl(*(uint32_t *)(package+index));
                    index += 4;
                }
            }
            break;
        case WMP_GROUP_FETCH_ID:
            p_wmp_group_fetch = create_wmp_group_fetch(0);
            p_wmp_group->param = p_wmp_group_fetch;
            p_wmp_group_fetch->attr = *(uint8_t *)(package+index);
            index++;
            p_wmp_group_fetch->group_id = ntohl(*(uint32_t *)(package+index));
            index+=4;
            if(p_wmp_group_fetch->attr == WMP_GROUP_FETCH_RSP)
            {
                p_wmp_group_fetch->property_num = ntohs(*(uint16_t *)(package+index));
                index+=2;
                set_wmp_group_fetch_num(p_wmp_group_fetch,p_wmp_group_fetch->property_num);
                for(uint16_t i=0;i<p_wmp_group_fetch->property_num;i++)
                {
                    p_wmp_group_fetch->properties[i].id = ntohs(*(uint16_t *)(package+index));
                    index += 2;
                    p_wmp_group_fetch->properties[i].data_len = *(uint8_t *)(package+index);
                    index++;
                    memcpy(p_wmp_group_fetch->properties[i].data,package+index,\
                           p_wmp_group_fetch->properties[i].data_len);
                    index += p_wmp_group_fetch->properties[i].data_len;
                }
            }
            break;
        default:
            break;
	}
	return WMP_GROUP_PARSER_SUCCESS;
}

/* Parser wmp_group_t. */
wmp_group_t *parser_wmp_group(const char *package,uint32_t pack_len)
{
	uint32_t index = 0;
	WMP_GroupParamLenCheck(index,14,pack_len)
	
    wmp_group_t *p_wmp_group = create_wmp_group();
	
	p_wmp_group->src = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_group->src);
	
	p_wmp_group->dst = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_group->dst);
	
	p_wmp_group->id = ntohs(*(uint16_t *)(package+index));
	index+=sizeof(p_wmp_group->id);
	
    int ret = parser_wmp_group_parameter(p_wmp_group,package+index,pack_len-index);
	if(ret!=WMP_GROUP_PARSER_SUCCESS)
	{
        delete_wmp_group(&p_wmp_group);
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
static uint32_t package_wmp_group_parameter(const wmp_group_t *p_wmp_group,char *package)
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
    wmp_group_fetch_t *p_wmp_group_fetch = NULL;
    wmp_group_list_t *p_wmp_group_list = NULL;
	
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
            *(uint32_t *)(package+index) = htonl(p_wmp_group_ntc->group_id);
            index+=4;
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
        case WMP_GROUP_LIST_ID:
            p_wmp_group_list = (wmp_group_list_t *)p_wmp_group->param;
            *(uint8_t *)(package+index) = p_wmp_group_list->attr;
            index++;
            *(uint32_t *)(package+index) = htonl(p_wmp_group_list->user_id);
            index+=4;
            if(p_wmp_group_list->attr == WMP_GROUP_LIST_RSP)
            {
                *(uint16_t *)(package+index) = htons(p_wmp_group_list->group_num);
                index+=2;
                for(uint16_t i=0;i<p_wmp_group_list->group_num;i++)
                {
                    *(uint32_t *)(package+index) = htonl(p_wmp_group_list->group_list[i]);
                    index += 4;
                }
            }
            break;
        case WMP_GROUP_FETCH_ID:
            p_wmp_group_fetch = (wmp_group_fetch_t *)p_wmp_group->param;
            *(uint8_t *)(package+index) = p_wmp_group_fetch->attr;
            index++;
            *(uint32_t *)(package+index) = htonl(p_wmp_group_fetch->group_id);
            index+=4;
            if(p_wmp_group_fetch->attr == WMP_GROUP_FETCH_RSP)
            {
                *(uint16_t *)(package+index) = htons(p_wmp_group_fetch->property_num);
                index+=2;
                for(uint16_t i=0;i<p_wmp_group_fetch->property_num;i++)
                {
                    *(uint16_t *)(package+index) = htons(p_wmp_group_fetch->properties[i].id);
                    index += 2;
                    *(uint8_t *)(package+index) = p_wmp_group_fetch->properties[i].data_len;
                    index++;
                    memcpy(package+index,p_wmp_group_fetch->properties[i].data,p_wmp_group_fetch->properties[i].data_len);
                    index += p_wmp_group_fetch->properties[i].data_len;
                }
            }
            break;
		default:
			break;
	}
	return index;
}

/* Package wmp_group_t. */
uint32_t package_wmp_group(char *package,const wmp_group_t *p_wmp_group)
{
	uint32_t index = 0;
	
	*(uint32_t *)(package+index) = htonl(p_wmp_group->src);
	index+=sizeof(p_wmp_group->src);
	
	*(uint32_t *)(package+index) = htonl(p_wmp_group->dst);
	index+=sizeof(p_wmp_group->dst);
	
    *(uint16_t *)(package+index) = htons(p_wmp_group->id);
	index+=sizeof(p_wmp_group->id);
	
    index += package_wmp_group_parameter(p_wmp_group,package+index);
	
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

/* Print wmp_group_t. */
void print_wmp_group(const wmp_group_t *p_wmp_group)
{
	if(!p_wmp_group)
	{
#ifdef WMP_DEBUG
		printf("wmp_group_t is null.\n");
#endif
		return ;
	}
    printf("********************************wm_group_start********************************\n");
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
    wmp_group_list_t *p_wmp_group_list = NULL;
    wmp_group_fetch_t *p_wmp_group_fetch = NULL;
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
            printf("attr:%02x;group_id:%02x;notice_len:%d;notice:%s;\n",p_wmp_group_ntc->attr,\
                    p_wmp_group_ntc->group_id,p_wmp_group_ntc->notice_len,p_wmp_group_ntc->notice);
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
        case WMP_GROUP_LIST_ID:
            p_wmp_group_list = (wmp_group_list_t *)p_wmp_group->param;
            if(!p_wmp_group_list)
            {
                printf("parameter is null.\n");
                break;
            }
            printf("grouip list parameter.\n");
            printf("attr:%02x;group_id:%d;group_num:%d;\n",p_wmp_group_list->attr,\
                    p_wmp_group_list->user_id,p_wmp_group_list->group_num);
            printf("group list:\n");
            for(uint16_t i=0;i<p_wmp_group_list->group_num;i++)
                printf("group_list[%d]:%d;",i,p_wmp_group_list->group_list[i]);
            printf("\n");
            break;
        case WMP_GROUP_FETCH_ID:
            p_wmp_group_fetch = (wmp_group_fetch_t *)p_wmp_group->param;
            if(!p_wmp_group_fetch)
            {
                printf("parameter is null.\n");
                break;
            }
            printf("grouip list parameter.\n");
            printf("attr:%02x;group_id:%d;property_num:%d;\n",p_wmp_group_fetch->attr,\
                    p_wmp_group_fetch->group_id,p_wmp_group_fetch->property_num);
            break;
		default:
			printf("unknown parameter.\n");
			break;
	}
	
    printf("*********************************wm_group_end*********************************\n");
}

/* Copy a new wmp_group_t instance. */
wmp_group_t *copy_wmp_group(const wmp_group_t *p_wmp_group)
{
    wmp_group_t *c_wmp_group = create_wmp_group();
    memcpy(c_wmp_group,p_wmp_group,sizeof(wmp_group_t));
    switch(p_wmp_group->id)
    {
        case WMP_GROUP_CET_ID:
            c_wmp_group->param = copy_wmp_group_cet((wmp_group_cet_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_DSV_ID:
            c_wmp_group->param = copy_wmp_group_dsv((wmp_group_dsv_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_JON_ID:
            c_wmp_group->param = copy_wmp_group_jon((wmp_group_jon_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_EXT_ID:
            c_wmp_group->param = copy_wmp_group_ext((wmp_group_ext_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_SET_ID:
            c_wmp_group->param = copy_wmp_group_set((wmp_group_set_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_MSG_ID:
            c_wmp_group->param = copy_wmp_group_msg((wmp_group_msg_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_FLE_ID:
            c_wmp_group->param = copy_wmp_group_fle((wmp_group_fle_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_NTC_ID:
            c_wmp_group->param = copy_wmp_group_ntc((wmp_group_ntc_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_IVT_ID:
            c_wmp_group->param = copy_wmp_group_ivt((wmp_group_ivt_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_LIST_ID:
            c_wmp_group->param = copy_wmp_group_list((wmp_group_list_t *)p_wmp_group->param);
            break;
        case WMP_GROUP_FETCH_ID:
            c_wmp_group->param = copy_wmp_group_fetch((wmp_group_fetch_t *)p_wmp_group->param);
            break;
        default:
            break;
    }

    return c_wmp_group;
}
