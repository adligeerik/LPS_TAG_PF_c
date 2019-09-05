IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

LIBS=-lm

DEPS = particle_filter.h parser.h vector_math.h file_handler.h
OBJ = particle_filter.o parser.o vector_math.o file_handler.c

%.o: %.c $(DEPS)
	$(CC) -g -o0 -c -o $@ $< $(CFLAGS)

particlefilter: $(OBJ)
	$(CC) -g -o0 -o $@ $^ $(CFLAGS) $(LIBS)
