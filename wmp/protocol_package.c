/* ************************************************************************
 *       Filename:  protocol_package.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include<malloc.h>
#include<stdint.h>
#include<string.h>
#include"protocol_package.h"
#include <stdio.h>



/* ***********************************************************************************
 * Allocate protocol_package.
 *
 * @param:	length	Protocol package length.
 *
 * @retval:	package	Protocol package.
 *
 * ***********************************************************************************/
protocol_package *allocate_package(uint32_t length)
{
	protocol_package *package = (protocol_package *)malloc(sizeof(protocol_package));
	memset(package,0,sizeof(protocol_package));

	if(length)
	{
		package->length = length;
		package->data = malloc(length);
		memset(package->data,0,length);
	}
	return package;
}

/* ***********************************************************************************
 * Deallocate protocol_package.
 *
 * @param:	package		The pointer of protocol package pointer.
 *
 * ***********************************************************************************/
void deallocate_package(protocol_package **package)
{
	if(package && (*package) && (*package)->data)
	{
		free((*package)->data);
		(*package)->data = NULL;
		free(*package);
		(*package) = NULL;
		return ;
	}
	if(package && (*package))
	{
		free(*package);
		(*package) = NULL;
	}
}

void set_package_length(protocol_package *package,uint32_t length)
{
	if(!package || !length)
		return ;

	if(package->data)
		free(package->data);

	package->data = (char *)malloc(length);
	memset(package->data,0,length);
	package->length = length;
}

/* ***********************************************************************************
 * Print protocol_package.
 *
 * @param:	package		Protocol package pointer.
 *
 * ***********************************************************************************/
void print_protocol_package(protocol_package *package)
{
	if(!package)
	{
		printf("package is null.\n");
		return ;
	}

	printf("***************************protocol package start*************************\n");
	printf("protocol package:\n");
	printf("length:%d\n",package->length);
	printf("data:");
    for(uint32_t i=0;i<package->length;i++)
	{
		printf("%02x ",(unsigned char)package->data[i]);
	}
	printf("\n");
	printf("***************************protocol package end*************************\n");
}


/* ***********************************************************************************
 * Print buffer.
 *
 * @param:	buffer		buffer need to print.
 * @param:	len			buffer length.
 *
 * ***********************************************************************************/
void print_buffer(const char *buffer,uint32_t len)
{
	if(!buffer || !len)
	{
		printf("buffer is null or length is 0.\n");
		return ;
	}

	printf("***************************protocol package start*************************\n");
	printf("length:%d\n",len);
	printf("data:");
	for(uint32_t i=0;i<len;i++)
	{
		printf("%02x ",(unsigned char)buffer[i]);
	}
	printf("\n");

	printf("***************************protocol package end*************************\n");
}



