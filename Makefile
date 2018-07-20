#============================================================================#
#                ASA 2018-2019, IEETA/DETI, UNIVERSITY OF AVEIRO             #
#============================================================================#
BIN    = .
CC     = gcc
CPLP   = -ffast-math -msse2 #fgnu89-inline 
#-----------------------------------------------------------------------------
CFLAGS = -O3 -Wall $(CPLP)
#-----------------------------------------------------------------------------
LIBS   = -lm
DEPS   = defs.h
PROGS  = $(BIN)/ASA
OBJS     = mem.o misc.o args.o buffer.o
#-----------------------------------------------------------------------------
all:
	$(MAKE) progs
progs: $(PROGS)
$(BIN)/ASA: asa.c $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) -o $(BIN)/ASA asa.c $(OBJS) $(LIBS)
mem.o: mem.c mem.h $(DEPS)
	$(CC) -c $(CFLAGS) mem.c
misc.o: misc.c misc.h $(DEPS)
	$(CC) -c $(CFLAGS) misc.c
args.o: args.c args.h $(DEPS)
	$(CC) -c $(CFLAGS) args.c
buffer.o: buffer.c buffer.h $(DEPS)
	$(CC) -c $(CFLAGS) buffer.c
##############################################################################
clean: 
	/bin/rm -f *.o
cleanall:
	/bin/rm -f *.o $(PROGS)
##############################################################################
