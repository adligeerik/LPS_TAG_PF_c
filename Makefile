CC=gcc
CFLAG=-I.

particlefilter: particle_filter.c parser.c
	$(CC) -o pf particle_filter.c parser.c