CC=gcc
CFLAG=-I.

particlefilter: particle_filter.c parser.c vector_math.c
	$(CC) -o pf.o particle_filter.c parser.c vector_math.c -lm
