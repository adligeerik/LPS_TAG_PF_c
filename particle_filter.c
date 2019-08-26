
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "particle_filter.h"
#include "parser.h"

/**
 * Calculates the ddist for all particles
 */
struct ddist
calculate_ddist(struct particle particles[M], struct anchor anchorMap[], int numAnchors)
{
}

/**
 * Move particles
 */
int move_particle(struct particle particles[M], double acceleration, int timestamp)
{
    return 0;
}

/**
 * Update the anchor map when needed
 */
int update_map(struct anchor anchorMap[])
{
    return 0;
}

/**
 * Normalize weigth for each particle
 */
int normalize_weight(struct particle particles[M])
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
multi_norm_pdf(double *x, double *mu, double *sigma, int numAnchorMeas)
{
}

/**
 * Particle particle_filter
 */
int particle_filter(struct particle particles[M], struct anchor anchorMap[], int numAnchors, char dataPackage[])
{

    return 0;
}

/**
 * Determine the max and min coordinate of the anchorMap and returns it as a minmax struct
 */
struct minmax
get_min_max(struct anchor anchorMap[], int numAnchors)
{
    struct minmax minmax;
    minmax.xmin = anchorMap[0].x;
    minmax.xmax = anchorMap[0].x;

    minmax.ymin = anchorMap[0].y;
    minmax.ymax = anchorMap[0].y;

    minmax.zmin = anchorMap[0].z;
    minmax.zmax = anchorMap[0].z;
    
    for (int i = 1; i < numAnchors; i++){
        if (minmax.xmax < anchorMap[0].x){
            minmax.xmax = anchorMap[0].x;
        }else
        {
            minmax.xmin = anchorMap[0].x;
        }

        if (minmax.ymax < anchorMap[0].y){
            minmax.ymax = anchorMap[0].y;
        }else
        {
            minmax.ymin = anchorMap[0].y;
        }

        if (minmax.zmax < anchorMap[0].z){
            minmax.zmax = anchorMap[0].z;
        }else
        {
            minmax.zmin = anchorMap[0].z;
        }
    }
    return minmax;
}



int main(void)
{

    struct anchor *anchorMap = read_map("coordinates.json");

    //for (int i = 0;i<4;i++){
    //    printf("Anchor name: :%s\n",anchorMap[i].anchorname);
    //    printf("x pos: %.10lf\n",anchorMap[i].x);
    //    printf("y Pos: %.10lf\n",anchorMap[i].y);
    //    printf("z pos: %.10lf\n",anchorMap[i].z);
    //    printf("Ref acnhor: %d\n",anchorMap[i].ref_anchor);
    //}
    
    int numAnchors = 4;
    struct minmax minmax = get_min_max(anchorMap, numAnchors);

    //printf("x max: %lf\n",minmax.xmax);
    //printf("y max: %lf\n",minmax.ymax);
    //printf("z max: %lf\n",minmax.zmax);
    //printf("x min: %lf\n",minmax.xmax);
    //printf("y min: %lf\n",minmax.ymax);
    //printf("z min: %lf\n",minmax.zmax);


    FILE *fp = fopen("tagdata.json", "r");
    if (fp == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }

    // Read lines using POSIX function getline
    // This code won't work on Windows
    char *line = NULL;
    size_t len = 0;

    // Read file line by line
    while (getline(&line, &len, fp) != -1)
    {
        //printf("line : %s\n", line);

        int numAnchor = sub_in_str(line, "addr");
        //printf("num anchors :%d\n",numAnchor);

        struct meas measurement[numAnchor];
        
        parse_data(line,measurement,numAnchor);

        // PARTICLE FILTER GOES HERE

    }

    //printf("\n\nMax line size: %zd\n", len);

    fclose(fp);
    free(line); // getline will resize the input buffer as necessary
                // the user needs to free the memory when not needed!

    return 0;
}