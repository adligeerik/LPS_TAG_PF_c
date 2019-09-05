#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "particle_filter.h"
#include "parser.h"
#include "vector_math.h"
#include "file_handler.h"

/**
 * Calculates the ddist for a particle to all anchors
 */
struct ddist
calculate_ddist(struct particle particle, struct anchor anchorMap[], int numAnchors,double ddistList[], char anchorOrder[][NAME_LEN])
{
    int n = numAnchors;
    double ddist =0;

    // Distance to ref anchor (master) 
    double refAnchorDist = sqrt(pow(particle.x,2)+ pow(particle.y,2) + pow(particle.z,2));

    // Calculate the ddist to all other anchors. ddist is the difference in lenght from the ref_anchor to another anchor.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((strcmp(anchorOrder[j],anchorMap[i].anchorname)) == 0)
            {
                if (anchorMap[i].ref_anchor == 1)
                {
                    ddistList[i] = 0;
                }
                else
                {
                    ddist = sqrt(pow(anchorMap[i].x-particle.x,2)+pow(anchorMap[i].y-particle.y,2)+pow(anchorMap[i].z-particle.z,2));
                    ddistList[i] = ddist - refAnchorDist;
                    //printf("ddist %f\n", ddistList[i]);
                }
            }
        }
    }
    //printf("ddist %f\n", ddistList[0]);
}

/**
 * Move particles
 */
int move_particle(struct particle particles[])
{
    for (int i = 0; i < M; i++)
    {
        particles[i].x = particles[i].x + gauss(0,VAR_ACC)/5;
        particles[i].y = particles[i].y + gauss(0,VAR_ACC)/5;
        particles[i].z = particles[i].z + gauss(0,VAR_ACC)/5;

    }
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
int normalize_weight(struct particle particles[])
{
    double weightSum = 0;
    // For each particle
    for (int i = 0; i < M; i++)
    {
        weightSum = weightSum + particles[i].w;
    }
    //printf("sumw: %e\n",weightSum);
    for (int i = 0; i < M; i++)
    {
        particles[i].w = particles[i].w/weightSum;
    }    
    return 0;
}

/**
 * Assign weigth to every particle
 */
double
assign_weight(struct particle *particles, struct anchor anchorMap[], int numAnchors, struct meas measurement[])
{
    int n = numAnchors;
    
    char anchorOrder[n][NAME_LEN]; 
    double mean[n];

    double cov[n];
    double variance = 0.02;

    for (int i = 0; i < n; i++)
    {
        strcpy(anchorOrder[i], measurement[i].anchorname);
        mean[i] = measurement[i].ddist;

        cov[i] = variance;
    }

    double pHigh = 0;
    double ddist[n];
    double p;
    for (int i = 0; i < M; i++)
    {
        memset(ddist,0,n*sizeof(ddist[0]));
        calculate_ddist(particles[i], anchorMap, n, ddist, anchorOrder);
        //printf("ddist[0] : %f\n",ddist[0]);
        p = multi_norm_pdf(ddist, mean, cov, n);
        //printf("p %f\n",p);
        particles[i].w = p;
        if (p > pHigh)
        {
            pHigh = p;
        }

    }
    //printf("pHigh :%f\n",pHigh);
    return pHigh;
}

/**
 * Resampling the particles by the low variance sampling algorithm
 */
struct particle *
low_variance_sampling(struct particle **particles, struct particle **newParticles)
{
    double inM = 1/M;
    double c = (*particles+0)->w;
    int i = 0;
    double U;
    double r = rand()/((double)RAND_MAX*M);
    for (int m = 0; m < M; m++)
    {
        U = r + m*inM;
        while (U > c)
        {
            i++;
            c += (*particles+i)->w;
            //printf("resampling i: %d\n", i);
        }
        (*newParticles+m)->x = (*particles+i)->x;
        (*newParticles+m)->y = (*particles+i)->y;
        (*newParticles+m)->z = (*particles+i)->z;
        (*newParticles+m)->w = (*particles+i)->w;
        
    }
    return *newParticles;
}

/**
 * Chooses the particle with the highest assign_weight
 */
int
highest_weight(struct particle particles[], struct particle bestParticle)
{
    double highestP = 0;
    for (int i = 0; i < M; i++)
    {
        if (particles[i].w > highestP)
        {
            highestP = particles[i].w;
        }
    }
    return 0;
}

/**
 * Calculates the most likely position of the tag given all the particles
 */
int
best_position(struct particle particles[], struct particle bestParticle)
{

    return 0;
}

/**
 * Initialise particle positions
 */
int
init(struct particle **particles, struct minmax minmax)
{
    
    srand(time(0));

    double x; 
    double y; 
    double z; 
    
    for(int i = 0; i < M; i++)
    {
        //printf("max : %f, min : %f\n", minmax.xmax, minmax.xmin);
        
        x = ((double)rand() * ( (minmax.xmax+0.5) - (minmax.xmin-0.5) ) ) / (double)RAND_MAX + minmax.xmin;
        y = ((double)rand() * ( (minmax.ymax+0.5) - (minmax.ymin-0.5) ) ) / (double)RAND_MAX + minmax.ymin;
        z = ((double)rand() * ( (minmax.zmax+0.5) - (minmax.zmin-0.5) ) ) / (double)RAND_MAX + minmax.zmin;

        (*particles+i)->x = x;
        (*particles+i)->y = y;
        (*particles+i)->z = z;
        (*particles+i)->w = 0;

        //printf("x pos :%f\n", particles[i].x);
        //printf("i : %d",i);
    }
    
    return 0;
}

/**
 * Calculates the likeliness of the particles ddist given the measurment value
 * (assumes that Sigma is diagonal, i.e. no covariance) 
 */
double
multi_norm_pdf(double *x, double *mu, double *sigma, int numAnchorMeas)
{
    int n = numAnchorMeas;

    double xSubmy[n];
    double sigmInv[n];
    double xSubmySigma[n];

    sub_vector(x, mu, n, xSubmy); 
    inv_matrix(sigma,n,sigmInv);
    element_product(xSubmy,sigmInv,n,xSubmySigma);
    double exponent = dot_product(xSubmySigma,xSubmy,n);

    double denumerator = 2*pow(PI,(n/2))*sqrt(abs_vector(sigma, n));
    double p = (1/denumerator)*exp(-exponent/2);

    return p;
}

/**
 * Particle particle_filter
 */
int particle_filter(struct particle **particles, struct anchor *anchorMap, int numAnchors, struct meas *measurement, struct particle **newParticles, struct particle bestParticle)
{
    // Calculate weight
    double pHigh =  assign_weight(*particles, anchorMap, numAnchors, measurement);

    // Normalize weight
    normalize_weight(*particles);

    // Resample
    struct particle *temp = *particles;
    struct particle **newParticles_pp = newParticles;
    *particles = low_variance_sampling(particles, newParticles_pp);
    *newParticles = temp;

    // Move particles
    move_particle(*particles);

    // Most likely position
    best_position(*particles, bestParticle);

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
    
    for (int i = 1; i < numAnchors; i++)
    {
        if (minmax.xmax < anchorMap[i].x)
        {
            minmax.xmax = anchorMap[i].x;
        }
        else if (minmax.xmin > anchorMap[i].x)
        {
            minmax.xmin = anchorMap[i].x;
        }

        if (minmax.ymax < anchorMap[i].y)
        {
            minmax.ymax = anchorMap[i].y;
        }
        else if (minmax.ymin > anchorMap[i].x)
        {
            minmax.ymin = anchorMap[i].y;
        }

        if (minmax.zmax < anchorMap[i].z)
        {
            minmax.zmax = anchorMap[i].z;
        }
        else if (minmax.zmin > anchorMap[i].x)
        {
            minmax.zmin = anchorMap[i].z;
        }
    }
    //printf("max : %f, min : %f\n", minmax.xmax, minmax.xmin);
    return minmax;
}



int main(void)
{   
    struct anchor *anchorMap = read_map("../data/coordinates.json");

    //for (int i = 0;i<4;i++){
    //    printf("Anchor name: :%s\n",anchorMap[i].anchorname);
    //    printf("x pos: %.10lf\n",anchorMap[i].x);
    //    printf("y Pos: %.10lf\n",anchorMap[i].y);
    //    printf("z pos: %.10lf\n",anchorMap[i].z);
    //    printf("Ref acnhor: %d\n",anchorMap[i].ref_anchor);
    //}
    
    int numAnchors = 4;
    write_file_anchor(anchorMap, "../plot_data/anchors.dat", numAnchors);

    struct minmax minmax = get_min_max(anchorMap, numAnchors);

    //printf("x max: %lf\n",minmax.xmax);
    //printf("y max: %lf\n",minmax.ymax);
    //printf("z max: %lf\n",minmax.zmax);
    //printf("x min: %lf\n",minmax.xmax);
    //printf("y min: %lf\n",minmax.ymax);
    //printf("z min: %lf\n",minmax.zmax);



    FILE *fp = fopen("../data/tagdata.json", "r");
    if (fp == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }

    // Read lines using POSIX function getline
    // This code won't work on Windows
    char *line = NULL;
    size_t len = 0;

    // Init particles
    struct particle *particles = malloc(M*sizeof(struct particle));
    struct particle **particles_pp = &particles;
    init(particles_pp, minmax);

    // Particles for resampling, two sets of struct arrays are needed 
    // for the resampling where the old particles goes into the new 
    // list and then the pointer is set to the new one and vise vers.
    struct particle *newParticles = malloc(M*sizeof(struct particle));
    struct particle **newParticles_pp = &newParticles;

    // Most likely position
    struct particle bestParticle;


    int index = 0;
    int numAnchor = 0;
    // Read file line by line
    while (getline(&line, &len, fp) != -1)
    {
        //printf("line : %s\n", line);
        char buf[40];
        snprintf(buf, 40, "../plot_data/particles_%d.dat", index);
        write_file_particle(*particles_pp, buf);

        // Parse line into measurment struct
        numAnchor = sub_in_str(line, "addr");
        //printf("numanchor : %d\n",numAnchor);
        struct meas measurement[numAnchor];
        parse_data(line,measurement,numAnchor);

        // PARTICLE FILTER GOES HERE
        //printf("\n===============\n");
        //printf("Address before, particles_pp: %p\n", (*particles_pp));
        //printf("Address before, newParticles_pp: %p\n", (*newParticles_pp));
        particle_filter(particles_pp, anchorMap, numAnchors, measurement, newParticles_pp, bestParticle);
        //printf("Address after, particles_pp: %p\n", (*particles_pp));
        //printf("Address after, newParticles_pp: %p\n", (*newParticles_pp));

        //printf("particle pp: %e\n", (*particles_pp)->w);

        index++;
    }

    //printf("\n\nMax line size: %zd\n", len);

    fclose(fp);
    free(line);

    free(particles);
    free(newParticles);

    printf("Done\n");
    return 0;
}