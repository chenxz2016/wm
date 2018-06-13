/* ************************************************************************
 *       Filename:  protocol_crypt.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include<stdio.h>
#include<stdint.h>
#include"tomcrypt.h"
#include"protocol_def.h"
#include"protocol_crypt.h"

prng_state ecc_state;
extern ltc_math_descriptor ltm_mp;
extern const ltc_math_descriptor ltm_desc;
extern const struct ltc_hash_descriptor sha512_desc;

/* ***********************************************************************************
 * Init protocol crypt.
 *
 * @param:	flag	Init parameter.
 *					P_CRYPT_CBC_ALG
 *					P_CRYPT_ECC_ALG
 * @retval:			
 *					P_CRYPT_REGISTER_ERROR
 *					P_CRYPT_SUCCESS
 *
 * ***********************************************************************************/
int protocol_crypt_init(int flag)
{
	if((flag & P_CRYPT_CBC_ALG)==P_CRYPT_CBC_ALG)
	{
		if(register_cipher(&aes_desc)==-1)
			return P_CRYPT_REGISTER_ERROR;
	}
	if((flag & P_CRYPT_ECC_ALG)==P_CRYPT_ECC_ALG)
	{
		yarrow_start(&ecc_state);
		ltc_mp = ltm_desc;
		int ret = register_hash(&sha512_desc);
		if(register_prng(&yarrow_desc)!=CRYPT_OK)
			return P_CRYPT_REGISTER_ERROR;

		if(ret==-1)
			return P_CRYPT_REGISTER_ERROR;

	}
	return P_CRYPT_SUCCESS;
}


/* ***********************************************************************************
 * Generate ECC crypt algorithm.
 *
 * @param:	pub_key		Public key.
 * @param:	pub_key_len	Public key length.
 * @param:	pri_key		Private key length.
 * @param:	pri_key_len	Public key length.
 *
 * @retval:			
 *						P_CRYPT_SUCCESS
 *
 * ***********************************************************************************/
int generate_ecc_key(char *pub_key,unsigned long *pub_key_len,char *pri_key,\
		unsigned long *pri_key_len)
{
	int ret = rng_make_prng(128,find_prng("yarrow"),&ecc_state,NULL);
	if(ret!=CRYPT_OK)
		return ret;

	ecc_key e_key;

	ret = ecc_make_key(&ecc_state,find_prng("yarrow"),20,&e_key);
	if(ret!=CRYPT_OK)
		return ret;

	if(pub_key && pub_key_len)
	{
		ret = ecc_export(pub_key,pub_key_len,PK_PUBLIC,&e_key);
		if(ret!=CRYPT_OK)
			return ret;
	}

	if(pri_key && pri_key_len)
	{
		ret = ecc_export(pri_key,pri_key_len,PK_PRIVATE,&e_key);
		if(ret!=CRYPT_OK)
			return ret;
	}
	return P_CRYPT_SUCCESS;
}

void ecc_encrypt_protocol(protocol_package *src,protocol_package *dst,const char *pub_key,uint16_t key_len)
{}


void ecc_decrypt_protocol(protocol_package *src,protocol_package *dst,const char *pri_key,uint16_t key_len)
{}


/* ***********************************************************************************
 * Encrypt char buffer using ECC crypt algorithm.
 *
 * @param:	src			Source char buffer.
 * @param:	src_len		Source char buffer length.
 * @param:	dst			Destination char buffer.
 * @param:	dst_len		Destination char buffer length.
 * @param:	pub_key		Public key.
 * @param:	key_len		Public key length.
 *
 * @retval:			
 *						P_CRYPT_SUCCESS
 *
 * ***********************************************************************************/
int ecc_encrypt_char_buffer(const char *src,unsigned long src_len,char *dst,\
		unsigned long *dst_len,const char *pub_key,unsigned long key_len)
{
	ecc_key key;
	int ret = ecc_import(pub_key,key_len,&key);
	if(ret!=CRYPT_OK)
		return ret;
	ret = ecc_encrypt_key(src,src_len,dst,dst_len,&ecc_state,find_prng("yarrow"),\
            find_hash("sha512"),&key);
    return ret;
}


/* ***********************************************************************************
 * Decrypt char buffer using ECC decrypt algorithm.
 *
 * @param:	src			Source char buffer.
 * @param:	src_len		Source char buffer length.
 * @param:	dst			Destination char buffer.
 * @param:	dst_len		Destination char buffer length.
 * @param:	pri_key		Private key.
 * @param:	key_len		Private key length.
 *
 * @retval:			
 *						P_CRYPT_SUCCESS
 *
 * ***********************************************************************************/
int ecc_decrypt_char_buffer(const char *src,unsigned long src_len,char *dst,\
		unsigned long *dst_len,const char *pri_key,unsigned long key_len)
{
	ecc_key key;
	int ret = ecc_import(pri_key,key_len,&key);
	if(ret!=CRYPT_OK)
		return ret;
    ret = ecc_decrypt_key(src,src_len,dst,dst_len,&key);
    return ret;
}

/* ***********************************************************************************
 * Generate CBC encrypt alogrithm key.
 *
 * @param:	key			CBC Key.
 * @param:	key_len		CBC Key length.
 *
 * @retval:			
 *						P_CRYPT_SUCCESS
 *
 * ***********************************************************************************/
int generate_cbc_key(unsigned char *key,unsigned long key_len)
{
	uint8_t temp=0;
    for(unsigned long i=0;i<key_len;i++)
	{
		while(temp<33 || temp>126)
			temp = rand()%256;
		key[i]=(unsigned char )temp;
		temp=0;
	}
	key[key_len]='\0';
	return P_CRYPT_SUCCESS;
}

/* ***********************************************************************************
 * Encrypt char buffer using CBC encrypt alogrithm key.
 *
 * @param:	src			Source char buffer.
 * @param:	src_len		Source char buffer length.
 * @param:	dst			Destination char buffer.
 * @param:	dst_len		Destination char buffer length.
 * @param:	key			CBC crypt key.
 * @param:	key_len		CBC crypt Key length.
 *
 * @retval:		
 *						P_CRYPT_DESC_ERROR
 *						P_CRYPT_KEY_ERROR
 *						P_CRYPT_SUCCESS
 *
 * ***********************************************************************************/
int cbc_encrypt_char_buffer(const char *src,unsigned long src_len,char *dst,\
		unsigned long *dst_len,const char *key,unsigned long key_len)
{
	symmetric_CBC cbc_aes = {0};
	int index = find_cipher("aes");
	if(index==-1)
		return P_CRYPT_DESC_ERROR;
	if(key_len<2 || key_len%2)
		return P_CRYPT_KEY_ERROR;
	unsigned char *iv = (unsigned char *)key;
	unsigned char *cbc_key = (unsigned char *)(key+key_len/2);
	int ret = cbc_start(index,iv,cbc_key,key_len/2,0,&cbc_aes);
	if(ret!=CRYPT_OK)
		return ret;

    unsigned int block_num = src_len/(key_len/2);
    unsigned int block_size = key_len/2;
	(*dst_len) = 0;
    for(unsigned int i=0;i<block_num;i++)
	{
		ret = cbc_encrypt(src+i*block_size,dst+i*block_size,block_size,&cbc_aes);
		if(ret!=CRYPT_OK)
			return ret;
		(*dst_len) += block_size;
	}
	if(src_len>(block_size*block_num))
	{
		char p_buf[16]="";
		memcpy(p_buf,src+block_num*block_size,src_len-block_num*block_size);
		ret = cbc_encrypt(p_buf,dst+block_num*block_size,block_size,&cbc_aes);
		(*dst_len) += block_size;
		if(ret!=CRYPT_OK)
			return ret;
	}
	return P_CRYPT_SUCCESS;
}

/* ***********************************************************************************
 * Decrypt char buffer using CBC encrypt alogrithm key.
 *
 * @param:	src			Source char buffer.
 * @param:	src_len		Source char buffer length.
 * @param:	dst			Destination char buffer.
 * @param:	dst_len		Destination char buffer length.
 * @param:	key			CBC decrypt key.
 * @param:	key_len		CBC decrypt Key length.
 *
 * @retval:		
 *						P_CRYPT_DESC_ERROR
 *						P_CRYPT_KEY_ERROR
 *						P_CRYPT_SUCCESS
 *
 * ***********************************************************************************/
int cbc_decrypt_char_buffer(const char *src,unsigned long src_len,char *dst,\
		unsigned long *dst_len,const char *key,unsigned long key_len)
{
	symmetric_CBC cbc_aes = {0};
	int index = find_cipher("aes");
	if(index==-1)
		return P_CRYPT_DESC_ERROR;
	if(key_len<2 || key_len%2)
		return P_CRYPT_KEY_ERROR;
	unsigned char *iv = (unsigned char *)key;
	unsigned char *cbc_key = (unsigned char *)(key+key_len/2);
	int ret = cbc_start(index,iv,cbc_key,key_len/2,0,&cbc_aes);
	if(ret!=CRYPT_OK)
		return ret;

    unsigned int block_num = src_len/(key_len/2);
    unsigned int block_size = key_len/2;
	(*dst_len) = 0;
    for(unsigned int i=0;i<block_num;i++)
	{
		ret = cbc_decrypt(src+i*block_size,dst+i*block_size,block_size,&cbc_aes);
		if(ret!=CRYPT_OK)
			return ret;
		(*dst_len) += block_size;
	}
	if(src_len>block_size*block_num)
	{
		char p_buf[16]="";
		memcpy(p_buf,src+block_num*block_size,src_len-block_num*block_size);
		ret = cbc_decrypt(p_buf,dst+block_num*block_size,block_size,&cbc_aes);
		(*dst_len) += block_size;
		if(ret!=CRYPT_OK)
			return ret;
	}
	return P_CRYPT_SUCCESS;
}


