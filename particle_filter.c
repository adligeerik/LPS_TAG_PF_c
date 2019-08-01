#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "particle_filter.h"


/**
 * Calculates the ddist for all particles
 */
struct ddist
calculate_ddist(struct particle particles[M],struct anchor anchorMap[], int numAnchors)
{

}


/**
 * Move particles
 */
int
move_particle(struct particle particles[M], double acceleration, int timestamp)
{
    return 0;
}


/**
 * Update the anchor map when needed
 */
int
update_map(struct anchor anchorMap[])
{
    return 0;
}

/**
 * Normalize weigth for each particle
 */
int
normalize_weight(struct particle particles[M])
{
    return 0;
}

/**
 * Assign weigth to every particle
 */
double
assign_weight(struct particle particles[M], struct anchor anchorMap[], int numAnchors, char measurment[])
{

}

/**
 * Resampling the particles by the low variance sampling algorithm
 */
int
low_variance_sampling(struct particle particles[M])
{
    return 0;
}

/**
 * Chooses the particle with the highest assign_weight
 */
int
highest_weight(struct particle particles[M])
{
    return 0;
}

/**
 * Calculates the most likely position of the tag given all the particles
 */
int
best_position(struct particle particles[M])
{
    return 0;
}

/**
 * Initialise particle positions
 */
int
init(struct particle particles[M], struct minmax minmax)
{
    return 0;
}

/**
 * Calculates the likeliness of the particles ddist given the measurment value
 */
double
multi_norm_pdf(double *x,double *mu,double *sigma,int numAnchorMeas)
{

}

/**
 * Particle particle_filter
 */
int
particle_filter(struct particle particles[M], struct anchor anchorMap[], int numAnchors, char dataPackage[])
{

    return 0;
}

/**
 * Determine the max and min coordinate of the anchorMap and returns it as a minmax struct
 */
struct minmax
get_min_max(struct anchor anchorMap[])
{

}

/**
 * Reads a file that contains the map of the system and returns it as a anchor struct
 */
struct anchor
read_map(char fileName)
{

}


int
main(void)
{
    FILE *fp = fopen("tagdata.json", "r");
    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    // Read lines using POSIX function getline
    // This code won't work on Windows
    char *line = NULL;
    size_t len = 0;

    // Read file line by line
    while(getline(&line, &len, fp) != -1) {
        printf("line length: %s\n", line);
        printf("len %zd\n",len);
    }

    printf("\n\nMax line size: %zd\n", len);

    fclose(fp);
    free(line);     // getline will resize the input buffer as necessary
                    // the user needs to free the memory when not needed!

    return 0;
}