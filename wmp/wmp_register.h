/* ************************************************************************
 *       Filename:  wmp_register.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_REGISTER_H_
#define WMP_REGISTER_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define WMP_REQ_REGISTER_PHONE_NUM_LENGTH					14
#define WMP_REQ_REGISTER_EMAIL_LENGTH						320


/* *********************************************************************************************
 * wmp_req_register_t structure.
 *
 * @attr                    wmp_req_register_t attribute.
 * @phone_num               wmp_req_register_t result.
 * @email_addr              wmp_req_register_t result.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint8_t phone_num[WMP_REQ_REGISTER_PHONE_NUM_LENGTH];
	uint8_t email_addr[WMP_REQ_REGISTER_EMAIL_LENGTH];
}wmp_req_register_t;

#define WMP_REQ_REGISTER_MIN_LENGTH							sizeof(uint16_t)+WMP_REQ_REGISTER_PHONE_NUM_LENGTH


/* ***********************************************************************************
 * Create wmp_message_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_req_register_t *create_wmp_req_register();

/* ***********************************************************************************
 * Delete wmp_message_t instance.
 *
 * @param:	p_req_wmp_register     	 wmp_message_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_req_register(wmp_req_register_t **p_req_wmp_register);

/* ***********************************************************************************
 * Parser wmp_message_t.
 *
 * @param:	package                 package pointer.
 * @param:  pack_len                package length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_req_register_t *parser_wmp_req_register(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_message_t.
 *
 * @param:	package                 package pointer.
 * @param:  p_wmp_req_register      wmp_req_register_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_req_register(char *package,const wmp_req_register_t *p_wmp_req_register);

/* ***********************************************************************************
 * Print wmp_message_t.
 *
 * @param:  p_wmp_req_register      wmp_req_register_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_req_register(const wmp_req_register_t *p_wmp_req_register);

/* ***********************************************************************************
 * Copy a new wmp_message_t instance.
 *
 * @param:  p_wmp_req_register      wmp_req_register_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_req_register_t *copy_wmp_req_register(const wmp_req_register_t *p_wmp_req_register);



#define WMP_REGISTER_IDENTIFY_CODE_LENGTH					6


/* *********************************************************************************************
 * wmp_register_t structure.
 *
 * @attr                    wmp_req_register_t attribute.
 * @user_id                 wmp_req_register_t user id.
 * @identify_code           wmp_req_register_t identify id.
 *
 * **********************************************************************************************/
typedef struct
{
	uint16_t attr;
	uint32_t user_id;
	uint8_t identify_code[WMP_REGISTER_IDENTIFY_CODE_LENGTH];
}wmp_register_t;

#define WMP_REGISTER_LENGTH								sizeof(uint16_t)+sizeof(uint32_t)+WMP_REGISTER_IDENTIFY_CODE_LENGTH
#define WMP_REGISTER_RESULT_SUCCESS						0
#define WMP_REGISTER_RESULT_FAILED_PHONE_NUM_USED		1


/* ***********************************************************************************
 * Create wmp_message_t instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_register_t *create_wmp_register();

/* ***********************************************************************************
 * Delete wmp_message_t instance.
 *
 * @param:  p_wmp_req_register      wmp_req_register_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_register(wmp_register_t **p_wmp_register);

/* ***********************************************************************************
 * Parser wmp_message_t instance.
 *
 * @param:  package                 package pointer.
 * @param:  pack_len                package length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_register_t *parser_wmp_register(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_message_t instance.
 *
 * @param:  package                 package pointer.
 * @param:  p_wmp_register          wmp_register_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_register(char *package,const wmp_register_t *p_wmp_register);

/* ***********************************************************************************
 * Print wmp_message_t.
 *
 * @param:  p_wmp_register          wmp_register_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_register(const wmp_register_t *p_wmp_register);

/* ***********************************************************************************
 * Copy a new wmp_message_t instance.
 *
 * @param:  p_wmp_register          wmp_register_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_register_t *copy_wmp_register(const wmp_register_t *p_wmp_register);


#ifdef __cplusplus
}
#endif

#endif
