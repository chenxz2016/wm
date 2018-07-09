/* ************************************************************************
 *       Filename:  wmp_user.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_USER_H_
#define WMP_USER_H_

#include "wmp_cfg.h"


#ifdef __cplusplus
extern "C"
{
#endif


/* *********************************************************************************************
 * wmp_user_add_t structure.
 * @attr			wmp_user_add_t attribute.
 * @msg_len			wmp_user_add_t message length.
 * @msg				wmp_user_add_t message data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint8_t msg_len;
	char msg[256];
}wmp_user_add_t;


/* ***********************************************************************************
 * Create wmp_user_add_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_add_t *create_wmp_user_add();


/* ***********************************************************************************
 * Delete wmp_user_add_t instance.
 *
 * @param:	p_wmp_user_add		wmp_user_add_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_user_add(wmp_user_add_t **p_wmp_user_add);


/* ***********************************************************************************
 * Copy a new wmp_user_add_t instance.
 *
 * @param:	p_wmp_user_add		wmp_user_add_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_add_t *copy_wmp_user_add(const wmp_user_add_t *p_wmp_user_add);



/* *********************************************************************************************
 * wmp_user_del_t structure.
 *
 * @attr			wmp_user_del_t attribute.
 * @id              wmp_user_del_t id
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
    uint32_t id;
}wmp_user_del_t;


/* ***********************************************************************************
 * Create wmp_user_del_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_del_t *create_wmp_user_del();


/* ***********************************************************************************
 * Delete wmp_user_del_t instance.
 *
 * @param:	p_wmp_user_del		wmp_user_del_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_user_del(wmp_user_del_t **p_wmp_user_del);


/* ***********************************************************************************
 * Copy a new wmp_user_del_t instance.
 *
 * @param:	p_wmp_user_del		wmp_user_del_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_del_t *copy_wmp_user_del(const wmp_user_del_t *p_wmp_user_del);


/* *********************************************************************************************
 * wmp_user_msg_t structure.
 * @attr			wmp_user_msg_t attribute.
 * @msg_len			wmp_user_msg_t message length.
 * @msg				wmp_user_msg_t message data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint32_t msg_len;
	char *msg;
}wmp_user_msg_t;


/* ***********************************************************************************
 * Create wmp_user_msg_t instance.
 *
 * @param:	msg_len				wmp_user_msg_t message length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_msg_t *create_wmp_user_msg(uint32_t msg_len);


/* ***********************************************************************************
 * Delete wmp_user_msg_t instance.
 *
 * @param:	p_wmp_user_msg		The pointer of wmp_user_msg_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_user_msg(wmp_user_msg_t **p_wmp_user_msg);


/* ***********************************************************************************
 * Set wmp_user_msg_t message length.
 *
 * @param:	p_wmp_user_msg		wmp_user_msg_t pointer.
 * @param:	msg_len				wmp_user_msg_t message length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_user_msg_len(wmp_user_msg_t *p_user_msg,uint32_t msg_len);


/* ***********************************************************************************
 * Copy a new wmp_user_msg_t instance.
 *
 * @param:	p_wmp_user_msg		wmp_user_msg_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_msg_t *copy_wmp_user_msg(const wmp_user_msg_t *p_wmp_user_msg);



/* *********************************************************************************************
 * wmp_user_property_t structure.
 *
 * @id				wmp_user_property_t attribute.
 * @type			wmp_user_property_t type.
 * @len				wmp_user_property_t data length.
 * @data			wmp_user_property_t data.
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
 * wmp_user_set_t structure.
 * @attr				wmp_user_set_t attribute.
 * @property_num		wmp_user_set_t property numbers.
 * @property_list		wmp_user_set_t property list.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint16_t property_num;
	wmp_user_property_t *property_list;
}wmp_user_set_t;


/* ***********************************************************************************
 * Create wmp_user_set_t instance.
 *
 * @param:	property_num			wmp_user_set_t message length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_set_t *create_wmp_user_set(uint16_t property_num);


/* ***********************************************************************************
 * Delete wmp_user_set_t instance.
 *
 * @param:	p_wmp_user_set		wmp_user_set_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_user_set(wmp_user_set_t **p_wmp_user_set);


/* ***********************************************************************************
 * Set wmp_user_set_t property number.
 *
 * @param:	p_wmp_user_set		wmp_user_set_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_user_set_property_num(wmp_user_set_t *p_user_set,uint32_t property_num);


/* ***********************************************************************************
 * Copy wmp_user_set_t a new instance.
 *
 * @param:	p_wmp_user_set		wmp_user_set_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_set_t *copy_wmp_user_set(const wmp_user_set_t *p_wmp_user_set);



/* *********************************************************************************************
 * wmp_user_friend_t structure.
 *
 * @attr				wmp_user_friend_t attribute.
 * @team_num            wmp_user_friend_t team number.
 * @team_index          wmp_user_friend_t team index.
 * @team_name_len		wmp_user_friend_t team name length.
 * @team_name           wmp_user_friend_t team name.
 * @friend_num          wmp_user_friend_t friend number.
 * @friend_list         wmp_user_friend_t friend list.
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



/* ***********************************************************************************
 * Create wmp_user_friend_t instance.
 *
 * @retval:	p_wmp_user_friend				wmp_user_friend_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_friend_t *create_wmp_user_friend(uint16_t friend_num);


/* ***********************************************************************************
 * Delete wmp_user_friend_t instance.
 *
 * @param:	p_wmp_user				wmp_user_friend_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_user_friend(wmp_user_friend_t **p_wmp_user_friend);


/* ***********************************************************************************
 * Set wmp_user_friend_t friend numbers.
 *
 * @param:	p_wmp_user_friend				wmp_user_friend_t pointer.
 * @param:	friend_num						friend numbers.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_user_friend_num(wmp_user_friend_t *p_wmp_user_friend,uint16_t friend_num);


/* ***********************************************************************************
 * Copy a new wmp_user_friend_t instance.
 *
 * @param:	p_wmp_user_friend				wmp_user_friend_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_friend_t *copy_wmp_user_friend(const wmp_user_friend_t *p_wmp_user_friend);


/* *********************************************************************************************
 * wmp_user_find_t structure.
 *
 * @attr				wmp_user_find_t attribute.
 * @condition           wmp_user_find_t condition.
 * @user_id             wmp_user_find_t user_id.
 * @sex         		wmp_user_find_t sex.
 * @address             wmp_user_find_t address.
 * @job                 wmp_user_find_t job.
 * @label_len           wmp_user_find_t label_len.
 * @label               wmp_user_find_t label.
 * @age                 wmp_user_find_t age.
 * @ctn                 wmp_user_find_t ctn.
 * @brithday            wmp_user_find_t brithday.
 * @result_num          wmp_user_find_t result number.
 * @result_list         wmp_user_find_t result list.
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


/* ***********************************************************************************
 * Create wmp_user_find_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_find_t *create_wmp_user_find(uint32_t result_num);


/* ***********************************************************************************
 * Delete wmp_user_find_t.
 *
 * @param:  p_wmp_user_find
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_user_find(wmp_user_find_t **p_wmp_user_find);


/* ***********************************************************************************
 * Set wmp_user_find_t result list number.
 *
 * @param:  p_wmp_user_find         The pointer of wmp_user_find_t.
 * @param:  result_num              wmp_user_find_t result number.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_user_find(wmp_user_find_t *p_wmp_user_find,uint32_t result_num);


/* ***********************************************************************************
 * Copy a new wmp_user_fetch_t instance.
 *
 * @param:  p_wmp_user_find             pointer of instance need to copy.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_find_t *copy_wmp_user_find(const wmp_user_find_t *p_wmp_user_find);



/* *********************************************************************************************
 * wmp_user_fetch_property_t structure.
 * @type				wmp_user_fetch_property_t property type.
 * @length              wmp_user_fetch_property_t property length.
 * @data                wmp_user_fetch_property_t property data.
 *
 *
 * wmp_user_fetch_t structure.
 * @attr				wmp_user_fetch_t attribute.
 * @property_num        wmp_user_fetch_t property number.
 * @properties          wmp_user_fetch_t property list.
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


/* ***********************************************************************************
 * Create wmp_user_fetch_t instance.
 *
 * @param:  property_num            property number
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_fetch_t *create_wmp_user_fetch(uint16_t property_num);


/* ***********************************************************************************
 * Delete wmp_user_fetch_t instance.
 *
 * @param:	p_wmp_user_fetch            wmp_user_fetch_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_user_fetch(wmp_user_fetch_t **p_wmp_user_fetch);


/* ***********************************************************************************
 * Set wmp_user_fetch_t property number.
 *
 * @param:	p_wmp_user_fetch            wmp_user_fetch_t pointer.
 * @param:	property_num                wmp_user_fetch_t property number.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_user_fetch_property_num(wmp_user_fetch_t *p_wmp_user_fetch,uint16_t property_num);


/* ***********************************************************************************
 * Copy a new wmp_user_fetch_t instance.
 *
 * @param:	p_wmp_user_fetch            wmp_user_fetch_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_fetch_t *copy_wmp_user_fetch(const wmp_user_fetch_t *p_wmp_user_fetch);




/* *********************************************************************************************
 * wmp_user_t structure.
 *
 * @src					wmp_user_t source id.
 * @dst					wmp_user_t destination id.
 * @id					wmp_user_t parameter id.
 * @param				wmp_user_t user parameter.
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


/* ***********************************************************************************
 * Create wmp_user_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_t *create_wmp_user();

/* ***********************************************************************************
 * Delete wmp_user_t instance.
 *
 * @param:	p_wmp_user				wmp_user_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_user(wmp_user_t **p_wmp_user);

/* ***********************************************************************************
 * Parser wmp_user_t.
 *
 * @param:	package				protocol package buffer.
 * @param:	pack_len			protocol package buffer length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_t *parser_wmp_user(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_user_t.
 *
 * @param:	package				protocol package buffer.
 * @param:	p_wmp_user			protocol package buffer length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_user(char *package,const wmp_user_t *p_wmp_user);

/* ***********************************************************************************
 * Print wmp_user_t.
 *
 * @param:	p_wmp_user			wmp_user_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_user(const wmp_user_t *p_wmp_user);

/* ***********************************************************************************
 * Copy a new wmp_user_t instance.
 *
 * @param:	p_wmp_user			wmp_user_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_user_t *copy_wmp_user(const wmp_user_t *p_wmp_user);


#ifdef __cplusplus
}
#endif

#endif
