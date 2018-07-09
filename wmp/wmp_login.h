/* ************************************************************************
 *       Filename:  wmp_login.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_LOGIN_H_
#define WMP_LOGIN_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define WMP_LOGIN_PWD_LENGTH						128


/* *********************************************************************************************
 * wmp_login_t structure.
 * @attr                    wmp_login_t attribute.
 * @result                  wmp_login_t result.
 * @user_id                 wmp_login_t user id.
 * @password                wmp_login_t password.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint8_t result;
	uint32_t user_id;
	uint8_t pwd_len;
	uint8_t password[WMP_LOGIN_PWD_LENGTH];
}wmp_login_t;

#define WMP_LOGIN_LENGTH							7
#define WMP_LOGIN_RESULT_SUCCESS					0
#define WMP_LOGIN_RESULT_FAILED_ERROR_PWD			1
#define WMP_LOGIN_RESULT_FAILED_ERROR_ID			2
#define WMP_LOGIN_RESULT_FAILED_LOGINED				3
#define WMP_LOGIN_RESULT_FAILED_SERVER_ERROR		4

#define WMP_LOGIN_STATUS_ONLINE						0
#define WMP_LOGIN_STATUS_LEAVE						1
#define WMP_LOGIN_STATUS_BUSSY						2
#define WMP_LOGIN_STATUS_INVISIBLE					3
#define WMP_LOGIN_STATUS_NOTALK						4


#define WMP_LoginCS(p_wmp_login) 					(p_wmp_login->attr & 1) 
#define WMP_LoginResult(p_wmp_login) 				(p_wmp_login->result)
#define WMP_LoginPassword(p_wmp_login)				(p_wmp_login->password)
#define WMP_LoginUserID(p_wmp_login) 				(p_wmp_login->user_id)


#define WMP_LoginSetCTS(p_wmp_login) 				(p_wmp_login->attr |= 1)
#define WMP_LoginSetSTC(p_wmp_login) 				(p_wmp_login->attr &= ~(1 << 1))
#define WMP_LoginSetResult(p_wmp_login,r)           (p_wmp_login->result = r)
#define WMP_LoginSetPassword(p_wmp_login,pwd,len) \
	(p_wmp_login)->pwd_len = len;\
	memcpy((p_wmp_login)->password,pwd,len);

#define WMP_LoginSetUserID(p_wmp_login,id)			(p_wmp_login->user_id = id);

/* ***********************************************************************************
 * Create a new wmp_login_t instance.
 *
 * @param:	p_wmp_login	wmp_login_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_login_t *create_wmp_login();

/* ***********************************************************************************
 * Delete wmp_login_t instance.
 *
 * @param:	p_wmp_login		The pointer of wmp_login_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_login(wmp_login_t **p_wmp_login);

/* ***********************************************************************************
 * Parser wmp_login_t package.
 *
 * @param:	package			Package buffer.
 * @param:	pack_len		Package buffer length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_login_t *parser_wmp_login(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_login_t package.
 *
 * @param:	package			Package buffer.
 * @param:	p_wmp_login		wmp_login_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_login(char *package,const wmp_login_t *p_wmp_login);

/* ***********************************************************************************
 * Print wmp_login_t package.
 *
 * @param:	p_wmp_login		wmp_login_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_login(const wmp_login_t *p_wmp_login);

/* ***********************************************************************************
 * Copy wmp_login_t a new instance.
 *
 * @param:	p_wmp_login		wmp_login_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_login_t *copy_wmp_login(const wmp_login_t *p_wmp_login);




#define WMP_KEY_LENGTH							255

#define WMP_LOGIN_KEY_PUBLIC                    1
#define WMP_LOGIN_KEY_PRIVATE                   2

/* *********************************************************************************************
 * wmp_login_key_t structure.
 * @attr                    wmp_login_key_t attribute.
 * @result                  wmp_login_key_t result.
 * @user_id                 wmp_login_key_t user id.
 * @type                    wmp_login_key_t type.
 * @key_len                 wmp_login_key_t key length.
 * @key                     wmp_login_key_t login key.
 *
 * **********************************************************************************************/
typedef struct
{
    uint8_t attr;
    uint8_t result;
    uint32_t user_id;
    uint8_t type;
    uint8_t key_len;
    uint8_t key[WMP_KEY_LENGTH];
}wmp_login_key_t;


/* ***********************************************************************************
 * Create wmp_login_key_t instance.
 *
 * @retval:	p_wmp_login_key		wmp_login_key_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_login_key_t *create_wmp_login_key();

/* ***********************************************************************************
 * Delete wmp_login_key_t package.
 *
 * @param:	p_wmp_login_key		wmp_login_key_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wmp_login_key(wmp_login_key_t **p_wmp_login_key);

/* ***********************************************************************************
 * Parser wmp_login_key_t package.
 *
 * @param:	package		raw package.
 * @param:	pack_len	package length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_login_key_t *parser_wmp_login_key(const char *package,uint32_t pack_len);

/* ***********************************************************************************
 * Package wmp_login_key_t package.
 *
 * @param:	package		package.
 * @param:	p_wmp_login_key	 wm_login_key_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN uint32_t package_wmp_login_key(char *package,const wmp_login_key_t *p_wmp_login_key);

/* ***********************************************************************************
 * Parser wmp_login_key_t package.
 *
 * @param:	p_wmp_login_key	 wm_login_key_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wmp_login_key(const wmp_login_key_t *p_wmp_login_key);

/* ***********************************************************************************
 * Copy wmp_login_key_t a new instance.
 *
 * @param:	p_wmp_login_key	 wm_login_key_t pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wmp_login_key_t *copy_wmp_login_key(const wmp_login_key_t *p_wmp_login_key);


#ifdef __cplusplus
}
#endif

#endif
