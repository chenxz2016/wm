/* ************************************************************************
 *       Filename:  protocol_def.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#ifndef PROTOCOL_DEF_H_
#define PROTOCOL_DEF_H_

#include "wmp_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include<stdio.h>

#if defined(WIN_OS) || defined(WIN32)
	#include<Winsock2.h>
    #include<winsock.h>
    #pragma comment(lib,"ws2_32.lib")
#elif defined(LINUX_OS)
	#include<stdint.h>
	#include<arpa/inet.h>
	#include<inttypes.h>
#endif

#include"wm_package.h"
#include"crc32.h"

#ifdef SERVER_PROTO

#elif defined(CLIENT_PROTO)
#undef CCP
#undef CTP
#undef GGP
#undef GCP
#undef GNCP
#undef GATEP
#endif


#ifdef CTP
#include"ct_protocol.h"
#endif

#ifdef CCP
#include"cc_protocol.h"
#endif

#ifdef CCP
#include"cc_protocol.h"
#endif

#ifdef GCP
#include"gc_protocol.h"
#endif

#ifdef GGP
#include"gg_protocol.h"
#endif

#ifdef GNCP
#include"gnc_protocol.h"
#endif

#ifdef GATEP
#include"gate_protocol.h"
#endif

#ifdef WMP
#include"wm_protocol.h"
#include"wmp_beat_heart.h"
#include"wmp_file.h"
#include"wmp_group.h"
#include"wmp_login.h"
#include"wmp_message.h"
#include"wmp_operations.h"
#include"wmp_register.h"
#include"wmp_session.h"
#include"wmp_sound.h"
#include"wmp_user.h"
#include"wmp_video.h"
#endif


#ifdef __cplusplus
}
#endif

#endif


