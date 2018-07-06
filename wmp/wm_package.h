/* ************************************************************************
 *       Filename:  protocol_package.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef PROTOCOL_PACKAGE_H_
#define PROTOCOL_PACKAGE_H_

#ifdef WMP_QT
#include "wmp_qt.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	char *data;
	uint32_t length;
}protocol_package;


/* Allocate protocol_package. */
WMPSHARED_EXPORT extern protocol_package* allocate_package(uint32_t length);

/* Deallocate protocol_package. */
WMPSHARED_EXPORT extern void deallocate_package(protocol_package **pckage);

/* Set protocol_package data length. */
WMPSHARED_EXPORT extern void set_package_length(protocol_package *package,uint32_t length);

/* Print protocol_package. */
WMPSHARED_EXPORT extern void print_protocol_package(protocol_package *package);

/* Print buffer. */
WMPSHARED_EXPORT extern void print_buffer(const char *buffer,uint32_t len);

#ifdef __cplusplus
}
#endif

#endif


