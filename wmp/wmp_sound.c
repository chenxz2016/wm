/* ************************************************************************
 *       Filename:  wmp_sound.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_sound.h"
#include<malloc.h>
#include<string.h>

#define WMP_SoundLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return NULL;

/* ***********************************************************************************
 * Allocate wmp_sound_t.
 *
 * @param:	sound_len		wmp_sound_t sound data length.
 *
 * @retval:	p_wmp_sound		wmp_sound_t pointer.
 *
 * ***********************************************************************************/
wmp_sound_t *allocate_wmp_sound(uint32_t sound_len)
{
	wmp_sound_t *p_wmp_sound = (wmp_sound_t *)malloc(sizeof(wmp_sound_t));
	memset(p_wmp_sound,0,sizeof(wmp_sound_t));
	if(sound_len)
	{
		p_wmp_sound->sound_len = sound_len;
		p_wmp_sound->sound = (uint8_t *)malloc(sound_len);
		memset(p_wmp_sound->sound,0,sound_len);
	}
	return p_wmp_sound;
}

/* ***********************************************************************************
 * Deallocate wmp_sound_t.
 *
 * @param:	p_wmp_sound		The pointer of wmp_sound_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_sound(wmp_sound_t **p_wmp_sound)
{
	if(p_wmp_sound && (*p_wmp_sound) && (*p_wmp_sound)->sound)
	{
		free(((*p_wmp_sound)->sound));
		(*p_wmp_sound)->sound = NULL;
		free(*p_wmp_sound);
		*p_wmp_sound = NULL;
	}
	
	if(p_wmp_sound && (*p_wmp_sound))
	{
		free(*p_wmp_sound);
		*p_wmp_sound = NULL;
	}
}


/* ***********************************************************************************
 * Parser wmp_sound_t.
 *
 * @param:	package			package buffer.
 * @param:	pack_len		package buffer length.
 *
 * @retval:	p_wmp_sound		wmp_sound_t pointer.
 *
 * ***********************************************************************************/
wmp_sound_t *parser_wmp_sound(const char *package,uint32_t pack_len)
{
	uint32_t index = 0;
	
	WMP_SoundLenCheck(index,14,pack_len)
	
	wmp_sound_t *p_wmp_sound = allocate_wmp_sound(0);
	
    p_wmp_sound->attr = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_sound->attr);

    p_wmp_sound->result = *(uint8_t *)(package+index);
    index+=sizeof(p_wmp_sound->result);

	p_wmp_sound->src = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_sound->src);

	p_wmp_sound->dst = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_sound->dst);

	p_wmp_sound->sound_len = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_sound->sound_len);

	memcpy(p_wmp_sound->sound,package+index,p_wmp_sound->sound_len);
	index+=p_wmp_sound->sound_len;
	
	return p_wmp_sound;
}

/* ***********************************************************************************
 * Package wmp_sound_t.
 *
 * @param:	package			package buffer.
 * @param:	p_wmp_sound		wmp_sound_t pointer.
 *
 * @retval:	index			wmp_sound_t protocol package length.
 *
 * ***********************************************************************************/
uint32_t package_wmp_sound(char *package,const wmp_sound_t *p_wmp_sound)
{
	uint32_t index = 0;
	
	*(uint16_t *)(package+index) = htons(p_wmp_sound->attr);
	index+=sizeof(p_wmp_sound->attr);
	*(uint32_t *)(package+index) = htonl(p_wmp_sound->src);
	index+=sizeof(p_wmp_sound->src);
	*(uint32_t *)(package+index) = htonl(p_wmp_sound->dst);
	index+=sizeof(p_wmp_sound->dst);
	*(uint32_t *)(package+index) = htonl(p_wmp_sound->sound_len);
	index+=sizeof(p_wmp_sound->sound_len);
	memcpy(package+index,p_wmp_sound->sound,p_wmp_sound->sound_len);
	index+=p_wmp_sound->sound_len;
	
	return index;
}

/* ***********************************************************************************
 * Set wmp_sound_t sound data length.
 *
 * @param:	p_wmp_sound		wmp_sound_t pointer.
 * @param:	pack_len		sound data length.
 *
 * ***********************************************************************************/
void set_wmp_sound_len(wmp_sound_t *p_wmp_sound,uint32_t sound_len)
{
	if(!p_wmp_sound || sound_len)
		return ;

	if(p_wmp_sound->sound)
		free(p_wmp_sound->sound);

	p_wmp_sound->sound_len = sound_len;
	p_wmp_sound->sound = (uint8_t *)malloc(sound_len);
	memset(p_wmp_sound->sound,0,sound_len);
}



