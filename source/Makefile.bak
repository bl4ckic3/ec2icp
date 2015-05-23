#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
_CFLAGS = -Wall -g -DICPDEBUG -DMQTTDEBUG -DCOBSDEBUG -DSYSDEBUG
CFLAGS = $(_CFLAGS) -DN_PC
CFLAGS2 = $(_CFLAGS) -DN_CAM
CFLAGS3 = $(_CFLAGS) -DN_EPS
CFLAGS4 = $(_CFLAGS) -DN_CDHS
# CFLAGS = -Wall -g -DMQTT_DEBUG -DICPDEBUG
# CFLAGS = -Wall -g 

# define any directories containing header files other than /usr/include
#
INCLUDES = -I../include

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
_SRCS = $(notdir $(wildcard *.c))
SRCS = $(filter-out MQTTClient.c MQTTVersion.c SSLSocket.c, $(_SRCS))

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)
OBJS2 = $(SRCS:.c=.o2)
OBJS3 = $(SRCS:.c=.o3)
OBJS4 = $(SRCS:.c=.o4)

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

.PHONY: depend clean
.SUFFIXES: .o2 .o3 .o4

all:    $(PC) $(CAM) $(EPS) $(CDHS)
pc:   	$(PC)
cam:    $(CAM)
eps:    $(EPS)
cdhs:   $(CDHS)

$(PC): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(PC) $(OBJS) $(LFLAGS) $(LIBS)
	
$(CAM): $(OBJS2) 
	$(CC) $(CFLAGS2) $(INCLUDES) -o $(CAM) $(OBJS2) $(LFLAGS) $(LIBS)

$(EPS): $(OBJS3) 
	$(CC) $(CFLAGS3) $(INCLUDES) -o $(EPS) $(OBJS3) $(LFLAGS) $(LIBS)
	
$(CDHS): $(OBJS4) 
	$(CC) $(CFLAGS4) $(INCLUDES) -o $(CDHS) $(OBJS4) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
.c.o2:
	$(CC) $(CFLAGS2) $(INCLUDES) -c $<  -o $@
.c.o3:
	$(CC) $(CFLAGS3) $(INCLUDES) -c $<  -o $@
.c.o4:
	$(CC) $(CFLAGS4) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *.o2 *.o3 *.o4 *~ $(PC) $(CAM) $(EPS) $(CDHS)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

Clients.o: ../include/Clients.h /usr/include/time.h /usr/include/_types.h
Clients.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
Clients.o: /usr/include/sys/_symbol_aliasing.h
Clients.o: /usr/include/sys/_posix_availability.h
Clients.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
Clients.o: /usr/include/sys/_pthread/_pthread_types.h
Clients.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_null.h
Clients.o: /usr/include/sys/_types/_size_t.h
Clients.o: /usr/include/sys/_types/_time_t.h
Clients.o: /usr/include/sys/_types/_timespec.h ../include/MQTTClient.h
Clients.o: /usr/include/stdio.h /usr/include/Availability.h
Clients.o: /usr/include/AvailabilityInternal.h
Clients.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
Clients.o: /usr/include/sys/_types/_off_t.h
Clients.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
Clients.o: /usr/include/secure/_common.h ../include/MQTTClientPersistence.h
Clients.o: ../include/LinkedList.h /usr/include/string.h
Clients.o: /usr/include/sys/_types/_rsize_t.h
Clients.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
Clients.o: /usr/include/secure/_string.h
Heap.o: ../include/Tree.h ../include/Log.h ../include/StackTrace.h
Heap.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
Heap.o: /usr/include/sys/_symbol_aliasing.h
Heap.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
Heap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
Heap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
Heap.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
Heap.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_size_t.h
Heap.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
Heap.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
Heap.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
Heap.o: ../include/Thread.h /usr/include/pthread.h
Heap.o: /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h
Heap.o: /usr/include/pthread_impl.h /usr/include/time.h
Heap.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
Heap.o: /usr/include/sys/_types/_timespec.h
Heap.o: /usr/include/sys/_pthread/_pthread_attr_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_cond_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_key_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_once_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
Heap.o: /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h
Heap.o: /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h
Heap.o: /usr/include/sys/_types/_sigset_t.h /usr/include/semaphore.h
Heap.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
Heap.o: /usr/include/machine/types.h /usr/include/i386/types.h
Heap.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
Heap.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
Heap.o: /usr/include/sys/_types/_intptr_t.h
Heap.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/machine/endian.h
Heap.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
Heap.o: /usr/include/libkern/_OSByteOrder.h
Heap.o: /usr/include/libkern/i386/_OSByteOrder.h
Heap.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
Heap.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
Heap.o: /usr/include/sys/_types/_in_addr_t.h
Heap.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
Heap.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
Heap.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_nlink_t.h
Heap.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
Heap.o: /usr/include/sys/_types/_uid_t.h
Heap.o: /usr/include/sys/_types/_useconds_t.h
Heap.o: /usr/include/sys/_types/_suseconds_t.h
Heap.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
Heap.o: /usr/include/sys/_types/_fd_def.h
Heap.o: /usr/include/sys/_types/_fd_setsize.h
Heap.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
Heap.o: /usr/include/sys/_types/_fd_zero.h
Heap.o: /usr/include/sys/_types/_fd_isset.h
Heap.o: /usr/include/sys/_types/_fd_copy.h
Heap.o: /usr/include/sys/_types/_fsblkcnt_t.h
Heap.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/fcntl.h
Heap.o: /usr/include/sys/_types/_o_sync.h /usr/include/sys/_types/_o_dsync.h
Heap.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/_types/_s_ifmt.h
Heap.o: /usr/include/sys/_types/_filesec_t.h /usr/include/sys/semaphore.h
Heap.o: /usr/include/memory.h /usr/include/string.h /usr/include/strings.h
Heap.o: /usr/include/secure/_string.h /usr/include/stdlib.h
Heap.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
Heap.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
Heap.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
Heap.o: /usr/include/mach/i386/_structs.h
Heap.o: /usr/include/sys/_types/_sigaltstack.h
Heap.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
Heap.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
Heap.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
Heap.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
Heap.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
Heap.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
Heap.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
Heap.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
Heap.o: /usr/include/sys/_types/_ptrdiff_t.h
Heap.o: /usr/include/sys/_types/_wint_t.h ../include/Heap.h
LinkedList.o: ../include/LinkedList.h /usr/include/stdlib.h
LinkedList.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
LinkedList.o: /usr/include/_types.h /usr/include/sys/_types.h
LinkedList.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
LinkedList.o: /usr/include/sys/_posix_availability.h
LinkedList.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
LinkedList.o: /usr/include/sys/_pthread/_pthread_types.h
LinkedList.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
LinkedList.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
LinkedList.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
LinkedList.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
LinkedList.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
LinkedList.o: /usr/include/sys/_pthread/_pthread_attr_t.h
LinkedList.o: /usr/include/sys/_types/_sigaltstack.h
LinkedList.o: /usr/include/sys/_types/_ucontext.h
LinkedList.o: /usr/include/sys/_types/_sigset_t.h
LinkedList.o: /usr/include/sys/_types/_size_t.h
LinkedList.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
LinkedList.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
LinkedList.o: /usr/include/sys/_types/_int16_t.h
LinkedList.o: /usr/include/sys/_types/_int32_t.h
LinkedList.o: /usr/include/sys/_types/_int64_t.h
LinkedList.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
LinkedList.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
LinkedList.o: /usr/include/sys/_types/_intptr_t.h
LinkedList.o: /usr/include/sys/_types/_uintptr_t.h
LinkedList.o: /usr/include/_types/_intmax_t.h
LinkedList.o: /usr/include/_types/_uintmax_t.h
LinkedList.o: /usr/include/sys/_types/_timeval.h
LinkedList.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
LinkedList.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
LinkedList.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
LinkedList.o: /usr/include/sys/_types/_ct_rune_t.h
LinkedList.o: /usr/include/sys/_types/_rune_t.h
LinkedList.o: /usr/include/sys/_types/_wchar_t.h
LinkedList.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
LinkedList.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
LinkedList.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
LinkedList.o: /usr/include/sys/_types/_rsize_t.h
LinkedList.o: /usr/include/sys/_types/_errno_t.h
LinkedList.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
LinkedList.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
LinkedList.o: /usr/include/memory.h ../include/Heap.h /usr/include/stdio.h
LinkedList.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
LinkedList.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
Log.o: ../include/Log.h ../include/MQTTPacket.h ../include/Socket.h
Log.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
Log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
Log.o: /usr/include/sys/_posix_availability.h /usr/include/machine/types.h
Log.o: /usr/include/i386/types.h /usr/include/i386/_types.h
Log.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
Log.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
Log.o: /usr/include/sys/_types/_intptr_t.h
Log.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/sys/_types.h
Log.o: /usr/include/machine/_types.h
Log.o: /usr/include/sys/_pthread/_pthread_types.h
Log.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
Log.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
Log.o: /usr/include/libkern/i386/_OSByteOrder.h
Log.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_blkcnt_t.h
Log.o: /usr/include/sys/_types/_blksize_t.h /usr/include/sys/_types/_gid_t.h
Log.o: /usr/include/sys/_types/_in_addr_t.h
Log.o: /usr/include/sys/_types/_in_port_t.h /usr/include/sys/_types/_ino_t.h
Log.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
Log.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_nlink_t.h
Log.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/_types/_pid_t.h
Log.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_uid_t.h
Log.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_size_t.h
Log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/sys/_types/_time_t.h
Log.o: /usr/include/sys/_types/_useconds_t.h
Log.o: /usr/include/sys/_types/_suseconds_t.h
Log.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
Log.o: /usr/include/sys/_types/_fd_def.h
Log.o: /usr/include/sys/_types/_fd_setsize.h
Log.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
Log.o: /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_isset.h
Log.o: /usr/include/sys/_types/_fd_copy.h
Log.o: /usr/include/sys/_pthread/_pthread_attr_t.h
Log.o: /usr/include/sys/_pthread/_pthread_cond_t.h
Log.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
Log.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
Log.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
Log.o: /usr/include/sys/_pthread/_pthread_once_t.h
Log.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
Log.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
Log.o: /usr/include/sys/_pthread/_pthread_t.h
Log.o: /usr/include/sys/_pthread/_pthread_key_t.h
Log.o: /usr/include/sys/_types/_fsblkcnt_t.h
Log.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/socket.h
Log.o: /usr/include/machine/_param.h /usr/include/i386/_param.h
Log.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
Log.o: /usr/include/sys/_types/_sa_family_t.h
Log.o: /usr/include/sys/_types/_socklen_t.h
Log.o: /usr/include/sys/_types/_iovec_t.h /usr/include/sys/param.h
Log.o: /usr/include/sys/_types/_null.h /usr/include/sys/syslimits.h
Log.o: /usr/include/machine/param.h /usr/include/i386/param.h
Log.o: /usr/include/limits.h /usr/include/machine/limits.h
Log.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
Log.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
Log.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
Log.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
Log.o: /usr/include/sys/_types/_sigaltstack.h
Log.o: /usr/include/sys/_types/_ucontext.h
Log.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/time.h
Log.o: /usr/include/sys/_types/_timespec.h /usr/include/sys/_types/_timeval.h
Log.o: /usr/include/time.h /usr/include/_types.h /usr/include/sys/_select.h
Log.o: /usr/include/sys/select.h /usr/include/netinet/in.h
Log.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
Log.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
Log.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
Log.o: /usr/include/_types/_uintmax_t.h /usr/include/netinet6/in6.h
Log.o: /usr/include/netinet/tcp.h /usr/include/arpa/inet.h
Log.o: /usr/include/netdb.h /usr/include/stdio.h
Log.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
Log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
Log.o: /usr/include/unistd.h /usr/include/sys/unistd.h
Log.o: /usr/include/sys/_types/_posix_vdisable.h
Log.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/_types/_uuid_t.h
Log.o: /usr/include/gethostuuid.h /usr/include/errno.h
Log.o: /usr/include/sys/errno.h /usr/include/fcntl.h /usr/include/sys/fcntl.h
Log.o: /usr/include/sys/_types/_o_sync.h /usr/include/sys/_types/_o_dsync.h
Log.o: /usr/include/sys/_types/_s_ifmt.h /usr/include/sys/_types/_filesec_t.h
Log.o: /usr/include/sys/uio.h ../include/LinkedList.h ../include/Clients.h
Log.o: ../include/MQTTClient.h ../include/MQTTClientPersistence.h
Log.o: ../include/MQTTPacketOut.h ../include/MQTTProtocol.h
Log.o: ../include/MQTTProtocolOut.h ../include/Messages.h
Log.o: ../include/MQTTProtocolClient.h ../include/StackTrace.h
Log.o: ../include/Thread.h /usr/include/pthread.h
Log.o: /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h
Log.o: /usr/include/pthread_impl.h /usr/include/pthread/qos.h
Log.o: /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h
Log.o: /usr/include/semaphore.h /usr/include/sys/semaphore.h
Log.o: /usr/include/stdlib.h /usr/include/sys/wait.h
Log.o: /usr/include/sys/resource.h /usr/include/alloca.h
Log.o: /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h
Log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/string.h
Log.o: /usr/include/strings.h /usr/include/secure/_string.h
Log.o: /usr/include/syslog.h /usr/include/sys/syslog.h
Log.o: /usr/include/sys/stat.h
MQTTAsync.o: /usr/include/stdlib.h /usr/include/Availability.h
MQTTAsync.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
MQTTAsync.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
MQTTAsync.o: /usr/include/sys/_symbol_aliasing.h
MQTTAsync.o: /usr/include/sys/_posix_availability.h
MQTTAsync.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_types.h
MQTTAsync.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
MQTTAsync.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
MQTTAsync.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
MQTTAsync.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
MQTTAsync.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_attr_t.h
MQTTAsync.o: /usr/include/sys/_types/_sigaltstack.h
MQTTAsync.o: /usr/include/sys/_types/_ucontext.h
MQTTAsync.o: /usr/include/sys/_types/_sigset_t.h
MQTTAsync.o: /usr/include/sys/_types/_size_t.h
MQTTAsync.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
MQTTAsync.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
MQTTAsync.o: /usr/include/sys/_types/_int16_t.h
MQTTAsync.o: /usr/include/sys/_types/_int32_t.h
MQTTAsync.o: /usr/include/sys/_types/_int64_t.h
MQTTAsync.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
MQTTAsync.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
MQTTAsync.o: /usr/include/sys/_types/_intptr_t.h
MQTTAsync.o: /usr/include/sys/_types/_uintptr_t.h
MQTTAsync.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
MQTTAsync.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
MQTTAsync.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
MQTTAsync.o: /usr/include/libkern/_OSByteOrder.h
MQTTAsync.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
MQTTAsync.o: /usr/include/sys/_types/_ct_rune_t.h
MQTTAsync.o: /usr/include/sys/_types/_rune_t.h
MQTTAsync.o: /usr/include/sys/_types/_wchar_t.h
MQTTAsync.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
MQTTAsync.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
MQTTAsync.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/time.h
MQTTAsync.o: /usr/include/sys/_types/_fd_def.h
MQTTAsync.o: /usr/include/sys/_types/_timespec.h
MQTTAsync.o: /usr/include/sys/_types/_time_t.h
MQTTAsync.o: /usr/include/sys/_types/_suseconds_t.h
MQTTAsync.o: /usr/include/sys/_types/_fd_setsize.h
MQTTAsync.o: /usr/include/sys/_types/_fd_set.h
MQTTAsync.o: /usr/include/sys/_types/_fd_clr.h
MQTTAsync.o: /usr/include/sys/_types/_fd_isset.h
MQTTAsync.o: /usr/include/sys/_types/_fd_zero.h
MQTTAsync.o: /usr/include/sys/_types/_fd_copy.h /usr/include/time.h
MQTTAsync.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_select.h
MQTTAsync.o: ../include/MQTTPersistence.h ../include/Clients.h
MQTTAsync.o: ../include/MQTTClient.h /usr/include/stdio.h
MQTTAsync.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
MQTTAsync.o: /usr/include/sys/_types/_off_t.h
MQTTAsync.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
MQTTAsync.o: /usr/include/secure/_common.h ../include/MQTTClientPersistence.h
MQTTAsync.o: ../include/LinkedList.h ../include/MQTTAsync.h
MQTTAsync.o: ../include/utf-8.h ../include/MQTTProtocol.h
MQTTAsync.o: ../include/MQTTPacket.h ../include/Socket.h
MQTTAsync.o: /usr/include/sys/types.h /usr/include/sys/_types/_blkcnt_t.h
MQTTAsync.o: /usr/include/sys/_types/_blksize_t.h
MQTTAsync.o: /usr/include/sys/_types/_gid_t.h
MQTTAsync.o: /usr/include/sys/_types/_in_addr_t.h
MQTTAsync.o: /usr/include/sys/_types/_in_port_t.h
MQTTAsync.o: /usr/include/sys/_types/_ino_t.h
MQTTAsync.o: /usr/include/sys/_types/_ino64_t.h
MQTTAsync.o: /usr/include/sys/_types/_key_t.h
MQTTAsync.o: /usr/include/sys/_types/_nlink_t.h
MQTTAsync.o: /usr/include/sys/_types/_useconds_t.h
MQTTAsync.o: /usr/include/sys/_types/_rsize_t.h
MQTTAsync.o: /usr/include/sys/_types/_errno_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_cond_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_once_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_t.h
MQTTAsync.o: /usr/include/sys/_pthread/_pthread_key_t.h
MQTTAsync.o: /usr/include/sys/_types/_fsblkcnt_t.h
MQTTAsync.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/socket.h
MQTTAsync.o: /usr/include/machine/_param.h /usr/include/i386/_param.h
MQTTAsync.o: /usr/include/sys/_types/_sa_family_t.h
MQTTAsync.o: /usr/include/sys/_types/_socklen_t.h
MQTTAsync.o: /usr/include/sys/_types/_iovec_t.h /usr/include/sys/param.h
MQTTAsync.o: /usr/include/sys/syslimits.h /usr/include/machine/param.h
MQTTAsync.o: /usr/include/i386/param.h /usr/include/limits.h
MQTTAsync.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
MQTTAsync.o: /usr/include/i386/_limits.h /usr/include/sys/select.h
MQTTAsync.o: /usr/include/netinet/in.h /usr/include/netinet6/in6.h
MQTTAsync.o: /usr/include/netinet/tcp.h /usr/include/arpa/inet.h
MQTTAsync.o: /usr/include/netdb.h /usr/include/unistd.h
MQTTAsync.o: /usr/include/sys/unistd.h
MQTTAsync.o: /usr/include/sys/_types/_posix_vdisable.h
MQTTAsync.o: /usr/include/sys/_types/_seek_set.h
MQTTAsync.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
MQTTAsync.o: /usr/include/errno.h /usr/include/sys/errno.h
MQTTAsync.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
MQTTAsync.o: /usr/include/sys/_types/_o_sync.h
MQTTAsync.o: /usr/include/sys/_types/_o_dsync.h
MQTTAsync.o: /usr/include/sys/_types/_s_ifmt.h
MQTTAsync.o: /usr/include/sys/_types/_filesec_t.h /usr/include/sys/uio.h
MQTTAsync.o: ../include/MQTTPacketOut.h ../include/MQTTProtocolOut.h
MQTTAsync.o: ../include/Log.h ../include/Messages.h
MQTTAsync.o: ../include/MQTTProtocolClient.h ../include/Thread.h
MQTTAsync.o: /usr/include/pthread.h /usr/include/pthread/pthread_impl.h
MQTTAsync.o: /usr/include/pthread/sched.h /usr/include/pthread_impl.h
MQTTAsync.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
MQTTAsync.o: /usr/include/sys/_types/_mach_port_t.h /usr/include/semaphore.h
MQTTAsync.o: /usr/include/sys/semaphore.h ../include/SocketBuffer.h
MQTTAsync.o: ../include/StackTrace.h ../include/Heap.h /usr/include/memory.h
MQTTAsync.o: /usr/include/string.h /usr/include/strings.h
MQTTAsync.o: /usr/include/secure/_string.h
MQTTPacket.o: ../include/MQTTPacket.h ../include/Socket.h
MQTTPacket.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
MQTTPacket.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
MQTTPacket.o: /usr/include/sys/_posix_availability.h
MQTTPacket.o: /usr/include/machine/types.h /usr/include/i386/types.h
MQTTPacket.o: /usr/include/i386/_types.h /usr/include/sys/_types/_int8_t.h
MQTTPacket.o: /usr/include/sys/_types/_int16_t.h
MQTTPacket.o: /usr/include/sys/_types/_int32_t.h
MQTTPacket.o: /usr/include/sys/_types/_int64_t.h
MQTTPacket.o: /usr/include/sys/_types/_intptr_t.h
MQTTPacket.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/sys/_types.h
MQTTPacket.o: /usr/include/machine/_types.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_types.h
MQTTPacket.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
MQTTPacket.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
MQTTPacket.o: /usr/include/libkern/i386/_OSByteOrder.h
MQTTPacket.o: /usr/include/sys/_types/_dev_t.h
MQTTPacket.o: /usr/include/sys/_types/_blkcnt_t.h
MQTTPacket.o: /usr/include/sys/_types/_blksize_t.h
MQTTPacket.o: /usr/include/sys/_types/_gid_t.h
MQTTPacket.o: /usr/include/sys/_types/_in_addr_t.h
MQTTPacket.o: /usr/include/sys/_types/_in_port_t.h
MQTTPacket.o: /usr/include/sys/_types/_ino_t.h
MQTTPacket.o: /usr/include/sys/_types/_ino64_t.h
MQTTPacket.o: /usr/include/sys/_types/_key_t.h
MQTTPacket.o: /usr/include/sys/_types/_mode_t.h
MQTTPacket.o: /usr/include/sys/_types/_nlink_t.h
MQTTPacket.o: /usr/include/sys/_types/_id_t.h
MQTTPacket.o: /usr/include/sys/_types/_pid_t.h
MQTTPacket.o: /usr/include/sys/_types/_off_t.h
MQTTPacket.o: /usr/include/sys/_types/_uid_t.h
MQTTPacket.o: /usr/include/sys/_types/_clock_t.h
MQTTPacket.o: /usr/include/sys/_types/_size_t.h
MQTTPacket.o: /usr/include/sys/_types/_ssize_t.h
MQTTPacket.o: /usr/include/sys/_types/_time_t.h
MQTTPacket.o: /usr/include/sys/_types/_useconds_t.h
MQTTPacket.o: /usr/include/sys/_types/_suseconds_t.h
MQTTPacket.o: /usr/include/sys/_types/_rsize_t.h
MQTTPacket.o: /usr/include/sys/_types/_errno_t.h
MQTTPacket.o: /usr/include/sys/_types/_fd_def.h
MQTTPacket.o: /usr/include/sys/_types/_fd_setsize.h
MQTTPacket.o: /usr/include/sys/_types/_fd_set.h
MQTTPacket.o: /usr/include/sys/_types/_fd_clr.h
MQTTPacket.o: /usr/include/sys/_types/_fd_zero.h
MQTTPacket.o: /usr/include/sys/_types/_fd_isset.h
MQTTPacket.o: /usr/include/sys/_types/_fd_copy.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_attr_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_cond_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_once_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_t.h
MQTTPacket.o: /usr/include/sys/_pthread/_pthread_key_t.h
MQTTPacket.o: /usr/include/sys/_types/_fsblkcnt_t.h
MQTTPacket.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/socket.h
MQTTPacket.o: /usr/include/machine/_param.h /usr/include/i386/_param.h
MQTTPacket.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
MQTTPacket.o: /usr/include/sys/_types/_sa_family_t.h
MQTTPacket.o: /usr/include/sys/_types/_socklen_t.h
MQTTPacket.o: /usr/include/sys/_types/_iovec_t.h /usr/include/sys/param.h
MQTTPacket.o: /usr/include/sys/_types/_null.h /usr/include/sys/syslimits.h
MQTTPacket.o: /usr/include/machine/param.h /usr/include/i386/param.h
MQTTPacket.o: /usr/include/limits.h /usr/include/machine/limits.h
MQTTPacket.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
MQTTPacket.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
MQTTPacket.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
MQTTPacket.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
MQTTPacket.o: /usr/include/sys/_types/_sigaltstack.h
MQTTPacket.o: /usr/include/sys/_types/_ucontext.h
MQTTPacket.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/time.h
MQTTPacket.o: /usr/include/sys/_types/_timespec.h
MQTTPacket.o: /usr/include/sys/_types/_timeval.h /usr/include/time.h
MQTTPacket.o: /usr/include/_types.h /usr/include/sys/_select.h
MQTTPacket.o: /usr/include/sys/select.h /usr/include/netinet/in.h
MQTTPacket.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
MQTTPacket.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
MQTTPacket.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
MQTTPacket.o: /usr/include/_types/_uintmax_t.h /usr/include/netinet6/in6.h
MQTTPacket.o: /usr/include/netinet/tcp.h /usr/include/arpa/inet.h
MQTTPacket.o: /usr/include/netdb.h /usr/include/stdio.h
MQTTPacket.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
MQTTPacket.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
MQTTPacket.o: /usr/include/unistd.h /usr/include/sys/unistd.h
MQTTPacket.o: /usr/include/sys/_types/_posix_vdisable.h
MQTTPacket.o: /usr/include/sys/_types/_seek_set.h
MQTTPacket.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
MQTTPacket.o: /usr/include/errno.h /usr/include/sys/errno.h
MQTTPacket.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
MQTTPacket.o: /usr/include/sys/_types/_o_sync.h
MQTTPacket.o: /usr/include/sys/_types/_o_dsync.h
MQTTPacket.o: /usr/include/sys/_types/_s_ifmt.h
MQTTPacket.o: /usr/include/sys/_types/_filesec_t.h /usr/include/sys/uio.h
MQTTPacket.o: ../include/LinkedList.h ../include/Clients.h
MQTTPacket.o: ../include/MQTTClient.h ../include/MQTTClientPersistence.h
MQTTPacket.o: ../include/MQTTPacketOut.h ../include/Log.h
MQTTPacket.o: ../include/MQTTPersistence.h ../include/Messages.h
MQTTPacket.o: ../include/StackTrace.h ../include/Thread.h
MQTTPacket.o: /usr/include/pthread.h /usr/include/pthread/pthread_impl.h
MQTTPacket.o: /usr/include/pthread/sched.h /usr/include/pthread_impl.h
MQTTPacket.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
MQTTPacket.o: /usr/include/sys/_types/_mach_port_t.h /usr/include/semaphore.h
MQTTPacket.o: /usr/include/sys/semaphore.h /usr/include/stdlib.h
MQTTPacket.o: /usr/include/sys/wait.h /usr/include/sys/resource.h
MQTTPacket.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
MQTTPacket.o: /usr/include/sys/_types/_rune_t.h
MQTTPacket.o: /usr/include/sys/_types/_wchar_t.h /usr/include/string.h
MQTTPacket.o: /usr/include/strings.h /usr/include/secure/_string.h
MQTTPacket.o: ../include/Heap.h /usr/include/memory.h
MQTTPacketOut.o: ../include/MQTTPacketOut.h ../include/MQTTPacket.h
MQTTPacketOut.o: ../include/Socket.h /usr/include/sys/types.h
MQTTPacketOut.o: /usr/include/sys/appleapiopts.h /usr/include/sys/cdefs.h
MQTTPacketOut.o: /usr/include/sys/_symbol_aliasing.h
MQTTPacketOut.o: /usr/include/sys/_posix_availability.h
MQTTPacketOut.o: /usr/include/machine/types.h /usr/include/i386/types.h
MQTTPacketOut.o: /usr/include/i386/_types.h /usr/include/sys/_types/_int8_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_int16_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_int32_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_int64_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_intptr_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_uintptr_t.h
MQTTPacketOut.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_types.h
MQTTPacketOut.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
MQTTPacketOut.o: /usr/include/sys/_endian.h
MQTTPacketOut.o: /usr/include/libkern/_OSByteOrder.h
MQTTPacketOut.o: /usr/include/libkern/i386/_OSByteOrder.h
MQTTPacketOut.o: /usr/include/sys/_types/_dev_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_blkcnt_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_blksize_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_gid_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_in_addr_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_in_port_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_ino_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_ino64_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_key_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_mode_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_nlink_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_id_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_pid_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_off_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_uid_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_clock_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_size_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_ssize_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_time_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_useconds_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_suseconds_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_rsize_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_errno_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_fd_def.h
MQTTPacketOut.o: /usr/include/sys/_types/_fd_setsize.h
MQTTPacketOut.o: /usr/include/sys/_types/_fd_set.h
MQTTPacketOut.o: /usr/include/sys/_types/_fd_clr.h
MQTTPacketOut.o: /usr/include/sys/_types/_fd_zero.h
MQTTPacketOut.o: /usr/include/sys/_types/_fd_isset.h
MQTTPacketOut.o: /usr/include/sys/_types/_fd_copy.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_attr_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_cond_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_once_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_t.h
MQTTPacketOut.o: /usr/include/sys/_pthread/_pthread_key_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_fsblkcnt_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_fsfilcnt_t.h
MQTTPacketOut.o: /usr/include/sys/socket.h /usr/include/machine/_param.h
MQTTPacketOut.o: /usr/include/i386/_param.h /usr/include/Availability.h
MQTTPacketOut.o: /usr/include/AvailabilityInternal.h
MQTTPacketOut.o: /usr/include/sys/_types/_sa_family_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_socklen_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_iovec_t.h /usr/include/sys/param.h
MQTTPacketOut.o: /usr/include/sys/_types/_null.h /usr/include/sys/syslimits.h
MQTTPacketOut.o: /usr/include/machine/param.h /usr/include/i386/param.h
MQTTPacketOut.o: /usr/include/limits.h /usr/include/machine/limits.h
MQTTPacketOut.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
MQTTPacketOut.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
MQTTPacketOut.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
MQTTPacketOut.o: /usr/include/i386/_mcontext.h
MQTTPacketOut.o: /usr/include/mach/i386/_structs.h
MQTTPacketOut.o: /usr/include/sys/_types/_sigaltstack.h
MQTTPacketOut.o: /usr/include/sys/_types/_ucontext.h
MQTTPacketOut.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/time.h
MQTTPacketOut.o: /usr/include/sys/_types/_timespec.h
MQTTPacketOut.o: /usr/include/sys/_types/_timeval.h /usr/include/time.h
MQTTPacketOut.o: /usr/include/_types.h /usr/include/sys/_select.h
MQTTPacketOut.o: /usr/include/sys/select.h /usr/include/netinet/in.h
MQTTPacketOut.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
MQTTPacketOut.o: /usr/include/_types/_uint16_t.h
MQTTPacketOut.o: /usr/include/_types/_uint32_t.h
MQTTPacketOut.o: /usr/include/_types/_uint64_t.h
MQTTPacketOut.o: /usr/include/_types/_intmax_t.h
MQTTPacketOut.o: /usr/include/_types/_uintmax_t.h /usr/include/netinet6/in6.h
MQTTPacketOut.o: /usr/include/netinet/tcp.h /usr/include/arpa/inet.h
MQTTPacketOut.o: /usr/include/netdb.h /usr/include/stdio.h
MQTTPacketOut.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
MQTTPacketOut.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
MQTTPacketOut.o: /usr/include/unistd.h /usr/include/sys/unistd.h
MQTTPacketOut.o: /usr/include/sys/_types/_posix_vdisable.h
MQTTPacketOut.o: /usr/include/sys/_types/_seek_set.h
MQTTPacketOut.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
MQTTPacketOut.o: /usr/include/errno.h /usr/include/sys/errno.h
MQTTPacketOut.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
MQTTPacketOut.o: /usr/include/sys/_types/_o_sync.h
MQTTPacketOut.o: /usr/include/sys/_types/_o_dsync.h
MQTTPacketOut.o: /usr/include/sys/_types/_s_ifmt.h
MQTTPacketOut.o: /usr/include/sys/_types/_filesec_t.h /usr/include/sys/uio.h
MQTTPacketOut.o: ../include/LinkedList.h ../include/Clients.h
MQTTPacketOut.o: ../include/MQTTClient.h ../include/MQTTClientPersistence.h
MQTTPacketOut.o: ../include/Log.h ../include/StackTrace.h ../include/Thread.h
MQTTPacketOut.o: /usr/include/pthread.h /usr/include/pthread/pthread_impl.h
MQTTPacketOut.o: /usr/include/pthread/sched.h /usr/include/pthread_impl.h
MQTTPacketOut.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
MQTTPacketOut.o: /usr/include/sys/_types/_mach_port_t.h
MQTTPacketOut.o: /usr/include/semaphore.h /usr/include/sys/semaphore.h
MQTTPacketOut.o: /usr/include/string.h /usr/include/strings.h
MQTTPacketOut.o: /usr/include/secure/_string.h /usr/include/stdlib.h
MQTTPacketOut.o: /usr/include/sys/wait.h /usr/include/sys/resource.h
MQTTPacketOut.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_rune_t.h
MQTTPacketOut.o: /usr/include/sys/_types/_wchar_t.h ../include/Heap.h
MQTTPacketOut.o: /usr/include/memory.h
MQTTPersistence.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
MQTTPersistence.o: /usr/include/sys/_symbol_aliasing.h
MQTTPersistence.o: /usr/include/sys/_posix_availability.h
MQTTPersistence.o: /usr/include/Availability.h
MQTTPersistence.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
MQTTPersistence.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
MQTTPersistence.o: /usr/include/i386/_types.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_types.h
MQTTPersistence.o: /usr/include/sys/_types/_va_list.h
MQTTPersistence.o: /usr/include/sys/_types/_size_t.h
MQTTPersistence.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
MQTTPersistence.o: /usr/include/sys/_types/_off_t.h
MQTTPersistence.o: /usr/include/sys/_types/_ssize_t.h
MQTTPersistence.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
MQTTPersistence.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
MQTTPersistence.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
MQTTPersistence.o: /usr/include/secure/_string.h ../include/MQTTPersistence.h
MQTTPersistence.o: ../include/Clients.h /usr/include/time.h
MQTTPersistence.o: /usr/include/sys/_types/_clock_t.h
MQTTPersistence.o: /usr/include/sys/_types/_time_t.h
MQTTPersistence.o: /usr/include/sys/_types/_timespec.h
MQTTPersistence.o: ../include/MQTTClient.h ../include/MQTTClientPersistence.h
MQTTPersistence.o: ../include/LinkedList.h
MQTTPersistence.o: ../include/MQTTPersistenceDefault.h
MQTTPersistence.o: ../include/MQTTProtocolClient.h ../include/MQTTPacket.h
MQTTPersistence.o: ../include/Socket.h /usr/include/sys/types.h
MQTTPersistence.o: /usr/include/sys/appleapiopts.h
MQTTPersistence.o: /usr/include/machine/types.h /usr/include/i386/types.h
MQTTPersistence.o: /usr/include/sys/_types/_int8_t.h
MQTTPersistence.o: /usr/include/sys/_types/_int16_t.h
MQTTPersistence.o: /usr/include/sys/_types/_int32_t.h
MQTTPersistence.o: /usr/include/sys/_types/_int64_t.h
MQTTPersistence.o: /usr/include/sys/_types/_intptr_t.h
MQTTPersistence.o: /usr/include/sys/_types/_uintptr_t.h
MQTTPersistence.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
MQTTPersistence.o: /usr/include/sys/_endian.h
MQTTPersistence.o: /usr/include/libkern/_OSByteOrder.h
MQTTPersistence.o: /usr/include/libkern/i386/_OSByteOrder.h
MQTTPersistence.o: /usr/include/sys/_types/_dev_t.h
MQTTPersistence.o: /usr/include/sys/_types/_blkcnt_t.h
MQTTPersistence.o: /usr/include/sys/_types/_blksize_t.h
MQTTPersistence.o: /usr/include/sys/_types/_gid_t.h
MQTTPersistence.o: /usr/include/sys/_types/_in_addr_t.h
MQTTPersistence.o: /usr/include/sys/_types/_in_port_t.h
MQTTPersistence.o: /usr/include/sys/_types/_ino_t.h
MQTTPersistence.o: /usr/include/sys/_types/_ino64_t.h
MQTTPersistence.o: /usr/include/sys/_types/_key_t.h
MQTTPersistence.o: /usr/include/sys/_types/_mode_t.h
MQTTPersistence.o: /usr/include/sys/_types/_nlink_t.h
MQTTPersistence.o: /usr/include/sys/_types/_id_t.h
MQTTPersistence.o: /usr/include/sys/_types/_pid_t.h
MQTTPersistence.o: /usr/include/sys/_types/_uid_t.h
MQTTPersistence.o: /usr/include/sys/_types/_useconds_t.h
MQTTPersistence.o: /usr/include/sys/_types/_suseconds_t.h
MQTTPersistence.o: /usr/include/sys/_types/_fd_def.h
MQTTPersistence.o: /usr/include/sys/_types/_fd_setsize.h
MQTTPersistence.o: /usr/include/sys/_types/_fd_set.h
MQTTPersistence.o: /usr/include/sys/_types/_fd_clr.h
MQTTPersistence.o: /usr/include/sys/_types/_fd_zero.h
MQTTPersistence.o: /usr/include/sys/_types/_fd_isset.h
MQTTPersistence.o: /usr/include/sys/_types/_fd_copy.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_attr_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_cond_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_once_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_t.h
MQTTPersistence.o: /usr/include/sys/_pthread/_pthread_key_t.h
MQTTPersistence.o: /usr/include/sys/_types/_fsblkcnt_t.h
MQTTPersistence.o: /usr/include/sys/_types/_fsfilcnt_t.h
MQTTPersistence.o: /usr/include/sys/socket.h /usr/include/machine/_param.h
MQTTPersistence.o: /usr/include/i386/_param.h
MQTTPersistence.o: /usr/include/sys/_types/_sa_family_t.h
MQTTPersistence.o: /usr/include/sys/_types/_socklen_t.h
MQTTPersistence.o: /usr/include/sys/_types/_iovec_t.h
MQTTPersistence.o: /usr/include/sys/param.h /usr/include/sys/syslimits.h
MQTTPersistence.o: /usr/include/machine/param.h /usr/include/i386/param.h
MQTTPersistence.o: /usr/include/limits.h /usr/include/machine/limits.h
MQTTPersistence.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
MQTTPersistence.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
MQTTPersistence.o: /usr/include/i386/signal.h
MQTTPersistence.o: /usr/include/machine/_mcontext.h
MQTTPersistence.o: /usr/include/i386/_mcontext.h
MQTTPersistence.o: /usr/include/mach/i386/_structs.h
MQTTPersistence.o: /usr/include/sys/_types/_sigaltstack.h
MQTTPersistence.o: /usr/include/sys/_types/_ucontext.h
MQTTPersistence.o: /usr/include/sys/_types/_sigset_t.h
MQTTPersistence.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval.h
MQTTPersistence.o: /usr/include/sys/_select.h /usr/include/sys/select.h
MQTTPersistence.o: /usr/include/netinet/in.h /usr/include/stdint.h
MQTTPersistence.o: /usr/include/_types/_uint8_t.h
MQTTPersistence.o: /usr/include/_types/_uint16_t.h
MQTTPersistence.o: /usr/include/_types/_uint32_t.h
MQTTPersistence.o: /usr/include/_types/_uint64_t.h
MQTTPersistence.o: /usr/include/_types/_intmax_t.h
MQTTPersistence.o: /usr/include/_types/_uintmax_t.h
MQTTPersistence.o: /usr/include/netinet6/in6.h /usr/include/netinet/tcp.h
MQTTPersistence.o: /usr/include/arpa/inet.h /usr/include/netdb.h
MQTTPersistence.o: /usr/include/unistd.h /usr/include/sys/unistd.h
MQTTPersistence.o: /usr/include/sys/_types/_posix_vdisable.h
MQTTPersistence.o: /usr/include/sys/_types/_seek_set.h
MQTTPersistence.o: /usr/include/sys/_types/_uuid_t.h
MQTTPersistence.o: /usr/include/gethostuuid.h /usr/include/errno.h
MQTTPersistence.o: /usr/include/sys/errno.h /usr/include/fcntl.h
MQTTPersistence.o: /usr/include/sys/fcntl.h /usr/include/sys/_types/_o_sync.h
MQTTPersistence.o: /usr/include/sys/_types/_o_dsync.h
MQTTPersistence.o: /usr/include/sys/_types/_s_ifmt.h
MQTTPersistence.o: /usr/include/sys/_types/_filesec_t.h
MQTTPersistence.o: /usr/include/sys/uio.h ../include/MQTTPacketOut.h
MQTTPersistence.o: ../include/Log.h ../include/MQTTProtocol.h
MQTTPersistence.o: ../include/MQTTProtocolOut.h ../include/Messages.h
MQTTPersistence.o: ../include/Heap.h /usr/include/memory.h
MQTTPersistence.o: /usr/include/stdlib.h /usr/include/sys/wait.h
MQTTPersistence.o: /usr/include/sys/resource.h /usr/include/alloca.h
MQTTPersistence.o: /usr/include/sys/_types/_ct_rune_t.h
MQTTPersistence.o: /usr/include/sys/_types/_rune_t.h
MQTTPersistence.o: /usr/include/sys/_types/_wchar_t.h ../include/StackTrace.h
MQTTPersistence.o: ../include/Thread.h /usr/include/pthread.h
MQTTPersistence.o: /usr/include/pthread/pthread_impl.h
MQTTPersistence.o: /usr/include/pthread/sched.h /usr/include/pthread_impl.h
MQTTPersistence.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
MQTTPersistence.o: /usr/include/sys/_types/_mach_port_t.h
MQTTPersistence.o: /usr/include/semaphore.h /usr/include/sys/semaphore.h
MQTTPersistenceDefault.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
MQTTPersistenceDefault.o: /usr/include/sys/_symbol_aliasing.h
MQTTPersistenceDefault.o: /usr/include/sys/_posix_availability.h
MQTTPersistenceDefault.o: /usr/include/Availability.h
MQTTPersistenceDefault.o: /usr/include/AvailabilityInternal.h
MQTTPersistenceDefault.o: /usr/include/_types.h /usr/include/sys/_types.h
MQTTPersistenceDefault.o: /usr/include/machine/_types.h
MQTTPersistenceDefault.o: /usr/include/i386/_types.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_types.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_va_list.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_size_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_null.h
MQTTPersistenceDefault.o: /usr/include/sys/stdio.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_off_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_ssize_t.h
MQTTPersistenceDefault.o: /usr/include/secure/_stdio.h
MQTTPersistenceDefault.o: /usr/include/secure/_common.h /usr/include/string.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_rsize_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_errno_t.h
MQTTPersistenceDefault.o: /usr/include/strings.h
MQTTPersistenceDefault.o: /usr/include/secure/_string.h /usr/include/errno.h
MQTTPersistenceDefault.o: /usr/include/sys/errno.h /usr/include/sys/stat.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_timespec.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_blkcnt_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_blksize_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_dev_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_ino_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_ino64_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_mode_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_nlink_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_uid_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_gid_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_time_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_s_ifmt.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_filesec_t.h
MQTTPersistenceDefault.o: /usr/include/dirent.h /usr/include/sys/dirent.h
MQTTPersistenceDefault.o: /usr/include/unistd.h /usr/include/sys/unistd.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_posix_vdisable.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_seek_set.h
MQTTPersistenceDefault.o: /usr/include/_types/_uint64_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_intptr_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_pid_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_useconds_t.h
MQTTPersistenceDefault.o: /usr/include/sys/select.h
MQTTPersistenceDefault.o: /usr/include/sys/appleapiopts.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fd_def.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_timeval.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_suseconds_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_sigset_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fd_setsize.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fd_set.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fd_clr.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fd_isset.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fd_zero.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fd_copy.h
MQTTPersistenceDefault.o: /usr/include/sys/_select.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_uuid_t.h
MQTTPersistenceDefault.o: /usr/include/gethostuuid.h
MQTTPersistenceDefault.o: ../include/MQTTClientPersistence.h
MQTTPersistenceDefault.o: ../include/MQTTPersistenceDefault.h
MQTTPersistenceDefault.o: ../include/StackTrace.h ../include/Log.h
MQTTPersistenceDefault.o: ../include/Thread.h /usr/include/pthread.h
MQTTPersistenceDefault.o: /usr/include/pthread/pthread_impl.h
MQTTPersistenceDefault.o: /usr/include/pthread/sched.h
MQTTPersistenceDefault.o: /usr/include/pthread_impl.h /usr/include/time.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_clock_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_attr_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_cond_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_key_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_once_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_pthread/_pthread_t.h
MQTTPersistenceDefault.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_mach_port_t.h
MQTTPersistenceDefault.o: /usr/include/semaphore.h /usr/include/sys/types.h
MQTTPersistenceDefault.o: /usr/include/machine/types.h
MQTTPersistenceDefault.o: /usr/include/i386/types.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_int8_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_int16_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_int32_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_int64_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_uintptr_t.h
MQTTPersistenceDefault.o: /usr/include/machine/endian.h
MQTTPersistenceDefault.o: /usr/include/i386/endian.h
MQTTPersistenceDefault.o: /usr/include/sys/_endian.h
MQTTPersistenceDefault.o: /usr/include/libkern/_OSByteOrder.h
MQTTPersistenceDefault.o: /usr/include/libkern/i386/_OSByteOrder.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_in_addr_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_in_port_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_key_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_id_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fsblkcnt_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_fsfilcnt_t.h
MQTTPersistenceDefault.o: /usr/include/sys/fcntl.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_o_sync.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_o_dsync.h
MQTTPersistenceDefault.o: /usr/include/sys/semaphore.h ../include/Heap.h
MQTTPersistenceDefault.o: /usr/include/memory.h /usr/include/stdlib.h
MQTTPersistenceDefault.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
MQTTPersistenceDefault.o: /usr/include/machine/signal.h
MQTTPersistenceDefault.o: /usr/include/i386/signal.h
MQTTPersistenceDefault.o: /usr/include/machine/_mcontext.h
MQTTPersistenceDefault.o: /usr/include/i386/_mcontext.h
MQTTPersistenceDefault.o: /usr/include/mach/i386/_structs.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_sigaltstack.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_ucontext.h
MQTTPersistenceDefault.o: /usr/include/sys/resource.h /usr/include/stdint.h
MQTTPersistenceDefault.o: /usr/include/_types/_uint8_t.h
MQTTPersistenceDefault.o: /usr/include/_types/_uint16_t.h
MQTTPersistenceDefault.o: /usr/include/_types/_uint32_t.h
MQTTPersistenceDefault.o: /usr/include/_types/_intmax_t.h
MQTTPersistenceDefault.o: /usr/include/_types/_uintmax_t.h
MQTTPersistenceDefault.o: /usr/include/alloca.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_ct_rune_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_rune_t.h
MQTTPersistenceDefault.o: /usr/include/sys/_types/_wchar_t.h
MQTTProtocolClient.o: /usr/include/stdlib.h /usr/include/Availability.h
MQTTProtocolClient.o: /usr/include/AvailabilityInternal.h
MQTTProtocolClient.o: /usr/include/_types.h /usr/include/sys/_types.h
MQTTProtocolClient.o: /usr/include/sys/cdefs.h
MQTTProtocolClient.o: /usr/include/sys/_symbol_aliasing.h
MQTTProtocolClient.o: /usr/include/sys/_posix_availability.h
MQTTProtocolClient.o: /usr/include/machine/_types.h
MQTTProtocolClient.o: /usr/include/i386/_types.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_types.h
MQTTProtocolClient.o: /usr/include/sys/wait.h
MQTTProtocolClient.o: /usr/include/sys/_types/_pid_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_id_t.h
MQTTProtocolClient.o: /usr/include/sys/signal.h
MQTTProtocolClient.o: /usr/include/sys/appleapiopts.h
MQTTProtocolClient.o: /usr/include/machine/signal.h
MQTTProtocolClient.o: /usr/include/i386/signal.h
MQTTProtocolClient.o: /usr/include/machine/_mcontext.h
MQTTProtocolClient.o: /usr/include/i386/_mcontext.h
MQTTProtocolClient.o: /usr/include/mach/i386/_structs.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_attr_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_sigaltstack.h
MQTTProtocolClient.o: /usr/include/sys/_types/_ucontext.h
MQTTProtocolClient.o: /usr/include/sys/_types/_sigset_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_size_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_uid_t.h
MQTTProtocolClient.o: /usr/include/sys/resource.h /usr/include/stdint.h
MQTTProtocolClient.o: /usr/include/sys/_types/_int8_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_int16_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_int32_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_int64_t.h
MQTTProtocolClient.o: /usr/include/_types/_uint8_t.h
MQTTProtocolClient.o: /usr/include/_types/_uint16_t.h
MQTTProtocolClient.o: /usr/include/_types/_uint32_t.h
MQTTProtocolClient.o: /usr/include/_types/_uint64_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_intptr_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_uintptr_t.h
MQTTProtocolClient.o: /usr/include/_types/_intmax_t.h
MQTTProtocolClient.o: /usr/include/_types/_uintmax_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_timeval.h
MQTTProtocolClient.o: /usr/include/machine/endian.h
MQTTProtocolClient.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
MQTTProtocolClient.o: /usr/include/libkern/_OSByteOrder.h
MQTTProtocolClient.o: /usr/include/libkern/i386/_OSByteOrder.h
MQTTProtocolClient.o: /usr/include/alloca.h
MQTTProtocolClient.o: /usr/include/sys/_types/_ct_rune_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_rune_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_wchar_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_null.h
MQTTProtocolClient.o: /usr/include/machine/types.h /usr/include/i386/types.h
MQTTProtocolClient.o: /usr/include/sys/_types/_dev_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_mode_t.h
MQTTProtocolClient.o: ../include/MQTTProtocolClient.h ../include/LinkedList.h
MQTTProtocolClient.o: ../include/MQTTPacket.h ../include/Socket.h
MQTTProtocolClient.o: /usr/include/sys/types.h
MQTTProtocolClient.o: /usr/include/sys/_types/_blkcnt_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_blksize_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_gid_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_in_addr_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_in_port_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_ino_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_ino64_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_key_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_nlink_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_off_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_clock_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_ssize_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_time_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_useconds_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_suseconds_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_rsize_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_errno_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fd_def.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fd_setsize.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fd_set.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fd_clr.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fd_zero.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fd_isset.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fd_copy.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_cond_t.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_once_t.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_t.h
MQTTProtocolClient.o: /usr/include/sys/_pthread/_pthread_key_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fsblkcnt_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_fsfilcnt_t.h
MQTTProtocolClient.o: /usr/include/sys/socket.h /usr/include/machine/_param.h
MQTTProtocolClient.o: /usr/include/i386/_param.h
MQTTProtocolClient.o: /usr/include/sys/_types/_sa_family_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_socklen_t.h
MQTTProtocolClient.o: /usr/include/sys/_types/_iovec_t.h
MQTTProtocolClient.o: /usr/include/sys/param.h /usr/include/sys/syslimits.h
MQTTProtocolClient.o: /usr/include/machine/param.h /usr/include/i386/param.h
MQTTProtocolClient.o: /usr/include/limits.h /usr/include/machine/limits.h
MQTTProtocolClient.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
MQTTProtocolClient.o: /usr/include/sys/time.h
MQTTProtocolClient.o: /usr/include/sys/_types/_timespec.h /usr/include/time.h
MQTTProtocolClient.o: /usr/include/sys/_select.h /usr/include/sys/select.h
MQTTProtocolClient.o: /usr/include/netinet/in.h /usr/include/netinet6/in6.h
MQTTProtocolClient.o: /usr/include/netinet/tcp.h /usr/include/arpa/inet.h
MQTTProtocolClient.o: /usr/include/netdb.h /usr/include/stdio.h
MQTTProtocolClient.o: /usr/include/sys/_types/_va_list.h
MQTTProtocolClient.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
MQTTProtocolClient.o: /usr/include/secure/_common.h /usr/include/unistd.h
MQTTProtocolClient.o: /usr/include/sys/unistd.h
MQTTProtocolClient.o: /usr/include/sys/_types/_posix_vdisable.h
MQTTProtocolClient.o: /usr/include/sys/_types/_seek_set.h
MQTTProtocolClient.o: /usr/include/sys/_types/_uuid_t.h
MQTTProtocolClient.o: /usr/include/gethostuuid.h /usr/include/errno.h
MQTTProtocolClient.o: /usr/include/sys/errno.h /usr/include/fcntl.h
MQTTProtocolClient.o: /usr/include/sys/fcntl.h
MQTTProtocolClient.o: /usr/include/sys/_types/_o_sync.h
MQTTProtocolClient.o: /usr/include/sys/_types/_o_dsync.h
MQTTProtocolClient.o: /usr/include/sys/_types/_s_ifmt.h
MQTTProtocolClient.o: /usr/include/sys/_types/_filesec_t.h
MQTTProtocolClient.o: /usr/include/sys/uio.h ../include/Clients.h
MQTTProtocolClient.o: ../include/MQTTClient.h
MQTTProtocolClient.o: ../include/MQTTClientPersistence.h
MQTTProtocolClient.o: ../include/MQTTPacketOut.h ../include/Log.h
MQTTProtocolClient.o: ../include/MQTTProtocol.h ../include/MQTTProtocolOut.h
MQTTProtocolClient.o: ../include/Messages.h ../include/MQTTPersistence.h
MQTTProtocolClient.o: ../include/SocketBuffer.h ../include/StackTrace.h
MQTTProtocolClient.o: ../include/Thread.h /usr/include/pthread.h
MQTTProtocolClient.o: /usr/include/pthread/pthread_impl.h
MQTTProtocolClient.o: /usr/include/pthread/sched.h
MQTTProtocolClient.o: /usr/include/pthread_impl.h /usr/include/pthread/qos.h
MQTTProtocolClient.o: /usr/include/sys/qos.h
MQTTProtocolClient.o: /usr/include/sys/_types/_mach_port_t.h
MQTTProtocolClient.o: /usr/include/semaphore.h /usr/include/sys/semaphore.h
MQTTProtocolClient.o: ../include/Heap.h /usr/include/memory.h
MQTTProtocolClient.o: /usr/include/string.h /usr/include/strings.h
MQTTProtocolClient.o: /usr/include/secure/_string.h
MQTTProtocolOut.o: /usr/include/stdlib.h /usr/include/Availability.h
MQTTProtocolOut.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
MQTTProtocolOut.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
MQTTProtocolOut.o: /usr/include/sys/_symbol_aliasing.h
MQTTProtocolOut.o: /usr/include/sys/_posix_availability.h
MQTTProtocolOut.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_types.h
MQTTProtocolOut.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
MQTTProtocolOut.o: /usr/include/sys/appleapiopts.h
MQTTProtocolOut.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
MQTTProtocolOut.o: /usr/include/machine/_mcontext.h
MQTTProtocolOut.o: /usr/include/i386/_mcontext.h
MQTTProtocolOut.o: /usr/include/mach/i386/_structs.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_attr_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_sigaltstack.h
MQTTProtocolOut.o: /usr/include/sys/_types/_ucontext.h
MQTTProtocolOut.o: /usr/include/sys/_types/_sigset_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_size_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_uid_t.h
MQTTProtocolOut.o: /usr/include/sys/resource.h /usr/include/stdint.h
MQTTProtocolOut.o: /usr/include/sys/_types/_int8_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_int16_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_int32_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_int64_t.h
MQTTProtocolOut.o: /usr/include/_types/_uint8_t.h
MQTTProtocolOut.o: /usr/include/_types/_uint16_t.h
MQTTProtocolOut.o: /usr/include/_types/_uint32_t.h
MQTTProtocolOut.o: /usr/include/_types/_uint64_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_intptr_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_uintptr_t.h
MQTTProtocolOut.o: /usr/include/_types/_intmax_t.h
MQTTProtocolOut.o: /usr/include/_types/_uintmax_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_timeval.h
MQTTProtocolOut.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
MQTTProtocolOut.o: /usr/include/sys/_endian.h
MQTTProtocolOut.o: /usr/include/libkern/_OSByteOrder.h
MQTTProtocolOut.o: /usr/include/libkern/i386/_OSByteOrder.h
MQTTProtocolOut.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_rune_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_wchar_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_null.h
MQTTProtocolOut.o: /usr/include/machine/types.h /usr/include/i386/types.h
MQTTProtocolOut.o: /usr/include/sys/_types/_dev_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_mode_t.h
MQTTProtocolOut.o: ../include/MQTTProtocolOut.h ../include/LinkedList.h
MQTTProtocolOut.o: ../include/MQTTPacket.h ../include/Socket.h
MQTTProtocolOut.o: /usr/include/sys/types.h
MQTTProtocolOut.o: /usr/include/sys/_types/_blkcnt_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_blksize_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_gid_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_in_addr_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_in_port_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_ino_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_ino64_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_key_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_nlink_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_off_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_clock_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_ssize_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_time_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_useconds_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_suseconds_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_rsize_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_errno_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fd_def.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fd_setsize.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fd_set.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fd_clr.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fd_zero.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fd_isset.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fd_copy.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_cond_t.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_once_t.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_t.h
MQTTProtocolOut.o: /usr/include/sys/_pthread/_pthread_key_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fsblkcnt_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_fsfilcnt_t.h
MQTTProtocolOut.o: /usr/include/sys/socket.h /usr/include/machine/_param.h
MQTTProtocolOut.o: /usr/include/i386/_param.h
MQTTProtocolOut.o: /usr/include/sys/_types/_sa_family_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_socklen_t.h
MQTTProtocolOut.o: /usr/include/sys/_types/_iovec_t.h
MQTTProtocolOut.o: /usr/include/sys/param.h /usr/include/sys/syslimits.h
MQTTProtocolOut.o: /usr/include/machine/param.h /usr/include/i386/param.h
MQTTProtocolOut.o: /usr/include/limits.h /usr/include/machine/limits.h
MQTTProtocolOut.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
MQTTProtocolOut.o: /usr/include/sys/time.h
MQTTProtocolOut.o: /usr/include/sys/_types/_timespec.h /usr/include/time.h
MQTTProtocolOut.o: /usr/include/sys/_select.h /usr/include/sys/select.h
MQTTProtocolOut.o: /usr/include/netinet/in.h /usr/include/netinet6/in6.h
MQTTProtocolOut.o: /usr/include/netinet/tcp.h /usr/include/arpa/inet.h
MQTTProtocolOut.o: /usr/include/netdb.h /usr/include/stdio.h
MQTTProtocolOut.o: /usr/include/sys/_types/_va_list.h
MQTTProtocolOut.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
MQTTProtocolOut.o: /usr/include/secure/_common.h /usr/include/unistd.h
MQTTProtocolOut.o: /usr/include/sys/unistd.h
MQTTProtocolOut.o: /usr/include/sys/_types/_posix_vdisable.h
MQTTProtocolOut.o: /usr/include/sys/_types/_seek_set.h
MQTTProtocolOut.o: /usr/include/sys/_types/_uuid_t.h
MQTTProtocolOut.o: /usr/include/gethostuuid.h /usr/include/errno.h
MQTTProtocolOut.o: /usr/include/sys/errno.h /usr/include/fcntl.h
MQTTProtocolOut.o: /usr/include/sys/fcntl.h /usr/include/sys/_types/_o_sync.h
MQTTProtocolOut.o: /usr/include/sys/_types/_o_dsync.h
MQTTProtocolOut.o: /usr/include/sys/_types/_s_ifmt.h
MQTTProtocolOut.o: /usr/include/sys/_types/_filesec_t.h
MQTTProtocolOut.o: /usr/include/sys/uio.h ../include/Clients.h
MQTTProtocolOut.o: ../include/MQTTClient.h ../include/MQTTClientPersistence.h
MQTTProtocolOut.o: ../include/MQTTPacketOut.h ../include/Log.h
MQTTProtocolOut.o: ../include/Messages.h ../include/MQTTProtocol.h
MQTTProtocolOut.o: ../include/MQTTProtocolClient.h ../include/StackTrace.h
MQTTProtocolOut.o: ../include/Thread.h /usr/include/pthread.h
MQTTProtocolOut.o: /usr/include/pthread/pthread_impl.h
MQTTProtocolOut.o: /usr/include/pthread/sched.h /usr/include/pthread_impl.h
MQTTProtocolOut.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
MQTTProtocolOut.o: /usr/include/sys/_types/_mach_port_t.h
MQTTProtocolOut.o: /usr/include/semaphore.h /usr/include/sys/semaphore.h
MQTTProtocolOut.o: ../include/Heap.h /usr/include/memory.h
MQTTProtocolOut.o: /usr/include/string.h /usr/include/strings.h
MQTTProtocolOut.o: /usr/include/secure/_string.h
Messages.o: ../include/Messages.h ../include/Log.h /usr/include/stdio.h
Messages.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
Messages.o: /usr/include/sys/_posix_availability.h
Messages.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
Messages.o: /usr/include/_types.h /usr/include/sys/_types.h
Messages.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
Messages.o: /usr/include/sys/_pthread/_pthread_types.h
Messages.o: /usr/include/sys/_types/_va_list.h
Messages.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
Messages.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
Messages.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
Messages.o: /usr/include/secure/_common.h /usr/include/stdlib.h
Messages.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
Messages.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
Messages.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
Messages.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
Messages.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
Messages.o: /usr/include/sys/_pthread/_pthread_attr_t.h
Messages.o: /usr/include/sys/_types/_sigaltstack.h
Messages.o: /usr/include/sys/_types/_ucontext.h
Messages.o: /usr/include/sys/_types/_sigset_t.h
Messages.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
Messages.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
Messages.o: /usr/include/sys/_types/_int16_t.h
Messages.o: /usr/include/sys/_types/_int32_t.h
Messages.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
Messages.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
Messages.o: /usr/include/_types/_uint64_t.h
Messages.o: /usr/include/sys/_types/_intptr_t.h
Messages.o: /usr/include/sys/_types/_uintptr_t.h
Messages.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
Messages.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
Messages.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
Messages.o: /usr/include/libkern/_OSByteOrder.h
Messages.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
Messages.o: /usr/include/sys/_types/_ct_rune_t.h
Messages.o: /usr/include/sys/_types/_rune_t.h
Messages.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
Messages.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
Messages.o: /usr/include/sys/_types/_mode_t.h /usr/include/memory.h
Messages.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
Messages.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
Messages.o: /usr/include/secure/_string.h ../include/Heap.h
Socket.o: ../include/Socket.h /usr/include/sys/types.h
Socket.o: /usr/include/sys/appleapiopts.h /usr/include/sys/cdefs.h
Socket.o: /usr/include/sys/_symbol_aliasing.h
Socket.o: /usr/include/sys/_posix_availability.h /usr/include/machine/types.h
Socket.o: /usr/include/i386/types.h /usr/include/i386/_types.h
Socket.o: /usr/include/sys/_types/_int8_t.h
Socket.o: /usr/include/sys/_types/_int16_t.h
Socket.o: /usr/include/sys/_types/_int32_t.h
Socket.o: /usr/include/sys/_types/_int64_t.h
Socket.o: /usr/include/sys/_types/_intptr_t.h
Socket.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/sys/_types.h
Socket.o: /usr/include/machine/_types.h
Socket.o: /usr/include/sys/_pthread/_pthread_types.h
Socket.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
Socket.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
Socket.o: /usr/include/libkern/i386/_OSByteOrder.h
Socket.o: /usr/include/sys/_types/_dev_t.h
Socket.o: /usr/include/sys/_types/_blkcnt_t.h
Socket.o: /usr/include/sys/_types/_blksize_t.h
Socket.o: /usr/include/sys/_types/_gid_t.h
Socket.o: /usr/include/sys/_types/_in_addr_t.h
Socket.o: /usr/include/sys/_types/_in_port_t.h
Socket.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
Socket.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
Socket.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
Socket.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_off_t.h
Socket.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_clock_t.h
Socket.o: /usr/include/sys/_types/_size_t.h
Socket.o: /usr/include/sys/_types/_ssize_t.h
Socket.o: /usr/include/sys/_types/_time_t.h
Socket.o: /usr/include/sys/_types/_useconds_t.h
Socket.o: /usr/include/sys/_types/_suseconds_t.h
Socket.o: /usr/include/sys/_types/_rsize_t.h
Socket.o: /usr/include/sys/_types/_errno_t.h
Socket.o: /usr/include/sys/_types/_fd_def.h
Socket.o: /usr/include/sys/_types/_fd_setsize.h
Socket.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
Socket.o: /usr/include/sys/_types/_fd_zero.h
Socket.o: /usr/include/sys/_types/_fd_isset.h
Socket.o: /usr/include/sys/_types/_fd_copy.h
Socket.o: /usr/include/sys/_pthread/_pthread_attr_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_cond_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_once_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_t.h
Socket.o: /usr/include/sys/_pthread/_pthread_key_t.h
Socket.o: /usr/include/sys/_types/_fsblkcnt_t.h
Socket.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/socket.h
Socket.o: /usr/include/machine/_param.h /usr/include/i386/_param.h
Socket.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
Socket.o: /usr/include/sys/_types/_sa_family_t.h
Socket.o: /usr/include/sys/_types/_socklen_t.h
Socket.o: /usr/include/sys/_types/_iovec_t.h /usr/include/sys/param.h
Socket.o: /usr/include/sys/_types/_null.h /usr/include/sys/syslimits.h
Socket.o: /usr/include/machine/param.h /usr/include/i386/param.h
Socket.o: /usr/include/limits.h /usr/include/machine/limits.h
Socket.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
Socket.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
Socket.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
Socket.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
Socket.o: /usr/include/sys/_types/_sigaltstack.h
Socket.o: /usr/include/sys/_types/_ucontext.h
Socket.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/time.h
Socket.o: /usr/include/sys/_types/_timespec.h
Socket.o: /usr/include/sys/_types/_timeval.h /usr/include/time.h
Socket.o: /usr/include/_types.h /usr/include/sys/_select.h
Socket.o: /usr/include/sys/select.h /usr/include/netinet/in.h
Socket.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
Socket.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
Socket.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
Socket.o: /usr/include/_types/_uintmax_t.h /usr/include/netinet6/in6.h
Socket.o: /usr/include/netinet/tcp.h /usr/include/arpa/inet.h
Socket.o: /usr/include/netdb.h /usr/include/stdio.h
Socket.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
Socket.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
Socket.o: /usr/include/unistd.h /usr/include/sys/unistd.h
Socket.o: /usr/include/sys/_types/_posix_vdisable.h
Socket.o: /usr/include/sys/_types/_seek_set.h
Socket.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
Socket.o: /usr/include/errno.h /usr/include/sys/errno.h /usr/include/fcntl.h
Socket.o: /usr/include/sys/fcntl.h /usr/include/sys/_types/_o_sync.h
Socket.o: /usr/include/sys/_types/_o_dsync.h
Socket.o: /usr/include/sys/_types/_s_ifmt.h
Socket.o: /usr/include/sys/_types/_filesec_t.h /usr/include/sys/uio.h
Socket.o: ../include/LinkedList.h ../include/Log.h ../include/SocketBuffer.h
Socket.o: ../include/Messages.h ../include/StackTrace.h ../include/Thread.h
Socket.o: /usr/include/pthread.h /usr/include/pthread/pthread_impl.h
Socket.o: /usr/include/pthread/sched.h /usr/include/pthread_impl.h
Socket.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
Socket.o: /usr/include/sys/_types/_mach_port_t.h /usr/include/semaphore.h
Socket.o: /usr/include/sys/semaphore.h /usr/include/stdlib.h
Socket.o: /usr/include/sys/wait.h /usr/include/sys/resource.h
Socket.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
Socket.o: /usr/include/sys/_types/_rune_t.h
Socket.o: /usr/include/sys/_types/_wchar_t.h /usr/include/string.h
Socket.o: /usr/include/strings.h /usr/include/secure/_string.h
Socket.o: /usr/include/signal.h /usr/include/ctype.h /usr/include/runetype.h
Socket.o: /usr/include/sys/_types/_wint_t.h ../include/Heap.h
Socket.o: /usr/include/memory.h
SocketBuffer.o: ../include/SocketBuffer.h /usr/include/sys/socket.h
SocketBuffer.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
SocketBuffer.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
SocketBuffer.o: /usr/include/sys/_posix_availability.h
SocketBuffer.o: /usr/include/machine/types.h /usr/include/i386/types.h
SocketBuffer.o: /usr/include/i386/_types.h /usr/include/sys/_types/_int8_t.h
SocketBuffer.o: /usr/include/sys/_types/_int16_t.h
SocketBuffer.o: /usr/include/sys/_types/_int32_t.h
SocketBuffer.o: /usr/include/sys/_types/_int64_t.h
SocketBuffer.o: /usr/include/sys/_types/_intptr_t.h
SocketBuffer.o: /usr/include/sys/_types/_uintptr_t.h
SocketBuffer.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_types.h
SocketBuffer.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
SocketBuffer.o: /usr/include/sys/_endian.h
SocketBuffer.o: /usr/include/libkern/_OSByteOrder.h
SocketBuffer.o: /usr/include/libkern/i386/_OSByteOrder.h
SocketBuffer.o: /usr/include/sys/_types/_dev_t.h
SocketBuffer.o: /usr/include/sys/_types/_blkcnt_t.h
SocketBuffer.o: /usr/include/sys/_types/_blksize_t.h
SocketBuffer.o: /usr/include/sys/_types/_gid_t.h
SocketBuffer.o: /usr/include/sys/_types/_in_addr_t.h
SocketBuffer.o: /usr/include/sys/_types/_in_port_t.h
SocketBuffer.o: /usr/include/sys/_types/_ino_t.h
SocketBuffer.o: /usr/include/sys/_types/_ino64_t.h
SocketBuffer.o: /usr/include/sys/_types/_key_t.h
SocketBuffer.o: /usr/include/sys/_types/_mode_t.h
SocketBuffer.o: /usr/include/sys/_types/_nlink_t.h
SocketBuffer.o: /usr/include/sys/_types/_id_t.h
SocketBuffer.o: /usr/include/sys/_types/_pid_t.h
SocketBuffer.o: /usr/include/sys/_types/_off_t.h
SocketBuffer.o: /usr/include/sys/_types/_uid_t.h
SocketBuffer.o: /usr/include/sys/_types/_clock_t.h
SocketBuffer.o: /usr/include/sys/_types/_size_t.h
SocketBuffer.o: /usr/include/sys/_types/_ssize_t.h
SocketBuffer.o: /usr/include/sys/_types/_time_t.h
SocketBuffer.o: /usr/include/sys/_types/_useconds_t.h
SocketBuffer.o: /usr/include/sys/_types/_suseconds_t.h
SocketBuffer.o: /usr/include/sys/_types/_rsize_t.h
SocketBuffer.o: /usr/include/sys/_types/_errno_t.h
SocketBuffer.o: /usr/include/sys/_types/_fd_def.h
SocketBuffer.o: /usr/include/sys/_types/_fd_setsize.h
SocketBuffer.o: /usr/include/sys/_types/_fd_set.h
SocketBuffer.o: /usr/include/sys/_types/_fd_clr.h
SocketBuffer.o: /usr/include/sys/_types/_fd_zero.h
SocketBuffer.o: /usr/include/sys/_types/_fd_isset.h
SocketBuffer.o: /usr/include/sys/_types/_fd_copy.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_attr_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_cond_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_once_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_t.h
SocketBuffer.o: /usr/include/sys/_pthread/_pthread_key_t.h
SocketBuffer.o: /usr/include/sys/_types/_fsblkcnt_t.h
SocketBuffer.o: /usr/include/sys/_types/_fsfilcnt_t.h
SocketBuffer.o: /usr/include/machine/_param.h /usr/include/i386/_param.h
SocketBuffer.o: /usr/include/Availability.h
SocketBuffer.o: /usr/include/AvailabilityInternal.h
SocketBuffer.o: /usr/include/sys/_types/_sa_family_t.h
SocketBuffer.o: /usr/include/sys/_types/_socklen_t.h
SocketBuffer.o: /usr/include/sys/_types/_iovec_t.h ../include/LinkedList.h
SocketBuffer.o: ../include/Log.h ../include/Messages.h
SocketBuffer.o: ../include/StackTrace.h /usr/include/stdio.h
SocketBuffer.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
SocketBuffer.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
SocketBuffer.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
SocketBuffer.o: ../include/Thread.h /usr/include/pthread.h
SocketBuffer.o: /usr/include/pthread/pthread_impl.h
SocketBuffer.o: /usr/include/pthread/sched.h /usr/include/pthread_impl.h
SocketBuffer.o: /usr/include/time.h /usr/include/sys/_types/_timespec.h
SocketBuffer.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
SocketBuffer.o: /usr/include/sys/_types/_mach_port_t.h
SocketBuffer.o: /usr/include/sys/_types/_sigset_t.h /usr/include/semaphore.h
SocketBuffer.o: /usr/include/sys/fcntl.h /usr/include/sys/_types/_o_sync.h
SocketBuffer.o: /usr/include/sys/_types/_o_dsync.h
SocketBuffer.o: /usr/include/sys/_types/_seek_set.h
SocketBuffer.o: /usr/include/sys/_types/_s_ifmt.h
SocketBuffer.o: /usr/include/sys/_types/_filesec_t.h
SocketBuffer.o: /usr/include/sys/semaphore.h /usr/include/stdlib.h
SocketBuffer.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
SocketBuffer.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
SocketBuffer.o: /usr/include/machine/_mcontext.h
SocketBuffer.o: /usr/include/i386/_mcontext.h
SocketBuffer.o: /usr/include/mach/i386/_structs.h
SocketBuffer.o: /usr/include/sys/_types/_sigaltstack.h
SocketBuffer.o: /usr/include/sys/_types/_ucontext.h
SocketBuffer.o: /usr/include/sys/resource.h /usr/include/stdint.h
SocketBuffer.o: /usr/include/_types/_uint8_t.h
SocketBuffer.o: /usr/include/_types/_uint16_t.h
SocketBuffer.o: /usr/include/_types/_uint32_t.h
SocketBuffer.o: /usr/include/_types/_uint64_t.h
SocketBuffer.o: /usr/include/_types/_intmax_t.h
SocketBuffer.o: /usr/include/_types/_uintmax_t.h
SocketBuffer.o: /usr/include/sys/_types/_timeval.h /usr/include/alloca.h
SocketBuffer.o: /usr/include/sys/_types/_ct_rune_t.h
SocketBuffer.o: /usr/include/sys/_types/_rune_t.h
SocketBuffer.o: /usr/include/sys/_types/_wchar_t.h /usr/include/memory.h
SocketBuffer.o: /usr/include/string.h /usr/include/strings.h
SocketBuffer.o: /usr/include/secure/_string.h ../include/Heap.h
StackTrace.o: ../include/StackTrace.h /usr/include/stdio.h
StackTrace.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
StackTrace.o: /usr/include/sys/_posix_availability.h
StackTrace.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
StackTrace.o: /usr/include/_types.h /usr/include/sys/_types.h
StackTrace.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_types.h
StackTrace.o: /usr/include/sys/_types/_va_list.h
StackTrace.o: /usr/include/sys/_types/_size_t.h
StackTrace.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
StackTrace.o: /usr/include/sys/_types/_off_t.h
StackTrace.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
StackTrace.o: /usr/include/secure/_common.h ../include/Log.h
StackTrace.o: ../include/Thread.h /usr/include/pthread.h
StackTrace.o: /usr/include/pthread/pthread_impl.h
StackTrace.o: /usr/include/pthread/sched.h /usr/include/pthread_impl.h
StackTrace.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
StackTrace.o: /usr/include/sys/_types/_time_t.h
StackTrace.o: /usr/include/sys/_types/_timespec.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_attr_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_cond_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_key_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_once_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
StackTrace.o: /usr/include/sys/_pthread/_pthread_t.h
StackTrace.o: /usr/include/pthread/qos.h /usr/include/sys/qos.h
StackTrace.o: /usr/include/sys/_types/_mach_port_t.h
StackTrace.o: /usr/include/sys/_types/_sigset_t.h /usr/include/semaphore.h
StackTrace.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
StackTrace.o: /usr/include/machine/types.h /usr/include/i386/types.h
StackTrace.o: /usr/include/sys/_types/_int8_t.h
StackTrace.o: /usr/include/sys/_types/_int16_t.h
StackTrace.o: /usr/include/sys/_types/_int32_t.h
StackTrace.o: /usr/include/sys/_types/_int64_t.h
StackTrace.o: /usr/include/sys/_types/_intptr_t.h
StackTrace.o: /usr/include/sys/_types/_uintptr_t.h
StackTrace.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
StackTrace.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
StackTrace.o: /usr/include/libkern/i386/_OSByteOrder.h
StackTrace.o: /usr/include/sys/_types/_dev_t.h
StackTrace.o: /usr/include/sys/_types/_blkcnt_t.h
StackTrace.o: /usr/include/sys/_types/_blksize_t.h
StackTrace.o: /usr/include/sys/_types/_gid_t.h
StackTrace.o: /usr/include/sys/_types/_in_addr_t.h
StackTrace.o: /usr/include/sys/_types/_in_port_t.h
StackTrace.o: /usr/include/sys/_types/_ino_t.h
StackTrace.o: /usr/include/sys/_types/_ino64_t.h
StackTrace.o: /usr/include/sys/_types/_key_t.h
StackTrace.o: /usr/include/sys/_types/_mode_t.h
StackTrace.o: /usr/include/sys/_types/_nlink_t.h
StackTrace.o: /usr/include/sys/_types/_id_t.h
StackTrace.o: /usr/include/sys/_types/_pid_t.h
StackTrace.o: /usr/include/sys/_types/_uid_t.h
StackTrace.o: /usr/include/sys/_types/_useconds_t.h
StackTrace.o: /usr/include/sys/_types/_suseconds_t.h
StackTrace.o: /usr/include/sys/_types/_rsize_t.h
StackTrace.o: /usr/include/sys/_types/_errno_t.h
StackTrace.o: /usr/include/sys/_types/_fd_def.h
StackTrace.o: /usr/include/sys/_types/_fd_setsize.h
StackTrace.o: /usr/include/sys/_types/_fd_set.h
StackTrace.o: /usr/include/sys/_types/_fd_clr.h
StackTrace.o: /usr/include/sys/_types/_fd_zero.h
StackTrace.o: /usr/include/sys/_types/_fd_isset.h
StackTrace.o: /usr/include/sys/_types/_fd_copy.h
StackTrace.o: /usr/include/sys/_types/_fsblkcnt_t.h
StackTrace.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/fcntl.h
StackTrace.o: /usr/include/sys/_types/_o_sync.h
StackTrace.o: /usr/include/sys/_types/_o_dsync.h
StackTrace.o: /usr/include/sys/_types/_seek_set.h
StackTrace.o: /usr/include/sys/_types/_s_ifmt.h
StackTrace.o: /usr/include/sys/_types/_filesec_t.h
StackTrace.o: /usr/include/sys/semaphore.h ../include/LinkedList.h
StackTrace.o: ../include/Clients.h ../include/MQTTClient.h
StackTrace.o: ../include/MQTTClientPersistence.h /usr/include/string.h
StackTrace.o: /usr/include/strings.h /usr/include/secure/_string.h
StackTrace.o: /usr/include/stdlib.h /usr/include/sys/wait.h
StackTrace.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
StackTrace.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
StackTrace.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
StackTrace.o: /usr/include/sys/_types/_sigaltstack.h
StackTrace.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
StackTrace.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
StackTrace.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
StackTrace.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
StackTrace.o: /usr/include/_types/_uintmax_t.h
StackTrace.o: /usr/include/sys/_types/_timeval.h /usr/include/alloca.h
StackTrace.o: /usr/include/sys/_types/_ct_rune_t.h
StackTrace.o: /usr/include/sys/_types/_rune_t.h
StackTrace.o: /usr/include/sys/_types/_wchar_t.h
Thread.o: ../include/Thread.h /usr/include/pthread.h /usr/include/_types.h
Thread.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
Thread.o: /usr/include/sys/_symbol_aliasing.h
Thread.o: /usr/include/sys/_posix_availability.h
Thread.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
Thread.o: /usr/include/sys/_pthread/_pthread_types.h
Thread.o: /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h
Thread.o: /usr/include/pthread_impl.h /usr/include/time.h
Thread.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_null.h
Thread.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_time_t.h
Thread.o: /usr/include/sys/_types/_timespec.h
Thread.o: /usr/include/sys/_pthread/_pthread_attr_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_cond_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_key_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_once_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
Thread.o: /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h
Thread.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
Thread.o: /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h
Thread.o: /usr/include/sys/_types/_sigset_t.h /usr/include/semaphore.h
Thread.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
Thread.o: /usr/include/machine/types.h /usr/include/i386/types.h
Thread.o: /usr/include/sys/_types/_int8_t.h
Thread.o: /usr/include/sys/_types/_int16_t.h
Thread.o: /usr/include/sys/_types/_int32_t.h
Thread.o: /usr/include/sys/_types/_int64_t.h
Thread.o: /usr/include/sys/_types/_intptr_t.h
Thread.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/machine/endian.h
Thread.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
Thread.o: /usr/include/libkern/_OSByteOrder.h
Thread.o: /usr/include/libkern/i386/_OSByteOrder.h
Thread.o: /usr/include/sys/_types/_dev_t.h
Thread.o: /usr/include/sys/_types/_blkcnt_t.h
Thread.o: /usr/include/sys/_types/_blksize_t.h
Thread.o: /usr/include/sys/_types/_gid_t.h
Thread.o: /usr/include/sys/_types/_in_addr_t.h
Thread.o: /usr/include/sys/_types/_in_port_t.h
Thread.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
Thread.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
Thread.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
Thread.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_off_t.h
Thread.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_ssize_t.h
Thread.o: /usr/include/sys/_types/_useconds_t.h
Thread.o: /usr/include/sys/_types/_suseconds_t.h
Thread.o: /usr/include/sys/_types/_rsize_t.h
Thread.o: /usr/include/sys/_types/_errno_t.h
Thread.o: /usr/include/sys/_types/_fd_def.h
Thread.o: /usr/include/sys/_types/_fd_setsize.h
Thread.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
Thread.o: /usr/include/sys/_types/_fd_zero.h
Thread.o: /usr/include/sys/_types/_fd_isset.h
Thread.o: /usr/include/sys/_types/_fd_copy.h
Thread.o: /usr/include/sys/_types/_fsblkcnt_t.h
Thread.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/fcntl.h
Thread.o: /usr/include/sys/_types/_o_sync.h
Thread.o: /usr/include/sys/_types/_o_dsync.h
Thread.o: /usr/include/sys/_types/_seek_set.h
Thread.o: /usr/include/sys/_types/_s_ifmt.h
Thread.o: /usr/include/sys/_types/_filesec_t.h /usr/include/sys/semaphore.h
Thread.o: ../include/StackTrace.h /usr/include/stdio.h
Thread.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
Thread.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
Thread.o: ../include/Log.h /usr/include/errno.h /usr/include/sys/errno.h
Thread.o: /usr/include/unistd.h /usr/include/sys/unistd.h
Thread.o: /usr/include/sys/_types/_posix_vdisable.h
Thread.o: /usr/include/_types/_uint64_t.h /usr/include/sys/select.h
Thread.o: /usr/include/sys/_types/_timeval.h /usr/include/sys/_select.h
Thread.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
Thread.o: /usr/include/sys/time.h /usr/include/fcntl.h
Thread.o: /usr/include/sys/stat.h /usr/include/limits.h
Thread.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
Thread.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h
Thread.o: /usr/include/memory.h /usr/include/string.h /usr/include/strings.h
Thread.o: /usr/include/secure/_string.h /usr/include/stdlib.h
Thread.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
Thread.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
Thread.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
Thread.o: /usr/include/mach/i386/_structs.h
Thread.o: /usr/include/sys/_types/_sigaltstack.h
Thread.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
Thread.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
Thread.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
Thread.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
Thread.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
Thread.o: /usr/include/sys/_types/_rune_t.h
Thread.o: /usr/include/sys/_types/_wchar_t.h
Tree.o: ../include/Tree.h /usr/include/stdlib.h /usr/include/Availability.h
Tree.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
Tree.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
Tree.o: /usr/include/sys/_symbol_aliasing.h
Tree.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
Tree.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
Tree.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
Tree.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
Tree.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
Tree.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
Tree.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
Tree.o: /usr/include/sys/_pthread/_pthread_attr_t.h
Tree.o: /usr/include/sys/_types/_sigaltstack.h
Tree.o: /usr/include/sys/_types/_ucontext.h
Tree.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_size_t.h
Tree.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
Tree.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
Tree.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
Tree.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
Tree.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
Tree.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
Tree.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
Tree.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
Tree.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
Tree.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
Tree.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
Tree.o: /usr/include/sys/_types/_ct_rune_t.h
Tree.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
Tree.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
Tree.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
Tree.o: /usr/include/sys/_types/_mode_t.h /usr/include/stdio.h
Tree.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
Tree.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
Tree.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
Tree.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
Tree.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
Tree.o: /usr/include/secure/_string.h /usr/include/memory.h ../include/Heap.h
icp.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
icp.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
icp.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
icp.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
icp.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
icp.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
icp.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
icp.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
icp.o: /usr/include/sys/_types/_intptr_t.h
icp.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
icp.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
icp.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
icp.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
icp.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
icp.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
icp.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
icp.o: /usr/include/secure/_common.h /usr/include/string.h
icp.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
icp.o: /usr/include/strings.h /usr/include/secure/_string.h
icp.o: /usr/include/stdlib.h /usr/include/sys/wait.h
icp.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
icp.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
icp.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
icp.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
icp.o: /usr/include/mach/i386/_structs.h
icp.o: /usr/include/sys/_pthread/_pthread_attr_t.h
icp.o: /usr/include/sys/_types/_sigaltstack.h
icp.o: /usr/include/sys/_types/_ucontext.h
icp.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
icp.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
icp.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
icp.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
icp.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
icp.o: /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h
icp.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
icp.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
icp.o: /usr/include/sys/_types/_mode_t.h ../include/icp.h
icp.o: ../include/icp_config.h ../include/icp_shared_config.h
icp.o: ../include/dbg.h /usr/include/errno.h /usr/include/sys/errno.h
icp.o: /usr/include/unistd.h /usr/include/sys/unistd.h
icp.o: /usr/include/sys/_types/_posix_vdisable.h
icp.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/_types/_gid_t.h
icp.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
icp.o: /usr/include/sys/_types/_fd_def.h /usr/include/sys/_types/_timespec.h
icp.o: /usr/include/sys/_types/_time_t.h
icp.o: /usr/include/sys/_types/_suseconds_t.h
icp.o: /usr/include/sys/_types/_fd_setsize.h
icp.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
icp.o: /usr/include/sys/_types/_fd_isset.h /usr/include/sys/_types/_fd_zero.h
icp.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
icp.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
icp.o: ../include/mqtt.h ../include/MQTTAsync.h
icp.o: ../include/MQTTClientPersistence.h
main.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
main.o: /usr/include/sys/_symbol_aliasing.h
main.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
main.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_size_t.h
main.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
main.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
main.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
main.o: /usr/include/unistd.h /usr/include/sys/unistd.h
main.o: /usr/include/sys/_types/_posix_vdisable.h
main.o: /usr/include/sys/_types/_seek_set.h /usr/include/_types/_uint64_t.h
main.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
main.o: /usr/include/sys/_types/_intptr_t.h /usr/include/sys/_types/_pid_t.h
main.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
main.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
main.o: /usr/include/sys/_types/_timespec.h
main.o: /usr/include/sys/_types/_timeval.h /usr/include/sys/_types/_time_t.h
main.o: /usr/include/sys/_types/_suseconds_t.h
main.o: /usr/include/sys/_types/_sigset_t.h
main.o: /usr/include/sys/_types/_fd_setsize.h
main.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
main.o: /usr/include/sys/_types/_fd_isset.h
main.o: /usr/include/sys/_types/_fd_zero.h /usr/include/sys/_types/_fd_copy.h
main.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
main.o: /usr/include/sys/_types/_mode_t.h /usr/include/sys/_types/_uuid_t.h
main.o: /usr/include/gethostuuid.h /usr/include/stdlib.h
main.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
main.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
main.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
main.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
main.o: /usr/include/sys/_pthread/_pthread_attr_t.h
main.o: /usr/include/sys/_types/_sigaltstack.h
main.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
main.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
main.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
main.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
main.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
main.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
main.o: /usr/include/_types/_uintmax_t.h /usr/include/machine/endian.h
main.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
main.o: /usr/include/libkern/_OSByteOrder.h
main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
main.o: /usr/include/sys/_types/_ct_rune_t.h
main.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
main.o: /usr/include/machine/types.h /usr/include/i386/types.h
main.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
main.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
main.o: /usr/include/secure/_string.h ../include/icp.h
main.o: ../include/icp_config.h ../include/icp_shared_config.h
main.o: ../include/topics.h ../include/mqtt.h ../include/MQTTAsync.h
main.o: ../include/MQTTClientPersistence.h ../include/dbg.h
main.o: /usr/include/errno.h /usr/include/sys/errno.h
mqtt.o: /usr/include/stdlib.h /usr/include/Availability.h
mqtt.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
mqtt.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
mqtt.o: /usr/include/sys/_symbol_aliasing.h
mqtt.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
mqtt.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
mqtt.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
mqtt.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
mqtt.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
mqtt.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
mqtt.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
mqtt.o: /usr/include/sys/_pthread/_pthread_attr_t.h
mqtt.o: /usr/include/sys/_types/_sigaltstack.h
mqtt.o: /usr/include/sys/_types/_ucontext.h
mqtt.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_size_t.h
mqtt.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
mqtt.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
mqtt.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
mqtt.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
mqtt.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
mqtt.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
mqtt.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
mqtt.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
mqtt.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
mqtt.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
mqtt.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
mqtt.o: /usr/include/sys/_types/_ct_rune_t.h
mqtt.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
mqtt.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
mqtt.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
mqtt.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
mqtt.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
mqtt.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
mqtt.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
mqtt.o: ../include/icp.h ../include/icp_config.h
mqtt.o: ../include/icp_shared_config.h ../include/topics.h ../include/mqtt.h
mqtt.o: ../include/MQTTAsync.h /usr/include/stdio.h
mqtt.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
mqtt.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
mqtt.o: ../include/MQTTClientPersistence.h ../include/dbg.h
mqtt.o: /usr/include/errno.h /usr/include/sys/errno.h
utf-8.o: /usr/include/stdlib.h /usr/include/Availability.h
utf-8.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
utf-8.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
utf-8.o: /usr/include/sys/_symbol_aliasing.h
utf-8.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
utf-8.o: /usr/include/i386/_types.h
utf-8.o: /usr/include/sys/_pthread/_pthread_types.h /usr/include/sys/wait.h
utf-8.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
utf-8.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
utf-8.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
utf-8.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
utf-8.o: /usr/include/mach/i386/_structs.h
utf-8.o: /usr/include/sys/_pthread/_pthread_attr_t.h
utf-8.o: /usr/include/sys/_types/_sigaltstack.h
utf-8.o: /usr/include/sys/_types/_ucontext.h
utf-8.o: /usr/include/sys/_types/_sigset_t.h
utf-8.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
utf-8.o: /usr/include/sys/resource.h /usr/include/stdint.h
utf-8.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
utf-8.o: /usr/include/sys/_types/_int32_t.h
utf-8.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
utf-8.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
utf-8.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
utf-8.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
utf-8.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
utf-8.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
utf-8.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
utf-8.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
utf-8.o: /usr/include/sys/_types/_ct_rune_t.h
utf-8.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
utf-8.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
utf-8.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
utf-8.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
utf-8.o: /usr/include/sys/_types/_rsize_t.h
utf-8.o: /usr/include/sys/_types/_errno_t.h
utf-8.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
utf-8.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
utf-8.o: ../include/StackTrace.h /usr/include/stdio.h
utf-8.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
utf-8.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
utf-8.o: ../include/Log.h ../include/Thread.h /usr/include/pthread.h
utf-8.o: /usr/include/pthread/pthread_impl.h /usr/include/pthread/sched.h
utf-8.o: /usr/include/pthread_impl.h /usr/include/time.h
utf-8.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
utf-8.o: /usr/include/sys/_types/_timespec.h
utf-8.o: /usr/include/sys/_pthread/_pthread_cond_t.h
utf-8.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
utf-8.o: /usr/include/sys/_pthread/_pthread_key_t.h
utf-8.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
utf-8.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
utf-8.o: /usr/include/sys/_pthread/_pthread_once_t.h
utf-8.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
utf-8.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
utf-8.o: /usr/include/sys/_pthread/_pthread_t.h /usr/include/pthread/qos.h
utf-8.o: /usr/include/sys/qos.h /usr/include/sys/_types/_mach_port_t.h
utf-8.o: /usr/include/semaphore.h /usr/include/sys/types.h
utf-8.o: /usr/include/sys/_types/_blkcnt_t.h
utf-8.o: /usr/include/sys/_types/_blksize_t.h
utf-8.o: /usr/include/sys/_types/_gid_t.h
utf-8.o: /usr/include/sys/_types/_in_addr_t.h
utf-8.o: /usr/include/sys/_types/_in_port_t.h
utf-8.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
utf-8.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_nlink_t.h
utf-8.o: /usr/include/sys/_types/_useconds_t.h
utf-8.o: /usr/include/sys/_types/_suseconds_t.h
utf-8.o: /usr/include/sys/_types/_fd_def.h
utf-8.o: /usr/include/sys/_types/_fd_setsize.h
utf-8.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
utf-8.o: /usr/include/sys/_types/_fd_zero.h
utf-8.o: /usr/include/sys/_types/_fd_isset.h
utf-8.o: /usr/include/sys/_types/_fd_copy.h
utf-8.o: /usr/include/sys/_types/_fsblkcnt_t.h
utf-8.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/fcntl.h
utf-8.o: /usr/include/sys/_types/_o_sync.h /usr/include/sys/_types/_o_dsync.h
utf-8.o: /usr/include/sys/_types/_seek_set.h
utf-8.o: /usr/include/sys/_types/_s_ifmt.h
utf-8.o: /usr/include/sys/_types/_filesec_t.h /usr/include/sys/semaphore.h
