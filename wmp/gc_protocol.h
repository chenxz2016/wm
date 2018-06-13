/* ************************************************************************
 *       Filename:  gc_protocol.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef GC_PROTOCOL_H_
#define GC_PROTOCOL_H_

#ifdef __cplusplus_
extern "C"
{
#endif

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

/* int8_t type */
#define GCP_TYPE_INT8_ID							1
/* uint8_t type */
#define GCP_TYPE_UINT8_ID							2
/* int16_t type */
#define GCP_TYPE_INT16_ID							3
/* uint16_t type */
#define GCP_TYPE_UINT16_ID							4
/* int32_t type */
#define GCP_TYPE_INT32_ID							5
/* uint32_t type */
#define GCP_TYPE_UINT32_ID							6
/* int64_t type */
#define GCP_TYPE_INT64_ID							7
/* uint64_t type */
#define GCP_TYPE_UINT64_ID							8
/* byte array type */
#define GCP_TYPE_BYTEARRAY_ID						9
/* c string type */
#define GCP_TYPE_STRING_ID							10
/* bcd type */
#define GCP_TYPE_BCD_ID								11
/* self custom type */
#define GCP_TYPE_CUSTOM_ID							12
#define GCP_TYPE_CHAR_ID							13
#define GCP_TYPE_FLOAT_ID							14
#define GCP_TYPE_DOUBLE_ID							15



/* *********************************************************************************************
 *	group-center protocol parameters definition.
 *
 *	Character means:
 *	@id:		group-center protocol paramsters id char.
 *	@type:		group-center protocol paramsters type.
 *	@length:	group-center protocol paramsters length.
 *	@target:	group-center protocol paramsters target. 
 *				GCP_CTG means this is send to group by center.
 *				GCP_GTC means this is send to center by group.
 *	@data:		group-center protocol paramsters data.
 *				It can be gc_login_on, gc_login_register, gc_login_off, gc_beat_heart,
 *				gc_report, gc_subscribe.
 * *********************************************************************************************/
typedef struct
{
	uint16_t id;
	uint16_t type;
	uint16_t length;
	char *data;
}gc_parameter_t;


/* *********************************************************************************************
 *	group-center protocol definition.	
 *
 *	Character mean:
 *	Blow does not need to crypt.
 *	@head:		group-center protocol head char.
 *	@attr:		Bit1 is crypt flag. If bit1 is 1, encrypt protocol; 
 *				Bit2 is crc check flag. If bit2 is 1, enable crc32 check.
 *				Bit3-Bit6 is crypt alogrithm.
 *	@sequence:	group-center protocol sequence.
 *	@length:		Protocol package length. If enable crypt, length means encrypted package length.
 *	@tail:		group-center protocol tail char.
 *
 *	Blow can be crypted, if needed.
 *	@main_id:	group-center protocol main id char.
 *	@src:		Source group id.
 *	@dst:		Dest group id.
 *	@param_num:	Protocol parameters numbers.
 *	@param:		Protocol parameters.
 *
 * **********************************************************************************************/
typedef struct
{
	char head;
	uint16_t attr;
	uint32_t crc_check;
	uint32_t sequence;
	uint32_t length;
	/*****crypt character******/
	uint16_t main_id;
	uint32_t src;
	uint32_t dst;
	uint16_t param_num;
	gc_parameter_t *param;
	/*****crypt character******/
	char tail;
}gc_protocol_t;


#define GCP_CRYPT_ECC_ALG							0
#define GCP_CRYPT_CBC_ALG							1

/* get gc_protocol_t crypt flag, if value is 1, means enable crypt */
#define GCP_CryptFlag(p_gc)							(p_gc->attr & 1)

/* get gc_protocol_t crc32 flag, if value is 1, means enable crc32 check */
#define GCP_CRC32Flag(p_gc)							(p_gc->attr & 2)

#define GCP_AttrGC(p_gc)							(p_gc->attr & 4)

/* get gc_protocol_t crypt alogrithm, if value is 1, means enable crc32 check */
#define GCP_CryptAlg(p_gc)							((p_gc->attr >> 3) & 63)


/* set gc_protocol_t crypt flag enable */
#define GCP_SetCryptEnable(p_gc)					(p_gc->attr |= 1);

/* set gc_protocol_t crypt flag disable */
#define GCP_SetCryptDisable(p_gc)					(p_gc->attr &= ~(1 << 1));

/* set gc_protocol_t crc32 check flag enable */
#define GCP_SetCRC32Enable(p_gc)					(p_gc->attr |= 2);

/* set gc_protocol_t crc32 check flag disable */
#define GCP_SetCRC32Disable(p_gc)					(p_gc->attr &= ~(1 << 2));

/* set gc_protocol_t crypt alogrithm */
#define GCP_SetCryptAlg(p_gc,alg)					(p_gc->attr |= (alg << 3));

#define GCP_SetAttrGTC(p_gc)						(p_gc->attr |= 4);
#define GCP_SetAttrCTG(p_gc)						(p_gc->attr &= ~(1 << 3));

#define GCP_SetHead(p_gc)							(p_gc->head = GCP_HEAD_ID);
#define GCP_SetTail(p_gc)							(p_gc->tail = GCP_TAIL_ID);
#define GCP_SetSequence(p_gc,seq)					(p_gc->sequence = seq);
#define GCP_SetMainID(p_gc,id)						(p_gc->main_id = id);
#define GCP_SetSrc(p_gc,id)							(p_gc->src = id);
#define GCP_SetDst(p_gc,id)							(p_gc->dst = id);

#define GCP_SetParam(param,arg1,arg2,arg3) \
	(param)->id = arg1;\
	(param)->type = arg2;\
	(param)->data = (char *)arg3;

/* group-center protocol crypt character index. */
#define GCP_ENCRYPT_INDEX							15


/* group center protocol head and tail */
#define GCP_HEAD_ID									'c'
#define GCP_TAIL_ID									'c'

/* group send to center */
#define GCP_GTC										4
/* center send to group */
#define GCP_CTG										0


/* group-center protocol login main id */
#define GCP_LOGIN_ID								0x0000
/* group-center protocol login on parameter id */
#define GCP_LOGIN_REQ_ID							0x0001
/* group-center protocol login on parameter id */
#define GCP_LOGIN_ON_ID								0x0002
/* group center protocol login off parameter id */
#define GCP_LOGIN_OFF_ID							0x0003
/* group center protocol login register parameter id */
#define GCP_LOGIN_REGISTER_ID						0x0004


/* *********************************************************************************************
 *	group-center protocol login on structure.
 *
 *	@group_id:		The group's id intend to login on center.
 *	@flag:			The group's open port intend to login on center.
 *
 * *********************************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint8_t flag;
}gc_login_request_t;

#define GCP_SetLoginRequest(p_login_request,arg1,arg2) \
	(p_login_request)->group_id = arg1;\
	(p_login_request)->flag = arg2;


/* create a gc_login_on_t structure */
extern gc_login_request_t *allocate_gcp_login_request();

/* delete a gc_login_on_t structure */
extern void deallocate_gcp_login_request(gc_login_request_t **p_login_request);


/* *********************************************************************************************
 *	group-center protocol login on structure.
 *	@group_id:		The group's id intend to login on center.
 *	@link_ip:		The group's link ip intend to login on center.
 *	@link_port:		The group's link port intend to login on center.
 *	@open_ip:		The group's open ip intend to login on center.
 *	@open_port:		The group's open port intend to login on center.
 *
 * *********************************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint32_t link_ip;
	uint16_t link_port;
	uint32_t open_ip;
	uint16_t open_port;
	uint8_t result;
}gc_login_on_t;

#define GCP_SetLoginOn(p_login_on,arg1,arg2,arg3,arg4,arg5,arg6) \
	(p_login_on)->group_id = arg1;\
	(p_login_on)->link_ip = arg2; \
	(p_login_on)->link_port = arg3;\
	(p_login_on)->open_ip = arg4;\
	(p_login_on)->open_port = arg5;\
	(p_login_on)->result = arg6;

/* create a gc_login_on_t structure */
extern gc_login_on_t *allocate_gcp_login_on();

/* delete a gc_login_on_t structure */
extern void deallocate_gcp_login_on(gc_login_on_t **p_login_on);


/* *********************************************************************************************
 *	group-center protocol login off structure.
 *	@group_id:		The group's id intend to logoff from center.
 *	@reason:		The group's reason intend to logoff from center.
 *
 * *********************************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint8_t reason;
}gc_login_off_t;

#define GCP_SetLoginOff(p_login_off,arg1,arg2) \
	(p_login_off)->group_id = arg1;\
	(p_login_off)->reason = arg2; \

/* create a gc_login_off_t structure */
extern gc_login_off_t *allocate_gcp_login_off();

/* delete a gc_login_off_t structure */
extern void deallocate_gcp_login_off(gc_login_off_t **p_login_off);


/* ********************************************************************************************
 *	group-center protocol login register structure.
 *	@group_id:		The group's id intends to register to center.
 *	@key:			The group's key intends to register to center.
 *	@result:		The result group intends to register to center.
 *	@key_len:		The group's key len. If group sends to center, key_len means ecc key length. 
 *					If group sends to center, key_len means cbc key length.
 *	@key:			The group's key. If group sends to center, key means ecc public key. 
 *					Center needs to use it encrypting protocl package.
 *					If center sends to group, key means cbc securit key.
 *					Ecc public key do not need encrypting. Cbc needs to encrypting.
 *
 * ********************************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint8_t result;
	uint8_t key_len;
	uint8_t key[256];
}gc_login_register_t;

#define GCP_SetLoginRegister(p_login_register,arg1,arg2,arg3,arg4) \
	(p_login_register)->group_id = arg1;\
	(p_login_register)->result = arg2; \
	(p_login_register)->key_len = arg3; \
	memcpy((p_login_register)->key,arg4,arg3);

/* create a gc_login_register_t structure */
extern gc_login_register_t *allocate_gcp_login_register();

/* delete a gc_login_register_t structure */
extern void deallocate_gcp_login_register(gc_login_register_t **p_login_register);

#define GCP_LOGIN_ON_SUCCESS_RESULT					0x0001
#define GCP_LOGIN_ON_FAILED_RESULT					0x0000
#define GCP_LOGIN_ON_FAILED_REASON_LINK_IP			1
#define GCP_LOGIN_ON_FAILED_REASON_LINK_PORT		2
#define GCP_LOGIN_ON_FAILED_REASON_OPEN_IP			4
#define GCP_LOGIN_ON_FAILED_REASON_OPEN_PORT		8
#define GCP_LOGIN_ON_FAILED_UNKNOWN_RESULT			9
#define GCP_LOGIN_ON_FAILED_UNREGISTER_RESULT		10
#define GCP_LOGIN_ON_FAILED_SK_ERROR_RESULT			11

#define GCP_LOGIN_REGISTER_SUCCESS_RESULT			1
#define GCP_LOGIN_REGISTER_FAILED_OCCUPY			2
#define GCP_LOGIN_REGISTER_FAILED_FULL				3

#define GCP_LOGIN_REQ_FLAG							1
#define GCP_LOGIN_RSP_FLAG							2

/* group center protocol beatheart party */
#define GCP_BEAT_HEART_ID							0x0100
#define GCP_BEAT_HEART_KEEPALIVE_ID					0x0101
#define GCP_BEAT_HEART_KEEPALIVE_REQ				1
#define GCP_BEAT_HEART_KEEPALIVE_RSP				2

typedef struct
{
	uint32_t group_id;
	uint8_t flag;
}gc_beat_heart_t;

#define GCP_SetBeatHeart(p_beat_heart,arg1,arg2) \
	(p_beat_heart)->group_id = arg1;\
	(p_beat_heart)->flag = arg2;

/* create a gc_beat_heart_t structure */
extern gc_beat_heart_t *allocate_gcp_beat_heart();

/* delete a gc_beat_heart_t structure */
extern void deallocate_gcp_beat_heart(gc_beat_heart_t **p_beat_heart);

#define GCP_REQUEST_ID								0x0200
#define GCP_REQUEST_GROUP_ID						0x0201
#define GCP_REQUEST_ALL_GROUP_ID					0x0202

typedef struct
{
	uint32_t group_id;
	uint32_t open_ip;
	uint16_t open_port;
}gc_group_info_t;

#define GCP_SetGroupsInfo(p_request_groups,i,arg1,arg2,arg3) \
	(p_request_groups)->groups_list[i].group_id = arg1;\
	(p_request_groups)->groups_list[i].open_ip = arg2;\
	(p_request_groups)->groups_list[i].open_port = arg3;

typedef struct
{
	uint32_t group_id;
	uint16_t group_num;
	gc_group_info_t *groups_list;
}gc_request_groups_t;

#define GCP_SetRequestGroups(p_request_groups,arg1) \
	(p_request_groups)->group_id = arg1;

/* create a gc_request_groups_t structure */
extern gc_request_groups_t *allocate_gcp_request_groups(uint16_t num);

/* delete a gc_request_groups_t structure */
extern void deallocate_gcp_request_groups(gc_request_groups_t **p_request_groups);

/* set gc_request_groups_t group info numbers */
extern void set_gcp_request_groups_num(gc_request_groups_t *p_request_groups,uint16_t num);



#define GCP_REPORT_ID								0x0300
#define GCP_REPORT_WARNING_ID						0x0301
#define GCP_REPORT_ERROR_ID							0x0302

typedef struct
{
	uint32_t group_id;
	uint8_t reserve;
}gc_report_t;

#define GCP_SetReport(p_report,arg1,arg2) \
	(p_report)->group_id = arg1;\
	(p_report)->reserve = arg2;

/* create a gc_report_t structure */
extern gc_report_t *allocate_gcp_report();

/* delete a gc_report_t structure */
extern void deallocate_gcp_report(gc_report_t **p_report);

#define GCP_REPORT_WARNING_OVERFLOW					0x0301
#define GCP_REPORT_ERROR_LINK_OFF					0x0302


#define GCP_SUBSCRIBE_ID							0x0400
#define GCP_SUBSCRIBE_GROUP_ID						0x0401
#define GCP_CANCEL_SUBSCRIBE_GROUP_ID				0x0402

typedef struct
{
	uint32_t group_id;
}gc_subscribe_t;

#define GCP_SetSubscribe(p_subscribe,arg1) \
	(p_subscribe)->group_id = arg1;

/* create a gc_subscribe_t structure */
extern gc_subscribe_t *allocate_gcp_subscribe();

/* delete a gc_subscribe_t structure */
extern void deallocate_gcp_subscribe(gc_subscribe_t **p_subscribe);


#define GCP_PARSER_SUCCESS							0
#define GCP_PARSER_FAILED							1

#define GCP_PACKAGE_SUCCESS							0
#define GCP_PACKAGE_FAILED							-1

#define GCP_PARAM_INDEX								26


extern gc_protocol_t *allocate_gcp(uint16_t num);


/* **************************************************************************************
 *
 * @function:	deallocate_gcp
 * @param:		
 *		protocol:	group cluster protocol pointer's pointer
 *		after free control protocol success, the control protocol pointer will be set 0.
 * @retval:
 *
 * ***************************************************************************************/
extern void deallocate_gcp(gc_protocol_t **p_gc);



/* ******************************************************************************
 *	@function:	parser_gcp
 *	@param:		
 *		package: need to parser protocol package
 *	@retval: corectrl_protocol
 *	
 * *******************************************************************************/
extern gc_protocol_t *parser_gcp(const protocol_package *package,const char *key,uint16_t key_len);

/* ******************************************************************************
 *	@function:	package_gcp
 *	@param:		
 *		protocol need to package protocol structure
 *	@retval:	protocol_package
 *
 * *******************************************************************************/
extern protocol_package *package_gcp(const gc_protocol_t *p_gc,const char *key,uint16_t key_len);


extern void set_gcp_param_num(gc_protocol_t *p_gc,uint16_t num);

/* copy gc_protocol_t head and param */
#define GCP_COPY_ALL_FLAG							0xffff
/* only copy gc_protocol_t head */
#define GCP_COPY_HEAD_FLAG							0x02
/* only copy gc_protocol_t param */
#define GCP_COPY_COPY_PARAM_FLAG					0x04

/* copy gc_protocol_t structure */
extern gc_protocol_t *copy_gcp(gc_protocol_t *p_gc,int flag);

/* print gc_protocol_t structure */
extern void print_gcp(gc_protocol_t *p_gc);

#ifdef __cplusplus_
}
#endif



#endif


