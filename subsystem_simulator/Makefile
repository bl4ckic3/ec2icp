#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#
PROJ_PATH += .
ICP_PATH += ../icp
MQTT_PATH += ../mqtt

# define any directories containing header files other than /usr/include
#
LIBRARY_PATHS += $(PROJ_PATH)
LIBRARY_PATHS += $(PROJ_PATH)/include
LIBRARY_PATHS += $(ICP_PATH)/include
LIBRARY_PATHS += $(MQTT_PATH)/include

LIBRARY_INCLUDES = $(addprefix -I,$(LIBRARY_PATHS))

PROJ_SOURCE_PATH += $(PROJ_PATH)/source
ICP_SOURCE_PATH += $(ICP_PATH)/source
MQTT_SOURCE_PATH += $(MQTT_PATH)/source

SOURCE_PATHS += $(PROJ_PATH) $(PROJ_SOURCE_PATH) $(ICP_SOURCE_PATH) $(MQTT_SOURCE_PATH)
VPATH = $(SOURCE_PATHS)

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# LFLAGS = -L../lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
# LIBS = -lmylib -lm
# LIBS = -lpaho-mqtt3a

# define the C source files
APPLICATION_SRCS += $(filter-out MQTTClient.c MQTTVersion.c SSLSocket.c,$(notdir $(wildcard ../mqtt/source/*.c)))
APPLICATION_SRCS += $(notdir $(wildcard ../icp/source/*.c))
APPLICATION_SRCS += $(notdir $(wildcard ./source/*.c))
SRCS = $(SYSTEM_FILE) $(notdir $(APPLICATION_SRCS))

OUTPUT_PATH = ./_build/

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(addprefix $(OUTPUT_PATH),$(SRCS:.c=.o))
OBJS2 = $(addprefix $(OUTPUT_PATH),$(SRCS:.c=.o2))
OBJS3 = $(addprefix $(OUTPUT_PATH),$(SRCS:.c=.o3))
OBJS4 = $(addprefix $(OUTPUT_PATH),$(SRCS:.c=.o4))
# DEPS = $(addprefix $(OUTPUT_PATH), $(SRCS:.c=.d))
# SRCS_AS = $(START_CODE)
# OBJS_AS = $(addprefix $(OUTPUT_PATH), $(SRCS_AS:.s=.os))


# define the C compiler to use
CC = gcc

# define any compile-time flags
_CFLAGS = -Wall -g -DICPDEBUG -DMQTTDEBUG -DSYSDEBUG $(LIBRARY_INCLUDES)
CFLAGS = $(_CFLAGS) -DN_PC
CFLAGS2 = $(_CFLAGS) -DN_CAM
CFLAGS3 = $(_CFLAGS) -DN_EPS
CFLAGS4 = $(_CFLAGS) -DN_CDHS

# define the executable file 
PC = pc
CAM = cam
EPS = eps
CDHS = cdhs

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean rebuild
.SUFFIXES: .o2 .o3 .o4

# all:    $(PC)
all:    $(PC) $(CAM) $(EPS) $(CDHS)
pc:   	$(PC)
cam:    $(CAM)
eps:    $(EPS)
cdhs:   $(CDHS)

rebuild: clean all

MAKE_BUILD_FOLDER = mkdir -p $(OUTPUT_PATH)

clean:
	rm -rf $(OUTPUT_PATH)
	$(RM) *.o *.o2 *.o3 *.o4 *~ $(PC) $(CAM) $(EPS) $(CDHS)


$(PC): $(OBJS) 
	$(CC) $(CFLAGS) -o $(PC) $(OBJS) $(LFLAGS) $(LIBS)
	
$(CAM): $(OBJS2) 
	$(CC) $(CFLAGS2) -o $(CAM) $(OBJS2) $(LFLAGS) $(LIBS)

$(EPS): $(OBJS3) 
	$(CC) $(CFLAGS3) -o $(EPS) $(OBJS3) $(LFLAGS) $(LIBS)
	
$(CDHS): $(OBJS4) 
	$(CC) $(CFLAGS4) -o $(CDHS) $(OBJS4) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
# .c.o:

$(OUTPUT_PATH)%.o: %.c
	$(MAKE_BUILD_FOLDER)
	$(CC) $(CFLAGS) -c $<  -o $@

$(OUTPUT_PATH)%.o2: %.c
	$(MAKE_BUILD_FOLDER)
	$(CC) $(CFLAGS2) -c $<  -o $@

$(OUTPUT_PATH)%.o3: %.c
	$(MAKE_BUILD_FOLDER)
	$(CC) $(CFLAGS3) -c $<  -o $@

$(OUTPUT_PATH)%.o4: %.c
	$(MAKE_BUILD_FOLDER)
	$(CC) $(CFLAGS4) -c $<  -o $@

depend: $(SRCS)
	makedepend $(LIBRARY_INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
