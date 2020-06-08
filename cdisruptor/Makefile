IDIR =./header
CC=gcc
CFLAGS=-I$(IDIR) -std=c11 -O3
ODIR=.

#_OBJ = queue.o yield.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) -g -c -o $@ $< $(CFLAGS) -fPIC -D_XOPEN_SOURCE=700

libcdisruptor.so: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -fPIC -shared -lrt

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
