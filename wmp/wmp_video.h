/* ************************************************************************
 *       Filename:  wmp_video.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_VIDEO_H_
#define WMP_VIDEO_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif



/* *********************************************************************************************
 * wmp_video_t structure.
 * @attr			wmp_video_t attribute.
 * @result			wmp_video_t result.
 * @src				wmp_video_t source id.
 * @dst				wmp_video_t destination id.
 * @video_len		wmp_video_t video length.
 * @data			wmp_video_t video data.
 *
 * **********************************************************************************************/
typedef struct
{
    uint8_t attr;
    uint8_t result;
	uint32_t src;
	uint32_t dst;
	uint32_t video_len;
	uint8_t *video;
}wmp_video_t;

#define WMP_VIDEO_LENGTH									sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint8_t)

#define WMP_VIDEO_PTG										1 
#define WMP_VIDEO_PTP										2
#define WMP_VIDEO_PTT										3
#define WMP_VIDEO_PTTS										4


#define WMP_VideoAttr(p_wmp_video) 							(p_wmp_video->attr)
#define WMP_VideoResult(p_wmp_video)                        (p_wmp_video->result)
#define WMP_VideoSrc(p_wmp_video) 							(p_wmp_video->src)
#define WMP_VideoDst(p_wmp_video) 							(p_wmp_video->dst)
#define WMP_VideoLen(p_wmp_video) 							(p_wmp_video->video_len)
#define WMP_Video(p_wmp_video) 								(p_wmp_video->video)


#define WMP_VideoSetAttr(p_wmp_video,a)                     (p_wmp_video->attr = a)
#define WMP_VideoSetResult(p_wmp_video,r)                   (p_wmp_video->result = r)
#define WMP_VideoSetSrc(p_wmp_video,id) 					(p_wmp_video->src = id)
#define WMP_VideoSetDst(p_wmp_video,id) 					(p_wmp_video->dst = id)


/* ***********************************************************************************
 * Create wmp_video_t instance.
 *
 * @param:	video_len			wmp_video_t video data length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_video_t *create_wmp_video(uint32_t video_len);

/* ***********************************************************************************
 * Delete wmp_video_t instance.
 *
 * @param:	p_wmp_video			The pointer of wmp_video_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_video(wmp_video_t **p_wmp_video);

/* ***********************************************************************************
 * Parser wmp_video_t.
 *
 * @param:	package				protocol package buffer.
 * @param:	pack_len			protocol package buffer length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_video_t *parser_wmp_video(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_video_t.
 *
 * @param:	package				protocol package buffer.
 * @param:	p_wmp_video			wmp_video_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_video(char *package,const wmp_video_t *p_wmp_video);

/* ***********************************************************************************
 * Set wmp_video_t video data length.
 *
 * @param:	p_wmp_video			wmp_video_t pointer.
 * @param:	video_len			protocol package buffer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_video_len(wmp_video_t *p_wmp_video,uint32_t video_len);

/* ***********************************************************************************
 * Print wmp_video_t.
 *
 * @param:	p_wmp_video			wmp_video_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_video(const wmp_video_t *p_wmp_video);

/* ***********************************************************************************
 * Copy a new wmp_video_t instance.
 *
 * @param:	p_wmp_video			wmp_video_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_video_t *copy_wmp_video(const wmp_video_t *p_wmp_video);

#ifdef __cplusplus
}
#endif

#endif
