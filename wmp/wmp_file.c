/* ************************************************************************
 *       Filename:  wmp_file.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"wmp_file.h"
#include<malloc.h>
#include<string.h>

#define WMP_FileLenCheck(index,delt,len) \
	if((index+delt)>len) \
		return NULL;

/* ***********************************************************************************
 * Allocate wmp_file_t.
 *
 * @param:	file_len	wmp_file_t file block data length.
 *
 * ***********************************************************************************/
wmp_file_t *allocate_wmp_file(uint32_t file_len)
{
	wmp_file_t *p_wmp_file = (wmp_file_t *)malloc(sizeof(wmp_file_t));
	memset(p_wmp_file,0,sizeof(wmp_file_t));
	if(file_len)
	{
		p_wmp_file->data_len = file_len;
		p_wmp_file->data = (char *)malloc(file_len);
		memset(p_wmp_file->data,0,file_len);
	}
	return p_wmp_file;
}

/* ***********************************************************************************
 * Deallocate wmp_file_t.
 *
 * @param:	p_wmp_file	wmp_file_t pointer.
 *
 * ***********************************************************************************/
void deallocate_wmp_file(wmp_file_t **p_wmp_file)
{
	if(p_wmp_file && (*p_wmp_file) && (*p_wmp_file)->data)
	{
		free(((*p_wmp_file)->data));
		(*p_wmp_file)->data = NULL;
		free(*p_wmp_file);
		(*p_wmp_file) = NULL;
	}
	
	if(p_wmp_file && (*p_wmp_file))
	{
		free(*p_wmp_file);
		*p_wmp_file = NULL;
	}
}


/* ***********************************************************************************
 * Parser wmp_file_t package.
 *
 * @param:	package		wmp_file_t package.
 * @param:	pack_len	wmp_file_t package length.
 *
 * @retval:	p_wmp_file	wmp_file_t pointer.
 *
 * ***********************************************************************************/
wmp_file_t *parser_wmp_file(const char *package,uint32_t pack_len)
{
	uint32_t index = 0;
	WMP_FileLenCheck(index,14,pack_len)
	
	wmp_file_t *p_wmp_file = allocate_wmp_file(0);
	
	*(uint8_t *)(package+index) = p_wmp_file->attr;
	index+=sizeof(p_wmp_file->attr);

	*(uint8_t *)(package+index) = p_wmp_file->result;
	index+=sizeof(p_wmp_file->result);
	
	p_wmp_file->src = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_file->src);
	
	p_wmp_file->dst = ntohl(*(uint32_t *)(package+index));
	index+=sizeof(p_wmp_file->dst);
	
	p_wmp_file->id = *(uint8_t *)(package+index);
	index+=sizeof(p_wmp_file->id);	
	
	if(p_wmp_file->result==WMP_FILE_TRANSMIT_RSP)
		return p_wmp_file;	
	
	switch(p_wmp_file->id)
	{
		case WMP_FILE_NAME_ID:
			p_wmp_file->block = ntohl(*(uint32_t *)(package+index));
			index+=sizeof(p_wmp_file->block);
			
			p_wmp_file->crc32_code = ntohl(*(uint32_t *)(package+index));
			index+=sizeof(p_wmp_file->crc32_code);
			
			p_wmp_file->filename_len = *(uint8_t *)(package+index);
			index+=sizeof(p_wmp_file->filename_len);
			
			memcpy(p_wmp_file->filename,package+index,p_wmp_file->filename_len);
			index+=p_wmp_file->filename_len;
			break;
		case WMP_FILE_DATA_ID:
		case WMP_FILE_END_ID:
            p_wmp_file->unique = ntohl(*(uint32_t *)(package+index));
            index+=sizeof(p_wmp_file->unique);

            p_wmp_file->sequence = ntohl(*(uint32_t *)(package+index));
            index+=sizeof(p_wmp_file->sequence);

			p_wmp_file->data_len = ntohl(*(uint32_t *)(package+index));
			index+=sizeof(p_wmp_file->data_len);
			
			memcpy(p_wmp_file->data,package+index,p_wmp_file->data_len);
			index+=p_wmp_file->data_len;
			break;
		default:
			break;
	}
	
	return p_wmp_file;
}

/* ***********************************************************************************
 * Package wmp_file_t package.
 *
 * @param:	package		wmp_file_t package.
 * @param:	p_wmp_file	wmp_file_t pointer.
 *
 * @retval:	index		Length of wmp_file_t package
 *
 * ***********************************************************************************/
uint32_t package_wmp_file(char *package,const wmp_file_t *p_wmp_file)
{
	uint32_t index = 0;
	
	*(uint8_t *)(package+index) = p_wmp_file->attr;
	index+=sizeof(p_wmp_file->attr);
	
	*(uint8_t *)(package+index) = p_wmp_file->result;
	index+=sizeof(p_wmp_file->result);
	
	*(uint32_t *)(package+index) = htonl(p_wmp_file->src);
	index+=sizeof(p_wmp_file->src);
	
	*(uint32_t *)(package+index) = htonl(p_wmp_file->dst);
	index+=sizeof(p_wmp_file->dst);
	
	*(uint8_t *)(package+index) = p_wmp_file->id;
	index+=sizeof(p_wmp_file->id);
	
	/* respond operaiton. */
	if(p_wmp_file->result==WMP_FILE_TRANSMIT_RSP)
		return index;
	
	switch(p_wmp_file->id)
	{
		case WMP_FILE_NAME_ID:
			*(uint32_t *)(package+index) = htonl(p_wmp_file->block);
			index+=sizeof(p_wmp_file->block);
			
			*(uint32_t *)(package+index) = htonl(p_wmp_file->crc32_code);
			index+=sizeof(p_wmp_file->crc32_code);
			
			*(uint8_t *)(package+index) = p_wmp_file->filename_len;
			index+=sizeof(p_wmp_file->filename_len);
			
			memcpy(package+index,p_wmp_file->filename,p_wmp_file->filename_len);
			index+=p_wmp_file->filename_len;
			break;
		case WMP_FILE_DATA_ID:
		case WMP_FILE_END_ID:
            *(uint32_t *)(package+index) = htonl(p_wmp_file->unique);
            index+=sizeof(p_wmp_file->unique);

            *(uint32_t *)(package+index) = htonl(p_wmp_file->sequence);
            index+=sizeof(p_wmp_file->sequence);

			*(uint32_t *)(package+index) = htonl(p_wmp_file->data_len);
			index+=sizeof(p_wmp_file->data_len);
			
			memcpy(package+index,p_wmp_file->data,p_wmp_file->data_len);
			index+=p_wmp_file->data_len;
			break;
		default:
			break;
	}
	
	return index;
}

/* ***********************************************************************************
 * Set wmp_file_t block data length.
 *
 * @param:	p_wmp_file	wmp_file_t pointer.
 * @param:	file_len	wmp_file_t block data length.
 *
 * ***********************************************************************************/
void set_wmp_file_data_len(wmp_file_t *p_wmp_file,uint32_t file_len)
{
	if(!p_wmp_file || !file_len)
		return ;

	if(p_wmp_file->data)
		free(p_wmp_file->data);

	p_wmp_file->data_len = file_len;
	p_wmp_file->data = (uint8_t *)malloc(file_len);
	memset(p_wmp_file->data,0,file_len);
}


/* ***********************************************************************************
 * Print wmp_file_t.
 *
 * @param:	p_wmp_file	wmp_file_t pointer.
 *
 * ***********************************************************************************/
void print_wmp_file(const wmp_file_t *p_wmp_file)
{
	if(!p_wmp_file)
	{
#ifdef WMP_DEBUG
		printf("wmp_file_t is null.\n");
#endif
		return ;
	}
	printf("***************************WM-file Protocol Start**********************\n");
	printf("attr:%d;src:%d;dst:%d;block:%d;sequence:%d;data_len:%d;data:",p_wmp_file->attr,\
			p_wmp_file->src,p_wmp_file->dst,p_wmp_file->block,p_wmp_file->sequence,\
			p_wmp_file->data_len);

	for(uint32_t i=0;i<p_wmp_file->data_len;i++)
	{
		printf("%02x ",p_wmp_file->data[i]);
	}
	printf("\n");

	printf("***************************WM-file Protocol End************************\n");
}


/* ***********************************************************************************
 * Copy wmp_file_t a new instance.
 *
 * @param:	p_wmp_file	wmp_file_t pointer.
 * @retval  c_wmp_file  The pointer of new instance.
 *
 * ***********************************************************************************/
wmp_file_t *copy_wmp_file(const wmp_file_t *p_wmp_file)
{
    wmp_file_t *c_wmp_file = allocate_wmp_file(p_wmp_file->data_len);
    memcpy(c_wmp_file,p_wmp_file,sizeof(wmp_file_t));
    memcpy(c_wmp_file->data,p_wmp_file->data,p_wmp_file->data_len);
    return c_wmp_file;
}
