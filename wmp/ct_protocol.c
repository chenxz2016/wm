/* ************************************************************************
 *       Filename:  ct_protocol.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/


#include"protocol_def.h"
#include"protocol_error.h"
#include"ct_protocol.h"
#include"protocol_crypt.h"
#include<string.h>
#include<malloc.h>

#define CTP_PARSER_FAILED							0

#define CTP_CheckLen(index,delt,len) \
	if((index+delt)>len)\
		return CTP_PARSER_FAILED;

extern void set_protocol_error(int err_flag);

/* ***************************************************************************************
 * Allocate ct_protocol_t structure.
 *
 * @param:	num		ct_protocol_t parameter numbers.
 *
 * @retval:	p_ct	ct_protocol_t pointer.
 *
 * ***************************************************************************************/
ct_protocol_t *allocate_ctp(uint16_t num)
{
	ct_protocol_t *p_ct = (ct_protocol_t *)malloc(sizeof(ct_protocol_t));
	memset(p_ct,0,sizeof(ct_protocol_t));
	if(num)
	{
		p_ct->param_num = num;
		p_ct->param = (ct_parameter_t *)malloc(sizeof(ct_parameter_t)*num);
		memset(p_ct->param,0,sizeof(ct_parameter_t)*num);
	}
	return p_ct;
}

/* ***************************************************************************************
 * Deallocate ct_protocol_t structure.
 *
 * @param:	p_cc	cc_protocol_t pointer.
 *
 * ***************************************************************************************/
void deallocate_ctp(ct_protocol_t **p_ct)
{
	if(p_ct && (*p_ct) && (*p_ct)->param)
	{
		free((*p_ct)->param);
		(*p_ct)->param = 0;
		free(*p_ct);
		(*p_ct) = 0;
		return ;
	}
	if(p_ct && (*p_ct))
	{
		free(*p_ct);
		(*p_ct) = 0;
	}
}

/* ***************************************************************************************
 * Set ct_protocol_t parameter numbers.
 *
 * @param:	p_ct	ct_protocol_t pointer.
 * @param:	num		ct_protocol_t parameter numbers.
 *
 * ***************************************************************************************/
void set_ctp_param_num(ct_protocol_t *p_ct,uint8_t num)
{
	if(!p_ct || !num)	
		return ;

	if(p_ct->param)
		free(p_ct->param);

	p_ct->param_num = num;
	p_ct->param = (ct_parameter_t *)malloc(sizeof(ct_parameter_t)*num);
	memset(p_ct->param,0,sizeof(ct_parameter_t)*num);
}

/* ***************************************************************************************
 * Copy ct_protocol_t structure.
 *
 * @param:	p_ct_src	ct_protocol_t pointer.
 * @param:	flag		Copy flag.
 *
 * @retval:	p_ct_dst	new ct_protocol_t.
 *
 * ***************************************************************************************/
ct_protocol_t* copy_ctp(ct_protocol_t *p_ct_src,int flag)
{
	if(!p_ct_src)
		return NULL;

	ct_protocol_t *p_ct_dst = (ct_protocol_t *)malloc(sizeof(ct_protocol_t));

	memcpy(p_ct_dst,p_ct_src,sizeof(ct_protocol_t));

	if((flag & CTP_COPY_ALL_FLAG) == CTP_COPY_EXCLUDE_PARAM_FLAG)
	{
		p_ct_dst->param_num = 0;
		p_ct_dst->param = 0;
		return p_ct_dst;
	}

	if(!p_ct_dst->param_num)
	{
		p_ct_dst->param_num = 0;
		p_ct_dst->param = 0;
		return p_ct_dst;
	}

	p_ct_dst->param = (ct_parameter_t *)malloc(sizeof(ct_parameter_t)*p_ct_dst->param_num);
	memcpy(p_ct_dst->param,p_ct_src->param,sizeof(ct_parameter_t)*p_ct_dst->param_num);
	
	if((flag & CTP_COPY_ALL_FLAG) == CTP_COPY_EXCLUDE_SEQUENCE_FLAG)
		p_ct_dst->sequence = 0;
	
	if((flag & CTP_COPY_ALL_FLAG) == CTP_COPY_EXCLUDE_LENGTH_FLAG)
		p_ct_dst->length = 0;	
	
	if((flag & CTP_COPY_ALL_FLAG) == CTP_COPY_EXCLUDE_CHECK_SUM_FLAG)
		p_ct_dst->check_sum = 0;		
	
	if((flag & CTP_COPY_ALL_FLAG) == CTP_COPY_EXCLUDE_ENCRYPT_FLAG)
		p_ct_dst->attr = 0;		

	if((flag & CTP_COPY_ALL_FLAG) == CTP_COPY_EXCLUDE_SRC_FLAG)
		p_ct_dst->src = 0;

	if((flag & CTP_COPY_ALL_FLAG) == CTP_COPY_EXCLUDE_DST_FLAG)
		p_ct_dst->dst = 0;
	
	if((flag & CTP_COPY_ALL_FLAG) == CTP_COPY_EXCLUDE_DST_FLAG)
		p_ct_dst->main_id = 0;
	
	return p_ct_dst;
}

/* ***************************************************************************************
 * Check ct_protocol_t package head and tail.
 *
 * @param:	package		ct_protocol_t protocol package.
 *
 * @retval:	CTP_PARSER_ERR_HEAD_OR_TAIL
 *						decrypt parameter success.
 * @retval CTP_PARSER_FAILED
 *						decrypt parameter failed.
 *
 * ***************************************************************************************/
static int check_head_tail(const protocol_package *package,ct_protocol_t *p_ct)
{
	if((unsigned char)*(package->data)!=CTP_HEAD_ID ||
	   (unsigned char)*(package->data+package->length-1) != CTP_TAIL_ID)
		return CTP_PARSER_FAILED;
	p_ct->head = CTP_HEAD_ID;
	p_ct->tail = CTP_TAIL_ID;
	return CTP_PARSER_SUCCESS;
}

/* ***************************************************************************************
 * Parser ct_protocol_t head.
 *
 * @param:	p_ct		ct_protocol_t pointer.
 * @param:	package		ct_protocol_t protocol package.
 *
 * ***************************************************************************************/
static uint16_t parser_head(ct_protocol_t *p_ct,const protocol_package *package)
{
	uint16_t index = 1;
	CTP_CheckLen(index,CTP_PARAM_INDEX,package->length)

	p_ct->check_sum = ntohl(*(uint32_t *)(package->data+index));
	index += 4;
	p_ct->sequence = ntohl(*(uint32_t *)(package->data+index));
	index += 4;
	p_ct->length = ntohs(*(uint16_t *)(package->data+index));
	index += 2;
	p_ct->attr = ntohs(*(uint16_t *)(package->data+index));
	index+=2;
	p_ct->src = ntohl(*(uint32_t *)(package->data+index));
	index += 4;
	p_ct->dst = ntohl(*(uint32_t *)(package->data+index));
	index += 4;
	p_ct->main_id = ntohs(*(uint16_t *)(package->data+index));
	index += 2;
	p_ct->param_num = *(package->data+index);
	index++;

	return index;
}

/* ***************************************************************************************
 * Parser ct_protocol_t parameter.
 *
 * @param:	p_ct		ct_protocol_t pointer.
 * @param:	package		ct_protocol_t protocol package.
 *
 * @retval:	index		Parser parameter length.
 * @retval:	CTP_PARSER_FAILED
 *
 * ***************************************************************************************/
static uint16_t parser_ctp_param(const char *buffer,uint16_t pack_len,ct_protocol_t *p_ct)
{
	uint16_t index = 0;
	for(uint16_t i=0;i<p_ct->param_num;i++)
	{
		CTP_CheckLen(index,4,pack_len)

		p_ct->param[i].id = ntohs(*(uint16_t *)(buffer+index));
		index += 2;
		p_ct->param[i].type = *(buffer+index);
		index++;
		p_ct->param[i].length = *(buffer+index);
		index++;

		CTP_CheckLen(index,p_ct->param[i].length,pack_len)

		uint16_t *ptr16 = NULL;
		uint32_t *ptr32 = NULL;
		uint64_t *ptr64 = NULL;
		float *ptr_f = NULL;
		double *ptr_d = NULL;
		switch(p_ct->param[i].type)
		{
			case CTP_TYPE_UINT8_ID:
			case CTP_TYPE_INT8_ID:
			case CTP_TYPE_CHAR_ID:
				p_ct->param[i].data[0] = *(buffer+index);
				index++;
				break;
			case CTP_TYPE_UINT16_ID:
			case CTP_TYPE_INT16_ID:
				ptr16 = (uint16_t *)p_ct->param[i].data;
				*ptr16 = ntohs(*(uint16_t *)(buffer+index));
				index+=2;
				break;
			case CTP_TYPE_UINT32_ID:
			case CTP_TYPE_INT32_ID:
				ptr32 = (uint32_t *)p_ct->param[i].data;
				*ptr32 = ntohs(*(uint32_t *)(buffer+index));
				index+=4;
				break;
			case CTP_TYPE_UINT64_ID:
			case CTP_TYPE_INT64_ID:
				ptr64 = (uint64_t *)p_ct->param[i].data;
				*ptr64 = *(uint64_t *)(buffer+index);
				index+=8;
				break;
			case CTP_TYPE_FLOAT_ID:
				ptr_f = (float *)p_ct->param[i].data;
				*ptr_f = *(float *)(buffer+index);
				index+=4;
				break;
			case CTP_TYPE_DOUBLE_ID:
				ptr_d = (double *)p_ct->param[i].data;
				*ptr_d = *(double *)(buffer+index);
				index+=8;
				break;
			case CTP_TYPE_STRING_ID:
			case CTP_TYPE_BYTEARRAY_ID:
			case CTP_TYPE_BCD_ID:
				memcpy(p_ct->param[i].data,buffer+index,p_ct->param[i].length);
				index+=p_ct->param[i].length;
				break;
			default:
				memcpy(p_ct->param[i].data,buffer+index,p_ct->param[i].length);
				index+=p_ct->param[i].length;
				break;
		}
	}

	return index;
}

/* ***********************************************************************************
 *	Parser control protocol.
 *
 *	@param:		package:	Control protocol package 
 *
 *	@retval:	p_ct		Parser success. The pointer of ct_protocol_t.
 *	@retval:	NULL		Parser failed.
 *
 * ***********************************************************************************/
ct_protocol_t* parser_ctp(const protocol_package *package,const char *key,uint16_t key_len)
{
	char buffer[1024*64]="";
	uint16_t len;
	if(!package)
	{
#ifdef CTP_DEBUG
		printf("[CTP] package is null.\n");
#endif
		set_protocol_error(CTP_FAILED_INVALID_PTR);
		return NULL;
	}

	ct_protocol_t *p_ct = allocate_ctp(0);

	int ret = check_head_tail(package,p_ct);
	if(ret==CTP_PARSER_FAILED)
	{
#ifdef CTP_DEBUG
		printf("[CTP] check head tail error.\n");
#endif
		set_protocol_error(CTP_FAILED_HEAD_TAIL_ERR);
		deallocate_ctp(&p_ct);
		return NULL;
	}

	ret = parser_head(p_ct,package);
	if(ret==CTP_PARSER_FAILED)
	{
#ifdef CTP_DEBUG
		printf("[CTP] parser head error.\n");
#endif
		set_protocol_error(CTP_FAILED_PARSER_HEAD_ERR);
		deallocate_ctp(&p_ct);
		return NULL;
	}

	if(CTP_CRC32Flag(p_ct))
	{
		uint32_t crc = crc32_check_char_buffer(package->data+CTP_PARAM_INDEX,package->length-CTP_PARAM_INDEX-1);
		if(crc!=p_ct->check_sum)
		{
#ifdef CTP_DEBUG
			printf("[CTP] crc32 check failed,check sum:%d,crc32:%d.\n",p_ct->check_sum,crc);
#endif
			set_protocol_error(CTP_FAILED_CRC_CHECK_ERR);
			deallocate_ctp(&p_ct);
			return NULL;
		}
	}

	if(CTP_CryptFlag(p_ct))
	{
		ret = cbc_decrypt_char_buffer(package->data+CTP_PARAM_INDEX,package->length-CTP_PARAM_INDEX-1,\
									  buffer,(unsigned long *)&len,key,key_len);
		if(ret!=P_CRYPT_SUCCESS)
		{
#ifdef CTP_DEBUG
			printf("[CTP] parser failed, decrypt failed,ret:%d\n",ret);
#endif
			deallocate_ctp(&p_ct);
			set_protocol_error(CTP_FAILED_DECRYPT_ERR);
			return NULL;
		}

		set_ctp_param_num(p_ct,p_ct->param_num);
		ret = parser_ctp_param(buffer,len,p_ct);
		if(ret==CTP_PARSER_FAILED)
		{
#ifdef CTP_DEBUG
			printf("[CTP] parser param error.num:%d\n",p_ct->param_num);
#endif
			set_protocol_error(CTP_FAILED_LENGTH_ERR);
			deallocate_ctp(&p_ct);
			return NULL;
		}
		return p_ct;
	}

	set_ctp_param_num(p_ct,p_ct->param_num);
	ret = parser_ctp_param(package->data+CTP_PARAM_INDEX,package->length-CTP_PARAM_INDEX,p_ct);
	if(ret==CTP_PARSER_FAILED)
	{
#ifdef CTP_DEBUG
		printf("[CTP] parser param error.num:%d\n",p_ct->param_num);
#endif
		set_protocol_error(CTP_FAILED_LENGTH_ERR);
		deallocate_ctp(&p_ct);
		return NULL;
	}

	return p_ct;
}


/* ***********************************************************************************
 *	Package control protocol.
 *
 *	@param:		buffer		package buffer.
 *	@param:		p_ct		Control protocol.
 *
 *	@retval:	index		package index.
 *
 * ***********************************************************************************/
static uint16_t package_head(char *buffer,const ct_protocol_t *p_ct)
{
	uint16_t index = 0;
	*(uint8_t *)(buffer+index) = p_ct->head;
	index++;
	*(uint32_t *)(buffer+index) = htonl(p_ct->check_sum);
	index+=4;
	*(uint32_t *)(buffer+index) = htonl(p_ct->sequence);
	index+=4;
	*(uint16_t *)(buffer+index) = htons(p_ct->length);
	index+=2;
	*(uint16_t *)(buffer+index) = htons(p_ct->attr);
	index+=2;
	*(uint32_t *)(buffer+index) = htonl(p_ct->src);
	index+=4;
	*(uint32_t *)(buffer+index) = htonl(p_ct->dst);
	index+=4;
	*(uint16_t *)(buffer+index) = htons(p_ct->main_id);
	index+=2;
	*(uint8_t *)(buffer+index) = p_ct->param_num;
	index++;
	return index;
}


/* ***********************************************************************************
 * Package ct_protocol_t parameter.
 *
 * @param:	buffer		package buffer.
 * @param:	p_ct		ct_protocol_t pointer.
 *		
 * @retval: index		package index.
 *
 * ***********************************************************************************/
static uint16_t package_param(char *buffer,const ct_protocol_t *p_ct)
{
	uint16_t index = 0;

	for(int i=0;i<p_ct->param_num;i++)
	{
		*(uint16_t *)(buffer+index) = htons(p_ct->param[i].id);
		index+=2;
		*(uint8_t *)(buffer+index) = p_ct->param[i].type;
		index++;
		*(uint8_t *)(buffer+index) = p_ct->param[i].length;
		index++;
		memcpy(buffer+index,p_ct->param[i].data,p_ct->param[i].length);
		index+=p_ct->param[i].length;
	}
	return index;
}


/* ***********************************************************************************
 * Package ct_protocol_t.
 *
 * @param:	p_ct		ct_parameter_t pointer.
 * @param:	key			encrypt key.
 * @param:	key_len		encrypt key length.
 *		
 * @retval: package		ct_protocol_t protocol_package.
 *
 * ***********************************************************************************/
protocol_package *package_ctp(const ct_protocol_t *p_ct,const char *key,uint16_t key_len)
{
	int ret = 0;
	volatile uint16_t uc_index = 0;
	char uc_buffer[1024]="";
	uint16_t nc_index = 0;
	char nc_buffer[1024]="";

	uint16_t crypt_len = 0;
	char crypt_buffer[1024]="";
	uint32_t *crc_ptr = NULL;

	if(!p_ct)
	{
#ifdef CTP_DEBUG
		printf("[CTP] p_ct is null.\n");
#endif
		set_protocol_error(CTP_FAILED_INVALID_PTR);
		return NULL;
	}
	
	uc_index = package_head(uc_buffer,p_ct);

	nc_index = package_param(nc_buffer,p_ct);

	if(CTP_CryptFlag(p_ct))
	{
		if(!key)
		{
#ifdef CTP_DEBUG
			printf("[CTP] key is null.\n ");
#endif
			set_protocol_error(CTP_FAILED_INVALID_KEY);
			return NULL;
		}

		if(!key_len)
		{
#ifdef CTP_DEBUG
			printf("[CTP] key length is 0.\n ");
#endif
			set_protocol_error(CTP_FAILED_INVALID_KEY_LENGTH);
			return NULL;
		}

		ret = cbc_encrypt_char_buffer(nc_buffer,nc_index,crypt_buffer,\
		  (unsigned long *)&crypt_len,key,key_len);
		if(ret!=P_CRYPT_SUCCESS)
		{
#ifdef CTP_DEBUG
			printf("[CTP] cbc encrypt failed,error:%d\n",ret);
#endif
			set_protocol_error(CTP_FAILED_ENCRYPT_ERR);
			return NULL;
		}

		protocol_package *package = allocate_package(crypt_len+uc_index+1);
		memcpy(package->data,uc_buffer,uc_index);
		memcpy(package->data+uc_index,crypt_buffer,crypt_len);
		*(uint32_t *)(package->data+1) = htonl(crc32_check_char_buffer(crypt_buffer,crypt_len));
		*(uint16_t *)(package->data+9) = htons(uc_index+crypt_len+1);
		*(package->data+crypt_len+uc_index) = p_ct->tail;
		return package;
	}
	else
	{
		protocol_package *package = allocate_package(nc_index+uc_index+1);
		memcpy(package->data,uc_buffer,uc_index);
		memcpy(package->data+uc_index,nc_buffer,nc_index);
		*(uint32_t *)(package->data+1) = htonl(crc32_check_char_buffer(nc_buffer,nc_index));
		*(uint16_t *)(package->data+9) = htons(uc_index+nc_index+1);
		*(package->data+nc_index+uc_index) = p_ct->tail;
		return package;
	}
}


/* ***********************************************************************************
 * Print ct_parameter_t data.
 *
 * @param:	param		ct_parameter_t pointer.
 *		
 * ***********************************************************************************/
static void print_ctp_param_data(const ct_parameter_t *param)
{
	printf("param_data:");
	const char *ptr = param->data;
	switch(param->type)
	{
		case CTP_TYPE_UINT8_ID:
			printf("%d;",*(uint8_t *)(ptr));
			break;
		case CTP_TYPE_UINT16_ID:
			printf("%hu;",*(uint16_t *)(ptr));
			break;
		case CTP_TYPE_UINT32_ID:
			printf("%u;",*(uint32_t *)(ptr));
			break;
		case CTP_TYPE_UINT64_ID:
			printf("%"PRIu64";",*(uint64_t *)(ptr));
			break;
		case CTP_TYPE_INT8_ID:
			printf("%d;",*(int8_t *)(ptr));
			break;
		case CTP_TYPE_INT16_ID:
			printf("%hd;",*(int16_t *)(ptr));
			break;
		case CTP_TYPE_INT32_ID:
			printf("%d;",*(int32_t *)(ptr));
			break;
		case CTP_TYPE_INT64_ID:
			printf("%"PRId64";",*(int64_t *)(ptr));
			break;
		case CTP_TYPE_CHAR_ID:
			printf("%c;",*(ptr));
			break;
		case CTP_TYPE_STRING_ID:
			printf("%s;",ptr);
			break;
		case CTP_TYPE_BYTEARRAY_ID:
			printf("[");
			for(int i=0;i<param->length;i++)
				printf("%x ",ptr[i]);
			printf("]");
			break;
		case CTP_TYPE_BCD_ID:
			printf("unsupport;");
			break;
		case CTP_TYPE_FLOAT_ID:
			printf("%f;",*(float *)(ptr));
			break;
		case CTP_TYPE_DOUBLE_ID:
			printf("%lf;",*(double *)(ptr));
			break;
		default:
			break;
	}
}

/* ***************************************************************************************
 * Set ct_parameter_t.
 *
 * @param:	param		The pointer to ct_parameter_t.
 * @param:	id			ct_parameter_t id.
 * @param:	type		ct_parameter_t parameter type.
 * @param:	len			ct_parameter_t parameter len.
 * @param:	data		ct_parameter_t parameter data.
 *
 * ***************************************************************************************/
void set_ctp_parameter(ct_parameter_t *param,uint16_t id,uint8_t type,uint8_t len,const void *data)
{
	if(!param)
		return ;

	param->id = id;
	param->type = type;
	switch(type)
	{
		case CTP_TYPE_INT8_ID:
		case CTP_TYPE_UINT8_ID:
		case CTP_TYPE_CHAR_ID:
			param->length = 1;
			memcpy(param->data,data,1);
			break;
		case CTP_TYPE_INT16_ID:
		case CTP_TYPE_UINT16_ID:
			param->length = 2;
			memcpy(param->data,data,2);
			break;
		case CTP_TYPE_INT32_ID:
		case CTP_TYPE_UINT32_ID:
			param->length = 4;
			memcpy(param->data,data,4);
			break;
		case CTP_TYPE_INT64_ID:
		case CTP_TYPE_UINT64_ID:
			param->length = 8;
			memcpy(param->data,data,8);
			break;
		case CTP_TYPE_FLOAT_ID:
			param->length = 4;
			memcpy(param->data,data,4);
			break;
		case CTP_TYPE_DOUBLE_ID:
			param->length = 8;
			memcpy(param->data,data,8);
			break;
		case CTP_TYPE_BYTEARRAY_ID:
		case CTP_TYPE_STRING_ID:
		case CTP_TYPE_BCD_ID:
		case CTP_TYPE_CUSTOM_ID:
			param->length = len;
			memcpy(param->data,data,len);
			break;
	}
}

/* ***********************************************************************************
 * Print ct_protocol_t.
 *
 * @param:	p_ct		ct_protocol_t pointer.
 * @param:	flag		print party control parameter
 *		
 * ***********************************************************************************/
void print_ctp(ct_protocol_t *p_ct)
{
	if(!p_ct)
		return ;

	printf("*************************print ct_protocol_t start*******************************\n");
	
	printf("ct_protocol_t:\n");
	printf("head:%02x;tail:%02x;check_sum:%d;sequence:%d;length:%d;attr:%d;src%d;dst:%d;main_id:%d;param_num:%d\n", \
			p_ct->head,p_ct->tail,p_ct->check_sum,p_ct->sequence,p_ct->length,p_ct->attr,p_ct->src,p_ct->dst,\
			p_ct->main_id,p_ct->param_num);

	for(int i=0;i<p_ct->param_num;i++)
	{
		printf("param[%d]\n",i);
		printf("id:%d;type:%d;len:%d;", \
				p_ct->param[i].id,p_ct->param[i].type,p_ct->param[i].length);

		print_ctp_param_data(p_ct->param+i);
		printf("\n");
	}

	printf("*************************print ct_protocol_t end*********************************\n");
}




