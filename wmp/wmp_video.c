/* ************************************************************************
 *       Filename:  wmp_video.c
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
#include"wmp_video.h"


#define WMP_VideoLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return NULL;

/* Create wmp_video_t instance. */
wmp_video_t *create_wmp_video(uint32_t video_len)
{
	wmp_video_t *p_wmp_video = (wmp_video_t *)malloc(sizeof(wmp_video_t));
	memset(p_wmp_video,0,sizeof(wmp_video_t));
	if(video_len)
	{
		p_wmp_video->video_len = video_len;
		p_wmp_video->video = (char *)malloc(video_len);
		memset(p_wmp_video->video,0,video_len);
	}
	return p_wmp_video;
}

/* Delete wmp_video_t instance. */
void delete_wmp_video(wmp_video_t **p_wmp_video)
{
	if(p_wmp_video && (*p_wmp_video) && (*p_wmp_video)->video)
	{
		free(((*p_wmp_video)->video));
		(*p_wmp_video)->video = NULL;
		free(*p_wmp_video);
		(*p_wmp_video) = NULL;
	}
	
	if(p_wmp_video && (*p_wmp_video))
	{
		free(*p_wmp_video);
		(*p_wmp_video) = NULL;
	}
}


/* Parser wmp_video_t */
wmp_video_t *parser_wmp_video(const char *package,uint32_t pack_len)
{
	uint32_t index = 0;
	WMP_VideoLenCheck(index,14,pack_len)
	
    wmp_video_t *p_wmp_video = create_wmp_video(0);
	
    p_wmp_video->attr = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_video->attr);

    p_wmp_video->result = *(uint8_t *)(package+index);
    index+=sizeof(p_wmp_video->result);

    p_wmp_video->src = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_video->src);

	p_wmp_video->dst = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_video->dst);

	p_wmp_video->video_len = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_video->video_len);

	WMP_VideoLenCheck(index,p_wmp_video->video_len,pack_len)
	memcpy(p_wmp_video->video,package+index,p_wmp_video->video_len);
	index+=p_wmp_video->video_len;
	
	return p_wmp_video;
}

/* Package wmp_video_t. */
uint32_t package_wmp_video(char *package,const wmp_video_t *p_wmp_video)
{
	uint32_t index = 0;
	
	*(uint16_t *)(package+index) = htons(p_wmp_video->attr);
	index+=sizeof(p_wmp_video->attr);
	*(uint32_t *)(package+index) = htonl(p_wmp_video->src);
	index+=sizeof(p_wmp_video->src);
	*(uint32_t *)(package+index) = htonl(p_wmp_video->dst);
	index+=sizeof(p_wmp_video->dst);
	*(uint32_t *)(package+index) = htonl(p_wmp_video->video_len);
	index+=sizeof(p_wmp_video->video_len);
	memcpy(package+index,p_wmp_video->video,p_wmp_video->video_len);
	index+=p_wmp_video->video_len;
	
	return index;
}

/* Set wmp_video_t video data length. */
void set_wmp_video_len(wmp_video_t *p_wmp_video,uint32_t video_len)
{
	if(!p_wmp_video || !video_len)
		return ;

	if(p_wmp_video->video)
		free(p_wmp_video->video);

	p_wmp_video->video = (uint8_t *)malloc(video_len);
	memset(p_wmp_video->video,0,video_len);
	p_wmp_video->video_len = video_len;
}

/* Print wmp_video_t. */
void print_wmp_video(const wmp_video_t *p_wmp_video)
{
    if(!p_wmp_video)
    {
#ifdef WMP_DEBUG
        printf("wmp_video_t is null.\n");
#endif
        return ;
    }
    printf("********************************wm_sound_start********************************\n");
    printf("attr:%d;result:%d;src:%d;dst:%d;video_len:%d;",p_wmp_video->attr,p_wmp_video->result,\
           p_wmp_video->src,p_wmp_video->dst,p_wmp_video->video_len);
    printf("video data:\n");
    for(uint32_t i=0;i<p_wmp_video->video_len;i++)
        printf("%02x ",p_wmp_video->video[i]);
    printf("\n");
    printf("*********************************wm_sound_end*********************************\n");
}

/* Copy a new wmp_video_t instance. */
wmp_video_t *copy_wmp_video(const wmp_video_t *p_wmp_video)
{
    wmp_video_t *c_wmp_video = create_wmp_video(p_wmp_video->video_len);

    c_wmp_video->attr = p_wmp_video->attr;
    c_wmp_video->result = p_wmp_video->result;
    c_wmp_video->src = p_wmp_video->src;
    c_wmp_video->dst = p_wmp_video->dst;
    memcpy(c_wmp_video->video,p_wmp_video->video,p_wmp_video->video_len);

    return c_wmp_video;
}

