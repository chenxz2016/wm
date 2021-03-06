/* ************************************************************************
 *       Filename:  wmp_login.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_login.h"
#include<malloc.h>
#include<string.h>


/* Create wmp_login_t instance. */
wmp_login_t *create_wmp_login()
{
	wmp_login_t *p_wmp_login = (wmp_login_t *)malloc(sizeof(wmp_login_t));
	memset(p_wmp_login,0,sizeof(wmp_login_t));
	return p_wmp_login;
}


/* Delete wmp_login_t instance. */
void delete_wmp_login(wmp_login_t **p_wmp_login)
{
	if(p_wmp_login && (*p_wmp_login))
	{
		free(*p_wmp_login);
		(*p_wmp_login) = 0;
	}
}

/* Parser wmp_login_t. */
wmp_login_t *parser_wmp_login(const char *package,uint32_t pack_len)
{
	if(!package || pack_len<WMP_LOGIN_LENGTH)
	{
#ifdef WMP_DEBUG
		printf("[WMP] parser wmp_login_t failed.\n");
#endif
		return NULL;
	}
	
	uint32_t index = 0;
    wmp_login_t *p_wmp_login = create_wmp_login();
	
	p_wmp_login->attr = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_login->attr);

	p_wmp_login->user_id = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_login->user_id);

	if((p_wmp_login->attr & 1) == 1)
	{
		p_wmp_login->result = *(uint8_t *)(package+index);
		index+=sizeof(p_wmp_login->result);
	}
	else if((p_wmp_login->attr & 1) == 0)
	{
		p_wmp_login->pwd_len = *(uint8_t *)(package+index);
		index+=sizeof(p_wmp_login->pwd_len);
	
		memcpy(p_wmp_login->password,package+index,p_wmp_login->pwd_len);
		index+=p_wmp_login->pwd_len;
	}
	
	return p_wmp_login;
}


/* Package wmp_login_t. */
uint32_t package_wmp_login(char *package,const wmp_login_t *p_wmp_login)
{
	uint32_t index = 0;
	*(uint8_t *)(package+index) = p_wmp_login->attr;
	index+=sizeof(p_wmp_login->attr);

	*(uint32_t *)(package+index) = htonl(p_wmp_login->user_id);
	index+=sizeof(p_wmp_login->user_id);

	if((p_wmp_login->attr & 1) == 1)
	{
		*(uint8_t *)(package+index) = p_wmp_login->result;
		index+=sizeof(p_wmp_login->result);
	}
	else if((p_wmp_login->attr & 1) == 0)
	{
		*(uint8_t *)(package+index) = p_wmp_login->pwd_len;
		index+=sizeof(p_wmp_login->pwd_len);
		
		memcpy(package+index,p_wmp_login->password,p_wmp_login->pwd_len);
		index+=p_wmp_login->pwd_len;
	}
	return index;
}

/* Print wmp_login_t. */
void print_wmp_login(const wmp_login_t *p_wmp_login)
{
	if(!p_wmp_login)
	{
#ifdef WMP_DEBUG
		printf("[WMP] wmp_login_t is null.\n");
#endif
		return ;
	}

    printf("********************************wm_login_start********************************\n");
	printf("attr:%d;result:%d;user_id:%d;pwd_len:%d;password:%s\n",p_wmp_login->attr,\
			p_wmp_login->result,p_wmp_login->user_id,p_wmp_login->pwd_len,p_wmp_login->password);
    printf("*********************************wm_login_end**********************************\n");
}


/* Copy a new wmp_login_t instance. */
wmp_login_t *copy_wmp_login(const wmp_login_t *p_wmp_login)
{
    wmp_login_t *c_wmp_login = create_wmp_login();

    memcpy(c_wmp_login,p_wmp_login,sizeof(wmp_login_t));

    return c_wmp_login;
}


/* Create wmp_login_key_t instance. */
wmp_login_key_t *create_wmp_login_key()
{
    wmp_login_key_t *p_wmp_login_key = (wmp_login_key_t *)malloc(sizeof(wmp_login_key_t));
    memset(p_wmp_login_key,0,sizeof(wmp_login_key_t));
    return p_wmp_login_key;
}


/* Delete wmp_login_key_t instance. */
void delete_wmp_login_key(wmp_login_key_t **p_wmp_login_key)
{
    if(p_wmp_login_key && (*p_wmp_login_key))
    {
        free(*p_wmp_login_key);
        (*p_wmp_login_key) = 0;
    }
}

/* Parser wmp_login_key_t. */
wmp_login_key_t *parser_wmp_login_key(const char *package,uint32_t pack_len)
{
    if(!package || pack_len<WMP_LOGIN_LENGTH)
    {
#ifdef WMP_DEBUG
        printf("[WMP] parser wmp_login_key_t failed.\n");
#endif
        return NULL;
    }

    uint32_t index = 0;
    wmp_login_key_t *p_wmp_login_key = create_wmp_login_key();

    p_wmp_login_key->attr = *(uint8_t *)(package+index);
    index+=sizeof(p_wmp_login_key->attr);

    p_wmp_login_key->user_id = ntohl(*(uint32_t *)(package+index));
    index+=sizeof(p_wmp_login_key->user_id);

    if((p_wmp_login_key->attr & 1) == 1)
    {
        p_wmp_login_key->result = *(uint8_t *)(package+index);
        index+=sizeof(p_wmp_login_key->result);
    }
	
	p_wmp_login_key->type = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_login_key->type);

	p_wmp_login_key->key_len = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_login_key->key_len);

	memcpy(p_wmp_login_key->key,package+index,p_wmp_login_key->key_len);
	index+=p_wmp_login_key->key_len;

    return p_wmp_login_key;
}


/* Package wmp_login_key_t. */
uint32_t package_wmp_login_key(char *package,const wmp_login_key_t *p_wmp_login_key)
{
    uint32_t index = 0;
    *(uint8_t *)(package+index) = p_wmp_login_key->attr;
    index+=sizeof(p_wmp_login_key->attr);

    *(uint32_t *)(package+index) = htonl(p_wmp_login_key->user_id);
    index+=sizeof(p_wmp_login_key->user_id);

    if((p_wmp_login_key->attr & 1) == 1)
    {
        *(uint8_t *)(package+index) = p_wmp_login_key->result;
        index+=sizeof(p_wmp_login_key->result);
    }
	
	*(uint8_t *)(package+index) = p_wmp_login_key->type;
	index+=sizeof(p_wmp_login_key->type);

	*(uint8_t *)(package+index) = p_wmp_login_key->key_len;
	index+=sizeof(p_wmp_login_key->key_len);

	memcpy(package+index,p_wmp_login_key->key,p_wmp_login_key->key_len);
	index+=p_wmp_login_key->key_len;
	
    return index;
}


/* Print wmp_login_key_t. */
void print_wmp_login_key(const wmp_login_key_t *p_wmp_login_key)
{
    if(!p_wmp_login_key)
    {
#ifdef WMP_DEBUG
        printf("[WMP] wmp_login_key_t is null.\n");
#endif
        return ;
    }

    printf("******************************wm_login_key_start******************************\n");
    printf("attr:%d;type:%d;result:%d;user_id:%d;key_len:%d\n",p_wmp_login_key->attr,\
           p_wmp_login_key->type,p_wmp_login_key->result,p_wmp_login_key->user_id,\
           p_wmp_login_key->key_len);
    printf("Key:");
    for(uint8_t i = 0;i<p_wmp_login_key->key_len;i++)
        printf("%c ",p_wmp_login_key->key[i]);

    printf("\n");
    printf("*******************************wm_login_key_end*******************************\n");
}


/* Copy a new wmp_login_key_t instance. */
wmp_login_key_t *copy_wmp_login_key(const wmp_login_key_t *p_wmp_login_key)
{
    wmp_login_key_t *c_wmp_login_key = create_wmp_login_key();

    memcpy(c_wmp_login_key,p_wmp_login_key,sizeof(wmp_login_key_t));

    return c_wmp_login_key;
}
