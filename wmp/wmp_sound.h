/* ************************************************************************
 *       Filename:  wmp_sound.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz,chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_SOUND_H_
#define WMP_SOUND_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* *********************************************************************************************
 * wmp_sound_t structure.
 * @attr			wmp_sound_t attribute.
 * @result			wmp_sound_t result.
 * @src				wmp_sound_t source id.
 * @dst				wmp_sound_t destination id.
 * @sound_len		wmp_sound_t data length.
 * @sound			wmp_sound_t data.
 *
 * **********************************************************************************************/
typedef struct
{
    uint8_t attr;
    uint8_t result;
	uint32_t src;
	uint32_t dst;
	uint32_t sound_len;
	uint8_t *sound;
}wmp_sound_t;

#define WMP_SOUND_LENGTH								sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint8_t)

#define WMP_SOUND_PTG									1 
#define WMP_SOUND_PTP									2
#define WMP_SOUND_PTT									3
#define WMP_SOUND_PTTS									4

#define WMP_SoundAttr(p_wmp_sound) 						(p_wmp_sound->attr)
#define WMP_SoundResult(p_wmp_sound) 					(p_wmp_sound->result)
#define WMP_SoundSrc(p_wmp_sound) 						(p_wmp_sound->src)
#define WMP_SoundDst(p_wmp_sound) 						(p_wmp_sound->dst)
#define WMP_SoundLen(p_wmp_sound) 						(p_wmp_sound->sound_len)
#define WMP_Sound(p_wmp_sound) 							(p_wmp_sound->sound)

#define WMP_SoundSetAttr(p_wmp_sound,a)                 (p_wmp_msg->attr = a)
#define WMP_SoundSetResult(p_wmp_sound,r)               (p_wmp_msg->result = r)
#define WMP_SoundSetSrc(p_wmp_sound,id) 				(p_wmp_msg->src = id)
#define WMP_SoundSetDst(p_wmp_sound,id) 				(p_wmp_msg->dst = id)


/* ***********************************************************************************
 * Create wmp_sound_t instance.
 *
 * @param:	sound_len		wmp_sound_t sound data length.
 *
 * @retval:	p_wmp_sound		wmp_sound_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_sound_t *create_wmp_sound(uint32_t sound_len);

/* ***********************************************************************************
 * Delete wmp_sound_t.
 *
 * @param:	p_wmp_sound		The pointer of wmp_sound_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_sound(wmp_sound_t **p_wmp_sound);

/* ***********************************************************************************
 * Parser wmp_sound_t.
 *
 * @param:	package			package buffer.
 * @param:	pack_len		package buffer length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_sound_t *parser_wmp_sound(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_sound_t.
 *
 * @param:	package			package buffer.
 * @param:	p_wmp_sound		wmp_sound_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_sound(char *package,const wmp_sound_t *p_wmp_sound);

/* ***********************************************************************************
 * Set wmp_sound_t sound data length.
 *
 * @param:	p_wmp_sound		wmp_sound_t pointer.
 * @param:	pack_len		sound data length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_sound_len(wmp_sound_t *p_wmp_sound,uint32_t msg_len);

/* ***********************************************************************************
 * Print wmp_sound_t.
 *
 * @param:	p_wmp_sound		wmp_sound_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_sound(const wmp_sound_t *p_wmp_sound);

/* ***********************************************************************************
 * Copy a new wmp_sound_t instance.
 *
 * @param:	p_wmp_sound		wmp_sound_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_sound_t *copy_wmp_sound(const wmp_sound_t *p_wmp_sound);


#ifdef __cplusplus
}
#endif

#endif
