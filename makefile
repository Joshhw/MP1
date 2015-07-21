# Makefile for building cs341 mp1 programs using the
# Standalone 486 or Pentium IBM PC running in 32-bit protected mode,
# or "SAPC" for short.  UNIX builds also, and "make clean"

# system directories needed for compilers, libraries, header files--
# assumes the environment variables SAPC_TOOLS and SAPC_GNUBIN
# have been set up by the ulab module

PC_LIB = $(SAPC_TOOLS)/lib
PC_INC = $(SAPC_TOOLS)/include

# for SAPC builds
PC_CC   = $(SAPC_GNUBIN)/i386-gcc
PC_CFLAGS = -Wall -Wno-implicit -Wshadow -I$(PC_INC) -I$(PROJ)
PC_AS   = $(SAPC_GNUBIN)/i386-as
PC_LD   = $(SAPC_GNUBIN)/i386-ld
PC_NM   = $(SAPC_GNUBIN)/i386-nm

# File suffixes:
# .c	C source (often useful both for UNIX and SAPC)
# .s 	assembly language source (gnu as for protected mode 486)
# .o    relocatable machine code, initialized data, etc., for UNIX
# .opc  relocatable machine code, initialized data, etc., for SAPC
# .lnx  executable image (bits as in memory), for SA PC (Linux a.out format)
# .syms text file of .exe's symbols and their values (the "symbol table")
# .usyms text file of UNIX executable's symbols

# where to find files
# change this to your homework folder
PROJ = /home/joshhw/cs341/mp1

PC_OBJS = $(PROJ)/tutor.opc $(PROJ)/slex.opc
UNIX_OBJS = $(PROJ)/tutor.o $(PROJ)/slex.o


# PC executable--tell ld to start code at 0x1000e0, load special startup
# module, special PC C libraries--
# Code has 0x20 byte header, so use "go 100100"

tutor.lnx: cmds.opc $(PC_OBJS) \
		$(PC_LIB)/startup0.opc $(PC_LIB)/startup.opc $(PC_LIB)/libc.a
	$(PC_LD) -N -Ttext 1000e0 -o tutor.lnx \
		$(PC_LIB)/startup0.opc $(PC_LIB)/startup.opc \
		$(PC_OBJS) cmds.opc $(PC_LIB)/libc.a
	rm -f syms;$(PC_NM) -n tutor.lnx>syms

# this rule allows you to build your own cmds.opc--
cmds.opc: cmds.c $(PROJ)/slex.h
	$(PC_CC) $(PC_CFLAGS) -c -o cmds.opc cmds.c

# these should already have been made for you--
$(PROJ)/tutor.opc: $(PROJ)/tutor.c $(PROJ)/slex.h
	$(PC_CC) $(PC_CFLAGS) -c -o $(PROJ)/tutor.opc $(PROJ)/tutor.c

$(PROJ)/slex.opc: $(PROJ)/slex.c $(PROJ)/slex.h
	$(PC_CC) $(PC_CFLAGS) -c -o $(PROJ)/slex.opc $(PROJ)/slex.c

# ************** UNIX build **********
# tell make to use gcc as C compiler, -g -W... for C compiler flags--
# check "man gcc" to find out what -W flags do
CC = gcc
CFLAGS = -Wall -Wno-implicit -Wshadow -g -I$(PROJ)

tutor:  $(UNIX_OBJS) cmds.o
	$(CC) -g -o tutor $(UNIX_OBJS) cmds.o
	rm -f usyms; nm -vpt x tutor > usyms

# make knows to use $(CC) and $(CFLAGS)
cmds.o:	cmds.c  $(PROJ)/slex.h
$(PROJ)/tutor.o: $(PROJ)/tutor.c $(PROJ)/slex.h
$(PROJ)/slex.o: $(PROJ)/slex.c  $(PROJ)/slex.h
# **************end of UNIX build ********

clean:
	rm -f *.o *.opc *.syms *.usyms *.lnx tutor core syms usyms

