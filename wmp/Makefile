###########################################################
#
#
#
#
#
#
###########################################################

CC 		= 	gcc
CXX		=	g++
CFLAGS	=	-shared -fPIC -O0 -g -std=c99
CXXFLAGS=	-shared -fPIC -O2 -g -Wall
INCLUDE	=	-I ../../3ty/ltm-0.41/libtommath-0.41 -I../../3ty/libtomcrypt-1.17/src/headers
LIBS	=	-L../../3ty/ltm-0.41/libtommath-0.41 -ltommath -L../../3ty/libtomcrypt-1.17 -ltomcrypt
DEFINES	=	-DCCP_DEBUG -DLTM_DESC -DUSE_LTM -DCTP_DEBUG -DGGP_DEBUG -DGCP_DEBUG -DWMP_DEBUG -DGNCP_DEBUG -DLINUX_OS -DCCP -DCTP -DGATEP
TARGET	= 	libprotocol.so
SOURCE	=	${wildcard *.c}

OBJS=${patsubst %c, %o, $(SOURCE)}

all:$(TARGET)	
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) $(DEFINES) -c $<
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(DEFINES) -o $@ $^ $(LIBS)

.PHONY	:	clean
clean:
	@rm -rf *.o $(TARGET)

