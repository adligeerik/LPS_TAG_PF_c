#include <stdlib.h>
#include <stdio.h>

#include "particle_filter.h"
#include "file_handler.h"
#include <string.h>

/**
 * Writes point coordinates to a file with filename
 */
void
write_file_particle(struct particle *particles, char *fileName)
{

    FILE *fptr;

    fptr = fopen(fileName, "w");

    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    char x[COORD_STRING_LEN];
    char y[COORD_STRING_LEN];
    char z[COORD_STRING_LEN];

    for (int i = 0; i < M; i++)
    {
        memset(x,0,COORD_STRING_LEN);
        memset(y,0,COORD_STRING_LEN);
        memset(z,0,COORD_STRING_LEN);

        snprintf(x, 50, "%f", particles[i].x);
        snprintf(y, 50, "%f", particles[i].y);
        snprintf(z, 50, "%f", particles[i].z);

        fprintf(fptr,"%s", x);
        fprintf(fptr," ");
        fprintf(fptr,"%s", y);
        fprintf(fptr," ");
        fprintf(fptr,"%s", z);
        fprintf(fptr,"\n");
    }

    fclose(fptr);
}


/**
 * Writes point coordinates to a file with filename
 */
void
write_file_anchor(struct anchor *anchors, char *fileName, int numAnchors)
{

    FILE *fptr;

    fptr = fopen(fileName, "w");

    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    char x[COORD_STRING_LEN];
    char y[COORD_STRING_LEN];
    char z[COORD_STRING_LEN];

    for (int i = 0; i < numAnchors; i++)
    {
        memset(x,0,COORD_STRING_LEN);
        memset(y,0,COORD_STRING_LEN);
        memset(z,0,COORD_STRING_LEN);

        snprintf(x, 50, "%f", anchors[i].x);
        snprintf(y, 50, "%f", anchors[i].y);
        snprintf(z, 50, "%f", anchors[i].z);

        fprintf(fptr,"%s", x);
        fprintf(fptr," ");
        fprintf(fptr,"%s", y);
        fprintf(fptr," ");
        fprintf(fptr,"%s", z);
        fprintf(fptr,"\n");
    }

    fclose(fptr);
}

/**
 * Appends point coordinates to a file with filename
 */
void
write_file_best_particle(struct particle *particles, char *fileName)
{

    FILE *fptr;
    fptr = fopen(fileName, "r");
    if(fptr)
    {
        fclose(fptr);
        fptr = fopen(fileName, "a");
    }
    else
    {
        fptr = fopen(fileName, "w");
    }
    

    if(fptr == NULL)
    {
      printf("Error!");
      exit(1);
    }

    char x[COORD_STRING_LEN];
    char y[COORD_STRING_LEN];
    char z[COORD_STRING_LEN];

    memset(x,0,COORD_STRING_LEN);
    memset(y,0,COORD_STRING_LEN);
    memset(z,0,COORD_STRING_LEN);

    snprintf(x, 50, "%f", (particles)->x);
    snprintf(y, 50, "%f", (particles)->y);
    snprintf(z, 50, "%f", (particles)->z);

    fprintf(fptr,"%s", x);
    fprintf(fptr," ");
    fprintf(fptr,"%s", y);
    fprintf(fptr," ");
    fprintf(fptr,"%s", z);
    fprintf(fptr,"\n");
        
    fclose(fptr);
}