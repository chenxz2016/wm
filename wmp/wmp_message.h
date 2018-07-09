/* ************************************************************************
 *       Filename:  wmp_message.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_MESSAGE_H_
#define WMP_MESSAGE_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif


/* *********************************************************************************************
 * wmp_message_t structure.
 *
 * @attr                    wmp_message_t attribute.
 * @result                  wmp_message_t result.
 * @src                     wmp_message_t result.
 * @dst                     wmp_message_t result.
 * @msg_len                 wmp_message_t user id.
 * @msg                     wmp_message_t password.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint8_t result;
	uint32_t src;
	uint32_t dst;
	uint32_t msg_len;
	uint8_t *msg;
}wmp_message_t;

#define WMP_MESSAGE_LENGTH								sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint8_t)

#define WMP_MSG_PTG										1 
#define WMP_MSG_PTP										2
#define WMP_MSG_PTT										3
#define WMP_MSG_PTTS									4

#define WMP_MsgAttr(p_wmp_msg)                          (p_wmp_msg->attr)
#define WMP_MsgResult(p_wmp_msg)						(p_wmp_msg->result)
#define WMP_MsgSrc(p_wmp_msg) 							(p_wmp_msg->src)
#define WMP_MsgDst(p_wmp_msg) 							(p_wmp_msg->dst)
#define WMP_MsgLen(p_wmp_msg) 							(p_wmp_msg->msg_len)
#define WMP_Msg(p_wmp_msg) 								(p_wmp_msg->msg)

#define WMP_MsgSetAttr(p_wmp_msg,a)                     (p_wmp_msg->attr = a)
#define WMP_MsgSetResult(p_wmp_msg)                     (p_wmp_msg->result = r)
#define WMP_MsgSetSrc(p_wmp_msg,id) 					(p_wmp_msg->src = id)
#define WMP_MsgSetDst(p_wmp_msg,id) 					(p_wmp_msg->dst = id)

/* ***********************************************************************************
 * Create wmp_message_t instance.
 *
 * @param:	msg_len     	 wmp_message_t message length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_message_t *create_wmp_message(uint32_t msg_len);

/* ***********************************************************************************
 * Delete wmp_message_t instance.
 *
 * @param:	p_wmp_login_key	 The pointer of wmp_message_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_message(wmp_message_t **p_wmp_msg);

/* ***********************************************************************************
 * Parser wmp_message_t.
 *
 * @param:	p_wmp_login_key	 The pointer of wmp_message_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_message_t *parser_wmp_message(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_message_t.
 *
 * @param:	p_wmp_login_key	 The pointer of wmp_message_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_message(char *package,const wmp_message_t *p_wmp_msg);

/* ***********************************************************************************
 * Set wmp_message_t message length.
 *
 * @param:	p_wmp_login_key	 The pointer of wmp_message_t pointer.
 * @param:  msg_len          Message length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wmp_message_len(wmp_message_t *p_wmp_msg,uint32_t msg_len);

/* ***********************************************************************************
 * Set wmp_message_t message length.
 *
 * @param:	p_wmp_login_key	 The pointer of wmp_message_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_message(const wmp_message_t *p_wmp_msg);

/* ***********************************************************************************
 * Copy a new wmp_message_t instance.
 *
 * @param:	p_wmp_login_key	 The pointer of wmp_message_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_message_t *copy_wmp_message(const wmp_message_t *p_wmp_msg);

#ifdef __cplusplus
}
#endif

#endif
