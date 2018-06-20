/* ************************************************************************
 *       Filename:  wmp_user.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_USER_H_
#define WMP_USER_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif


#ifdef __cplusplus
extern "C"
{
#endif


/* *********************************************************************************************
 * Walking Message protocol user add.
 * @attr			Walking Message user add attribute.
 * @msg_len			Walking Message user add message length.
 * @msg				Walking Message user add message data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint8_t msg_len;
	char msg[256];
}wmp_user_add_t;

/* Create wmp_user_add_t structure. */
WMPSHARED_EXPORT extern wmp_user_add_t *allocate_wmp_user_add();

/* Delete wmp_user_add_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_user_add(wmp_user_add_t **p_wmp_user_add);


/* *********************************************************************************************
 * Walking Message protocol user del.
 * @attr			Walking Message user del attribute.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
    uint32_t id;
}wmp_user_del_t;

/* Create wmp_user_del_t structure. */
WMPSHARED_EXPORT extern wmp_user_del_t *allocate_wmp_user_del();

/* Delete wmp_user_del_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_user_del(wmp_user_del_t **p_wmp_user_del);


/* *********************************************************************************************
 * Walking Message protocol user msg.
 * @attr			Walking Message user msg attribute.
 * @msg_len			Walking Message user msg message length.
 * @msg				Walking Message user msg message data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint32_t msg_len;
	char *msg;
}wmp_user_msg_t;

/* Create wmp_user_msg_t structure. */
WMPSHARED_EXPORT extern wmp_user_msg_t *allocate_wmp_user_msg(uint32_t msg_len);

/* Delete wmp_user_msg_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_user_msg(wmp_user_msg_t **p_wmp_user_msg);

/* Set wmp_user_msg_t message length. */
WMPSHARED_EXPORT extern void set_wmp_user_msg_len(wmp_user_msg_t *p_user_msg,uint32_t msg_len);



/* *********************************************************************************************
 * Walking Message protocol user property.
 * @id				Walking Message user property attribute.
 * @type			Walking Message user property type.
 * @len				Walking Message user property data length.
 * @data			Walking Message user property data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t id;
	uint16_t type;
	uint8_t len;
	char data[256];
}wmp_user_property_t;



/* *********************************************************************************************
 * Walking Message protocol user property.
 * @attr				Walking Message user property attribute.
 * @property_num		Walking Message user property numbers.
 * @property_list		Walking Message user property list.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint16_t property_num;
	wmp_user_property_t *property_list;
}wmp_user_set_t;

/* Create wmp_user_set_t structure. */
WMPSHARED_EXPORT extern wmp_user_set_t *allocate_wmp_user_set(uint16_t property_num);

/* Delete wmp_user_set_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_user_set(wmp_user_set_t **p_wmp_user_set);

/* Set wmp_user_set_t property number. */
WMPSHARED_EXPORT extern void set_wmp_user_set_property_num(wmp_user_set_t *p_user_set,uint32_t property_num);



/* *********************************************************************************************
 * Walking Message protocol user property.
 * @attr				Walking Message user property attribute.
 * @property_num		Walking Message user property numbers.
 * @property_list		Walking Message user property list.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint8_t team_name_len;
	uint8_t team_name[255];
	uint16_t friend_num;
	uint32_t *friend_list;
}wmp_user_friend_t;

/* Create wmp_user_friend_t structure. */
WMPSHARED_EXPORT extern wmp_user_friend_t *allocate_wmp_user_friend(uint16_t friend_num);

/* Delete wmp_user_set_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_user_friend(wmp_user_friend_t **p_wmp_user_friend);

/* Set wmp_user_set_t property number. */
WMPSHARED_EXPORT extern void set_wmp_user_friend_num(wmp_user_friend_t *p_wmp_user_friend,uint16_t friend_num);


/* *********************************************************************************************
 * Walking Message protocol user.
 * @attr				Walking Message user attribute.
 * @src					Walking Message user source id.
 * @dst					Walking Message user destination id.
 * @id					Walking Message user parameter id.
 * @param				Walking Message user parameter.
 *
 * **********************************************************************************************/
typedef struct
{
	uint32_t src;
	uint32_t dst;
	uint16_t id;
	uint8_t *param;
}wmp_user_t;

#define WMP_USER_MIN_LENGTH									sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint8_t)

#define WMP_USER_PTG										1 
#define WMP_USER_PTP										2
#define WMP_USER_PTT										3
#define WMP_USER_PTTS										4

#define WMP_USER_ADD_ID                                     0x0601
#define WMP_USER_DEL_ID                                     0x0602
#define WMP_USER_SET_ID                                     0x0603
#define WMP_USER_MSG_ID                                     0x0604


#define WMP_UserSrc(p_wmp_user) 							(p_wmp_user->src)
#define WMP_UserDst(p_wmp_user) 							(p_wmp_user->dst)
#define WMP_UserID(p_wmp_user)                              (p_wmp_user->id)


#define WMP_UserSetSrc(p_wmp_user,id) 						(p_wmp_user->src = id)
#define WMP_UserSetDst(p_wmp_user,id) 						(p_wmp_user->dst = id)
#define WMP_UserSetID(p_wmp_user,i) 						(p_wmp_user->id = i)

WMPSHARED_EXPORT extern wmp_user_t *allocate_wmp_user();

WMPSHARED_EXPORT extern void deallocate_wmp_user(wmp_user_t **p_wmp_user);

WMPSHARED_EXPORT extern wmp_user_t *parser_wmp_user(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_user(char *package,const wmp_user_t *p_wmp_user);

WMPSHARED_EXPORT extern void print_wmp_user(const wmp_user_t *p_wmp_user);


#ifdef __cplusplus
}
#endif

#endif
