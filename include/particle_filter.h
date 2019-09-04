/** Naming
 * functions: words seperated by "_". Ex get_val(int val);
 * variables: words start with upper case letter. Ex newVal = oldVal;
 */

#ifndef PARTICLE_FILTER_H
#define PARTICLE_FILTER_H

#define NAME_LEN 6 // Max Lenght of anchor NAME_LEN 
#define M 100 // Number of particles
#define PI 3.14159265359
#define VAR_ACC 1

struct particle
{

    double x;
    double y;
    double z;

    double w;
};

struct ddist
{
    char anchorname[NAME_LEN];
    double ddist;
    int ref_anchor;
};

struct anchor
{
    char anchorname[NAME_LEN];
    double x;
    double y;
    double z;
    int ref_anchor;
};

struct minmax
{
    double xmin;
    double ymin;
    double zmin;

    double xmax;
    double ymax;
    double zmax;
};

struct meas
{
    char anchorname[8];
    double ddist;
};

struct ddist calculate_ddist(struct particle particle, struct anchor anchorMap[], int numAnchors, double ddistList[], char anchorOrder[][NAME_LEN]);
int move_particle(struct particle particles[]);
int update_map(struct anchor anchorMap[]);
int normalize_weight(struct particle particles[]);
double assign_weight(struct particle *particles, struct anchor *anchorMap, int numAnchors, struct meas *measurement);
struct particle * low_variance_sampling(struct particle **particles, struct particle **newParticles);
int highest_weight(struct particle particles[], struct particle bestParticle);
int best_position(struct particle particles[], struct particle bestParticle);
int particle_filter(struct particle **particles, struct anchor anchorMap[], int numAnchors, struct meas *measurement, struct particle **newParticles, struct particle bestParticle);
int init(struct particle **particles, struct minmax minmax);
double multi_norm_pdf(double *x, double *mu, double *sigma, int numAnchorMeas);
struct minmax get_min_max(struct anchor anchorMap[], int numAnchors);

int main();

#endif