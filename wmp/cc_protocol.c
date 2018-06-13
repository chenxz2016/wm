/* ************************************************************************
 *       Filename:  cc_protocol.c
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
#include"cc_protocol.h"
#include<string.h>
#include<malloc.h>

#define CCP_SUCCESS									PROTO_SUCCESS
#define CCP_MAX_PARAMETER_NUM						1

extern void set_protocol_error(int err_flag);

/* ***************************************************************************************
 * Allocate cc_protocol_t structure.
 *
 * @param:	num		cc_protocol_t parameter numbers.
 * @retval:	p_cc	cc_protocol_t pointer.
 *
 * ***************************************************************************************/
cc_protocol_t *allocate_ccp(uint8_t num)
{
	cc_protocol_t *p_cc = (cc_protocol_t *)malloc(sizeof(cc_protocol_t));
	memset(p_cc,0,sizeof(cc_protocol_t));

	if(num)
	{
		p_cc->param = (cc_parameter_t *)malloc(sizeof(cc_parameter_t)*num);
		memset(p_cc->param,0,sizeof(cc_parameter_t)*num);
		p_cc->param_num = num;
	}

	return p_cc;
}

/* ***************************************************************************************
 * Deallocate cc_protocol_t structure.
 *
 * @param:	p_cc	cc_protocol_t pointer.
 *
 * ***************************************************************************************/
void deallocate_ccp(cc_protocol_t **p_cc)
{
	if(p_cc && (*p_cc) && (*p_cc)->param)
	{
		free((*p_cc)->param);
		(*p_cc)->param = NULL;
		free((*p_cc));
		(*p_cc) = NULL;
		return ;
	}

	if(p_cc && (*p_cc))
	{
		free((*p_cc));
		(*p_cc) = NULL;
	}
}

/* ***************************************************************************************
 * Set cc_protocol_t parameter numbers.
 *
 * @param:	p_cc	cc_protocol_t pointer.
 * @param:	num		parameter numbers.
 *
 * ***************************************************************************************/
void set_ccp_param_num(cc_protocol_t *p_cc,uint8_t num)
{
	if(!p_cc || !num)
		return ;
	
	if(p_cc->param)
		free(p_cc->param);

	p_cc->param_num = num;
	p_cc->param = (cc_parameter_t*)malloc(sizeof(cc_parameter_t)*num);
	memset(p_cc->param,0,sizeof(cc_parameter_t)*num);
}


/* ***************************************************************************************
 * Parser cc_protocol_t parameter.
 *
 * @param:	p_cc		cc_protocol_t pointer.
 * @param:	package		protocol package pointer.
 *
 * ***************************************************************************************/
static int parser_ccp_param(cc_protocol_t *p_cc,const protocol_package *package)
{
	set_ccp_param_num(p_cc,p_cc->param_num);
	char array[256][128]={0};
	char buffer[1024]="";
	memcpy(buffer,package->data,package->length);

	int index=0;
	for(char *ptr =strtok(buffer," ");ptr;ptr=strtok(NULL," "))
	{
		strncpy(array[index],ptr,strlen(ptr));
		index++;
	}

	char flag = 0;
	int idx=0;

	if(!strcmp(array[0],"-l"))
	{	
		if(index>2)
			return CCP_FAILED_LOAD_MORE_PARAM;

		p_cc->param[0].id = CCP_REQ_LOAD_ID;
		sscanf(array[1],"%[^-]-%s",p_cc->param[0].program,p_cc->param[0].param);

		if(!strcmp(p_cc->param[0].program,""))
			return CCP_FAILED_LOAD_NO_PROGRAM;

		if(!strcmp(p_cc->param[0].param,""))
			return CCP_FAILED_LOAD_NO_PARAM;

		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-rl"))
	{
		if(index>2)
			return CCP_FAILED_RLOAD_MORE_PARAM;

		p_cc->param[0].id = CCP_RES_LOAD_ID;
		sscanf(array[1],"%[^-]-%d",p_cc->param[0].program,&p_cc->param[0].result);

		if(!strcmp(p_cc->param[0].program,""))
			return CCP_FAILED_RLOAD_NO_PROGRAM;

		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-ul"))
	{
		if(index>2)
			return CCP_FAILED_UNLOAD_MORE_PARAM;
		
		p_cc->param[0].id = CCP_REQ_UNLOAD_ID;
		strncpy(p_cc->param[0].program,array[1],strlen(array[1]));

		if(!strcmp(p_cc->param[0].program,""))
			return CCP_FAILED_ULOAD_NO_PROGRAM;

		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-rul"))
	{
		if(index>2)
			return CCP_FAILED_RUNLOAD_MORE_PARAM;

		p_cc->param[0].id = CCP_RES_UNLOAD_ID;
		sscanf(array[1],"%[^-]-%d",p_cc->param[0].program,&p_cc->param[0].result);

		if(!strcmp(p_cc->param[0].program,""))
			return CCP_FAILED_RULOAD_NO_PROGRAM;

		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-c"))
	{
		if(index>2)
			return CCP_FAILED_CONTROL_MORE_PARAM;

		p_cc->param[0].id = CCP_REQ_CONTROL_ID;
		sscanf(array[1],"%d-%c",&p_cc->param[0].pid,&p_cc->param[0].ctrl_cmd);

		if(p_cc->param[0].ctrl_cmd>Start || p_cc->param[0].ctrl_cmd<Stop)
			return CCP_FAILED_CONTROL_NO_CMD;

		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-rc"))
	{
		if(index>2)
			return CCP_FAILED_RCONTROL_MORE_PARAM;

		p_cc->param[0].id = CCP_RES_CONTROL_ID;
		sscanf(array[1],"%d-%c-%d",&p_cc->param[0].pid,\
				&p_cc->param[0].ctrl_cmd,&p_cc->param[0].result);

		if(!p_cc->param[0].ctrl_cmd>Start || p_cc->param[0].ctrl_cmd<Stop)
			return CCP_FAILED_RCONTROL_NO_CMD;

		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-st"))
	{
		if(index>2)
			return CCP_FAILED_START_TIME_MORE_PARAM;

		p_cc->param[0].id = CCP_REQ_START_TIME_ID;
		sscanf(array[1],"%d",&p_cc->param[0].pid);

		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-rst"))
	{
		if(index>2)
			return CCP_FAILED_RSTART_TIME_MORE_PARAM;

		p_cc->param[0].id = CCP_RES_START_TIME_ID;
		sscanf(array[1],"%d-%d",&p_cc->param[0].pid,&p_cc->param[0].result);

		if(!p_cc->param[0].result)
			return CCP_FAILED_RSTART_TIME_ERR_TIME;

		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-cn"))
	{
		if(index>1)
			return CCP_FAILED_CLIENT_MORE_PARAM;

		p_cc->param[0].id = CCP_REQ_CLIENT_ID;
		return CCP_SUCCESS;
	}
	else if(!strcmp(array[0],"-rcn"))
	{
		if(index>2)
			return CCP_FAILED_RCLIENT_MORE_PARAM;

		p_cc->param[0].id = CCP_RES_CLIENT_ID;
		sscanf(array[1],"%d",&p_cc->param[0].result);

		return CCP_SUCCESS;
	}

	return CCP_FAILED_NO_CMD_ID;
}


/* ***************************************************************************************
 * Parser cc_protocol_t.
 *
 * @param:	package		protocol package pointer.
 * @retval:	p_cc		The pointer of p_cc.
 *
 * ***************************************************************************************/
cc_protocol_t *parser_ccp(const protocol_package *package)
{
	if(!package || !package->data || !package->length)
	{
#ifdef CCP_DEBUG
		printf("[CCP] Package is null.\n");
#endif
		return NULL;
	}
	
	uint32_t index = 0;
	cc_protocol_t *p_cc = allocate_ccp(CCP_MAX_PARAMETER_NUM);
	int ret = parser_ccp_param(p_cc,package);
	set_protocol_error(ret);
	if(ret!=CCP_SUCCESS)
	{
#ifdef CCP_DEBUG
		printf("[CCP] Parser parameter failed.\n");
#endif
		deallocate_ccp(&p_cc);
		return NULL;
	}

	return p_cc;
}

/* ***************************************************************************************
 * Package cc_protocol_t length.
 *
 * @param:	p_cc		The pointer to cc_protocol_t.
 * @param:	package		cc_protocol_t package.
 *
 * @retval:				Length of cc_protocol_t package.
 *
 * ***************************************************************************************/
static uint32_t package_ccp_param(const cc_protocol_t *p_cc,char *package)
{
	uint32_t index =0;

	switch(p_cc->param[0].id)
	{
		case CCP_REQ_LOAD_ID:
			index += sprintf(package+index,"-l %s-%s",p_cc->param[0].program,p_cc->param[0].param);
			break;
		case CCP_RES_LOAD_ID:
			index += sprintf(package+index,"-rl %s-%d",p_cc->param[0].program,p_cc->param[0].result);
			break;
		case CCP_REQ_UNLOAD_ID:
			index += sprintf(package+index,"-ul %d",p_cc->param[0].pid);
			break;
		case CCP_RES_UNLOAD_ID:
			index += sprintf(package+index,"-rul %d-%d",p_cc->param[0].pid,p_cc->param[0].result);
			break;
		case CCP_REQ_CONTROL_ID:
			index += sprintf(package+index,"-c %d-%d",p_cc->param[0].ctrl_cmd,p_cc->param[0].pid);
			break;
		case CCP_RES_CONTROL_ID:
			index += sprintf(package+index,"-rc %d-%d-%d",p_cc->param[0].ctrl_cmd,\
					p_cc->param[0].pid,p_cc->param[0].result);
			break;
		case CCP_REQ_START_TIME_ID:
			index += sprintf(package+index,"-st %d",p_cc->param[0].pid);
			break;
		case CCP_RES_START_TIME_ID:
			index += sprintf(package+index,"-rst %d-%d",p_cc->param[0].pid,p_cc->param[0].result);
			break;
		case CCP_REQ_CLIENT_ID:
			index += sprintf(package+index,"-cn %s",p_cc->param[0].program);
			break;
			case CCP_RES_CLIENT_ID:
			index += sprintf(package+index,"-rcn %d",p_cc->param[0].result);
			break;
	}

	return index;
}

/* ***************************************************************************************
 * Package cc_protocol_t length.
 *
 * @param:	p_cc		The pointer to cc_protocol_t.
 *
 * @retval:	package		cc_protocol_t package.
 *
 * ***************************************************************************************/
protocol_package *package_ccp(const cc_protocol_t *p_cc)
{
	char buffer[2048] = "";

	uint32_t length = package_ccp_param(p_cc,buffer);
	protocol_package *package = allocate_package(length);
	memcpy(package->data,buffer,length);

	return package;
}

/* ***************************************************************************************
 * Set cc_parameter_t.
 *
 * @param:	param		The pointer to cc_parameter_t.
 * @param:	id			cc_parameter_t id.
 * @param:	type		cc_parameter_t parameter type.
 * @param:	len			cc_parameter_t parameter len.
 * @param:	data		cc_parameter_t parameter data.
 *
 * ***************************************************************************************/
void set_ccp_parameter(cc_parameter_t *param,uint16_t id,const char *program,\
		const char *p,uint32_t result,uint32_t pid,uint8_t ctrl_cmd)
{
	if(!param)
		return ;

	param->id = id;
	if(program)
		strncpy(param->program,program,strlen(program));
	if(p)
		strncpy(param->param,p,strlen(p));

	param->result = result;
	param->pid = pid;
	param->ctrl_cmd = ctrl_cmd;
}

/* ***************************************************************************************
 * Print cc_protocol_t.
 *
 * @param:	p_cc		The pointer to cc_protocol_t.
 *
 * ***************************************************************************************/
void print_ccp(const cc_protocol_t *p_cc)
{
	if(!p_cc)
	{
#ifdef CCP_DEBUG
		printf("[CCP] cc_protocol_t is null.\n");
#endif
		return ;
	}

	uint16_t id;
	char program[256];
	char param[256];
	uint32_t result;
	uint32_t pid;
	uint8_t ctrl_cmd;

	printf("***************************CCP Start**********************\n");
	printf("param_num:%d\n",p_cc->param_num);
	printf("parameter:\n");
	for(uint8_t i=0;i<p_cc->param_num;i++)
	{
		printf("parameter[%d] id:%d;",i,p_cc->param[i].id);
		switch(p_cc->param[i].id)
		{
			case CCP_REQ_LOAD_ID:
				printf("cmd:load-req,program:%s,parameter:%s.\n",p_cc->param[i].program,\
						p_cc->param[i].param);
				break;
			case CCP_RES_LOAD_ID:
				printf("cmd:load-res,program:%s,result:%d.\n",p_cc->param[i].program,\
						p_cc->param[i].result);
				break;
			case CCP_REQ_UNLOAD_ID:
				printf("cmd:unload-req,pid:%d.\n",p_cc->param[i].pid);
				break;
			case CCP_RES_UNLOAD_ID:
				printf("cmd:unload-res,pid:%d,result:%d.\n",p_cc->param[i].pid,\
						p_cc->param[i].result);
				break;
			case CCP_REQ_CONTROL_ID:
				printf("cmd:control-req,pid:%d,cmd:%d,result:%d.\n",p_cc->param[i].pid,\
						p_cc->param[i].ctrl_cmd,p_cc->param[i].result);
				break;
			case CCP_RES_CONTROL_ID:
				printf("cmd:control-res,pid:%d,cmd:%d,result:%d.\n",p_cc->param[i].pid,\
						p_cc->param[i].ctrl_cmd,p_cc->param[i].result);
				break;
			case CCP_REQ_START_TIME_ID:
				printf("cmd:start_time-req,pid:%d.\n",p_cc->param[i].pid);
				break;
			case CCP_RES_START_TIME_ID:
				printf("cmd:start_time-res,pid:%d,result:%d.\n",p_cc->param[i].pid,\
						p_cc->param[i].result);
				break;
			case CCP_REQ_CLIENT_ID:
				printf("cmd:client-req,pid:%d\n",p_cc->param[i].pid);
				break;
			case CCP_RES_CLIENT_ID:
				printf("cmd:client-res,pid:%d,result:%d.\n",p_cc->param[i].pid,\
						p_cc->param[i].result);
				break;
			default:
				printf("\n");
				break;
		}
	}

	printf("***************************CCP End************************\n");

}



