CC=gcc
CFLAG=-I.

DEPS = particle_filter.h parser.h vector_math.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

particlefilter: particle_filter.o parser.o vector_math.o
	$(CC) -o pf.o particle_filter.c parser.c vector_math.c -lm
