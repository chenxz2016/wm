/* ************************************************************************
 *       Filename:  protocol_error.c
 *    Description:  
 *        Version:  1.0
 *        Created:  11/01/2017 08:15:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include"protocol_def.h"
#include"protocol_error.h"

int p_error;

const char *error_array[]=
{
	"[PROTOCOL] Success.",
#ifdef CCP
	"[CCP] Load cmd error, more parameter.",
	"[CCP] Load cmd error, no program.",
	"[CCP] Load cmd error, no parameter.",
	"[CCP] Res Load cmd error, more parameter.",
	"[CCP] Res Load cmd error, no program.",
	"[CCP] Unload cmd error, more parameter.",
	"[CCP] Unload cmd error, no program.",
	"[CCP] Res Unload cmd error, more parameter.",
	"[CCP] Res Unload cmd error, no program.",
	"[CCP] Control cmd error, more parameter.",
	"[CCP] Control cmd error, no this cmd.",
	"[CCP] Res Control cmd error, more parameter.",
	"[CCP] Res Control cmd error, no this cmd.",
	"[CCP] Start Time cmd error, more parameter.",
	"[CCP] Res Start Time cmd error, more parameter.",
	"[CCP] Res Start Time cmd error, error time.",
	"[CCP] Client cmd error, more parameter.",
	"[CCP] Res Client cmd error, more parameter.",
	"[CCP] No this cmd.",
#endif
#ifdef CTP
	"[CTP] Invalid pointer.",
	"[CTP] Invalid key.",
	"[CTP] Key length is 0.",
	"[CTP] Encrypt error.",
	"[CTP] Head and Tail error.",
	"[CTP] Parser head error.",
	"[CTP] CRC check error.",
	"[CTP] Decrypt error.",
	"[CTP] Package length error.",
#endif


	"Unknown error."
};

void set_protocol_error(int err_flag)
{
	if(err_flag>PROTO_UNKNOWN_ERROR || err_flag < PROTO_SUCCESS)
	{
		p_error = PROTO_UNKNOWN_ERROR;
		return ;
	}
	p_error = err_flag;
}

const char *protocol_error()
{
	return error_array[p_error];
}


