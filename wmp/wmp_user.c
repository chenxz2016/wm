/* ************************************************************************
 *       Filename:  wmp_user.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_user.h"
#include<malloc.h>
#include<string.h>

#define WMP_UserLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return NULL;


/* ***********************************************************************************
 * Allocate wmp_user_add_t.
 *
 * @retval:	p_wmp_user_add		wmp_user_add_t pointer.
 *
 * ***********************************************************************************/
wmp_user_add_t *allocate_wmp_user_add()
{
	wmp_user_add_t *p_wmp_user_add = (wmp_user_add_t *)malloc(sizeof(wmp_user_add_t));
	memset(p_wmp_user_add,0,sizeof(wmp_user_add_t));
	return p_wmp_user_add;
}

/* ***********************************************************************************
 * Deallocate wmp_user_add_t.
 *
 * @param:	p_wmp_user_add		wmp_user_add_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_user_add(wmp_user_add_t **p_wmp_user_add)
{
	if(p_wmp_user_add && (*p_wmp_user_add))
	{
		free(*p_wmp_user_add);
		(*p_wmp_user_add) = NULL;
	}
}

/* ***********************************************************************************
 * Allocate wmp_user_del_t.
 *
 * @retval:	p_wmp_user_del		wmp_user_del_t pointer.
 *
 * ***********************************************************************************/
wmp_user_del_t *allocate_wmp_user_del()
{
	wmp_user_del_t *p_wmp_user_del = (wmp_user_del_t *)malloc(sizeof(wmp_user_del_t));
	memset(p_wmp_user_del,0,sizeof(wmp_user_del_t));
	return p_wmp_user_del;
}

/* ***********************************************************************************
 * Deallocate wmp_user_del_t.
 *
 * @param:	p_wmp_user_del		wmp_user_del_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_user_del(wmp_user_del_t **p_wmp_user_del)
{
	if(p_wmp_user_del && (*p_wmp_user_del))
	{
		free(*p_wmp_user_del);
		(*p_wmp_user_del) = NULL;
	}	
}

/* ***********************************************************************************
 * Allocate wmp_user_msg_t.
 *
 * @param:	msg_len				wmp_user_msg_t message length.
 *
 * @retval:	p_wmp_user_msg		wmp_user_msg_t pointer.
 *
 * ***********************************************************************************/
wmp_user_msg_t *allocate_wmp_user_msg(uint32_t msg_len)
{
	wmp_user_msg_t *p_wmp_user_msg = (wmp_user_msg_t *)malloc(sizeof(wmp_user_msg_t));
	memset(p_wmp_user_msg,0,sizeof(wmp_user_msg_t));
	if(msg_len)
	{
		p_wmp_user_msg->msg = (char *)malloc(msg_len);
		p_wmp_user_msg->msg_len = msg_len;
		memset(p_wmp_user_msg->msg,0,msg_len);
	}
	return p_wmp_user_msg;
}

/* ***********************************************************************************
 * Deallocate wmp_user_msg_t.
 *
 * @param:	p_wmp_user_msg		wmp_user_msg_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_user_msg(wmp_user_msg_t **p_wmp_user_msg)
{
	if(p_wmp_user_msg && (*p_wmp_user_msg) && (*p_wmp_user_msg)->msg)
	{
		free((*p_wmp_user_msg)->msg);
		(*p_wmp_user_msg)->msg = NULL;
		free(*p_wmp_user_msg);
		(*p_wmp_user_msg) = NULL;
		return ;
	}
	if(p_wmp_user_msg && (*p_wmp_user_msg))
	{
		free(*p_wmp_user_msg);
		(*p_wmp_user_msg) = NULL;		
	}
}

/* ***********************************************************************************
 * Set wmp_user_msg_t message length.
 *
 * @param:	p_wmp_user_msg		wmp_user_msg_t pointer.
 * @param:	msg_len				wmp_user_msg_t message length.
 *
 * ***********************************************************************************/
void set_wmp_user_msg_len(wmp_user_msg_t *p_wmp_user_msg,uint32_t msg_len)
{
	if(!p_wmp_user_msg || !msg_len)
		return ;
	
	if(p_wmp_user_msg->msg)
		free(p_wmp_user_msg->msg);
	
	p_wmp_user_msg->msg = (char *)malloc(msg_len);
	memset(p_wmp_user_msg->msg,0,msg_len);
	p_wmp_user_msg->msg_len = msg_len;
}

/* ***********************************************************************************
 * Allocate wmp_user_set_t.
 *
 * @param:	property_num			wmp_user_set_t message length.
 *
 * @retval:	p_wmp_user_msg			wmp_user_set_t pointer.
 *
 * ***********************************************************************************/
wmp_user_set_t *allocate_wmp_user_set(uint16_t property_num)
{
	wmp_user_set_t *p_wmp_user_set = (wmp_user_set_t *)malloc(sizeof(wmp_user_set_t));
	memset(p_wmp_user_set,0,sizeof(wmp_user_set_t));
	if(property_num)
	{
		p_wmp_user_set->property_num = property_num;
		p_wmp_user_set->property_list = (wmp_user_property_t *)malloc(sizeof(wmp_user_property_t)*property_num);
		memset(p_wmp_user_set->property_list,0,sizeof(wmp_user_property_t)*property_num);
	}
	return p_wmp_user_set;
}


/* ***********************************************************************************
 * Deallocate wmp_user_set_t.
 *
 * @param:	p_wmp_user_set		wmp_user_set_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_user_set(wmp_user_set_t **p_wmp_user_set)
{
	if(p_wmp_user_set && (*p_wmp_user_set) && (*p_wmp_user_set)->property_list)
	{
		free((*p_wmp_user_set)->property_list);
		(*p_wmp_user_set)->property_list = NULL;
		free((*p_wmp_user_set));
		(*p_wmp_user_set) = NULL;
	}

	if(p_wmp_user_set && (*p_wmp_user_set))
	{
		free((*p_wmp_user_set));
		(*p_wmp_user_set) = NULL;
	}
}

/* ***********************************************************************************
 * Deallocate wmp_user_set_t.
 *
 * @param:	p_wmp_user_set		wmp_user_set_t pointer.
 *
 * ***********************************************************************************/
void set_wmp_user_set_property_num(wmp_user_set_t *p_wmp_user_set,uint32_t property_num)
{
	if(!p_wmp_user_set || !property_num)
		return ;

	if(p_wmp_user_set->property_list)
		free(p_wmp_user_set->property_list);

	p_wmp_user_set->property_num = property_num;
	p_wmp_user_set->property_list = (wmp_user_property_t *)malloc(sizeof(wmp_user_property_t)*property_num);
	memset(p_wmp_user_set->property_list,0,sizeof(wmp_user_property_t)*property_num);
}



/* ***********************************************************************************
 * Allocate wmp_user_friend_t.
 *
 * @retval:	p_wmp_user_friend				wmp_user_friend_t pointer.
 *
 * ***********************************************************************************/
wmp_user_friend_t *allocate_wmp_user_friend(uint16_t friend_num)
{
	wmp_user_friend_t *p_wmp_user_friend = (wmp_user_friend_t *)malloc(sizeof(wmp_user_friend_t));
	memset(p_wmp_user_friend,0,sizeof(wmp_user_friend_t));
	if(friend_num)
	{
		p_wmp_user_friend->friend_list = (uint32_t *)malloc(friend_num * sizeof(uint32_t));
		memset(p_wmp_user_friend->friend_list,0,friend_num * sizeof(uint32_t));
	}
	return p_wmp_user_friend;
}

/* ***********************************************************************************
 * Deallocate wmp_user_friend_t.
 *
 * @retval:	p_wmp_user				wmp_user_friend_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_user_friend(wmp_user_friend_t **p_wmp_user_friend)
{
	if((*p_wmp_user_friend)->friend_list)
	{
		free((*p_wmp_user_friend)->friend_list);
		(*p_wmp_user_friend)->friend_list = NULL;
	}
	free(*p_wmp_user_friend);
	p_wmp_user_friend = NULL;
}

/* ***********************************************************************************
 * Set wmp_user_friend_t friend numbers.
 *
 * @param:	p_wmp_user_friend				wmp_user_friend_t pointer.
 * @param:	friend_num						friend numbers.
 *
 * ***********************************************************************************/
void set_wmp_user_friend_num(wmp_user_friend_t *p_wmp_user_friend,uint16_t friend_num)
{
    if(p_wmp_user_friend->friend_list)
        free(p_wmp_user_friend->friend_list);

    p_wmp_user_friend->friend_num = friend_num;
    p_wmp_user_friend->friend_list = (uint32_t *)malloc(friend_num * sizeof(uint32_t));
    memset(p_wmp_user_friend->friend_list,0,friend_num * sizeof(uint32_t));
}




/* ***********************************************************************************
 * Allocate wmp_user_t.
 *
 * @retval:	p_wmp_user				wmp_user_t pointer.
 *
 * ***********************************************************************************/
wmp_user_t *allocate_wmp_user()
{
	wmp_user_t *p_wmp_user = (wmp_user_t *)malloc(sizeof(wmp_user_t));
	memset(p_wmp_user,0,sizeof(wmp_user_t));
	return p_wmp_user;
}


/* ***********************************************************************************
 * Deallocate wmp_user_t.
 *
 * @param:	p_wmp_user				wmp_user_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_user(wmp_user_t **p_wmp_user)
{
	if(p_wmp_user && (*p_wmp_user) && (*p_wmp_user)->param)
	{
		switch((*p_wmp_user)->id)	
		{
			case WMP_USER_ADD_ID:
				deallocate_wmp_user_add((wmp_user_add_t **)&((*p_wmp_user)->param));
				break;
			case WMP_USER_DEL_ID:
				deallocate_wmp_user_del((wmp_user_del_t **)&((*p_wmp_user)->param));
				break;
			case WMP_USER_SET_ID:
				deallocate_wmp_user_set((wmp_user_set_t **)&((*p_wmp_user)->param));
				break;
			case WMP_USER_MSG_ID:
				deallocate_wmp_user_msg((wmp_user_msg_t **)&((*p_wmp_user)->param));
				break;
		}
		free((*p_wmp_user));
		(*p_wmp_user) = NULL;
	}

	if(p_wmp_user && (*p_wmp_user))
	{
		free((*p_wmp_user));
		(*p_wmp_user) = NULL;
	}
}


/* ***********************************************************************************
 * Parser wmp_user_t paremeter.
 *
 * @param:	package				protocol package buffer.
 * @param:	pack_len			protocol package buffer length.
 * @param:	p_wmp_user			wmp_user_t pointer.
 *
 * @retval:	index				wmp_user_t parameter length.
 *
 * ***********************************************************************************/
static uint32_t parser_wmp_user_parameter(const char *package,uint32_t pack_lem,wmp_user_t *p_wmp_user)
{
	uint32_t index = 0;

	wmp_user_add_t *p_wmp_user_add = NULL;
	wmp_user_del_t *p_wmp_user_del = NULL;
	wmp_user_msg_t *p_wmp_user_msg = NULL;
	wmp_user_set_t *p_wmp_user_set = NULL;
	switch(p_wmp_user->id)
	{
		case WMP_USER_ADD_ID:
			p_wmp_user_add = allocate_wmp_user_add();
			p_wmp_user->param = (uint8_t *)p_wmp_user_add;
			p_wmp_user_add->attr = ntohs(*(uint16_t *)(package+index));
			index+=2;
			p_wmp_user_add->msg_len = *(uint8_t *)(package+index);
			index++;
			if(p_wmp_user_add->msg_len)
			{
				memcpy(p_wmp_user_add->msg,package+index,p_wmp_user_add->msg_len);
				index+=p_wmp_user_add->msg_len;
			}
			break;
		case WMP_USER_DEL_ID:
			p_wmp_user_del = allocate_wmp_user_del();
			p_wmp_user->param = (uint8_t *)p_wmp_user_del;
			p_wmp_user_del->attr = ntohs(*(uint16_t *)(package+index));
			index+=2;
			break;
		case WMP_USER_SET_ID:
			p_wmp_user_set = allocate_wmp_user_set(0);
			p_wmp_user->param = (uint8_t *)p_wmp_user_set;
			p_wmp_user_set->attr = ntohs(*(uint16_t *)(package+index));
			index+=2;
			p_wmp_user_set->property_num = ntohs(*(uint16_t *)(package+index));
			index+=2;
			set_wmp_user_set_property_num(p_wmp_user_set,\
					p_wmp_user_set->property_num);
			for(uint16_t i=0;i<p_wmp_user_set->property_num;i++)
			{
				p_wmp_user_set->property_list->id = ntohs(*(uint16_t *)(package+index));
				index+=2;
				p_wmp_user_set->property_list->type = ntohs(*(uint16_t *)(package+index));
				index+=2;
				p_wmp_user_set->property_list->len = *(uint8_t *)(package+index);
				index++;
				memcpy(p_wmp_user_set->property_list->data,package+index,p_wmp_user_set->property_list->len);
				index+=p_wmp_user_set->property_list->len;
			}

			break;
		case WMP_USER_MSG_ID:
			p_wmp_user_msg = allocate_wmp_user_msg(0);
			p_wmp_user->param = (uint8_t *)p_wmp_user_msg;
			p_wmp_user_msg->attr = ntohs(*(uint16_t *)(package+index));
			index+=2;
			p_wmp_user_msg->msg_len = ntohl(*(uint32_t *)(package+index));
			index+=4;
			if(p_wmp_user_msg->msg_len)
			{
				set_wmp_user_msg_len(p_wmp_user_msg,p_wmp_user_msg->msg_len);
				memcpy(p_wmp_user_add->msg,package+index,p_wmp_user_add->msg_len);
				index+=p_wmp_user_add->msg_len;
			}
			break;
		default:
			return 0;
	}
	return index;
}

/* ***********************************************************************************
 * Parser wmp_user_t.
 *
 * @param:	package				protocol package buffer.
 * @param:	pack_len			protocol package buffer length.
 *
 * @retval:	p_wmp_user			wmp_user_t pointer.
 *
 * ***********************************************************************************/
wmp_user_t *parser_wmp_user(const char *package,uint32_t pack_len)
{
	if(!package || pack_len < WMP_USER_MIN_LENGTH)
	{
#ifdef WMP_DEBUG
		printf("[WMP] parser wmp failed.\n");
#endif
		return NULL;
	}

	uint32_t index = 0;
	wmp_user_t *p_wmp_user = allocate_wmp_user();

	p_wmp_user->src = ntohl(*(uint32_t *)(package+index));
	index+=4;

	p_wmp_user->dst = ntohl(*(uint32_t *)(package+index));
	index+=4;

	p_wmp_user->id = ntohs(*(uint16_t *)(package+index));
	index+=2;

	uint32_t ret= parser_wmp_user_parameter(package+index,pack_len-index,p_wmp_user);
	if(!ret)
	{
#ifdef WMP_DEBUG
		printf("[WMP] parser wmp_user_t parameter failed.\n");
#endif
		deallocate_wmp_user(&p_wmp_user);
		return NULL;
	}
	return p_wmp_user;
}

static uint32_t package_wmp_user_parameter(char *package,const wmp_user_t *p_wmp_user)
{
	uint32_t index = 0;

	wmp_user_add_t *p_wmp_user_add = NULL;
	wmp_user_del_t *p_wmp_user_del = NULL;
	wmp_user_msg_t *p_wmp_user_msg = NULL;
	wmp_user_set_t *p_wmp_user_set = NULL;
	
	switch(p_wmp_user->id)
	{

		case WMP_USER_ADD_ID:
			p_wmp_user_add = (wmp_user_add_t *)(p_wmp_user->param);
			*(uint16_t *)(package+index) = htons(p_wmp_user_add->attr);
			index+=2;
			*(uint8_t *)(package+index) = p_wmp_user_add->msg_len;
			index++;
			if(p_wmp_user_add->msg_len)
			{
				memcpy(package+index,p_wmp_user_add->msg,p_wmp_user_add->msg_len);
				index+=p_wmp_user_add->msg_len;
			}
			break;
		case WMP_USER_DEL_ID:
			p_wmp_user_del = (wmp_user_del_t *)(p_wmp_user->param);
			*(uint16_t *)(package+index) = htons(p_wmp_user_del->attr);
			index+=2;
			break;
		case WMP_USER_SET_ID:
			p_wmp_user_set = (wmp_user_set_t *)(p_wmp_user->param);
			*(uint16_t *)(package+index) = htons(p_wmp_user_set->attr);
			index+=2;
			*(uint16_t *)(package+index) = htons(p_wmp_user_set->property_num);
			index+=2;
			for(uint16_t i=0;i<p_wmp_user_set->property_num;i++)
			{
				*(uint16_t *)(package+index) = ntohs(p_wmp_user_set->property_list->id);
				index+=2;
				*(uint16_t *)(package+index) = ntohs(p_wmp_user_set->property_list->type);
				index+=2;
				*(uint8_t *)(package+index) = p_wmp_user_set->property_list->len;
				index++;
				memcpy(p_wmp_user_set->property_list->data,package+index,p_wmp_user_set->property_list->len);
				index+=p_wmp_user_set->property_list->len;
			}

			break;
		case WMP_USER_MSG_ID:
			p_wmp_user_msg = (wmp_user_msg_t *)(p_wmp_user->param);
			*(uint16_t *)(package+index) = htons(p_wmp_user_msg->attr);
			index+=2;
			*(uint32_t *)(package+index) = htonl(p_wmp_user_msg->msg_len);
			index+=4;
			if(p_wmp_user_msg->msg_len)
			{
				memcpy(package+index,p_wmp_user_msg->msg,p_wmp_user_msg->msg_len);
				index+=p_wmp_user_msg->msg_len;
			}
			break;
		default:
			return 0;
	}
	return index;
}

/* ***********************************************************************************
 * Package wmp_user_t.
 *
 * @param:	package				protocol package buffer.
 * @param:	p_wmp_user			protocol package buffer length.
 *
 * @retval:	index				wmp_user_t protocol package length.
 *
 * ***********************************************************************************/
uint32_t package_wmp_user(char *package,const wmp_user_t *p_wmp_user)
{
	if(!package || !p_wmp_user)
	{
#ifdef WMP_DEBUG
		printf("[WMP] package wmp_user_t failed.\n");
#endif
		return 0;
	}
	uint32_t index = 0;

	*(uint32_t *)(package+index) = htonl(p_wmp_user->src);
	index+=4;

	*(uint32_t *)(package+index) = htonl(p_wmp_user->dst);
	index+=4;

	*(uint16_t *)(package+index) = htons(p_wmp_user->id);
	index+=2;

	index += package_wmp_user_parameter(package+index,p_wmp_user);

	return index;
}

/* ***********************************************************************************
 * Print wmp_user_t.
 *
 * @param:	p_wmp_user			wmp_user_t pointer.
 *
 * ***********************************************************************************/
void print_wmp_user(const wmp_user_t *p_wmp_user)
{
	if(!p_wmp_user)
	{
#ifdef WMP_DEBUG
		printf("[WMP] wmp_user_t is null.\n");
#endif
		return ;
	}

	printf("***************************WM-user Protocol Start**********************\n");

    printf("src:%d;dst:%d;id:%d;",p_wmp_user->src,p_wmp_user->dst,p_wmp_user->id);

	wmp_user_add_t *p_wmp_user_add = NULL;
	wmp_user_del_t *p_wmp_user_del = NULL;
	wmp_user_set_t *p_wmp_user_set = NULL;
	wmp_user_msg_t *p_wmp_user_msg = NULL;

	switch(p_wmp_user->id)
	{
		case WMP_USER_ADD_ID:
			p_wmp_user_add = (wmp_user_add_t *)p_wmp_user->param;
			if(!p_wmp_user_add)
			{
				printf("paramter is null.\n");
				break;
			}
			printf("attr:%d;msg_len:%d;msg:%s;\n",p_wmp_user_add->attr,p_wmp_user_add->msg_len,\
					p_wmp_user_add->msg);
			break;
		case WMP_USER_DEL_ID:
			p_wmp_user_del = (wmp_user_del_t *)p_wmp_user->param;
			if(!p_wmp_user_del)
			{
				printf("paramter is null.\n");
				break;
			}
			printf("attr:%d;\n",p_wmp_user_del->attr);
			break;
		case WMP_USER_MSG_ID:
			p_wmp_user_msg = (wmp_user_msg_t *)p_wmp_user->param;
			if(!p_wmp_user_msg)
			{
				printf("paramter is null.\n");
				break;
			}
			printf("attr:%d;msg_len:%d;msg:%s;\n",p_wmp_user_msg->attr,p_wmp_user_msg->msg_len,\
					p_wmp_user_msg->msg);
			break;
		case WMP_USER_SET_ID:
			p_wmp_user_set = (wmp_user_set_t *)p_wmp_user->param;
			printf("attr:%d;property_num:%d;",p_wmp_user_set->attr,p_wmp_user_set->property_num);
			for(uint16_t i=0;i<p_wmp_user_set->property_num;i++)
			{
				printf("id:%d;type:%d;len:%d;",p_wmp_user_set->property_list[i].id,\
						p_wmp_user_set->property_list[i].type,
						p_wmp_user_set->property_list[i].len);
				for(uint8_t j=0;j<p_wmp_user_set->property_list[i].len;j++)
					printf("%02x ",p_wmp_user_set->property_list[i].data[j]);
			}
			printf("\n");
			break;
		default:
			printf("unknown parameter.\n");
			break;
	}

	printf("***************************WM-user Protocol End***********************\n");
}



