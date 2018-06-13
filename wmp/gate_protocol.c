/* ************************************************************************
 *       Filename:  gate_protocol.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017Äê07ÔÂ08ÈÕ 10Ê±13·Ö30Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include<string.h>
#include<malloc.h>
#include"protocol_def.h"
#include"protocol_error.h"
#include"protocol_package.h"
#include"gate_protocol.h"

extern void set_protocol_error(int err_flag);


/* ***************************************************************************************
 * Allocate gate_protocol_t.
 *
 * @param param_num		parameter number.
 * @retval p_gate		gate protocol structure pointer.
 *
 * ***************************************************************************************/
gate_protocol_t *allocate_gatep(uint16_t param_num)
{
	gate_protocol_t *p_gate = (gate_protocol_t *)malloc(sizeof(gate_protocol_t));
	memset(p_gate,0,sizeof(gate_protocol_t));
	if(!param_num)
	{
		p_gate->param_num = 0;
		p_gate->param = 0;
		return p_gate;
	}

	p_gate->param_num = param_num;
	p_gate->param = (gate_parameter_t *)malloc(sizeof(gate_parameter_t)*param_num);
	memset(p_gate->param,0,sizeof(gate_parameter_t)*param_num);
	return p_gate;
}


/* **************************************************************************************
 * Dealocate gate_protocol_t structure.
 *
 * @param p_gate	gate protocol pointer's pointer.
 *
 * ***************************************************************************************/
void deallocate_gatep(gate_protocol_t **p_gate)
{
	if((*p_gate) && (*p_gate)->param)
	{
		free((*p_gate)->param);
		(*p_gate)->param = NULL;
		free((*p_gate));
		(*p_gate) = NULL;
		return ;
	}

	if((*p_gate))
	{
		free((*p_gate));
		(*p_gate) = NULL;
		return ;
	}
}


/* **************************************************************************************
 * Set gate_protocol_t parameter number.
 *
 * @param p_gate	gate protocol pointer's pointer.
 * @param param_num	gate_protocol_t parameter numbers.
 *
 * ***************************************************************************************/
void set_gate_param_num(gate_protocol_t *p_gate,uint16_t param_num)
{
	if(!p_gate || !param_num)
		return ;
	
	if(p_gate->param)
		free(p_gate->param);

	p_gate->param_num = param_num;
	p_gate->param = (gate_parameter_t*)malloc(sizeof(gate_parameter_t)*param_num);
}

/* **************************************************************************************
 * Allocate gate_req_t structure.
 *
 * @param num		gate_req_t type numbers.
 *
 * @retval p_gate_req	pointer of gate_req_t.
 *
 * ***************************************************************************************/
gate_req_t* allocate_gate_req(uint16_t num)
{
	gate_req_t *p_gate_req = (gate_req_t *)malloc(sizeof(gate_req_t));
	memset(p_gate_req,0,sizeof(gate_req_t));
	if(num)
	{
		p_gate_req->type_num = num;
		p_gate_req->type_list = (uint16_t*)malloc(sizeof(uint16_t)*num);
		memset(p_gate_req->type_list,0,sizeof(uint16_t)*num);
	}
	return p_gate_req;
}

/* **************************************************************************************
 * Deallocate gate_req_t.
 *
 * @param p_gate_req	pointer of gate_req_t.
 *
 * ***************************************************************************************/
void deallocate_gate_req(gate_req_t **p_gate_req)
{
	if(p_gate_req && (*p_gate_req))
	{
		free(*p_gate_req);
		(*p_gate_req) = NULL;
	}
}

/* **************************************************************************************
 * Set gate_req_t parameter number.
 *
 * @param p_gate_req	pointer of gate_req_t.
 * @param num			gate_req_t parameter number.
 *
 * ***************************************************************************************/
void set_gate_req_num(gate_req_t *p_gate_req,uint16_t num)
{
	if(!p_gate_req || !num)
		return ;
	if(p_gate_req->type_list)
		free(p_gate_req->type_list);

	p_gate_req->type_num = num;
	p_gate_req->type_list = (uint16_t *)malloc(sizeof(uint16_t)*num);
	memset(p_gate_req->type_list,0,sizeof(uint16_t)*num);
}

/* **************************************************************************************
 * Allocate gate_broadcast_t.
 *
 * @param num			gate_broadcast_t parameter number.
 *
 * @retval p_gate_bc	pointer of gate_broadcast_t.
 *
 * ***************************************************************************************/
gate_broadcast_t *allocate_gate_broadcast(uint32_t num)
{
	gate_broadcast_t *p_gate_bc = (gate_broadcast_t *)malloc(sizeof(gate_broadcast_t));
	memset(p_gate_bc,0,sizeof(gate_broadcast_t));
	if(num)
	{
		p_gate_bc->id_num = num;
		p_gate_bc->id_list = (uint32_t *)malloc(sizeof(uint32_t)*num);
		memset(p_gate_bc->id_list,0,sizeof(uint16_t)*num);
	}
	return p_gate_bc;
}

/* **************************************************************************************
 * Deallocate gate_broadcast_t.
 *
 * @param p_gate_bc		pointer of gate_broadcast_t.
 *
 * ***************************************************************************************/
void deallocate_gate_broadcast(gate_broadcast_t **p_gate_bc)
{
	if(p_gate_bc && (*p_gate_bc) && (*p_gate_bc)->id_list)
	{
		free((*p_gate_bc)->id_list);
		(*p_gate_bc)->id_list = NULL;
		free((*p_gate_bc));
		(*p_gate_bc) = NULL;
		return ;
	}
	if(p_gate_bc && (*p_gate_bc))
	{
		free((*p_gate_bc));
		(*p_gate_bc) = NULL;
	}
}

/* **************************************************************************************
 * Set gate_broadcast_t id number.
 *
 * @param p_gate_bc		pointer of gate_broadcast_t.
 * @param id_num		id numbers.
 *
 * ***************************************************************************************/
void set_gate_broadcast_num(gate_broadcast_t *p_gate_bc,uint32_t id_num)
{
	if(!p_gate_bc || !id_num)
		return ;

	if(p_gate_bc->id_list)
		free(p_gate_bc->id_list);

	p_gate_bc->id_num = id_num;
	p_gate_bc->id_list = (uint32_t *)malloc(sizeof(uint16_t)*id_num);
	memset(p_gate_bc->id_list,0,sizeof(uint16_t)*id_num);
}

/* **************************************************************************************
 * Check gate_protocol_t package head and tail..
 *
 * @param package		pointer of protocol_package.
 *
 * @retval GATEP_PARSER_FAILED		check failed.
 * @retval GATEP_PARSER_SUCCESS		check success.
 *
 * ***************************************************************************************/
static int check_head_tail(const protocol_package *package)
{
	if(!package)
		return GATEP_PARSER_FAILED;
	if(*package->data!=GATEP_HEAD_ID || *(package->data+package->length)!=GATEP_TAIL_ID)
		return GATEP_PARSER_FAILED;
	return GATEP_PARSER_SUCCESS;
}

/* **************************************************************************************
 * Parser gate_protocol_t parameter.
 *
 * @param p_gate		pointer of gate_protocol_t.
 * @param package		pointer of protocol_package.
 *
 * @retval GATEP_PARSER_FAILED		parser failed.
 * @retval GATEP_PARSER_SUCCESS		parser success.
 *
 * ***************************************************************************************/
static int parser_gatep_param(gate_protocol_t *p_gate,const protocol_package *package)
{
	gate_req_t *p_gate_req = 0;
	gate_broadcast_t *p_gate_bc = 0;
	uint32_t index = GATEP_PARAM_INDEX;
	set_gate_param_num(p_gate,p_gate->param_num);
	for(int i=0;i<p_gate->param_num;i++)
	{
		if((package->length) <= (index+4))
			return GATEP_PARSER_FAILED;
		
		p_gate->param[i].id = *(uint16_t *)(package->data + index);
		index += 2;
		p_gate->param[i].attr = *(uint8_t *)(package->data + index);
		index++;
		p_gate->param[i].length = *(uint8_t *)(package->data + index);
		index++;
		if((index+p_gate->param[i].length)>=package->length)
			return GATEP_PARSER_FAILED;

		switch(p_gate->param[i].id)
		{
			case GATEP_REQ_DATA_ID:
				p_gate_req = allocate_gate_req(0);
				p_gate->param[i].data = p_gate_req;
				if(GATEP_NG(p_gate->param)==GATEP_NTG_FLAG)
				{
					p_gate_req->src = *(uint32_t *)(package->data+index);
					index+=4;
					p_gate_req->dst = *(uint32_t *)(package->data+index);
					index+=4;
					p_gate_req->type_num = *(uint16_t *)(package->data+index);
					index+=2;
					set_gate_req_num(p_gate_req,p_gate_req->type_num);
					for(uint16_t i=0;i<p_gate_req->type_num;i++)
					{
						p_gate_req->type_list[i] = *(uint16_t *)(package->data+index);
						index+=2;
					}
				}
				else
				{
					p_gate_req->src = *(uint32_t *)(package->data+index);
					index+=4;
					p_gate_req->dst = *(uint32_t *)(package->data+index);
					index+=4;
					p_gate_req->result = *(uint8_t *)(package->data+index);
					index++;
				}
				break;
			case GATEP_REQ_CANCEL_ID:
				p_gate_req = allocate_gate_req(0);
				p_gate->param[i].data = p_gate_req;
				if(GATEP_NG(p_gate->param)==GATEP_NTG_FLAG)
				{
					p_gate_req->src = *(uint32_t *)(package->data+index);
					index+=4;
					p_gate_req->dst = *(uint32_t *)(package->data+index);
					index+=4;
					set_gate_req_num(p_gate_req,p_gate_req->type_num);
					for(uint16_t i=0;i<p_gate_req->type_num;i++)
					{
						p_gate_req->type_list[i] = *(uint16_t *)(package->data+index);
						index+=2;
					}
				}
				else
				{
					p_gate_req->src = *(uint32_t *)(package->data+index);
					index+=4;
					p_gate_req->dst = *(uint32_t *)(package->data+index);
					index+=4;
					p_gate_req->result = *(uint8_t *)(package->data+index);
					index++;
				}
				break;
			case GATEP_BROADCAST_EXIT_ID:
				p_gate_bc = allocate_gate_broadcast(0);
				p_gate->param[i].data = p_gate_bc;
				if(GATEP_NG(p_gate->param)==GATEP_NTG_FLAG)
				{
					p_gate_req->src = *(uint32_t *)(package->data+index);
					index+=4;
					p_gate_req->src = *(uint32_t *)(package->data+index);
					index+=4;
				}
				break;
			case GATEP_BROADCAST_INFORM_ID:
			case GATEP_BROADCAST_GET_ALL_ID:
			default:
				break;
		}
	}
	return GATEP_PARSER_SUCCESS;
}

/* **************************************************************************************
 * Parser gate_protocol_t.
 *
 * @param package		pointer of protocol_package.
 *
 * @retval NULL			parser failed.
 * @retval p_gate		parser success.
 *
 * ***************************************************************************************/
gate_protocol_t *parser_gatep(const protocol_package *package)
{
	if(!package)
	{
#ifdef GATEP
		printf("[GATEP] package is null.\n");
#endif
		set_protocol_error(GATEP_FAILED_INVALID_PTR);
		return NULL;
	}
	
	if(check_head_tail(package)!=GATEP_PARSER_SUCCESS)
	{
#ifdef GATEP
		printf("[GATEP] head or tail error.\n");
#endif
		set_protocol_error(GATEP_FAILED_HEAD_OR_TAIL);
		return NULL;
	}

	gate_protocol_t *p_gate = allocate_gatep(0);
	int index = 0;
	p_gate->length = *(uint16_t *)(package->data+index);
	index+=2;
	p_gate->id = *(uint16_t *)(package->data+index);
	index+=2;
	p_gate->param_num = *(uint16_t *)(package->data+index);
	index+=2;
	int ret = parser_gatep_param(p_gate,package);
	set_protocol_error(ret);
	if(ret!=GATEP_PARSER_SUCCESS)
	{
#ifdef GATEP
		printf("[GATEP] parser gate_protocol_t failed.\n");
#endif
		deallocate_gatep(&p_gate);
		return NULL;
	}

	return p_gate;
}

/* **************************************************************************************
 * Package gate_protocol_t parameter.
 *
 * @param p_gate		pointer of gate_protocol_t.
 * @param package		pointer of protocol_package.
 *
 * ***************************************************************************************/
static uint32_t package_gatep_param(const gate_protocol_t *p_gate,protocol_package *package)
{
	gate_req_t *p_gate_req = NULL;
	gate_broadcast_t *p_gate_bc = NULL;
	uint32_t index = GATEP_PARAM_INDEX;
	for(int i=0;i<p_gate->param_num;i++)
	{
		*(uint16_t *)(package->data + index) = p_gate->param[i].id;
		index += 2;
		*(uint8_t *)(package->data + index) = p_gate->param[i].attr;
		index++;
		*(uint8_t *)(package->data + index) = p_gate->param[i].length;
		index++;
		switch(p_gate->param[i].id)
		{
			case GATEP_REQ_DATA_ID:
				p_gate_req = (gate_req_t *)p_gate->param[i].data;
				if(GATEP_NG(p_gate->param)==GATEP_NTG_FLAG)
				{
					*(uint32_t *)(package->data+index) = p_gate_req->src;
					index+=4;
					*(uint32_t *)(package->data+index) = p_gate_req->dst;
					index+=4;
					*(uint16_t *)(package->data+index) = p_gate_req->type_num;
					index+=2;
					for(uint16_t i=0;i<p_gate_req->type_num;i++)
					{
						*(uint16_t *)(package->data+index) = p_gate_req->type_list[i];
						index+=2;
					}
				}
				else
				{
					*(uint32_t *)(package->data+index) = p_gate_req->src;
					index+=4;
					*(uint32_t *)(package->data+index) = p_gate_req->dst;
					index+=4;
					*(uint8_t *)(package->data+index) = p_gate_req->result;
					index++;
				}
				break;
			case GATEP_REQ_CANCEL_ID:
				p_gate_req = (gate_req_t *)p_gate->param[i].data;
				if(GATEP_NG(p_gate->param)==GATEP_NTG_FLAG)
				{
					*(uint32_t *)(package->data+index) = p_gate_req->src;
					index+=4;
					*(uint32_t *)(package->data+index) = p_gate_req->dst;
					index+=4;
					for(uint16_t i=0;i<p_gate_req->type_num;i++)
					{
						*(uint16_t *)(package->data+index) = p_gate_req->type_list[i];
						index+=2;
					}
				}
				else
				{
					*(uint32_t *)(package->data+index) = p_gate_req->src;
					index+=4;
					*(uint32_t *)(package->data+index) = p_gate_req->dst;
					index+=4;
					*(uint8_t *)(package->data+index) = p_gate_req->result;
					index++;
				}
				break;
			case GATEP_BROADCAST_EXIT_ID:
				p_gate_bc = (gate_broadcast_t *)p_gate->param[i].data;
				if(GATEP_NG(p_gate->param)==GATEP_NTG_FLAG)
				{
					*(uint32_t *)(package->data+index) = p_gate_req->src;
					index+=4;
					*(uint32_t *)(package->data+index) = p_gate_req->dst;
					index+=4;
				}
				break;
			case GATEP_BROADCAST_INFORM_ID:
			case GATEP_BROADCAST_GET_ALL_ID:
			default:
				break;
		}
	}
	return index;
}

static uint16_t calculate_protocol_length(const gate_protocol_t *p_gate)
{
	return 1024;
}

/* **************************************************************************************
 * Package gate_protocol_t.
 *
 * @param p_gate		pointer of gate_protocol_t.
 *
 * @retval package		pointer of protocol_package.
 *
 * ***************************************************************************************/
protocol_package *package_gatep(const gate_protocol_t *p_gate)
{
	uint16_t length = calculate_protocol_length(p_gate);
	
	protocol_package *package = allocate_package(length);
	uint16_t index = 0;
	package->data[0] = GATEP_HEAD_ID;
	index++;
	*(uint16_t *)(package->data+index) = p_gate->length;
	index+=2;
	*(uint16_t *)(package->data+index) = p_gate->id;
	index+=2;
	*(uint16_t *)(package->data+index) = p_gate->param_num;
	index+=2;

	package_gatep_param(p_gate,package);

	package->data[length] = GATEP_TAIL_ID;
	return package;
}

/* **************************************************************************************
 * Print gate_protocol_t.
 *
 * @param p_gate		pointer of gate_protocol_t.
 *
 * ***************************************************************************************/
void print_gatep(const gate_protocol_t *p_gate)
{}

