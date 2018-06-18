/* ************************************************************************
 *       Filename:  wmp_login.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_LOGIN_H_
#define WMP_LOGIN_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define WMP_LOGIN_PWD_LENGTH						128


/* *********************************************************************************************
 * Walking Message protocol login.
 * @attr			Walking Message login attribute.
 * @result			Walking Message login result.
 * @user_id			Walking Message login user id.
 * @password		Walking Message login password.
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

/* Allocate wmp_login_t. */
WMPSHARED_EXPORT extern wmp_login_t *allocate_wmp_login();

/* Deallocate wmp_login_t. */
WMPSHARED_EXPORT extern void deallocate_wmp_login(wmp_login_t **p_wmp_login);

/* Parser wmp_login_t package. */
WMPSHARED_EXPORT extern wmp_login_t *parser_wmp_login(const char *package,uint32_t pack_len);

/* Package wmp_login_t package. */
WMPSHARED_EXPORT extern uint32_t package_wmp_login(char *package,const wmp_login_t *p_wmp_login);

/* Print wmp_login_t. */
WMPSHARED_EXPORT extern void print_wmp_login(wmp_login_t *p_wmp_login);




#define WMP_KEY_LENGTH							255

#define WMP_LOGIN_KEY_PUBLIC                    1
#define WMP_LOGIN_KEY_PRIVATE                   2

/* *********************************************************************************************
 * Walking Message protocol login key.
 * @attr			Walking Message login attribute.
 * @result			Walking Message login result.
 * @user_id			Walking Message login user id.
 * @type			Walking Message login type.
 * @key_len 		Walking Message login key length.
 * @key      		Walking Message login key.
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


/* Allocate wmp_login_key_t. */
WMPSHARED_EXPORT extern wmp_login_key_t *allocate_wmp_login_key();

/* Deallocate wmp_login_key_t. */
WMPSHARED_EXPORT extern void deallocate_wmp_login_key(wmp_login_key_t **p_wmp_login_key);

/* Parser wmp_login_key_t package. */
WMPSHARED_EXPORT extern wmp_login_key_t *parser_wmp_login_key(const char *package,uint32_t pack_len);

/* Package wmp_login_key_t package. */
WMPSHARED_EXPORT extern uint32_t package_wmp_login_key(char *package,const wmp_login_key_t *p_wmp_login_key);

/* Print wmp_login_key_t. */
WMPSHARED_EXPORT extern void print_wmp_login_key(wmp_login_key_t *p_wmp_login_key);



#ifdef __cplusplus
}
#endif

#endif

