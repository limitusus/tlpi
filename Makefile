LIBS=lib/error_functions.o lib/get_num.o
OBJS=src/my_tee.o src/fileio/seek_io.o src/my_cp.o
EXES=bin/my_tee bin/seek_io bin/my_cp

CFLAGS+=-Ilib

TARGET=$(LIBS) $(OBJS) $(EXES)

all: $(TARGET)

.PHONY: clean
clean:
	-$(RM) $(TARGET)

lib/error_functions.o: lib/error_functions.c lib/tlpi_hdr.h lib/ename.c.inc

lib/get_num.o: lib/get_num.c lib/get_num.h

src/my_tee.o: src/my_tee.c

src/fileio/seek_io.o: src/fileio/seek_io.c

src/my_cp.o: src/my_cp.c

bin/my_tee: src/my_tee.o $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

bin/seek_io: src/fileio/seek_io.o
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

bin/my_cp: src/my_cp.o $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)
