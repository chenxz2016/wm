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

/* Copy wmp_user_add_t new instance. */
WMPSHARED_EXPORT extern wmp_user_add_t *copy_wmp_user_add(wmp_user_add_t *p_wmp_user_add);



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

/* Delete wmp_user_del_t structure. */
WMPSHARED_EXPORT extern wmp_user_del_t *copy_wmp_user_del(wmp_user_del_t *p_wmp_user_del);


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

/* Copy wmp_user_msg_t new instance. */
WMPSHARED_EXPORT extern wmp_user_msg_t *copy_wmp_user_msg(wmp_user_msg_t *p_wmp_user_msg);



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

/* Copy wmp_user_set_t new instance. */
WMPSHARED_EXPORT extern wmp_user_set_t *copy_wmp_user_set(wmp_user_set_t *p_wmp_user_set);



/* *********************************************************************************************
 * Walking Message protocol user property.
 * @attr				Walking Message user friend attribute.
 * @team_num            Walking Message user friend team number.
 * @team_index          Walking Message user friend team index.
 * @team_name_len		Walking Message user friend name length.
 * @team_name           Walking Message user friend name.
 * @friend_num          Walking Message user friend number.
 * @friend_list         Walking Message user friend list.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
    uint16_t team_num;
    uint16_t team_index;
	uint8_t team_name_len;
	uint8_t team_name[255];
	uint16_t friend_num;
	uint32_t *friend_list;
}wmp_user_friend_t;

#define WMP_USER_FRIEND_LIST_REQ            0x0101
#define WMP_USER_FRIEND_LIST_RSP            0x0102
#define WMP_USER_FRIEND_NUM_REQ             0x0201
#define WMP_USER_FRIEND_NUM_RSP             0x0202


/* Create wmp_user_friend_t structure. */
WMPSHARED_EXPORT extern wmp_user_friend_t *allocate_wmp_user_friend(uint16_t friend_num);

/* Delete wmp_user_set_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_user_friend(wmp_user_friend_t **p_wmp_user_friend);

/* Set wmp_user_set_t property number. */
WMPSHARED_EXPORT extern void set_wmp_user_friend_num(wmp_user_friend_t *p_wmp_user_friend,uint16_t friend_num);

/* Set wmp_user_set_t property number. */
WMPSHARED_EXPORT extern wmp_user_friend_t *copy_wmp_user_friend(wmp_user_friend_t *p_wmp_user_friend);


/* *********************************************************************************************
 * Walking Message protocol find other user information.
 * @attr				Walking Message user find attribute.
 * @condition           Walking Message user find condition.
 * @user_id             Walking Message user find user_id.
 * @sex         		Walking Message user find sex.
 * @address             Walking Message user find address.
 * @job                 Walking Message user find job.
 * @label_len           Walking Message user find label_len.
 * @label               Walking Message user find label.
 * @age                 Walking Message user find age.
 * @ctn                 Walking Message user find ctn.
 * @brithday            Walking Message user find brithday.
 * @result_num          Walking Message user find result number.
 * @result_list         Walking Message user find result list.
 *
 * **********************************************************************************************/
typedef struct
{
    uint16_t attr;
    uint16_t condition;
    uint32_t user_id;
    uint8_t sex;
    uint32_t address[2];
    uint8_t job;
    uint8_t label_len;
    uint8_t label[255];
    uint8_t age;
    uint8_t ctn;
    uint32_t brithday;
    uint32_t result_num;
    uint32_t *result_list;
}wmp_user_find_t;

#define WMP_USER_FIND_REQ                   1
#define WMP_USER_FIND_RSP                   2

#define WMP_USER_FIND_BY_ID                 1
#define WMP_USER_FIND_BY_SEX                2
#define WMP_USER_FIND_BY_ADDRESS            4
#define WMP_USER_FIND_BY_JOB                8
#define WMP_USER_FIND_BY_LABEL              16
#define WMP_USER_FIND_BY_AGE                32
#define WMP_USER_FIND_BY_CTN                64
#define WMP_USER_FIND_BY_BRITHDAY           128

/* Create wmp_user_fetch_t structure. */
WMPSHARED_EXPORT extern wmp_user_find_t *allocate_wmp_user_find(uint32_t result_num);

/* Delete wmp_user_fetch_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_user_find(wmp_user_find_t **p_wmp_user_find);

/* Set wmp_user_fetch_t result list number. */
WMPSHARED_EXPORT extern void set_wmp_user_find(wmp_user_find_t *p_wmp_user_find,uint32_t result_num);

/* Copy wmp_user_fetch_t a new instance. */
WMPSHARED_EXPORT extern wmp_user_find_t *copy_wmp_user_find(wmp_user_find_t *p_wmp_user_find);



/* *********************************************************************************************
 * Walking Message protocol fetch property structure.
 * @type				Walking Message user find property type.
 * @length              Walking Message user find property length.
 * @data                Walking Message user find property data.
 *
 *
 * Walking Message protocol fetch other user information.
 * @attr				Walking Message user find attribute.
 * @property_num        Walking Message user find property number.
 * @properties          Walking Message user find properties.
 *
 * **********************************************************************************************/
typedef struct
{
    uint8_t type;
    uint8_t length;
    uint8_t data[255];
}wmp_user_fetch_property_t;

typedef struct
{
    uint16_t attr;
    uint16_t property_num;
    wmp_user_fetch_property_t *properties;
}wmp_user_fetch_t;

/* Create wmp_user_fetch_t structure. */
WMPSHARED_EXPORT extern wmp_user_fetch_t *allocate_wmp_user_fetch(uint16_t property_num);

/* Delete wmp_user_fetch_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_user_fetch(wmp_user_fetch_t **p_wmp_user_fetch);

/* Set wmp_user_fetch_t properties number structure. */
WMPSHARED_EXPORT extern void set_wmp_user_fetch_property_num(wmp_user_fetch_t *p_wmp_user_fetch,uint16_t property_num);

/* Set wmp_user_fetch_t properties number structure. */
WMPSHARED_EXPORT extern wmp_user_fetch_t *copy_wmp_user_fetch(wmp_user_fetch_t *p_wmp_user_fetch);




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
    void *param;
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
#define WMP_USER_FRIEND_ID                                  0x0605
#define WMP_USER_FIND_ID                                    0x0606
#define WMP_USER_FETCH_ID                                   0x0607


#define WMP_UserSrc(p_wmp_user) 							(p_wmp_user->src)
#define WMP_UserDst(p_wmp_user) 							(p_wmp_user->dst)
#define WMP_UserID(p_wmp_user)                              (p_wmp_user->id)


#define WMP_UserSetSrc(p_wmp_user,id) 						(p_wmp_user->src = id)
#define WMP_UserSetDst(p_wmp_user,id) 						(p_wmp_user->dst = id)
#define WMP_UserSetID(p_wmp_user,i) 						(p_wmp_user->id = i)

#define WMP_UserSwapID(p_wmp_user,i) \
    uint32_t id = p_wmp_user->src;\
    p_wmp_user->src = p_wmp_user->dst;\
    p_wmp_user->dst = id;


WMPSHARED_EXPORT extern wmp_user_t *allocate_wmp_user();

WMPSHARED_EXPORT extern void deallocate_wmp_user(wmp_user_t **p_wmp_user);

WMPSHARED_EXPORT extern wmp_user_t *parser_wmp_user(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_user(char *package,const wmp_user_t *p_wmp_user);

WMPSHARED_EXPORT extern void print_wmp_user(const wmp_user_t *p_wmp_user);

WMPSHARED_EXPORT extern wmp_user_t *copy_wmp_user(const wmp_user_t *p_wmp_user);


#ifdef __cplusplus
}
#endif

#endif
