/* ************************************************************************
 *       Filename:  wmp_register.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_REGISTER_H_
#define WMP_REGISTER_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define WMP_REQ_REGISTER_PHONE_NUM_LENGTH					14
#define WMP_REQ_REGISTER_EMAIL_LENGTH						320

typedef struct
{
	uint16_t attr;
	uint8_t phone_num[WMP_REQ_REGISTER_PHONE_NUM_LENGTH];
	uint8_t email_addr[WMP_REQ_REGISTER_EMAIL_LENGTH];
}wmp_req_register_t;

#define WMP_REQ_REGISTER_MIN_LENGTH							sizeof(uint16_t)+WMP_REQ_REGISTER_PHONE_NUM_LENGTH

WMPSHARED_EXPORT extern wmp_req_register_t *allocate_wmp_req_register();

WMPSHARED_EXPORT extern void deallocate_wmp_req_register(wmp_req_register_t **p_req_wmp_register);

WMPSHARED_EXPORT extern wmp_req_register_t *parser_wmp_req_register(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_req_register(char *package,const wmp_req_register_t *p_wmp_req_register);

WMPSHARED_EXPORT extern void print_wmp_req_register(const wmp_req_register_t *p_wmp_req_register);


#define WMP_REGISTER_IDENTIFY_CODE_LENGTH					6

typedef struct
{
	uint16_t attr;
	uint32_t user_id;
	uint8_t identify_code[WMP_REGISTER_IDENTIFY_CODE_LENGTH];
}wmp_register_t;

#define WMP_REGISTER_LENGTH								sizeof(uint16_t)+sizeof(uint32_t)+WMP_REGISTER_IDENTIFY_CODE_LENGTH
#define WMP_REGISTER_RESULT_SUCCESS						0
#define WMP_REGISTER_RESULT_FAILED_PHONE_NUM_USED		1


WMPSHARED_EXPORT extern wmp_register_t *allocate_wmp_register();

WMPSHARED_EXPORT extern void deallocate_wmp_register(wmp_register_t **p_wmp_register);

WMPSHARED_EXPORT extern wmp_register_t *parser_wmp_register(const char *package,uint32_t pack_len);

WMPSHARED_EXPORT extern uint32_t package_wmp_register(char *package,const wmp_register_t *p_wmp_register);

WMPSHARED_EXPORT extern void print_wmp_register(const wmp_register_t *p_wmp_register);


#ifdef __cplusplus
}
#endif

#endif
