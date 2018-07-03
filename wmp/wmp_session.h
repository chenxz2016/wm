/* ************************************************************************
 *       Filename:  wmp_session.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_SESSION_H_
#define WMP_SESSION_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    uint8_t id;
    uint8_t data_len;
    uint8_t data[255];
}wmp_session_property_t;

/* **********************************************************************************************
 *	wm_session_cet_t structure.
 *
 *	@attr:				wm_session_cet_t attribute.
 *	@session_id:		wm_session_cet_t session id.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t session_id;
}wmp_session_cet_t;

/* Create wmp_session_cet_t structure. */
WMPSHARED_EXPORT extern wmp_session_cet_t *allocate_wmp_session_cet();

/* Delete wmp_session_cet_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_session_cet(wmp_session_cet_t **p_wmp_session_cet);

/* Copy wmp_session_cet_t structure. */
WMPSHARED_EXPORT extern wmp_session_cet_t *copy_wmp_session_cet(wmp_session_cet_t *p_wmp_session_cet);


/* **********************************************************************************************
 *	wm_session_dsv_t structure.
 *
 *	@attr:				wm_session_dsv_t attribute.
 *	@session_id:		wm_session_dsv_t session id.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t session_id;
}wmp_session_dsv_t;

/* Create wmp_session_dsv_t structure. */
WMPSHARED_EXPORT extern wmp_session_dsv_t *allocate_wmp_session_dsv();

/* Delete wmp_session_dsv_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_session_dsv(wmp_session_dsv_t **p_wmp_session_dsv);

/* Copy wmp_session_dsv_t a new instance. */
WMPSHARED_EXPORT extern wmp_session_dsv_t *copy_wmp_session_dsv(wmp_session_dsv_t *p_wmp_session_dsv);


/* **********************************************************************************************
 *	wm_session_ext_t structure.
 *
 *	@attr:				wm_session_ext_t attribute.
 *	@session_id:		wm_session_ext_t session id.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t session_id;
}wmp_session_ext_t;

/* Create wmp_session_ext_t structure. */
WMPSHARED_EXPORT extern wmp_session_ext_t *allocate_wmp_session_ext();

/* Delete wmp_session_ext_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_session_ext(wmp_session_ext_t **p_wmp_session_ext);

/* Copy wmp_session_ext_t a new instance. */
WMPSHARED_EXPORT extern wmp_session_ext_t *copy_wmp_session_ext(wmp_session_ext_t *p_wmp_session_ext);


/* **********************************************************************************************
 *	wm_session_msg_t structure.
 *
 *	@attr:				wm_session_msg_t attribute.
 *	@session_id:		wm_session_msg_t session id.
 *	@msg_len:			wm_session_msg_t message length.
 *	@msg:				wm_session_msg_t message.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t session_id;
	uint16_t msg_len;
	char *msg;
}wmp_session_msg_t;

/* Create wmp_session_msg_t structure. */
WMPSHARED_EXPORT extern wmp_session_msg_t *allocate_wmp_session_msg(uint16_t msg_len);

/* Delete wmp_session_msg_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_session_msg(wmp_session_msg_t **p_wmp_session_msg);

/* Set wmp_session_msg_t length. */
WMPSHARED_EXPORT extern void set_wmp_session_msg_len(wmp_session_msg_t *p_wmp_session_msg,uint16_t msg_len);

/* Copy wmp_session_msg_t a new instance. */
WMPSHARED_EXPORT extern wmp_session_msg_t *copy_wmp_session_msg(wmp_session_msg_t *p_wmp_session_msg);


/* **********************************************************************************************
 *	wm_session_fle_t structure.
 *
 *	@attr:				wm_session_fle_t attribute.
 *	@session_id:		wm_session_fle_t session id.
 *	@block:				wm_session_fle_t file total block.
 *	@sequence:			wm_session_fle_t file current sequence.
 *	@filename_len:		wm_session_fle_t filename length.
 *	@filename:			wm_session_fle_t filename.
 *	@file_len:			wm_session_fle_t file data length.
 *	@file:				wm_session_fle_t file data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t session_id;
	uint32_t block;
	uint32_t sequence;
	uint8_t filename_len;
	char filename[256];
	uint16_t file_len;
	char *file;
}wmp_session_fle_t;

/* Create wmp_session_fle_t structure. */
WMPSHARED_EXPORT extern wmp_session_fle_t *allocate_wmp_session_fle(uint16_t file_len);

/* Delete wmp_session_fle_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_session_fle(wmp_session_fle_t **p_wmp_session_fle);

/* Set wmp_session_fle_t structure. */
WMPSHARED_EXPORT extern void set_wmp_session_fle_len(wmp_session_fle_t *p_wmp_session_fle,uint16_t file_len);

/* Copy wmp_session_fle_t a new instance. */
WMPSHARED_EXPORT extern wmp_session_fle_t *copy_wmp_session_fle(wmp_session_fle_t *p_wmp_session_fle);



/* **********************************************************************************************
 *	wm_session_ivt_t structure.
 *
 *	@attr:				wm_session_ivt_t attribute.
 *	@session_id:		wm_session_ivt_t session id.
 *	@invite_id:			wm_session_ivt_t invite id.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t session_id;
	uint32_t invite_id;
}wmp_session_ivt_t;

/* Create wmp_session_ivt_t structure. */
WMPSHARED_EXPORT extern wmp_session_ivt_t *allocate_wmp_session_ivt();

/* Delete wmp_session_ivt_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_session_ivt(wmp_session_ivt_t **p_wmp_session_ivt);

/* Copy wmp_session_ivt_t a new instance. */
WMPSHARED_EXPORT extern wmp_session_ivt_t *copy_wmp_session_ivt(wmp_session_ivt_t *p_wmp_session_ivt);


/* *********************************************************************************************
 * Walking Message protocol session list.
 * @attr			Walking Message session list attribute.
 * @user_id         Walking Message session list user id.
 * @session_num     Walking Message session list number.
 * @session_list    Walking Message session list.
 *
 * **********************************************************************************************/
typedef struct
{
    uint8_t attr;
    uint32_t user_id;
    uint16_t session_num;
    uint32_t *session_list;
}wmp_session_list_t;


#define WMP_SESSION_LIST_REQ                    0x00
#define WMP_SESSION_LIST_RSP                    0x01

/* Create wmp_session_list_t structure. */
WMPSHARED_EXPORT extern wmp_session_list_t *allocate_wmp_session_list(uint16_t session_num);

/* Delete wmp_session_list_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_session_list(wmp_session_list_t **p_wmp_session_list);

/* Set wmp_session_list_t group number. */
WMPSHARED_EXPORT extern void set_wmp_session_list_num(wmp_session_list_t *p_wmp_session_list,uint16_t session_num);

/* Copy wmp_session_list_t a new instance. */
WMPSHARED_EXPORT extern wmp_session_list_t * copy_wmp_session_list(const wmp_session_list_t *p_wmp_session_list);


/* *********************************************************************************************
 * Walking Message protocol session fetch.
 * @attr			Walking Message session fetch attribute.
 * @session_id      Walking Message session fetch group id.
 * @property_num    Walking Message session fetch property number.
 * @properties		Walking Message session fetch property list.
 *
 * **********************************************************************************************/
typedef struct
{
    uint8_t attr;
    uint32_t session_id;
    uint16_t property_num;
    wmp_session_property_t *properties;
}wmp_session_fetch_t;


#define WMP_SESSION_FETCH_REQ                   0x00
#define WMP_SESSION_FETCH_RSP                   0x01

/* Create wmp_session_fetch_t structure. */
WMPSHARED_EXPORT extern wmp_session_fetch_t *allocate_wmp_session_fetch(uint16_t property_num);

/* Delete wmp_session_fetch_t structure. */
WMPSHARED_EXPORT extern void deallocate_wmp_session_fetch(wmp_session_fetch_t **p_wmp_session_fetch);

/* Set wmp_session_fetch_t group number. */
WMPSHARED_EXPORT extern void set_wmp_session_fetch_num(wmp_session_fetch_t *p_wmp_group_fetch,uint16_t property_num);

/* Copy wmp_session_fetch_t a new instance. */
WMPSHARED_EXPORT extern wmp_session_fetch_t * copy_wmp_group_fetch(const wmp_session_fetch_t *p_wmp_session_fetch);



/* **********************************************************************************************
 *	wm_session_t structure.
 *
 *	@attr:				wm_session_t attribute.
 *	@src:				wm_session_t source id.
 *	@dst:				wm_session_t destination id.
 *	@id:				wm_session_t parameter id.
 *	@param:				wm_session_t parameter.
 *
 * **********************************************************************************************/
typedef struct
{
	uint32_t src;
	uint32_t dst;
	uint32_t id;
    void *param;
}wmp_session_t;

#define WMP_SESSION_LENGTH									sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint8_t)

#define WMP_SESSION_CET_ID									0x0501
#define WMP_SESSION_DSV_ID									0x0502
#define WMP_SESSION_EXT_ID									0x0503
#define WMP_SESSION_MSG_ID									0x0504
#define WMP_SESSION_FLE_ID									0x0505
#define WMP_SESSION_IVT_ID									0x0506
#define WMP_SESSION_LIST_ID									0x0507
#define WMP_SESSION_FETCH_ID                                0x0508

#define WMP_PARSER_SESSION_FAILED							(-1)
#define WMP_PARSER_SESSION_SUCCESS							(0)

#define WMP_SessionSrc(p_wmp_session) 						(p_wmp_session->src)
#define WMP_SessionDst(p_wmp_session) 						(p_wmp_session->dst)
#define WMP_SessionID(p_wmp_session)                        (p_wmp_session->id)
#define WMP_Session(p_wmp_session) 							(p_wmp_session->param)

#define WMP_SessionSetSrc(p_wmp_session,id) 				(p_wmp_session->src = id)
#define WMP_SessionSetDst(p_wmp_session,id) 				(p_wmp_session->dst = id)
#define WMP_SessionSetID(p_wmp_session,i) 					(p_wmp_session->id = i)

WMPSHARED_EXPORT extern wmp_session_t *allocate_wmp_session();

WMPSHARED_EXPORT extern void deallocate_wmp_session(wmp_session_t **p_wmp_session);

WMPSHARED_EXPORT extern wmp_session_t *parser_wmp_session(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_session(char *package,const wmp_session_t *p_wmp_session);

WMPSHARED_EXPORT extern void print_wmp_session(const wmp_session_t *p_wmp_session);

WMPSHARED_EXPORT extern wmp_session_t *copy_wmp_session(const wmp_session_t *p_wmp_session);


#ifdef __cplusplus
}
#endif

#endif
