/* ************************************************************************
 *       Filename:  wm_beat_heart.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_BEAT_HEART_H_
#define WMP_BEAT_HEART_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif


/* *********************************************************************************************
 * wm_beat_heart_t structure.
 *
 * @attr                wm_beat_heart_t attr.
 * @user_id             wm_beat_heart_t user id.
 * @flag                wm_beat_heart_t flag.
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

/* ***********************************************************************************
 * Create a wmp_beat_heart_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_beat_heart_t *create_wmp_beat_heart();

/* ***********************************************************************************
 * Delete wmp_beat_heart_t instance.
 *
 * @param:	p_wmp_bh            The pointer of wmp_beat_heart_t.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_beat_heart(wmp_beat_heart_t **p_wmp_bh);

/* ***********************************************************************************
 * Parser package as wmp_beat_heart_t.
 *
 * @param:	package		package buffer.
 * @param:	pack_len	package length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_beat_heart_t *parser_wmp_beat_heart(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_beat_heart_t as package.
 *
 * @param:	package		package buffer.
 * @param:	p_wmp_bh	The pointer of wmp_beat_heart_t.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_beat_heart(char *package,const wmp_beat_heart_t *p_wmp_bh);

/* ***********************************************************************************
 * Print wmp_beat_heart_t.
 *
 * @param:	p_wmp_bh	The pointer of wmp_beat_heart_t.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_beat_heart(const wmp_beat_heart_t *p_wmp_bh);

/* ***********************************************************************************
 * Copy a new wmp_beat_heart_t instance.
 *
 * @param:	p_wmp_bh	The pointer of wmp_beat_heart_t.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_beat_heart_t *copy_wmp_beat_heart(wmp_beat_heart_t *p_wmp_bh);


#ifdef __cplusplus
}
#endif

#endif
