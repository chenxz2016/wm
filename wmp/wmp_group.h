/* ************************************************************************
 *       Filename:  wmp_group.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_GROUP_H_
#define WMP_GROUP_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif


/* *********************************************************************************************
 * Walking Message protocol group.
 * @attr			Walking Message group property attribute.
 * @data_len		Walking Message group property data length.
 * @data			Walking Message group property data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t id;
	uint8_t data_len;
	char data[256];
}wmp_group_property_t;


/* *********************************************************************************************
 * Walking Message protocol group create.
 * @attr			Walking Message group create attribute.
 * @group_id		Walking Message group create group id.
 * @result			Walking Message group create group result.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
}wmp_group_cet_t;

/* Create wmp_group_cet_t structure. */
WMPSHARED_EXPORT extern wmp_group_cet_t *allocate_wmp_group_cet();

/* Delete wmp_group_cet_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_cet(wmp_group_cet_t **p_wmp_group_cet);

/* Copy wmp_group_cet_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_cet_t *copy_wmp_group_cet(wmp_group_cet_t *p_wmp_group_cet);


/* *********************************************************************************************
 * Walking Message protocol group dissolve.
 * @attr			Walking Message group dissolve attribute.
 * @group_id		Walking Message group dissolve group id.
 * @result			Walking Message group dissolve group result.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
}wmp_group_dsv_t;

/* Create wmp_group_dsv_t structure. */
WMPSHARED_EXPORT extern wmp_group_dsv_t *allocate_wmp_group_dsv();

/* Delete wmp_group_dsv_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_dsv(wmp_group_dsv_t **p_wmp_group_dsv);

/* Copy wmp_group_dsv_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_dsv_t *copy_wmp_group_dsv(wmp_group_dsv_t *p_wmp_group_dsv);


/* *********************************************************************************************
 * Walking Message protocol group join.
 * @attr			Walking Message group join group attribute.
 * @group_id		Walking Message group join group id.
 * @result			Walking Message group join group result.
 * @msg_len			Walking Message group join group message length.
 * @msg				Walking Message group join group message.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
	uint8_t msg_len;
	char msg[256];
}wmp_group_jon_t;

/* Create wmp_group_jon_t structure. */
WMPSHARED_EXPORT extern wmp_group_jon_t *allocate_wmp_group_jon();

/* Delete wmp_group_jon_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_jon(wmp_group_jon_t **p_wmp_group_jon);

/* Copy wmp_group_jon_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_jon_t *copy_wmp_group_jon(wmp_group_jon_t *p_wmp_group_jon);


/* *********************************************************************************************
 * Walking Message protocol group exit.
 * @attr			Walking Message group exit group attribute.
 * @group_id		Walking Message group exit group id.
 * @result			Walking Message group exit group result.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
}wmp_group_ext_t;

/* Create wmp_group_ext_t structure. */
WMPSHARED_EXPORT extern wmp_group_ext_t *allocate_wmp_group_ext();

/* Delete wmp_group_ext_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_ext(wmp_group_ext_t **p_wmp_group_ext);

/* Copy wmp_group_ext_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_ext_t *copy_wmp_group_ext(wmp_group_ext_t *p_wmp_group_ext);


/* *********************************************************************************************
 * Walking Message protocol group set property.
 * @attr			Walking Message group set property attribute.
 * @properties		Walking Message group property.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t property_num;
	wmp_group_property_t *properties;
}wmp_group_set_property_t;

/* *********************************************************************************************
 * Walking Message protocol group set.
 * @attr			Walking Message group set attribute.
 * @group_id		Walking Message group id.
 * @result			Walking Message group set result.
 * @property		Walking Message group property.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
	wmp_group_set_property_t property;
}wmp_group_set_t;

/* Create wmp_group_set_t structure. */
WMPSHARED_EXPORT extern wmp_group_set_t *allocate_wmp_group_set(uint16_t num);

/* Delete wmp_group_set_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_set(wmp_group_set_t **p_wmp_group_set);

/* Set wmp_group_set_t property numbers. */
WMPSHARED_EXPORT extern void set_wmp_group_property_num(wmp_group_set_t *p_wmp_group_set,uint16_t num);

/* Copy wmp_group_set_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_set_t *copy_wmp_group_set(wmp_group_set_t *p_wmp_group_set);


/* *********************************************************************************************
 * Walking Message protocol group message.
 * @attr			Walking Message group message attribute.
 * @group_id		Walking Message group message group id.
 * @result			Walking Message group message result.
 * @msg_len			Walking Message group message length.
 * @msg				Walking Message group message.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
	uint16_t msg_len;
	char *msg;
}wmp_group_msg_t;

/* Create wmp_group_msg_t structure. */
WMPSHARED_EXPORT extern wmp_group_msg_t *allocate_wmp_group_msg(uint16_t msg_len);

/* Delete wmp_group_msg_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_msg(wmp_group_msg_t **p_wmp_group_msg);

/* Set wmp_group_msg_t length. */
WMPSHARED_EXPORT extern void set_wmp_group_msg_len(wmp_group_msg_t *p_wmp_group_msg,uint16_t msg_len);

/* Copy wmp_group_msg_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_msg_t *copy_wmp_group_msg(wmp_group_msg_t *p_wmp_group_msg);


/* *********************************************************************************************
 * Walking Message protocol group file.
 * @attr			Walking Message group file attribute.
 * @group_id		Walking Message group file block.
 * @sequence		Walking Message group file current sequence.
 * @filename_len	Walking Message group file filename length.
 * @filename		Walking Message group file filename.
 * @file_len		Walking Message group file file length.
 * @file			Walking Message group file file data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t block;
	uint32_t sequence;
	uint8_t filename_len;
	char filename[256];
	uint16_t file_len;
	char *file;
}wmp_group_fle_t;

/* Create wmp_group_fle_t structure. */
WMPSHARED_EXPORT extern wmp_group_fle_t *allocate_wmp_group_fle(uint16_t file_len);

/* Delete wmp_group_fle_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_fle(wmp_group_fle_t **p_wmp_group_fle);

/* Set wmp_group_fle_t structure. */
WMPSHARED_EXPORT extern void set_wmp_group_fle_len(wmp_group_fle_t *p_wmp_group_fle,uint16_t file_len);

/* Copy wmp_group_fle_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_fle_t *copy_wmp_group_fle(wmp_group_fle_t *p_wmp_group_fle);


/* *********************************************************************************************
 * Walking Message protocol group notice.
 * @attr			Walking Message group notice attribute.
 * @notice_len		Walking Message group notice length.
 * @notice			Walking Message group notice.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
    uint32_t group_id;
	uint16_t notice_len;
	char *notice;
}wmp_group_ntc_t;

/* Create wmp_group_ntc_t structure. */
WMPSHARED_EXPORT extern wmp_group_ntc_t *allocate_wmp_group_ntc(uint16_t notice_len);

/* Delete wmp_group_ntc_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_ntc(wmp_group_ntc_t **p_wmp_group_ntc);

/* Set wmp_group_ntc_t notice length. */
WMPSHARED_EXPORT extern void set_wmp_group_ntc_len(wmp_group_ntc_t *p_wmp_group_ntc,uint16_t notice_len);

/* Copy wmp_group_ntc_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_ntc_t *copy_wmp_group_ntc(wmp_group_ntc_t *p_wmp_group_ntc);


/* *********************************************************************************************
 * Walking Message protocol group invite.
 * @attr			Walking Message group invite attribute.
 * @group_id		Walking Message group invite group id.
 * @invite_id		Walking Message group invite id.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint32_t invite_id;
}wmp_group_ivt_t;

/* Create wmp_group_ivt_t structure. */
WMPSHARED_EXPORT extern wmp_group_ivt_t *allocate_wmp_group_ivt();

/* Delete wmp_group_ivt_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_ivt(wmp_group_ivt_t **p_wmp_group_ivt);

/* Copy wmp_group_ivt_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_ivt_t * copy_wmp_group_ivt(wmp_group_ivt_t *p_wmp_group_ivt);



/* *********************************************************************************************
 * Walking Message protocol group list.
 * @attr			Walking Message group list attribute.
 * @user_id         Walking Message group list user id.
 * @group_num       Walking Message group list number.
 * @group_list		Walking Message group list.
 *
 * **********************************************************************************************/
typedef struct
{
    uint8_t attr;
    uint32_t user_id;
    uint16_t group_num;
    uint32_t *group_list;
}wmp_group_list_t;


#define WMP_GROUP_LIST_REQ                  0x00
#define WMP_GROUP_LIST_RSP                  0x01

/* Create wmp_group_fetch_t structure. */
WMPSHARED_EXPORT extern wmp_group_list_t *allocate_wmp_group_list(uint16_t group_num);

/* Delete wmp_group_list_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_list(wmp_group_list_t **p_wmp_group_list);

/* Set wmp_group_list_t group number. */
WMPSHARED_EXPORT extern void set_wmp_group_list_num(wmp_group_list_t *p_wmp_group_list,uint16_t group_num);

/* Copy wmp_group_list_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_list_t * copy_wmp_group_list(const wmp_group_list_t *p_wmp_group_list);




/* *********************************************************************************************
 * Walking Message protocol group fetch.
 * @attr			Walking Message group fetch attribute.
 * @user_id         Walking Message group fetch group id.
 * @group_num       Walking Message group fetch property number.
 * @group_list		Walking Message group fetch property list.
 *
 * **********************************************************************************************/
typedef struct
{
    uint8_t attr;
    uint32_t group_id;
    uint16_t property_num;
    wmp_group_property_t *properties;
}wmp_group_fetch_t;


#define WMP_GROUP_FETCH_REQ                 0x00
#define WMP_GROUP_FETCH_RSP                 0x01

/* Create wmp_group_fetch_t structure. */
WMPSHARED_EXPORT extern wmp_group_fetch_t *allocate_wmp_group_fetch(uint16_t property_num);

/* Delete wmp_group_fetch_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_group_fetch(wmp_group_fetch_t **p_wmp_group_fetch);

/* Set wmp_group_fetch_t group number. */
WMPSHARED_EXPORT extern void set_wmp_group_fetch_num(wmp_group_fetch_t *p_wmp_group_fetch,uint16_t property_num);

/* Copy wmp_group_fetch_t a new instance. */
WMPSHARED_EXPORT extern wmp_group_fetch_t * copy_wmp_group_fetch(const wmp_group_fetch_t *p_wmp_group_fetch);



/* *********************************************************************************************
 * Walking Message protocol group.
 * @attr			Walking Message group attribute.
 * @src				Walking Message group source id.
 * @dst				Walking Message group destination id.
 * @id				Walking Message group parameter id.
 * @param			Walking Message group parameter.
 *
 * **********************************************************************************************/
typedef struct
{
	uint32_t src;
	uint32_t dst;
	uint16_t id;
    void *param;
}wmp_group_t;

#define WMP_GROUP_LENGTH									sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint8_t)

#define WMP_GROUP_CET_ID									0x0501
#define WMP_GROUP_DSV_ID									0x0502
#define WMP_GROUP_JON_ID									0x0503
#define WMP_GROUP_EXT_ID									0x0504
#define WMP_GROUP_SET_ID									0x0505
#define WMP_GROUP_MSG_ID									0x0506
#define WMP_GROUP_FLE_ID									0x0507
#define WMP_GROUP_NTC_ID									0x0508
#define WMP_GROUP_IVT_ID									0x0509
#define WMP_GROUP_LIST_ID									0x050a
#define WMP_GROUP_FETCH_ID									0x050b

#define WMP_GROUP_PARSER_SUCCESS							0
#define WMP_GROUP_PARSER_FAILED								-1

#define WMP_GroupSrc(p_wmp_group) 							(p_wmp_group->src)
#define WMP_GroupDst(p_wmp_group) 							(p_wmp_group->dst)
#define WMP_GroupID(p_wmp_group) 							(p_wmp_group->id)
#define WMP_GroupParam(p_wmp_group) 						(p_wmp_group->param)

#define WMP_GroupSetSrc(p_wmp_group,id) 					(p_wmp_group->src = id)
#define WMP_GroupSetDst(p_wmp_group,id) 					(p_wmp_group->dst = id)
#define WMP_GroupSetID(p_wmp_group,i) 						(p_wmp_group->id = i)

WMPSHARED_EXPORT extern wmp_group_t *allocate_wmp_group();

WMPSHARED_EXPORT extern void deallocate_wmp_group(wmp_group_t **p_wmp_group);

WMPSHARED_EXPORT extern wmp_group_t *parser_wmp_group(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_group(char *package,wmp_group_t *p_wmp_group);

WMPSHARED_EXPORT extern void print_wmp_group(const wmp_group_t *p_wmp_group);

WMPSHARED_EXPORT extern wmp_group_t *copy_wmp_group(const wmp_group_t *p_wmp_group);


#ifdef __cplusplus
}
#endif

#endif
