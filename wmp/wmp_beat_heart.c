/* ************************************************************************
 *       Filename:  wmp_beat_heart.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_beat_heart.h"
#include<malloc.h>
#include<string.h>

/* ***********************************************************************************
 * Allocate wmp_beat_heart_t.
 *
 * @retval:	p_wm_bh		The pointer of wmp_beat_heart_t.
 *
 * ***********************************************************************************/
wmp_beat_heart_t *allocate_wmp_beat_heart()
{
	wmp_beat_heart_t *p_wmp_bh = (wmp_beat_heart_t *)malloc(sizeof(wmp_beat_heart_t));
	memset(p_wmp_bh,0,sizeof(wmp_beat_heart_t));
	return p_wmp_bh;
}

/* ***********************************************************************************
 * Deallocate wmp_beat_heart_t.
 *
 * @param:	p_wmp_bh	The pointer of wmp_beat_heart_t.
 *
 * ***********************************************************************************/
void deallocate_wmp_beat_heart(wmp_beat_heart_t **p_wmp_bh)
{
	if(p_wmp_bh && (*p_wmp_bh))
	{
		free(*p_wmp_bh);
		(*p_wmp_bh) = NULL;
	}
}
/* ***********************************************************************************
 * Parser wmp_beat_heart_t package.
 *
 * @param:	package		package buffer.
 * @param:	pack_len	package length.
 *
 * @retval:	p_wm_bh		The pointer of wm_beat_heart_t.
 *
 * ***********************************************************************************/
wmp_beat_heart_t *parser_wmp_beat_heart(const char *package,uint32_t pack_len)
{
	if(!package || pack_len<WMP_BEAT_HEART_LENGTH)
	{
#ifdef WMP_DEBUG
		printf("[WMP] parser beat heart failed.\n");
#endif
		return NULL;
	}
	
	uint32_t index = 0;
	wmp_beat_heart_t *p_wmp_bh = allocate_wmp_beat_heart();
	
	p_wmp_bh->attr = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_bh->attr);

	p_wmp_bh->user_id = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_bh->user_id);

	p_wmp_bh->flag = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_bh->flag);

	return p_wmp_bh;
}

/* ***********************************************************************************
 * Package wmp_beat_heart_t.
 *
 * @param:	package		package buffer.
 * @param:	p_wmp_bh	The pointer of wmp_beat_heart_t.
 *
 * @retval:	index		Length of wmp_beat_heart_t package.
 *
 * ***********************************************************************************/
uint32_t package_wmp_beat_heart(char *package,const wmp_beat_heart_t *p_wmp_bh)
{
	uint32_t index = 0;

	*(uint8_t *)(package+index) = p_wmp_bh->attr;
	index+=sizeof(p_wmp_bh->attr);

	*(uint32_t *)(package+index) = htonl(p_wmp_bh->user_id);
	index+=sizeof(p_wmp_bh->user_id);

	*(uint8_t *)(package+index) = p_wmp_bh->flag;
	index+=sizeof(p_wmp_bh->flag);
	
	return index;
}

/* ***********************************************************************************
 * Print wmp_beat_heart_t.
 *
 * @param:	p_wmp_bh	The pointer of wmp_beat_heart_t.
 *
 * ***********************************************************************************/
void print_wmp_beat_heart(const wmp_beat_heart_t *p_wmp_bh)
{
	if(!p_wmp_bh)
	{
#ifdef WMP_DEBUG
		printf("wmp_beat_heart_ is null.\n");
#endif
		return ;
	}

	printf("***************************WM-beat_heart Protocol Start**********************\n");
	printf("attr:%02x;user_id:%d;flag:%d;\n",p_wmp_bh->attr,p_wmp_bh->user_id,p_wmp_bh->flag);
	printf("***************************WM-beat_heart Protocol End************************\n");
}




