/* ************************************************************************
 *       Filename:  wmp_cfg.h
 *    Description:
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen),
 *        Company:
 * ************************************************************************/

#ifndef WMP_CFG_H
#define WMP_CFG_H

#define WMP_EXTERN          extern

#if defined(_WIN32)
#  define WMP_EXPORT        __declspec(dllexport)
#else
#  define WMP_EXPORT
#endif

/* redefine base data type. */
#if defined(_WIN32) || defined(WIN32)
typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef __int64             int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned __int64    uint64_t;
#endif

#endif // WMP_CFG_H
