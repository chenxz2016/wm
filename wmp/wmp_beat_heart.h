/* ************************************************************************
 *       Filename:  wm_beat_heart.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_BEAT_HEART_H_
#define WMP_BEAT_HEART_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif


/* *********************************************************************************************
 * Walking Message protocol beat heart.
 * @attr			Walking Message beat heart attr.
 * @user_id			Walking Message beat heart user id.
 * @flag			Walking Message beat heart flag.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t user_id;
	uint8_t flag;
}wmp_beat_heart_t;

#define WMP_BEAT_HEART_LENGTH							sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint8_t)

#define WMP_BEAT_HEART_REQ								(0)
#define WMP_BEAT_HEART_RSP								(1)



#define WMP_BeatHeartCS(p_wmp_bh)						(p_wmp_bh->attr & 1)
#define WMP_BeatHeartUserID(p_wmp_bh) 					(p_wmp_bh->user_id)
#define WMP_BeatHeartFlag(p_wmp_bh) 					(p_wmp_bh->flag) 

#define WMP_BeatHeartSetCTS(p_wmp_bh) 					(p_wmp_bh->attr |= 1)
#define WMP_BeatHeartSetSTC(p_wmp_bh) 					(p_wmp_bh->attr &= ~( 1 << 1 ))
#define WMP_BeatHeartSetUserID(p_wmp_bh,id)             (p_wmp_bh->user_id = id)
#define WMP_BeatHeartSetFlag(p_wmp_bh,f)                (p_wmp_bh->flag = f)

WMPSHARED_EXPORT extern wmp_beat_heart_t *allocate_wmp_beat_heart();

WMPSHARED_EXPORT extern void deallocate_wmp_beat_heart(wmp_beat_heart_t **p_wmp_bh);

WMPSHARED_EXPORT extern wmp_beat_heart_t *parser_wmp_beat_heart(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_beat_heart(char *package,const wmp_beat_heart_t *p_wmp_bh);

WMPSHARED_EXPORT extern void print_wmp_beat_heart(const wmp_beat_heart_t *p_wmp_bh);


#ifdef __cplusplus
}
#endif

#endif
