#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "particle_filter.h"

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
int low_variance_sampling(struct particle particles[M])
{
    return 0;
}

/**
 * Chooses the particle with the highest assign_weight
 */
int highest_weight(struct particle particles[M])
{
    return 0;
}

/**
 * Calculates the most likely position of the tag given all the particles
 */
int best_position(struct particle particles[M])
{
    return 0;
}

/**
 * Initialise particle positions
 */
int init(struct particle particles[M], struct minmax minmax)
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
get_min_max(struct anchor anchorMap[])
{
}

/**
 * Reads a file that contains the map of the system and returns it as a anchor struct
 */
struct anchor
read_map(char fileName[])
{

    char *buffer = 0;
    long length;
    FILE *f = fopen(fileName, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    //printf("%ld\n", length);
    struct anchor anchor1;
    if (buffer)
    {    
        int openBrackets = 0;
        int quotMark = 0;
        char *name;
        name = malloc(20);
        for (int i = 0; i < length; i++)
        {
            
            if (buffer[i] == (int)'{')
            {
                openBrackets++;
                i++;
            }
            if (buffer[i] == (int)'}')
            {
                openBrackets--;
                i++;
            }
            if (buffer[i] == (int)'"')
            {
                quotMark++;
                quotMark = quotMark % 2;
                i++;
            }
            if (quotMark)
            {
                int j = 0;
                while (quotMark)
                {

                    name[j] = buffer[i];
                    i++;
                    j++;
                    if (buffer[i] == (int)'"')
                    {
                        quotMark++;
                        quotMark = quotMark % 2;
                        name[j] = 0;
                    }
                }
                if(openBrackets == 1){
                    strcpy( anchor1.anchorname, name);
                }
                char strVal[30];       
                char xstr[] = "x";
                char ystr[] = "y";
                char zstr[] = "z";
                char refAncstr[] = "ref_anchor";
                if (!strcmp(name,xstr)){
                    i++;
                    i++;
                    int j = 0;
                    while(!(buffer[i] == (int)','||buffer[i] == (int)'\n')){
                        strVal[j] = buffer[i];
                        i++;
                        j++;
                    }
                    
                    anchor1.x = atof(strVal);
                }
                       
                
                if (!strcmp(name,ystr)){
                    i++;
                    i++;
                    int j = 0;
                    while(!(buffer[i] == (int)','||buffer[i] == (int)'\n')){
                        strVal[j] = buffer[i];
                        i++;
                        j++;
                    }
                    
                    anchor1.y = atof(strVal);
                }

                if (!strcmp(name,zstr)){
                    i++;
                    i++;
                    int j = 0;
                    while(!(buffer[i] == (int)','||buffer[i] == (int)'\n')){
                        strVal[j] = buffer[i];
                        i++;
                        j++;
                    }
                    
                    anchor1.z = atof(strVal);
                }

                if (!strcmp(name,refAncstr)){
                    i++;
                    i++;
                    int j = 0;
                    while(!(buffer[i] == (int)','||buffer[i] == (int)'\n')){
                        strVal[j] = buffer[i];
                        i++;
                        j++;
                    }
                    
                    anchor1.ref_anchor = atof(strVal);
                }
            }
        }
    }
    return anchor1;
}

int main(void)
{

    read_map("coordinates.json");

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
        //printf("line length: %s\n", line);

        // PARTICLE FILTER GOES HERE

        //printf("len %zd\n", len);
    }

    //printf("\n\nMax line size: %zd\n", len);

    fclose(fp);
    free(line); // getline will resize the input buffer as necessary
                // the user needs to free the memory when not needed!

    return 0;
}