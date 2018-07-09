/* ************************************************************************
 *       Filename:  crc32.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/18 19:03:39
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/
 
#ifndef CRC32_H_
#define CRC32_H_

#include "wmp_cfg.h"
#include "wm_package.h"

#ifdef __cplusplus
extern "C"
{
#endif

WMP_EXPORT WMP_EXTERN uint32_t crc32_check_package(const wm_package *package);

WMP_EXPORT WMP_EXTERN uint32_t crc32_check_char_buffer(const char *buffer,uint32_t len);

#ifdef __cplusplus
}
#endif


#endif
