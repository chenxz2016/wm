/* ************************************************************************
 *       Filename:  wm_protocol.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WM_PROTOCOL_H_
#define WM_PROTOCOL_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include "protocol_package.h"

#define WMP_PROTO_LOGIN_KEY_ID					0
#define WMP_PROTO_LOGIN_ID						1
#define WMP_PROTO_BH_ID							2
#define WMP_PROTO_FILE_ID						3
#define WMP_PROTO_GROUP_ID						4
#define WMP_PROTO_MSG_ID						5
#define WMP_PROTO_REGISTER_ID					6
#define WMP_PROTO_SESSION_ID					7
#define WMP_PROTO_SOUND_ID						8
#define WMP_PROTO_VIDEO_ID						9
#define WMP_PROTO_USER_ID						10

/* **********************************************************************************************
 *	wm_base_t structure.
 *
 *	@proto_type:		protocol type.
 *	@src:				source sender id.
 *	@dst:				destination receive id.
 *	@device:			device name, 24 byte.
 *	@time:				send time.
 *	@version:			protocol version, 10 byte.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t proto_type;
	uint32_t src;
	uint32_t dst;
	char device[24];
	uint8_t network;
	uint32_t time;
	char version[10];
}wm_base_t;

/* wm_base_t structure length marco. */
#define WMP_BASE_LENGTH								49

/* **********************************************************************************************
 *	wm_parameter_t structure.
 *
 *	@attr:				parameter attribue.
 *	@main_id:			parameter list main id.
 *	@length:			parameter data length.
 *	@data:				parameter data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint32_t attr;
    uint16_t main_id;
    uint32_t length;
    void *data;
}wm_parameter_t;

/* **********************************************************************************************
 *	wm_body_t structure.
 *
 *	@param_num:			parameter list num.
 *	@param:				parameter list pointer.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t param_num;
	wm_parameter_t *param;
}wm_body_t;

/* **********************************************************************************************
 *	wm_protocol_t structure.
 *
 *	@head:				wm_protocol head flag.
 *	@sequence:			wm_protocol sequence.
 *	@crc_check:			wm_protocol crc32 check code.
 *	@attr:				wm_protocol attribute.
 *	@length:			wm_protocol package length.
 *	@base:				wm_protocol wm_base_t.
 *	@body:				wm_protocol wm_body_t.
 *	@tail:				wm_protocol tail flag.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t head;
	uint32_t sequence;
	uint32_t crc_check;
	uint32_t attr;
	uint32_t length;
	wm_base_t base;
	wm_body_t body;
	uint8_t tail;
}wm_protocol_t;


/* The marco of index from head to start of wm_base_t. */
#define WMP_BASE_INDEX								17

/* wm_protocol_t allocate. */
WMPSHARED_EXPORT extern wm_protocol_t *allocate_wmp(uint16_t param_num);

/* wm_protocol_t deallocate. */
WMPSHARED_EXPORT extern void deallocate_wmp(wm_protocol_t **p_wm);

/* Set wm_body_t parameter numbers. */
WMPSHARED_EXPORT extern void set_wmp_body_param_num(wm_body_t *p_wm_body,uint16_t num);

/* Set wm_parameter_t parameter data length. */
WMPSHARED_EXPORT extern void set_wmp_param_len(wm_parameter_t *p_wm_param,uint16_t len);

/* wm_protocol_t crypt attribute marco */
#define WMP_CRYPT_ENABLE_FLAG						1
#define WMP_CRYPT_DISABLE_FLAG						0

/* wm_protocol_t crc32 check attribute marco */
#define WMP_CRC32_ENABLE_FLAG						2
#define WMP_CRC32_DISABLE_FLAG						0

/* wm_protocol_t crypt attribute get marco */
#define WMP_CryptFlag(p_wm)							(p_wm->attr & 1)
/* wm_protocol_t crc32 check attribute get marco */
#define WMP_CRC32Flag(p_wm)							(p_wm->attr & 2)

/* wm_protocol_t crypt attribute set marco */
#define WMP_SetCryptEnable(p_wm)					(p_wm->attr |= 1);
#define WMP_SetCryptDisable(p_wm)					(p_wm->attr &= ~(1 << 1));


/* wm_protocol_t crc32 check attribute set marco */
#define WMP_SetCRC32Enable(p_wm)					(p_wm->attr |= 2);
#define WMP_SetCRC32Disable(p_wm)					(p_wm->attr &= ~(1 << 2));

/* wm_parameter_t parameter data swap marco. */
#define WMP_ParamDataSwap(p_param,ptr) \
	ptr = (p_param)->data;\
	(p_param)->data = NULL;

/* wm_parameter_t parameter data and length swap marco. */
#define WMP_ParamDataLenSwap(p_param,ptr,len) \
	ptr = (p_param)->data;\
	len = (p_param)->length;\
	(p_param)->data = NULL;\
	(p_param)->length = 0;

#define WMP_SetHead(p_wm)							(p_wm->head = WMP_HEAD_ID);
#define WMP_SetTail(p_wm)							(p_wm->tail = WMP_TAIL_ID);
#define WMP_SetSequence(p_wm,seq)					(p_wm->sequence = seq);

#define WMP_SetBase(p_wm,arg1,arg2,arg3,arg4,arg5,arg6,arg7) \
	(p_wm)->base.proto_type = arg1;\
	(p_wm)->base.src = arg2;\
	(p_wm)->base.dst = arg3;\
	strcpy((p_wm)->base.device,arg4);\
	(p_wm)->base.network = arg5;\
	(p_wm)->base.time = arg6;\
	strcpy((p_wm)->base.version,arg7);

#define WMP_SetBody(p_wm,arg)\
	(p_wm)->body.main_id = arg;

#define WMP_SetParam(p_wm,i,arg1,arg2,arg3)\
	(p_wm)->body.param[i].attr = arg1;\
	(p_wm)->body.param[i].length = arg2;\
	memcpy((p_wm)->body.param[i].data,arg3,arg2);

#define WMP_SwapID(p_wm)\
	uint32_t id = (p_wm)->base.dst;\
	(p_wm)->base.dst = (p_wm)->base.src;\
	(p_wm)->base.src = id;

/* walking message protocol type */
#define WMP_TYPE_UINT8_ID							0x01
#define WMP_TYPE_UINT16_ID							0x02
#define WMP_TYPE_UINT32_ID							0x03
#define WMP_TYPE_UINT64_ID							0x04
#define WMP_TYPE_INT8_ID							0x05
#define WMP_TYPE_INT16_ID							0x06
#define WMP_TYPE_INT32_ID							0x07
#define WMP_TYPE_INT64_ID							0x08
#define WMP_TYPE_CHAR_ID							0x09
#define WMP_TYPE_FLOAT_ID							0x0a
#define WMP_TYPE_DOUBLE_ID							0x0b
#define WMP_TYPE_STRING_ID							0x0c
#define WMP_TYPE_WSTRING_ID							0x0d
#define WMP_TYPE_BYTEARRAY_ID						0x0e
#define WMP_TYPE_BCD_ID								0x0f
#define WMP_TYPE_CUSTOM_ID							0x10


/* walking message protocol head and tail definition. */
#define WMP_HEAD_ID									0xfe
#define WMP_TAIL_ID									0xfe

/* Parser successfully*/
#define WMP_PARSER_SUCCESS							0
#define WMP_PARSER_FAILED							1
 
/* Base parser error */
#define WMP_PARSER_FAILED_PACK_LEN					1
#define WMP_PARSER_FAILED_CRC_WRONG					2
#define WMP_PARSER_FAILED_DEVICE_WRONG				3
#define WMP_PARSER_FAILED_NETWORK_WRONG				4
#define WMP_PARSER_FAILED_DST_WRONG					5
#define WMP_PARSER_FAILED_SETTING_WRONG				6
#define WMP_PARSER_FAILED_PROTO_UNSUPPORT			7



/* Walking message network marco definition */
#define WMP_NETWORK_GSM								1
#define WMP_NETWORK_EDGE							2
#define WMP_NETWORK_3G								3
#define WMP_NETWORK_4G								4
#define WMP_NETWORK_5G								5
#define WMP_NETWORK_WIFI							6

/* wm_protocol_t parser function. */
WMPSHARED_EXPORT extern wm_protocol_t *parser_wmp(const protocol_package *package,const char *key,const uint16_t key_len);

/* wm_protocol_t package function. */
WMPSHARED_EXPORT extern protocol_package *package_wmp(const wm_protocol_t *p_wm,const char *key,const uint16_t key_len);

/* print wm_protocol_t function. */
WMPSHARED_EXPORT extern void print_wmp(const wm_protocol_t *p_wm);

/* copy wm_protocol_t structure. */
WMPSHARED_EXPORT extern wm_protocol_t * copy_wmp(const wm_protocol_t *p_wm);


#ifdef __cplusplus
}
#endif

#endif
