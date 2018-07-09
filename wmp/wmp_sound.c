/* ************************************************************************
 *       Filename:  wmp_sound.c
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
#include"wmp_sound.h"

#define WMP_SoundLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return NULL;

/* Create wmp_sound_t instance. */
wmp_sound_t *create_wmp_sound(uint32_t sound_len)
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

/* Delete wmp_sound_t. */
void delete_wmp_sound(wmp_sound_t **p_wmp_sound)
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


/* Parser wmp_sound_t. */
wmp_sound_t *parser_wmp_sound(const char *package,uint32_t pack_len)
{
	uint32_t index = 0;
	
	WMP_SoundLenCheck(index,14,pack_len)
	
    wmp_sound_t *p_wmp_sound = create_wmp_sound(0);
	
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

/* Package wmp_sound_t. */
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

/* Set wmp_sound_t sound data length. */
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

/* Print wmp_sound_t. */
void print_wmp_sound(const wmp_sound_t *p_wmp_sound)
{
    if(!p_wmp_sound)
    {
#ifdef WMP_DEBUG
        printf("wmp_sound_t is null.\n");
#endif
        return ;
    }
    printf("********************************wm_sound_start********************************\n");
    printf("attr:%d;result:%d;src:%d;dst:%d;sound_len:%d;",p_wmp_sound->attr,p_wmp_sound->result,\
           p_wmp_sound->src,p_wmp_sound->dst,p_wmp_sound->sound_len);
    printf("sound data:\n");
    for(uint32_t i=0;i<p_wmp_sound->sound_len;i++)
        printf("%02x ",p_wmp_sound->sound[i]);
    printf("\n");
    printf("********************************wm_sound_start********************************\n");
}

/* Copy a new wmp_sound_t instance. */
wmp_sound_t *copy_wmp_sound(const wmp_sound_t *p_wmp_sound)
{
    wmp_sound_t *c_wmp_sound = create_wmp_sound(p_wmp_sound->sound_len);

    c_wmp_sound->attr = p_wmp_sound->attr;
    c_wmp_sound->result = p_wmp_sound->result;
    c_wmp_sound->src = p_wmp_sound->src;
    c_wmp_sound->dst = p_wmp_sound->dst;

    memcpy(c_wmp_sound->sound,p_wmp_sound->sound,p_wmp_sound->sound_len);

    return c_wmp_sound;
}
