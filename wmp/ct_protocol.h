/* ************************************************************************
 *       Filename:  ct_protocol.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef CT_PROTOCOL_H_
#define CT_PROTOCOL_H_

#ifdef __cplusplus_
extern "C"
{
#endif

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

/* **********************************************************************************************
 *	ct_parameter_t structure.
 *
 *	@id:				parameter id.
 *	@type:				parameter type.
 *	@length:			parameter data length.
 *	@data:				parameter data, max 256 bytes.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t id;
	uint8_t type;
	uint8_t length;
	char data[256];
}ct_parameter_t;

/* **********************************************************************************************
 *	ct_protocol_t structure.
 *
 *	@check_sum:			crc check sum.
 *	@sequence:			protocol package sequence.
 *	@length:			protocol package length.
 *	@attr:				protocol package attr flag.
 *	@src:				source id.
 *	@dst:				destination id.
 *	@main_id:			protocol main id.
 *	@param_num:			ct_parameter_t parameter numbers.
 *	@param:				parameter list.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t head;
	uint32_t check_sum;
	uint32_t sequence;
	uint16_t length;
	uint16_t attr;
	uint32_t src;
	uint32_t dst;
	uint16_t main_id;
	uint8_t param_num;
	ct_parameter_t *param;
	uint8_t tail;
}ct_protocol_t;


/* get ct_protocol_t crypt flag, if value is 1, means enable crypt. */
#define CTP_CryptFlag(p_ct)							(p_ct->attr & 1)

/* get ct_protocol_t crc32 flag, if value is 1, means enable crc32 check. */
#define CTP_CRC32Flag(p_ct)							(p_ct->attr & 2)

/* set ct_protocol_t crypt flag enable */
#define CTP_SetCryptEnable(p_ct)					(p_ct->attr |= 1);

/* set ct_protocol_t crypt flag disable */
#define CTP_SetCryptDisable(p_ct)					(p_ct->attr &= ~(1 << 1));

/* set ct_protocol_t crc32 flag enable */
#define CTP_SetCRC32Enable(p_ct)					(p_ct->attr |= 2);

/* set ct_protocol_t crc32 flag disable */
#define CTP_SetCRC32Disable(p_ct)					(p_ct->attr &= ~(1 << 2));

#define CTP_SetAttrTTC(p_ct)						(p_ct->attr |= 4);
#define CTP_SetAttrCTT(p_ct)						(p_ct->attr &= ~(1 << 4));
#define CTP_SetSequence(p_ct,seq)					(p_ct->sequence = seq);
#define CTP_SetSrc(p_ct,id)							(p_ct->src = id);
#define CTP_SetDst(p_ct,id)							(p_ct->dst = id);
#define CTP_SetMainID(p_ct,id)						(p_ct->main_id = id);

#define CTP_SetParam(param,arg1,arg2,arg3,arg4) \
	(param)->id = arg1;\
	(param)->type = arg2;\
	(param)->length = arg3;\
	memcpy((param)->data,arg4,arg3);

#define CTP_SetHead(p_ct)							(p_ct->head = CTP_HEAD_ID);
#define CTP_SetTail(p_ct)							(p_ct->tail = CTP_TAIL_ID);

/* Allocate ct_protocol_t structure. */
extern ct_protocol_t *allocate_ctp(uint16_t num);

/* Deallocate ct_protocol_t structure. */
extern void deallocate_ctp(ct_protocol_t **p_ct);


/* control protocol head and tail define */
#define CTP_HEAD_ID									0xfe
#define CTP_TAIL_ID									0xff

#define CTP_TTC										4
#define CTP_CTT										0

/* control protocol encrypt flag define */
#define CTP_ENCRYPT_ENABLE_ID						1
#define CTP_ENCRYPT_DISABLE_ID						0

#define CTP_SRC_ID									0
#define CTP_DST_ID									1

#define CTP_REQ_ID									0
#define CTP_RES_ID									1

/* Control protocol data type. */
#define CTP_TYPE_UINT8_ID							0x01
#define CTP_TYPE_UINT16_ID							0x02
#define CTP_TYPE_UINT32_ID							0x03
#define CTP_TYPE_UINT64_ID							0x04
#define CTP_TYPE_INT8_ID							0x05
#define CTP_TYPE_INT16_ID							0x06
#define CTP_TYPE_INT32_ID							0x07
#define CTP_TYPE_INT64_ID							0x08
#define CTP_TYPE_CHAR_ID							0x09
#define CTP_TYPE_STRING_ID							0x0a
#define CTP_TYPE_BYTEARRAY_ID						0x0b
#define CTP_TYPE_BCD_ID								0x0c
#define CTP_TYPE_FLOAT_ID							0x0d
#define CTP_TYPE_DOUBLE_ID							0x0e
#define CTP_TYPE_CUSTOM_ID							0x0f



/*
 * control protocol definition 
 */

/* heart beat */
#define CTP_HEART_BEAT_ID							0x0001
#define CTP_KEEPALIVE_ID							0x0002

/* connect refuse */
#define CTP_REFUSE_CONNECT_ID						0x0010 
#define CTP_REFUSE_CONNECT_REASON_ID				0x0011
#define CTP_REFUSE_CONNECT_INVALID_ID				0x01
#define CTP_REFUSE_CONNECT_CONNECTED_ID				0x02




#define CTP_REQUEST_ID								0x0100

/* request system resourcce */
#define CTP_REQUEST_SYS_RESOURCE_ID					0x0100
#define CTP_REQUEST_CPU_RESOURCE_ID					0x0101
#define CTP_REQUEST_MEM_RESOURCE_ID					0x0102
#define CTP_REQUEST_DISK_RESOURCE_ID				0x0103

/* request time */
#define CTP_REQUEST_TIME_ID							0x0104
#define CTP_REQUEST_SYSTEM_TIME_ID					0x0105
#define CTP_REQUEST_SERVICE_START_TIME_ID			0x0106
#define CTP_REQUEST_CORE_START_TIME_ID				0x0107
#define CTP_REQUEST_CCTRL_START_TIME_ID				0x0108


/* request service info */
#define CTP_REQUEST_SERVICE_ID						0x0109
#define CTP_REQUEST_SERVICE_NUM_ID					0x010a
#define CTP_REQUEST_SERVICE_NAME_ID					0x010b
#define CTP_REQUEST_SERVICE_CPU_ID					0x010c
#define CTP_REQUEST_SERVICE_MEM_ID					0x010d
#define CTP_REQUEST_SERVICE_DISK_ID					0x010e
#define CTP_REQUEST_CORE_ID							0x010f

#define CTP_REQUEST_ACTIVE_ID						0x0110

/* request client info */
#define CTP_REQUEST_CLIENT_ID						0x0200
#define CTP_REQUEST_CLIENT_NUM_ID					0x0201


/* update file. */
#define CTP_UPLOAD_ID								0x0300
#define CTP_UPLOAD_INFO_ID							0x0301
#define CTP_UPLOAD_CONTENT_ID						0x0302
#define CTP_UPLOAD_END_ID							0x0303
#define CTP_UPLOAD_RESULT_ID						0x0304

#define CTP_UPLOAD_SUCCESS_FLAG						0
#define CTP_UPLOAD_FAILED_FLAG						1


/* core remote control */
#define CTP_CCTRL_ID								0x0400
#define CTP_CCTRL_START_SERVICE_ID					0x0401
#define CTP_CCTRL_STOP_SERVICE_ID					0x0402
#define CTP_CCTRL_PAUSE_SERVICE_ID					0x0403
#define CTP_CCTRL_LOAD_SERVICE_ID					0x0404
#define CTP_CCTRL_UNLOAD_SERVICE_ID					0x0405
#define CTP_CCTRL_START_CORE_ID						0x0406
#define CTP_CCTRL_STOP_CORE_ID						0x0407
#define CTP_CCTRL_PAUSE_CORE_ID						0x0408
#define CTP_CCTRL_LOAD_CORE_ID						0x0409
#define CTP_CCTRL_UNLOAD_CORE_ID					0x040a
#define CTP_CCTRL_GET_SERVICE_ID					0x040b

#define CTP_STATUS_UNLOAD_FLAG						0
#define CTP_STATUS_RUNNING_FLAG						1
#define CTP_STATUS_STOP_FLAG						2
#define CTP_STATUS_PAUSE_FLAG						3

/* gate remote control */
#define CTP_GCTRL_ID								0x0500
#define CTP_GCTRL_START_CORE_ID						0x0501
#define CTP_GCTRL_PAUSE_CORE_ID						0x0502


/* other definition */
#define CTP_LENGTH_MIN								32
#define CTP_PARAM_INDEX								24

#define CTP_PARSER_SUCCESS							1
#define CTP_PARSER_FAILED							0


/* Parser ct_protocol_t. */
extern ct_protocol_t* parser_ctp(const protocol_package *package,const char *key,uint16_t key_len);


/*	Package ct_protocol_t. */
extern protocol_package* package_ctp(const ct_protocol_t *p_ct,const char *key,uint16_t key_len);


/* Copy control protocol flag marco. */
#define CTP_COPY_ALL_FLAG							0xffff
#define CTP_COPY_EXCLUDE_PARAM_FLAG					0x0001
#define CTP_COPY_EXCLUDE_SEQUENCE_FLAG				0x0002
#define CTP_COPY_EXCLUDE_LENGTH_FLAG				0x0004
#define CTP_COPY_EXCLUDE_CHECK_SUM_FLAG				0x0008
#define CTP_COPY_EXCLUDE_ENCRYPT_FLAG				0x0010
#define CTP_COPY_EXCLUDE_SRC_FLAG					0x0022
#define CTP_COPY_EXCLUDE_DST_FLAG					0x0022
#define CTP_COPY_EXCLUDE_MAIN_ID_FLAG				0x0022

/* Copy control protocol. */
extern ct_protocol_t* copy_ctp(ct_protocol_t *p_ct_src,int flag);


/* Set ct_protocol_t parameter numbers. */
extern void set_ctp_param_num(ct_protocol_t *p_ct,uint8_t num);

/* Set ct_parameter_t data. */
extern void set_ctp_parameter(ct_parameter_t *param,uint16_t id,uint8_t type,uint8_t len,const void *data);

#define CTP_PRINT_HEAD								0x01
#define CTP_PRINT_BODY								0x02
#define CTP_PRINT_PARAM								0x04

/* Print ct_protocol_t structure. */
extern void print_ctp(ct_protocol_t *p_ct);



#ifdef __cplusplus_
}
#endif


#endif


