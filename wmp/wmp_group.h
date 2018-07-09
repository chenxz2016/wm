/* ************************************************************************
 *       Filename:  wmp_group.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_GROUP_H_
#define WMP_GROUP_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif


/* *********************************************************************************************
 * wmp_group_property_t structure.
 * @attr			wmp_group_property_t attribute.
 * @data_len		wmp_group_property_t data length.
 * @data			wmp_group_property_t property data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t id;
	uint8_t data_len;
    char data[255];
}wmp_group_property_t;


/* *********************************************************************************************
 * wmp_group_cet_t structure.
 * @attr			wmp_group_cet_t attribute.
 * @group_id		wmp_group_cet_t id.
 * @result			wmp_group_cet_t result.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
}wmp_group_cet_t;


/* ***********************************************************************************
 * Create wmp_group_cet_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_cet_t *create_wmp_group_cet();

/* ***********************************************************************************
 * Delete wmp_group_cet_t instance.
 *
 * @param:	p_wmp_group_cet		The pointer of wmp_group_cet_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_cet(wmp_group_cet_t **p_wmp_group_cet);

/* ***********************************************************************************
 * Copy a new wmp_group_cet_t instance.
 *
 * @param:	p_wmp_group_cet		wmp_group_cet_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_cet_t *copy_wmp_group_cet(const wmp_group_cet_t *p_wmp_group_cet);

/* *********************************************************************************************
 * wmp_group_dsv_t structure.
 * @attr			wmp_group_dsv_t attribute.
 * @group_id		wmp_group_dsv_t id.
 * @result			wmp_group_dsv_t result.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
}wmp_group_dsv_t;


/* ***********************************************************************************
 * Create wmp_group_dsv_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_dsv_t *create_wmp_group_dsv();

/* ***********************************************************************************
 * Delete wmp_group_dsv_t instance.
 *
 * @param:	p_wmp_group_dsv		The pointer of wmp_group_dsv_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_dsv(wmp_group_dsv_t **p_wmp_group_dsv);

/* ***********************************************************************************
 * Copy a new wmp_group_dsv_t instance.
 *
 * @param:	p_wmp_group_dsv		wmp_group_dsv_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_dsv_t *copy_wmp_group_dsv(const wmp_group_dsv_t *p_wmp_group_dsv);


/* *********************************************************************************************
 * wmp_group_jon_t structure.
 * @attr			wmp_group_jon_t attribute.
 * @group_id		wmp_group_jon_t id.
 * @result			wmp_group_jon_t result.
 * @msg_len			wmp_group_jon_t length.
 * @msg				wmp_group_jon_t message.
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


/* ***********************************************************************************
 * Create wmp_group_jon_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_jon_t *create_wmp_group_jon();

/* ***********************************************************************************
 * Delete wmp_group_jon_t instance.
 *
 * @param:	p_wmp_group_jon		wmp_group_jon_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_jon(wmp_group_jon_t **p_wmp_group_jon);

/* ***********************************************************************************
 * Copy a new wmp_group_jon_t instance.
 *
 * @param:	p_wmp_group_jon		wmp_group_jon_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_jon_t *copy_wmp_group_jon(const wmp_group_jon_t *p_wmp_group_jon);


/* *********************************************************************************************
 * wmp_group_ext_t structure.
 * @attr			wmp_group_ext_t attribute.
 * @group_id		wmp_group_ext_t id.
 * @result			wmp_group_ext_t result.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
}wmp_group_ext_t;

/* ***********************************************************************************
 * Create wmp_group_ext_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_ext_t *create_wmp_group_ext();

/* ***********************************************************************************
 * Delete wmp_group_ext_t instance.
 *
 * @param:	p_wmp_group_ext		wmp_group_ext_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_ext(wmp_group_ext_t **p_wmp_group_ext);

/* ***********************************************************************************
 * Copy a new wmp_group_set_t instance.
 *
 * @param:	p_wmp_group_set		wmp_group_set_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_ext_t *copy_wmp_group_ext(const wmp_group_ext_t *p_wmp_group_ext);


/* *********************************************************************************************
 * wmp_group_set_property_t structure.
 * @property_num                wmp_group_set_property_t property number.
 * @properties                  wmp_group_set_property_t property list.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t property_num;
	wmp_group_property_t *properties;
}wmp_group_set_property_t;

/* *********************************************************************************************
 * wmp_group_set_t structure.
 * @attr			wmp_group_set_t attribute.
 * @group_id		wmp_group_set_t id.
 * @result			wmp_group_set_t result.
 * @property		wmp_group_set_t property.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint8_t result;
	wmp_group_set_property_t property;
}wmp_group_set_t;

/* ***********************************************************************************
 * Create a new wmp_group_set_t instance.
 *
 * @param:	num					wmp_group_set_t property numbers.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_set_t *create_wmp_group_set(uint16_t num);

/* ***********************************************************************************
 * Delete wmp_group_set_t instance.
 *
 * @param:	p_wmp_group_set		wmp_group_set_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_set(wmp_group_set_t **p_wmp_group_set);

/* ***********************************************************************************
 * Set wmp_group_set_t property numbers.
 *
 * @param:	num					wmp_group_set_t property numbers.
 * @param:	p_wmp_group_set		wmp_group_set_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_group_property_num(wmp_group_set_t *p_wmp_group_set,uint16_t num);

/* ***********************************************************************************
 * Copy a new wmp_group_set_t instance.
 *
 * @param:	p_wmp_group_set		wmp_group_set_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_set_t *copy_wmp_group_set(const wmp_group_set_t *p_wmp_group_set);


/* *********************************************************************************************
 * wmp_group_msg_t structure.
 * @attr			wmp_group_msg_t attribute.
 * @group_id		wmp_group_msg_t id.
 * @result			wmp_group_msg_t result.
 * @msg_len			wmp_group_msg_t length.
 * @msg				wmp_group_msg_t message.
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

/* ***********************************************************************************
 * Create wmp_group_msg_t instance.
 *
 * @param:	msg_len				wmp_group_msg_t message length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_msg_t *create_wmp_group_msg(uint16_t msg_len);

/* ***********************************************************************************
 * Delete wmp_group_msg_t instance.
 *
 * @param:	p_wmp_group_msg		wmp_group_msg_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_msg(wmp_group_msg_t **p_wmp_group_msg);

/* ***********************************************************************************
 * Set wmp_group_msg_t property numbers.
 *
 * @param:	msg_len				wmp_group_msg_t message length.
 * @param:	p_wmp_group_msg		wmp_group_msg_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_group_msg_len(wmp_group_msg_t *p_wmp_group_msg,uint16_t msg_len);

/* ***********************************************************************************
 * Copy a new wmp_group_msg_t instance.
 *
 * @param:	p_wmp_group_msg		wmp_group_msg_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_msg_t *copy_wmp_group_msg(const wmp_group_msg_t *p_wmp_group_msg);


/* *********************************************************************************************
 * wmp_group_fle_t structure.
 * @attr			wmp_group_fle_t attribute.
 * @group_id		wmp_group_fle_t block.
 * @sequence		wmp_group_fle_t current sequence.
 * @filename_len	wmp_group_fle_t filename length.
 * @filename		wmp_group_fle_t filename.
 * @file_len		wmp_group_fle_t file length.
 * @file			wmp_group_fle_t file data.
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


/* ***********************************************************************************
 * Create wmp_group_fle_t instance.
 *
 * @param:	file_len			wmp_group_fle_t current file block length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_fle_t *create_wmp_group_fle(uint16_t file_len);

/* ***********************************************************************************
 * Delete wmp_group_msg_t.
 *
 * @param:	p_wmp_group_msg		wmp_group_msg_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_fle(wmp_group_fle_t **p_wmp_group_fle);

/* ***********************************************************************************
 * Set wmp_group_fle_t property numbers.
 *
 * @param:	file_len			wmp_group_fle_t current file block length.
 * @param:	p_wmp_group_fle		wmp_group_fle_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_group_fle_len(wmp_group_fle_t *p_wmp_group_fle,uint16_t file_len);

/* ***********************************************************************************
 * Copy a new wmp_group_fle_t instance.
 *
 * @param:	p_wmp_group_fle		wmp_group_fle_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_fle_t *copy_wmp_group_fle(const wmp_group_fle_t *p_wmp_group_fle);


/* *********************************************************************************************
 * wmp_group_ntc_t structure.
 * @attr			wmp_group_ntc_t attribute.
 * @group_id        wmp_group_ntc_t group id.
 * @notice_len		wmp_group_ntc_t notice length.
 * @notice			wmp_group_ntc_t notice.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
    uint32_t group_id;
	uint16_t notice_len;
	char *notice;
}wmp_group_ntc_t;


/* ***********************************************************************************
 * Create wmp_group_ntc_t instance.
 *
 * @param:	notice_len			wmp_group_ntc_t notice length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_ntc_t *create_wmp_group_ntc(uint16_t notice_len);

/* ***********************************************************************************
 * Delete wmp_group_ntc_t instance.
 *
 * @param:	p_wmp_group_ntc		wmp_group_ntc_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_ntc(wmp_group_ntc_t **p_wmp_group_ntc);

/* ***********************************************************************************
 * Set wmp_group_ntc_t property numbers.
 *
 * @param:	notice_len              wmp_group_ntc_t notice length.
 * @param:	p_wmp_group_ntc         wmp_group_ntc_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_group_ntc_len(wmp_group_ntc_t *p_wmp_group_ntc,uint16_t notice_len);

/* ***********************************************************************************
 * Copy a new wmp_group_ntc_t instance.
 *
 * @param:	p_wmp_group_ntc         wmp_group_ntc_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_ntc_t *copy_wmp_group_ntc(const wmp_group_ntc_t *p_wmp_group_ntc);


/* *********************************************************************************************
 * wmp_group_ivt_t structure.
 * @attr                            wmp_group_ivt_t attribute.
 * @group_id                        wmp_group_ivt_t group id.
 * @invite_id                       wmp_group_ivt_t invite id.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint32_t group_id;
	uint32_t invite_id;
}wmp_group_ivt_t;

/* ***********************************************************************************
 * Create wmp_group_ivt_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_ivt_t *create_wmp_group_ivt();

/* ***********************************************************************************
 * Delete wmp_group_ivt_t instance.
 *
 * @param:	p_wmp_group_ivt         wmp_group_ivt_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_ivt(wmp_group_ivt_t **p_wmp_group_ivt);

/* ***********************************************************************************
 * Copy a new wmp_group_ivt_t instance.
 *
 * @param:	p_wmp_group_ivt         wmp_group_ivt_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_ivt_t *copy_wmp_group_ivt(const wmp_group_ivt_t *p_wmp_group_ivt);



/* *********************************************************************************************
 * wmp_group_list_t structure.
 * @attr                            wmp_group_list_t attribute.
 * @user_id                         wmp_group_list_t user id.
 * @group_num                       wmp_group_list_t list number.
 * @group_list                      wmp_group_list_t list.
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

/* ***********************************************************************************
 * Create wmp_group_list_t instance.
 *
 * @param:	group_num               wmp_group_fetch_t group number.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_list_t *create_wmp_group_list(uint16_t group_num);

/* ***********************************************************************************
 * Delete wmp_group_list_t instance.
 *
 * @param:	wmp_group_list_t		wmp_group_list_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_list(wmp_group_list_t **p_wmp_group_list);

/* ***********************************************************************************
 * Set wmp_group_list_t group_list.
 *
 * @param:	wmp_group_list_t		wmp_group_list_t pointer.
 * @param:  group_num               wmp_group_list_t group number.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_group_list_num(wmp_group_list_t *p_wmp_group_list,uint16_t group_num);

/* ***********************************************************************************
 * Copy a new wmp_group_list_t instance.
 *
 * @param:	p_wmp_group_list		wmp_group_list_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_list_t * copy_wmp_group_list(const wmp_group_list_t *p_wmp_group_list);




/* *********************************************************************************************
 * wmp_group_fetch_t structure.
 * @attr                            wmp_group_fetch_t attribute.
 * @user_id                         wmp_group_fetch_t group id.
 * @group_num                       wmp_group_fetch_t property number.
 * @group_list                      wmp_group_fetch_t property list.
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

/* ***********************************************************************************
 * Create wmp_group_fetch_t instance.
 *
 * @param:	property_num    		property number of wmp_group_fetch_t.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_fetch_t *create_wmp_group_fetch(uint16_t property_num);

/* ***********************************************************************************
 * Delete wmp_group_fetch_t instance.
 *
 * @param:	wmp_group_fetch_t		wmp_group_fetch_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group_fetch(wmp_group_fetch_t **p_wmp_group_fetch);

/* ***********************************************************************************
 * Set wmp_group_fetch_t property number.
 *
 * @param:	wmp_group_fetch_t		wmp_group_fetch_t pointer.
 * @param:  property_num            property number.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_group_fetch_num(wmp_group_fetch_t *p_wmp_group_fetch,uint16_t property_num);

/* ***********************************************************************************
 * Copy a new wmp_group_fetch_t instance.
 *
 * @param:	p_wmp_group_fetch		wmp_group_fetch_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_fetch_t * copy_wmp_group_fetch(const wmp_group_fetch_t *p_wmp_group_fetch);



/* *********************************************************************************************
 * wmp_group_t structure.
 * @attr                            wmp_group_t attribute.
 * @src                             wmp_group_t source id.
 * @dst                             wmp_group_t destination id.
 * @id                              wmp_group_t parameter id.
 * @param                           wmp_group_t parameter.
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

/* ***********************************************************************************
 * Create a wmp_group_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_t *create_wmp_group();

/* ***********************************************************************************
 * Delete wmp_group_t instance.
 *
 * @param:	p_wmp_group             wmp_group_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_group(wmp_group_t **p_wmp_group);

/* ***********************************************************************************
 * Parser wmp_group_t.
 *
 * @param:	package                 protocol package.
 * @param:	pack_len                protocol package length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_t *parser_wmp_group(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_group_t.
 *
 * @param:	p_wmp_group             wmp_group_t pointer.
 * @param:	package                 protocol package.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_group(char *package,const wmp_group_t *p_wmp_group);

/* ***********************************************************************************
 * Print wmp_group_t.
 *
 * @param:	p_wmp_group             wmp_group_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_group(const wmp_group_t *p_wmp_group);

/* ***********************************************************************************
 * Copy a new wmp_group_t instance.
 *
 * @param:	p_wmp_group             wmp_group_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_group_t *copy_wmp_group(const wmp_group_t *p_wmp_group);


#ifdef __cplusplus
}
#endif

#endif
