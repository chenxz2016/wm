/* ************************************************************************
 *       Filename:  wmp_file.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WMP_FILE_H_
#define WMP_FILE_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif


/* *********************************************************************************************
 * Walking Message protocol file.
 * @attr			Walking Message file operation attribute.
 * @result			Walking Message file operation result.
 * @src				Walking Message file operation source id.
 * @dst				Walking Message file operation destination id.
 * @block			Walking Message file operation block numbers.
 * @sequence		Walking Message file operation current sequence.
 * @data_len		Walking Message file operation current block data length.
 * @data			Walking Message file operation current block data.
 *
 * **********************************************************************************************/
typedef struct
{
	uint8_t attr;
	uint8_t result;
	uint32_t src;
	uint32_t dst;
	uint8_t id;
	uint32_t block;
	uint32_t crc32_code;
	uint8_t filename_len;
	uint8_t filename[256];
	
    uint32_t unique;
	uint32_t sequence;
	uint32_t data_len;
	uint8_t *data;
}wmp_file_t;

#define WMP_FILE_LENGTH										sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint8_t)

/* Contains file name, transmit data block number. */
#define WMP_FILE_NAME_ID									1

/* Contains file data. */
#define WMP_FILE_DATA_ID									2

/* Transmit end id. */
#define WMP_FILE_END_ID										3

#define WMP_FILE_PTG										1 
#define WMP_FILE_PTP										2
#define WMP_FILE_PTT										3
#define WMP_FILE_PTTS										4

#define WMP_FILE_TRANSMIT_REQ								0
#define WMP_FILE_TRANSMIT_RSP								1

#define WMP_FILE_SEND_OFFLINE_ID							1
#define WMP_FILE_SEND_ONLINE_ID								2
#define WMP_FILE_UPLOAD_GROUP_ID							3
#define WMP_FILE_UPLOAD_SESSION_ID							4

#define WMP_FILE_RESULT_SUCCESS								0
#define WMP_FILE_RESULT_TIMEOUT								1
#define WMP_FILE_RESULT_OVER								2
#define WMP_FILE_RESULT_CRC_ERROR							3


#define WMP_FileCrypt(p_wmp_file)							(p_wmp_file->attr & 1)
#define WMP_FileCRC32(p_wmp_file)							(p_wmp_file->attr & 2)
#define WMP_FileResult(p_wmp_file) 							(p_wmp_file->result)
#define WMP_FileSrc(p_wmp_file) 							(p_wmp_file->src)
#define WMP_FileDst(p_wmp_file) 							(p_wmp_file->dst)
#define WMP_FileDataLen(p_wmp_file) 						(p_wmp_file->data_len)
#define WMP_FileData(p_wmp_file) 							(p_wmp_file->data)

#define WMP_FileSetCryptEnable(p_wmp_file)					(p_wmp_file->attr |= 1)
#define WMP_FileSetCryptDisable(p_wmp_file)					(p_wmp_file->attr &= ~(1 << 1))
#define WMP_FileSetCRC32Enable(p_wmp_file)					(p_wmp_file->attr |= 2)
#define WMP_FileSetCRC32Disable(p_wmp_file)					(p_wmp_file->attr &= ~(1 << 2))
#define WMP_FileSetResult(p_wmp_file,result) 				(p_wmp_file->result = result)
#define WMP_FileSetSrc(p_wmp_file,id) 						(p_wmp_file->src_id = id)
#define WMP_FileSetDst(p_wmp_file,id) 						(p_wmp_file->dst_id = id)

#define WMP_FileSetData(p_wmp_file,data,len)\
 	p_wmp_file->data_len = len;\
	memcpy(p_wmp_file->data,data,len);

/* Allocate wmp_file_t.  */
WMPSHARED_EXPORT extern wmp_file_t *allocate_wmp_file(uint32_t data_len);

/* Deallocate wmp_file_t.  */
WMPSHARED_EXPORT extern void deallocate_wmp_file(wmp_file_t **p_wmp_file);

/* Parser wmp_file_t protocol.  */
WMPSHARED_EXPORT extern wmp_file_t *parser_wmp_file(const char *package,uint32_t pack_len);

/* Package wmp_file_t protocol.  */
WMPSHARED_EXPORT extern uint32_t package_wmp_file(char *package,const wmp_file_t *p_wmp_file);

/* Set wmp_file_t current file block data length.  */
WMPSHARED_EXPORT extern void set_wmp_file_data_len(wmp_file_t *p_wmp_file,uint32_t data_len);

/* Print wmp_file_t. */
WMPSHARED_EXPORT extern void print_wmp_file(const wmp_file_t *p_wmp_file);

#ifdef __cplusplus
}
#endif

#endif
