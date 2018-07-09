/* ************************************************************************
 *       Filename:  wm_package.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2017/07/08 10:13:30
 *       Revision:  none
 *       Compiler:  msvc/gcc
 *         Author:  YOUR NAME (xz.chen), 
 *        Company:  
 * ************************************************************************/

#include<malloc.h>
#include<stdint.h>
#include<string.h>
#include<stdio.h>
#include"wm_package.h"

/* Create wm_package instance. */
wm_package *create_wm_package(uint32_t length)
{
    wm_package *package = (wm_package *)malloc(sizeof(wm_package));

    memset(package,0,sizeof(wm_package));
	if(length)
	{
		package->length = length;
        package->data = (char *)malloc(length);
		memset(package->data,0,length);
	}
	return package;
}

/* Delete wm_package instance. */
void delete_wm_package(wm_package **package)
{
    if(package && (*package))
	{
        if((*package)->data)
        {
            free((*package)->data);
            (*package)->data = NULL;
        }
        free((*package));
		(*package) = NULL;
	}
}

/* Set wm_package data length and realloc memory and clear it as 0. */
void set_wm_package_length(wm_package *package,uint32_t length)
{
    if(!package)
		return ;

	if(package->data)
		free(package->data);

    package->length = length;
	package->data = (char *)malloc(length);
	memset(package->data,0,length);
}

/* Print wm_package. */
void print_wm_package(const wm_package *package)
{
	if(!package)
	{
        printf("wm_package is null.\n");
		return ;
	}

    printf("******************************wm_package_start******************************\n");
    printf("wm_package:\n");
	printf("length:%d\n",package->length);
	printf("data:");
    for(uint32_t i=0;i<package->length;i++)
		printf("%02x ",(unsigned char)package->data[i]);
	printf("\n");
    printf("*******************************wm_package_end*******************************\n");
}

/* Print buffer. */
void print_buffer(const char *buffer,uint32_t len)
{
	if(!buffer || !len)
	{
		printf("buffer is null or length is 0.\n");
		return ;
	}

    printf("********************************buffer_start********************************\n");
	printf("length:%d\n",len);
	printf("data:");
	for(uint32_t i=0;i<len;i++)
		printf("%02x ",(unsigned char)buffer[i]);
	printf("\n");

    printf("*********************************buffer_end*********************************\n");
}
