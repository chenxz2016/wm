/* ************************************************************************
 *       Filename:  cc_protocol.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef CC_PROTOCOL_H_
#define CC_PROTOCOL_H_

#ifdef __cplusplus_
extern "C"
{
#endif

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#define CCP_TYPE_INT8_ID							1
#define CCP_TYPE_UINT8_ID							2
#define CCP_TYPE_INT16_ID							3
#define CCP_TYPE_UINT16_ID							4
#define CCP_TYPE_INT32_ID							5
#define CCP_TYPE_UINT32_ID							6
#define CCP_TYPE_INT64_ID							7
#define CCP_TYPE_UINT64_ID							8
#define CCP_TYPE_BYTEARRAY_ID						9
#define CCP_TYPE_STRING_ID							10
#define CCP_TYPE_BCD_ID								11
#define CCP_TYPE_CUSTOM_ID							12



/* **********************************************************************************************
 *	cc_parameter_t structure.
 *
 *	@id:				parameter id.
 *	@length:			parameter data length.
 *	@data:				parameter data, max 256 bytes.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t id;
	char program[256];
	char param[256];
	uint32_t result;
	uint32_t pid;
	uint8_t ctrl_cmd;
}cc_parameter_t;



/* **********************************************************************************************
 *	core control parameter note.
 *
 *	-l:			load service.
 *	-ul:		unload service.
 *	-c:			control core status.
 *				1. stop
 *				2. pause
 *				3. start
 *	-st:		get start time.	if parameter data is 0,means get core start time.
 *	-cn:		get client num.
 *
 *	example:
 *	-l program param/result
 *	-ul pid result
 *	-c stop pid result
 *	-c pause pid result
 *	-c start pid result
 *	-st pid result
 *	-cn result
 *
 *	-g shm/sn
 *
 * **********************************************************************************************/


/* -l load service. */
#define CCP_REQ_LOAD_ID								1
#define CCP_RES_LOAD_ID								2

/* -ul unload service */
#define CCP_REQ_UNLOAD_ID							3
#define CCP_RES_UNLOAD_ID							4

/* -c control core */
#define CCP_REQ_CONTROL_ID							5
#define CCP_RES_CONTROL_ID							6

/* -st get start time */ 
#define CCP_REQ_START_TIME_ID						7
#define CCP_RES_START_TIME_ID						8

/* -cn get client num. */
#define CCP_REQ_CLIENT_ID							9
#define CCP_RES_CLIENT_ID							10

#define CTRL_CMD_NUM								5

typedef enum
{
	Load=0,
	Unload,
	Stop,
	Pause,
	Start,
	None
}ctrl_cmd;

/* **********************************************************************************************
 *	cc_protocol_t structure.
 *
 *	@param_num:			protocol parameter numbers.
 *	@param:				protocol parameter list pointer.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t param_num;
	cc_parameter_t *param;
}cc_protocol_t;


/* Allocate cc_protocol_t structure. */
extern cc_protocol_t *allocate_ccp(uint8_t num);

/* Deallocate cc_protocol_t structure. */
extern void deallocate_ccp(cc_protocol_t **p_cc);

/* Set cc_protocol_t parameter numbers. */
extern void set_ccp_param_num(cc_protocol_t *p_cc,uint8_t num);

/* Parser cc_protocol_t. */
extern cc_protocol_t *parser_ccp(const protocol_package *package);

/* Package cc_protocol_t. */
extern protocol_package *package_ccp(const cc_protocol_t *p_cc);

/* Set cc_parameter_t data. */
extern void set_ccp_parameter(cc_parameter_t *param,uint16_t id,const char *program,\
		const char *p,uint32_t result,uint32_t pid,uint8_t ctrl_cmd);

/* Print cc_protocol_t. */
extern void print_ccp(const cc_protocol_t *p_cc);



#ifdef __cplusplus_
}
#endif



#endif


