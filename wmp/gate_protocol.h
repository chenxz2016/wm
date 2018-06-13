/* ************************************************************************
 *       Filename:  gate_protocol.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef GATE_PROTOCOL_H_
#define GATE_PROTOCOL_H_

#ifdef __cpluseplus_
extern "C"
{
#endif

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

/* **********************************************************************************************
 *	gate_parameter_t structure.
 *
 *	@id:				parameter id.
 *	@attr:				parameter attribute.
 *	@length:			parameter data length.
 *	@data:				parameter data, max 256 bytes.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t id;
	uint8_t attr;
	uint8_t length;
	void *data;
}gate_parameter_t;


/* **********************************************************************************************
 *	gate_parameter_t structure.
 *
 *	@head:				package head.
 *	@length:			package length.
 *	@length:			package id.
 *	@data:				package parameter number.
 *	@param:				package parameter.
 *	@tail:				package tail.
 *
 * **********************************************************************************************/
typedef struct
{
	char head;
	uint16_t length;
	uint16_t id;
	uint16_t param_num;
	gate_parameter_t *param;
	char tail;
}gate_protocol_t;


#define GATEP_GTN_FLAG							0
#define GATEP_NTG_FLAG							1

#define GATEP_NG(p_gate_param)					(p_gate_param->attr & 1)

#define GATEP_SetNTG(p_gate_param)				(p_gate_param->attr |= 1)
#define GATEP_SetGTN(p_gate_param)				(p_gate_param->attr &= ~(1 << 1))

/* Allocate gate_protocol_t structure. */
extern gate_protocol_t *allocate_gatep(uint16_t param_num);

/* Deallocate gate_protocol_t. */
extern void deallocate_gatep(gate_protocol_t **p_gate);


/* gate protocol head and tail */
#define GATEP_HEAD_ID									'c'
#define GATEP_TAIL_ID									'c'

#define GATEP_PARAM_INDEX								22

typedef struct
{
	uint32_t src;
	uint32_t dst;
	uint8_t result;
	uint16_t type_num;
	uint16_t *type_list;
}gate_req_t;

extern gate_req_t* allocate_gate_req(uint16_t num);

extern void deallocate_gate_req(gate_req_t **p_gate_req);

extern void set_gate_req_num(gate_req_t *p_gate_req,uint16_t num);

/* gate protocol core status */
#define GATEP_REQ_ID									0x0000
#define GATEP_REQ_DATA_ID								0x0001
#define GATEP_REQ_CANCEL_ID								0x0002

#define GATEP_REQ_SUCCESS_FLAG							0
#define GATEP_REQ_FAILED_REPEAT_FLAG					1

typedef struct
{
	uint32_t src;
	uint32_t dst;
	uint32_t id_num;
	uint32_t *id_list;
}gate_broadcast_t;

extern gate_broadcast_t *allocate_gate_broadcast(uint32_t num);

extern void deallocate_gate_broadcast(gate_broadcast_t **p_gate_bc);

extern void set_gate_broadcast_num(gate_broadcast_t *p_gate_bc,uint32_t id_num);

/* gate protocol broadcast option */
#define GATEP_BROADCAST_ID								0x0100
#define GATEP_BROADCAST_INFORM_ID						0x0101
#define GATEP_BROADCAST_EXIT_ID							0x0102
#define GATEP_BROADCAST_GET_ALL_ID						0x0103


/* parser corectrl protocol definition */
#define GATEP_PARSER_SUCCESS							0
#define GATEP_PARSER_FAILED								1

/* ******************************************************************************
 *	@function:	parser_gatep
 *	@param:		
 *		package: need to parser protocol package
 *	@retval: gate_protocol_t
 *	
 * *******************************************************************************/
extern gate_protocol_t *parser_gatep(const protocol_package *package);

/* ******************************************************************************
 *	@function:	package_gatep
 *	@param:		
 *		protocol need to package protocol structure
 *	@retval:	protocol_package
 *
 * *******************************************************************************/
extern protocol_package *package_gatep(const gate_protocol_t *p_gate);


extern void set_gate_param_num(gate_protocol_t *p_gate,uint16_t param_num);


extern void print_gatep(const gate_protocol_t *p_gate);

#ifdef __cplusplus_
}
#endif



#endif


