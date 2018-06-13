/* ************************************************************************
 *       Filename:  protocol_crypt.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef PROTOCOL_CRYPT_H_
#define PROTOCOL_CRYPT_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif


#define P_CRYPT_SUCCESS								0
#define P_CRYPT_REGISTER_ERROR						0x0101
#define P_CRYPT_DESC_ERROR							0x0102
#define P_CRYPT_KEY_ERROR							0x0103

#define P_CRYPT_CBC_ALG								1
#define P_CRYPT_ECC_ALG								2


/* Encrypt char buffer. */
WMPSHARED_EXPORT extern int ecc_encrypt_char_buffer(const char *src,unsigned long src_len,char *dst,\
		unsigned long *dst_len,const char *pub_key,unsigned long key_len);


/* Dencrypt char buffer. */
WMPSHARED_EXPORT extern int ecc_decrypt_char_buffer(const char *src,unsigned long src_len,char *dst,\
		unsigned long *dst_len,const char *pri_key,unsigned long key_len);


/* Generate ECC key. */
WMPSHARED_EXPORT extern int generate_ecc_key(char *pub_key,unsigned long *pub_key_len,char *pri_key,\
		unsigned long *pri_key_len);

/* Init protocol crypt. */
WMPSHARED_EXPORT extern int protocol_crypt_init(int flag);


/* Generate cbc key. */
WMPSHARED_EXPORT extern int generate_cbc_key(unsigned char *key,unsigned long key_len);

/* Encrypt char buffer by cbc. */
WMPSHARED_EXPORT extern int cbc_encrypt_char_buffer(const char *src,unsigned long src_len,char *dst,\
		unsigned long *dst_len,const char *key,unsigned long key_len);

/* Dencrypt char buffer by cbc. */
WMPSHARED_EXPORT extern int cbc_decrypt_char_buffer(const char *src,unsigned long src_len,char *dst,\
		unsigned long *dst_len,const char *key,unsigned long key_len);




#ifdef __cplusplus
}
#endif


#endif


