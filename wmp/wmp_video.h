/* ************************************************************************
 *       Filename:  wmp_video.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_VIDEO_H_
#define WMP_VIDEO_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif



/* *********************************************************************************************
 * Walking Message protocol video.
 * @attr			Walking Message video attribute.
 * @result			Walking Message video result.
 * @src				Walking Message video source id.
 * @dst				Walking Message video destination id.
 * @video_len		Walking Message video length.
 * @data			Walking Message video data.
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

WMPSHARED_EXPORT extern wmp_video_t *allocate_wmp_video(uint32_t video_len);

WMPSHARED_EXPORT extern void deallocate_wmp_video(wmp_video_t **p_wmp_video);

WMPSHARED_EXPORT extern wmp_video_t *parser_wmp_video(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_video(char *package,const wmp_video_t *p_wmp_video);

WMPSHARED_EXPORT extern void set_wmp_video_len(wmp_video_t *p_wmp_video,uint32_t video_len);


#ifdef __cplusplus
}
#endif

#endif
