/* ************************************************************************
 *       Filename:  wmp_sound.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz,chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_SOUND_H_
#define WMP_SOUND_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* *********************************************************************************************
 * Walking Message protocol sound.
 * @attr			Walking Message sound attribute.
 * @result			Walking Message sound result.
 * @src				Walking Message sound source id.
 * @dst				Walking Message sound destination id.
 * @sound_len		Walking Message sound data length.
 * @sound			Walking Message sound data.
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


WMPSHARED_EXPORT extern wmp_sound_t *allocate_wmp_sound(uint32_t sound_len);

WMPSHARED_EXPORT extern void deallocate_wmp_sound(wmp_sound_t **p_wmp_sound);

WMPSHARED_EXPORT extern wmp_sound_t *parser_wmp_sound(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_sound(char *package,const wmp_sound_t *p_wmp_sound);

WMPSHARED_EXPORT extern void set_wmp_sound_len(wmp_sound_t *p_wmp_sound,uint32_t msg_len);

WMPSHARED_EXPORT extern wmp_sound_t *copy_wmp_sound(wmp_sound_t *p_wmp_sound);


#ifdef __cplusplus
}
#endif

#endif
