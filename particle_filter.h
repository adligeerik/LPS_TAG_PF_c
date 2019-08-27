/** Naming
 * functions: words seperated by "_". Ex get_val(int val);
 * variables: words start with upper case letter. Ex newVal = oldVal;
 */

#ifndef PARTICLE_FILTER_H
#define PARTICLE_FILTER_H

#define M 100

struct particle
{

    double x;
    double y;
    double z;

    double w;
};

struct ddist
{
    char anchorname[6];
    double ddist;
    int ref_anchor;
};

struct anchor
{
    char anchorname[6];
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

struct ddist calculate_ddist(struct particle particles[], struct anchor anchorMap[], int numAnchors);
int move_particle(struct particle particles[], double acceleration, int timestamp);
int update_map(struct anchor anchorMap[]);
int normalize_weight(struct particle particles[]);
double assign_weight(struct particle particles[], struct anchor anchorMap[], int numAnchors, char measurment[]);
int low_variance_sampling(struct particle particles[]);
int highest_weight(struct particle particles[]);
int best_position(struct particle particles[]);
int particle_filter(struct particle particles[], struct anchor anchorMap[], int numAnchors, char dataPackage[]);
int init(struct particle particles[], struct minmax minmax);
double multi_norm_pdf(double *x, double *mu, double *sigma, int numAnchorMeas);
struct minmax get_min_max(struct anchor anchorMap[], int numAnchors);

int main();

#endif