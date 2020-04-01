## Process this file with automake to produce Makefile.in
noinst_LIBRARIES = libbc.a

AM_CPPFLAGS = -I. -I.. -I$(srcdir)/../h

libbc_a_SOURCES = getopt.c getopt1.c vfprintf.c number.c bi.c

DEFS = @DEFS@ $(DEFSADD)

AM_CFLAGS = @CFLAGS@

MAINTAINERCLEANFILES = Makefile.in number.c bi.c
CLEANFILES = testmul specialnumber muldigits.h

newnumber.o: number.c muldigits.h bi.h
	$(CC) $(CFLAGS) $(INCLUDES) -I./.. -I./../h -c -DMULDIGITS -o newnumber.o $(srcdir)/number.c

muldigits.h: testmul
	@echo "The following may take up to 10 minutes."
	./testmul > muldigits.h

testmul: testmul.o number.o
	$(CC) $(CFLAGS) $(INCLUDES) -o testmul testmul.o number.o bi.o

specialnumber: newnumber.o
	cp newnumber.o number.o
