/* ************************************************************************
 *       Filename:  wmp_login.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_login.h"
#include<malloc.h>
#include<string.h>

/* ***********************************************************************************
 * Allocate wmp_login_t.
 *
 * @param:	p_wmp_login	wmp_login_t pointer.
 *
 * ***********************************************************************************/
wmp_login_t *allocate_wmp_login()
{
	wmp_login_t *p_wmp_login = (wmp_login_t *)malloc(sizeof(wmp_login_t));
	memset(p_wmp_login,0,sizeof(wmp_login_t));
	return p_wmp_login;
}

/* ***********************************************************************************
 * Deallocate wmp_login_t.
 *
 * @param:	p_wmp_login		The pointer of wmp_login_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_login(wmp_login_t **p_wmp_login)
{
	if(p_wmp_login && (*p_wmp_login))
	{
		free(*p_wmp_login);
		(*p_wmp_login) = 0;
	}
}

/* ***********************************************************************************
 * Parser wmp_login_t package.
 *
 * @param:	package			Package buffer.
 * @param:	pack_len		Package buffer length.
 *
 * @retval:	p_wmp_login		wmp_login_t pointer.
 *
 * ***********************************************************************************/
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
	wmp_login_t *p_wmp_login = allocate_wmp_login();
	
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


/* ***********************************************************************************
 * Package wmp_login_t package.
 *
 * @param:	package			Package buffer.
 * @param:	p_wmp_login		wmp_login_t pointer.
 *
 * @param:	index			wmp_login_t package length.
 *
 * ***********************************************************************************/
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

/* ***********************************************************************************
 * Print wmp_login_t package.
 *
 * @param:	p_wmp_login		wmp_login_t pointer.
 *
 * ***********************************************************************************/
void print_wmp_login(wmp_login_t *p_wmp_login)
{
	if(!p_wmp_login)
	{
#ifdef WMP_DEBUG
		printf("[WMP] wmp_login_t is null.\n");
#endif
		return ;
	}

	printf("***************************WM-login Protocol Start**********************\n");
	printf("attr:%d;result:%d;user_id:%d;pwd_len:%d;password:%s\n",p_wmp_login->attr,\
			p_wmp_login->result,p_wmp_login->user_id,p_wmp_login->pwd_len,p_wmp_login->password);
	printf("***************************WM-login Protocol End************************\n");
}

/* ***********************************************************************************
 * Allocate wmp_login_key_t package.
 *
 * @retval:	p_wmp_login_key		wmp_login_key_t pointer.
 *
 * ***********************************************************************************/
wmp_login_key_t *allocate_wmp_login_key()
{
    wmp_login_key_t *p_wmp_login_key = (wmp_login_key_t *)malloc(sizeof(wmp_login_key_t));
    memset(p_wmp_login_key,0,sizeof(wmp_login_key_t));
    return p_wmp_login_key;
}


/* ***********************************************************************************
 * Deallocate wmp_login_key_t package.
 *
 * @param:	p_wmp_login_key		wmp_login_key_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_login_key(wmp_login_key_t **p_wmp_login_key)
{
    if(p_wmp_login_key && (*p_wmp_login_key))
    {
        free(*p_wmp_login_key);
        (*p_wmp_login_key) = 0;
    }
}

/* ***********************************************************************************
 * Parser wmp_login_key_t package.
 *
 * @param:	package		raw package.
 * @param:	pack_len	package length.
 *
 * @retval: p_wm_login_key wm_login_key_t pointer.
 *
 * ***********************************************************************************/
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
    wmp_login_key_t *p_wmp_login_key = allocate_wmp_login_key();

    p_wmp_login_key->attr = *(uint8_t *)(package+index);
    index+=sizeof(p_wmp_login_key->attr);

    p_wmp_login_key->user_id = ntohl(*(uint32_t *)(package+index));
    index+=sizeof(p_wmp_login_key->user_id);

    if((p_wmp_login_key->attr & 1) == 1)
    {
        p_wmp_login_key->result = *(uint8_t *)(package+index);
        index+=sizeof(p_wmp_login_key->result);
    }
    else if((p_wmp_login_key->attr & 1) == 0)
    {
        p_wmp_login_key->type = *(uint8_t *)(package+index);
        index+=sizeof(p_wmp_login_key->type);

        p_wmp_login_key->key_len = *(uint8_t *)(package+index);
        index+=sizeof(p_wmp_login_key->key_len);

        memcpy(p_wmp_login_key->key,package+index,p_wmp_login_key->key_len);
        index+=p_wmp_login_key->key_len;
    }

    return p_wmp_login_key;
}

/* ***********************************************************************************
 * Parser wmp_login_key_t package.
 *
 * @param:	package		package.
 * @param:	p_wmp_login_key	 wm_login_key_t pointer.
 *
 * @retval: index       package length.
 *
 * ***********************************************************************************/
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
    else if((p_wmp_login_key->attr & 1) == 0)
    {
        *(uint8_t *)(package+index) = p_wmp_login_key->type;
        index+=sizeof(p_wmp_login_key->type);

        *(uint8_t *)(package+index) = p_wmp_login_key->key_len;
        index+=sizeof(p_wmp_login_key->key_len);

        memcpy(package+index,p_wmp_login_key->key,p_wmp_login_key->key_len);
        index+=p_wmp_login_key->key_len;
    }
    return index;
}

/* ***********************************************************************************
 * Parser wmp_login_key_t package.
 *
 * @param:	p_wmp_login_key	 wm_login_key_t pointer.
 *
 * ***********************************************************************************/
void print_wmp_login_key(wmp_login_key_t *p_wmp_login_key)
{
    if(!p_wmp_login_key)
    {
#ifdef WMP_DEBUG
        printf("[WMP] wmp_login_key_t is null.\n");
#endif
        return ;
    }

    printf("***************************WM-login key Protocol Start**********************\n");
    printf("attr:%d;type:%d;result:%d;user_id:%d;key_len:%d\n",p_wmp_login_key->attr,\
           p_wmp_login_key->type,p_wmp_login_key->result,p_wmp_login_key->user_id,\
           p_wmp_login_key->key_len);
    printf("Key:");
    for(uint8_t i = 0;i<p_wmp_login_key->key_len;i++)
        printf("%c ",p_wmp_login_key->key[i]);

    printf("\n");
    printf("***************************WM-login Protocol End************************\n");
}


