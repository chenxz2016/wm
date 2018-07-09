/* ************************************************************************
 *       Filename:  wm_package.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef WM_PACKAGE_H_
#define WM_PACKAGE_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ***********************************************************************************
 * wm_package structure.
 *
 * @data:                   wm_package data.
 * @length:                 wm_package data length.
 *
 * ***********************************************************************************/
typedef struct
{
	char *data;
	uint32_t length;
}wm_package;


/* ***********************************************************************************
 * Create wm_package instance.
 *
 * @param:	length      wm_package data length.
 * @retval:	package     The pointer of wm_package instance.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN wm_package* create_wm_package(uint32_t length);

/* ***********************************************************************************
 * Delete wm_package instance.
 *
 * @param:	package		The pointer of wm package pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void delete_wm_package(wm_package **package);

/* ***********************************************************************************
 * Set wm_package data length and realloc memory and clear it as 0.
 *
 * @param:	package		The pointer of wm package pointer.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void set_wm_package_length(wm_package *package,uint32_t length);

/* ***********************************************************************************
 * Print wm_package.
 *
 * @param:	package		print wm_package data.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_wm_package(const wm_package *package);

/* ***********************************************************************************
 * Print buffer.
 *
 * @param:	buffer		buffer need to print.
 * @param:	len			buffer length.
 *
 * ***********************************************************************************/
WMP_EXPORT WMP_EXTERN void print_buffer(const char *buffer,uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
