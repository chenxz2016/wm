/* ************************************************************************
 *       Filename:  gnc_protocol.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef GNC_PROTOCOL_H_
#define GNC_PROTOCOL_H_

#ifdef __cplusplus_
extern "C"
{
#endif

#define GNCP_TYPE_INT8_ID								1
#define GNCP_TYPE_UINT8_ID								2
#define GNCP_TYPE_INT16_ID								3
#define GNCP_TYPE_UINT16_ID								4
#define GNCP_TYPE_INT32_ID								5
#define GNCP_TYPE_UINT32_ID								6
#define GNCP_TYPE_INT64_ID								7
#define GNCP_TYPE_UINT64_ID								8
#define GNCP_TYPE_BYTEARRAY_ID							9
#define GNCP_TYPE_STRING_ID								10
#define GNCP_TYPE_BCD_ID								11
#define GNCP_TYPE_CUSTOM_ID								12
#define GNCP_TYPE_CHAR_ID								13
#define GNCP_TYPE_FLOAT_ID								14
#define GNCP_TYPE_DOUBLE_ID								15


/* *********************************************************************************************
 * Group-NodeCore protocol
 * @head			Group_NodeCore protocol head flag.
 * @sequence		Group-NodeCore protocol package sequence.
 * @id				Group-NodeCore protocol server id.
 * @length			Group-NodeCore protocol data length.
 * @data			Group-NodeCore protocol data pointer.
 * @tail			Group-NodeCore protocol tail flag.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t head;
	uint32_t sequence;
	uint16_t type;
	uint32_t src;
	uint32_t dst;
	uint32_t length;
	char *data;
	uint8_t tail;
}gnc_protocol_t;

#define GNCP_SetHead(p_gnc)								((p_gnc)->head = GNCP_HEAD_ID);
#define GNCP_SetTail(p_gnc)								((p_gnc)->tail = GNCP_TAIL_ID);
#define GNCP_SetSequence(p_gnc,seq)						((p_gnc)->sequence = seq);
#define GNCP_SetType(p_gnc,t)							((p_gnc)->type = t);
#define GNCP_SetSrc(p_gnc,id)							((p_gnc)->src = id);
#define GNCP_SetDst(p_gnc,id)							((p_gnc)->dst = id);
#define GNCP_SetData(p_gnc,d)							((p_gnc)->data = (char *)d);

/* group to group protocol head and tail */
#define GNCP_HEAD_ID									'8'
#define GNCP_TAIL_ID									'8'


#define GNCP_DISCONNECT_ID								0x0100

#define GNCP_DISCONNECT_UPDATE_FLAG						1
#define GNCP_DISCONNECT_ERROR_FLAG						2
#define GNCP_DISCONNECT_KILLED_FLAG						3
#define GNCP_DISCONNECT_UNKNOWN_FLAG					4

/* *********************************************************************************************
 *	Group_NodeCore protocol disconnect item.
 *	@reason			Group-NodeCore protocol server disconnect reason.
 *
 * *********************************************************************************************/
typedef struct
{
	uint8_t reason;	
}gnc_disconnect_t;

#define GNCP_SetDisconnect(p_disconnect,arg1)			((p_disconnect)->reason = arg1);

/* Create gnc_disconnect_t structure. */
extern gnc_disconnect_t *allocate_gncp_disconnect();

/* Delete gnc_disconnect_t structure. */
extern void deallocate_gncp_disconnect(gnc_disconnect_t **p_disconnect);

#define GNCP_BEAT_HEART_ID								0x0200
#define GNCP_BEAT_HEART_REQ_FLAG						1
#define GNCP_BEAT_HEART_RSP_FLAG						2


/* *********************************************************************************************
 *	Group_NodeCore protocol beatheart item.
 *	@flag			Group-NodeCore protocol beat heart request and respond flag.
 *
 * *********************************************************************************************/
typedef struct
{
	uint8_t flag;
}gnc_beatheart_t;


#define GNCP_SetBeatheart(p_beatheart,arg1)			((p_beatheart)->flag = arg1);

/* Create gnc_beatheart_t structure. */
extern gnc_beatheart_t *allocate_gncp_beatheart();

/* Delete gnc_beatheart_t structure. */
extern void deallocate_gncp_beatheart(gnc_beatheart_t **p_beatheart);

#define GNCP_REGISTER_ID								0x0300

#define GNCP_REGISTER_SUCCESS							1
#define GNCP_REGISTER_FAILED							2

/* *********************************************************************************************
 *	Group_NodeCore protocol register item.
 *	@id			Group-NodeCore protocol server register id.
 *	@result		Group-NodeCore protocol server register result.
 *
 * *********************************************************************************************/
typedef struct
{
	uint16_t id;
	uint8_t result;
}gnc_register_t;

#define GNCP_SetRegister(p_beatheart,arg1,arg2)\
	((p_beatheart)->id = arg1);\
	((p_beatheart)->result = arg2);

/* Create gnc_register_t structure. */
extern gnc_register_t *allocate_gncp_register();

/* Delete gnc_register_t structure. */
extern void deallocate_gncp_register(gnc_register_t **p_register);



#define GNCP_UPDATE_ID									0x0400
#define GNCP_UPDATE_ADD_FLAG							1
#define GNCP_UPDATE_DEL_FLAG							2

typedef struct
{
	uint8_t flag;
	uint16_t type;
	uint32_t id_num;
	uint32_t *id_list;
}gnc_update_t;

#define GNCP_SetUpdate(p_update,arg1,arg2) \
	((p_update)->flag = arg1);\
	((p_update)->type = arg2);\
	
#define GNCP_SetUpdateID(p_update,i,arg1)\
	((p_update)->id_list[i] = arg1);


/* Create gnc_update_t structure. */
extern gnc_update_t *allocate_gncp_update(uint16_t num);

/* Delete gnc_update_t structure. */
extern void deallocate_gncp_update(gnc_update_t **p_update);

/* Set gnc_update_t id num. */
extern void set_gncp_update_num(gnc_update_t *p_update,uint16_t num);


#define GNCP_PARSER_SUCCESS								0
#define GNCP_PARSER_FAILED								1

#define GNCP_PACKAGE_FAILED								0

#define GNCP_PARAM_INDEX								19


/* Allocate gnc_protocol_t. */
extern gnc_protocol_t *allocate_gncp();

/* Deallocate gnc_protocol_t. */
extern void deallocate_gncp(gnc_protocol_t **p_gnc);

/* Set gnc_protocol_t data length. */
extern void set_gncp_data_length(gnc_protocol_t *p_gnc,uint32_t length);


/* Parser gnc_protocol_t. */
extern gnc_protocol_t *parser_gncp(const protocol_package *p);

/* Package gnc_protocol_t. */
extern protocol_package *package_gncp(const gnc_protocol_t *p_gnc);


#define GNCP_COPY_ALL_FLAG								0xffff
#define GNCP_COPY_HEAD_FLAG								0x02
#define GNCP_COPY_DATA_FLAG								0x04

/* Copy gnc_protocol_t. */
extern gnc_protocol_t *copy_gnc(const gnc_protocol_t *p_gnc,int flag);

#define GNCP_PRINT_DATA_FLAG							1
#define GNCP_PRINT_HEAD_FLAG							2
#define GNCP_PRINT_ALL_FLAG								0xff

/* Print gnc_protocol_t. */
extern void print_gncp(const gnc_protocol_t *p_gnc,int flag);


#ifdef __plusplus_
}
#endif

#endif


