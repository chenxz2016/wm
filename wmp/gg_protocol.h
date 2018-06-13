/* ************************************************************************
 *       Filename:  gg_protocol.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef GG_PROTOCOL_H_
#define GG_PROTOCOL_H_


#ifdef __cplusplus_
extern "C"
{
#endif

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#define GGP_TYPE_INT8_ID							1
#define GGP_TYPE_UINT8_ID							2
#define GGP_TYPE_INT16_ID							3
#define GGP_TYPE_UINT16_ID							4
#define GGP_TYPE_INT32_ID							5
#define GGP_TYPE_UINT32_ID							6
#define GGP_TYPE_INT64_ID							7
#define GGP_TYPE_UINT64_ID							8
#define GGP_TYPE_BYTEARRAY_ID						9
#define GGP_TYPE_STRING_ID							10
#define GGP_TYPE_BCD_ID								11
#define GGP_TYPE_CUSTOM_ID							12
#define GGP_TYPE_CHAR_ID							13
#define GGP_TYPE_FLOAT_ID							14
#define GGP_TYPE_DOUBLE_ID							15


/* ******************************************************************************
 *	Group-Group Protocol parameter definition.
 *	@type		Parameter type.
 *	@id			Parameter id.
 *	@length		Parameter length.
 *	@data		Parameter data.
 *
 * ******************************************************************************/
typedef struct
{
	uint16_t id;
	uint16_t attr;
	uint32_t length;
	char *data;
}gg_parameter_t;


/* ******************************************************************************
 *	Group-Group Protocol Package definition.
 *	@head		Group-Group Protocol head flag.
 *	@attr		Group-Group Protocol attr character.
 *	@crc_check	Group-Group Protocol crc32 check code.
 *	@sequence	Group-Group Protocol sequence.
 *	@length		Group-Group Protocol Package length.
 *	@src		Group-Group Protocol Package src group id.
 *	@dst		Group-Group Protocol Package dst group id.
 *	@param_num	Group-Group Protocol Package parameter number.
 *	@param		Group-Group Protocol Package parameter list pointer.
 *	@tail		Group-Group Protocol Package tail flag.
 *
 * ******************************************************************************/
typedef struct
{
	uint8_t head;
	uint16_t attr;
	uint32_t crc_check;
	uint32_t sequence;
	uint32_t length;
	uint16_t main_id;
	uint32_t src;
	uint32_t dst;
	uint16_t param_num;
	gg_parameter_t *param;
	uint8_t tail;
}gg_protocol_t;


/* get gc_protocol_t crypt flag, if value is 1, means enable crypt */
#define GGP_CryptFlag(p_gg)							(p_gg->attr & 1)
/* get gc_protocol_t crc32 flag, if value is 1, means enable crc32 check */
#define GGP_CRC32Flag(p_gg)							(p_gg->attr & 2)
/* get gc_protocol_t crypt alogrithm, if value is 1, means enable crc32 check */
#define GGP_CryptAlg(p_gg)							((p_gg->attr >> 2) & 63)

/* set gc_protocol_t crypt flag enable */
#define GGP_SetCryptEnable(p_gg)					(p_gg->attr |= 1);
/* set gc_protocol_t crypt flag disable */
#define GGP_SetCryptDisable(p_gg)					(p_gg->attr &= ~(1 << 1));
/* set gc_protocol_t crc32 check flag enable */
#define GGP_SetCRC32Enable(p_gg)					(p_gg->attr |= 2);
/* set gc_protocol_t crc32 check flag disable */
#define GGP_SetCRC32Disable(p_gg)					(p_gg->attr &= ~(1 << 2));
/* set gc_protocol_t crypt alogrithm */
#define GGP_SetCryptAlg(p_gg,alg)					(p_gg->attr |= (alg << 2));

#define GGP_SetParam(p_param,arg1,arg2,arg3) \
	(p_param)->id = arg1;\
	(p_param)->attr = arg2;\
	(p_param)->data = (char *)arg3;


#define GGP_SetHead(p_gg)							(p_gg->head = GGP_HEAD_ID);
#define GGP_SetTail(p_gg)							(p_gg->tail = GGP_TAIL_ID);
#define GGP_SetSequence(p_gg,seq)					(p_gg->sequence = seq);
#define GGP_SetMainID(p_gg,id)						(p_gg->main_id = id);
#define GGP_SetSrc(p_gg,id)							(p_gg->src = id);
#define GGP_SetDst(p_gg,id)							(p_gg->dst = id);

/* group to group protocol head and tail */
#define GGP_HEAD_ID									'8'
#define GGP_TAIL_ID									'8'

#define GGP_CONNECT_ID								0x0000
#define GGP_CONNECT_REQ_ID							0x0001
#define GGP_CONNECT_RSP_ID							0x0002


/* ******************************************************************************
 *	Group-Group Protocol Connect definition.
 *	@flag		Connect flag.
 *	@key_len	Source group crypt key length.
 *	@key		Source group crypt key.
 *	@open_ip	Source group open ip.
 *	@open_port	Source group open port.
 *	@result		Connect result.
 *
 * ******************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint32_t open_ip;
	uint16_t open_port;
	uint8_t result;
	uint8_t key_len;
	char key[256];
}gg_connect_t;

#define GGP_SetConnect(p_connect,arg1,arg2,arg3,arg4,arg5,arg6) \
	(p_connect)->group_id = arg1;\
	(p_connect)->open_ip = arg2;\
	(p_connect)->open_port = arg3;\
	(p_connect)->result = arg4;\
	(p_connect)->key_len = arg5;\
	memcpy((p_connect)->key,arg6,arg5);

/* Create a gg_connect_t structure. */
extern gg_connect_t *allocate_ggp_connect();

/* Delete a gg_connect_t structure. */
extern void deallocate_ggp_connect(gg_connect_t **p_connect);

#define GGP_CONNECT_RESULT_SUCCESS_FLAG				0
#define GGP_CONNECT_RESULT_CONNECTED_FLAG			1
#define GGP_CONNECT_RESULT_KEY_ERROR_FLAG			2
#define GGP_CONNECT_RESULT_GROUP_ERROR_FLAG			3


#define GGP_DISCONNECT_ID							0x0100
#define GGP_DISCONNECT_INFORM_ID					0x0101


/* ******************************************************************************
 *	Group-Group Protocol Disconnect definition.
 *	@group_id	Source group id.
 *	@reason		Disconnect reason.
 *
 * ******************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint8_t reason;
}gg_disconnect_t;

#define GGP_SetDisconnect(p_disconnect,arg1,arg2) \
	(p_disconnect)->group_id = arg1;\
	(p_disconnect)->reason = arg2;

/* Create a disconnect structure. */
extern gg_disconnect_t *allocate_ggp_disconnect();

/* Delete a disconnect structure. */
extern void deallocate_ggp_disconnect(gg_disconnect_t **p_disconnect);

#define GGP_BEAT_HEART_ID							0x0200
#define GGP_BEAT_HEART_KEEPALIVE_ID					0x0201
#define GGP_BEAT_HEART_REQ_FLAG						1
#define GGP_BEAT_HEART_RSP_FLAG						2


/* ******************************************************************************
 *	Group-Group Protocol Beat Heart definition.
 *	@group_id	Source group id.
 *	@reason		Disconnect reason.
 *
 * ******************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint8_t flag;
}gg_beatheart_t;

#define GGP_SetBeatHeart(p_beatheart,arg1,arg2)	\
	(p_beatheart)->group_id = arg1;\
	(p_beatheart)->flag = arg2;

/* Create a beat heart structure. */
extern gg_beatheart_t *allocate_ggp_beatheart();

/* Delete a beat heart structure. */
extern void deallocate_ggp_beatheart(gg_beatheart_t **p_beatheart);

/* update group info */
#define GGP_UPDATE_ID								0x0300
#define GGP_UPDATE_ADD_REQ_ID						0x0301
#define GGP_UPDATE_ADD_RSP_ID						0x0302
#define GGP_UPDATE_DEL_REQ_ID						0x0303
#define GGP_UPDATE_DEL_RSP_ID						0x0304


/* ******************************************************************************
 *	Group-Group Protocol Update definition.
 *	@group_id		Source group id.
 *	@type			update type.
 *	@user_num		The need to update user number.
 *	@user_id_list	User id list.
 *
 * ******************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint16_t type;
	uint8_t result;
	uint32_t id_num;
	uint32_t *id_list;
}gg_update_t;

#define GGP_SetUpdate(p_update,arg1,arg2) \
	(p_update)->group_id = arg1;\
	(p_update)->type = arg2;

#define GGP_SetUpdateID(p_update,i,arg1) \
	(p_update)->id_list[i] = arg1;

/* Create a update structure. */
extern gg_update_t *allocate_ggp_update(uint32_t user_num);

/* Create a update structure. */
extern void deallocate_ggp_update(gg_update_t **p_update);

/* Set a update structure user number. */
extern void set_ggp_update_num(gg_update_t *p_update,uint32_t id_num);



/* Group-Group transaction */
#define GGP_TRANSACTION_ID							0x0400
#define GGP_TRANSACTION_BUSSINESS_REQ_ID			0x0401
#define GGP_TRANSACTION_BUSSINESS_RSP_ID			0x0402

/* ******************************************************************************
 *	Group-Group Protocol Transaction definition.
 *	@group_id		Source group id.
 *	@id				Transaction id.
 *	@len			Transaction data length.
 *	@data			Transaction data.
 *
 * ******************************************************************************/
typedef struct
{
	uint32_t group_id;
	uint16_t id;
	uint32_t len;
	uint8_t result;
	char *data;
}gg_transaction_t;

#define GGP_SetTST(p_tst,arg1,arg2,arg3,arg4) \
	(p_tst)->group_id = arg1;\
	(p_tst)->id = arg2;\
	(p_tst)->len = arg3;\
	memcpy((p_tst)->data,arg4,arg3);

/* Create a transaction structure. */
extern gg_transaction_t *allocate_ggp_tst(uint32_t len);

/* Create a transaction structure. */
extern void deallocate_ggp_tst(gg_transaction_t **p_tst);

/* Set a transaction structure user number. */
extern void set_ggp_tst_len(gg_transaction_t *p_tst,uint32_t len);


#define GGP_PARSER_SUCCESS							0
#define GGP_PARSER_FAILED							1


#define GGP_CRYPT_ECC_ALG							0
#define GGP_CRYPT_CBC_ALG							1


#define GGP_PARAM_INDEX								26

#define GGP_ENABLE_CRCCHECK							1
#define GGP_ENABLE_ENCRYPT							2

/* Allocate gg_protocol_t. */
extern gg_protocol_t *allocate_ggp(uint16_t num);

/* Deallocate gg_protocol_t. */
extern void deallocate_ggp(gg_protocol_t **p_gg);


/* Parser gg_protocol_t package. */
extern gg_protocol_t *parser_ggp(const protocol_package *p,const char *key,uint8_t key_len);

/* Package gg_protocol_t. */
extern protocol_package *package_ggp(const gg_protocol_t *p_gg,const char *key,uint8_t key_len);

/* Set gg_protocol_t parameter. */
extern void set_ggp_param_num(gg_protocol_t *p_gg,uint16_t num);


#define GGP_COPY_ALL_FLAG							0xffff
#define GGP_COPY_HEAD_FLAG							0x02
#define GGP_COPY_PARAM_FLAG							0x04

/* Copy gg_protocol_t. */
extern gg_protocol_t *copy_ggp(const gg_protocol_t *p_gg,int flag);

/* Print gg_protocol_t. */
extern void print_ggp(const gg_protocol_t *p_gg);


#ifdef __plusplus_
}
#endif

#endif


