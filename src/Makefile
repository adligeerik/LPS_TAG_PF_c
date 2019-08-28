IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

LIBS=-lm

DEPS = particle_filter.h parser.h vector_math.h
OBJ = particle_filter.o parser.o vector_math.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

particlefilter: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
