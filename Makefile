LIBS=lib/error_functions.o lib/get_num.o
OBJS=src/my_tee.o src/fileio/seek_io.o src/my_cp.o src/my_append_seek_write.o src/my_atomic_append.o
EXES=bin/my_tee bin/seek_io bin/my_cp bin/my_append_seek_write bin/my_atomic_append

CFLAGS+=-Ilib

TARGET=$(LIBS) $(OBJS) $(EXES)

all: $(TARGET)

.PHONY: clean
clean:
	-$(RM) $(TARGET)
	-find . -name '*~' | xargs rm

lib/error_functions.o: lib/error_functions.c lib/tlpi_hdr.h lib/ename.c.inc

lib/get_num.o: lib/get_num.c lib/get_num.h

src/my_tee.o: src/my_tee.c

src/fileio/seek_io.o: src/fileio/seek_io.c

src/my_cp.o: src/my_cp.c

src/my_append_seek_write.o: src/my_append_seek_write.c

src/my_atomic_append.o: src/my_atomic_append.c

bin/my_tee: src/my_tee.o $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

bin/seek_io: src/fileio/seek_io.o
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

bin/my_cp: src/my_cp.o $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

bin/my_append_seek_write: src/my_append_seek_write.o $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

bin/my_atomic_append: src/my_atomic_append.o $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)
