#ifndef PARTICLE_FILTER_H
#define PARTICLE_FILTER_H

#define M 100


/** Naming
 * functions: words seperated by "_". Ex get_val(int val);
 *  variables: words start with upper case letter. Ex newVal = oldVal;
 */

struct particle {

    double x;
    double y;
    double z;

    double w;
};

struct ddist { 
    char anchorname[6];
    double ddist;
    int ref_anchor;
};

struct anchor{
    char anchorname[6];
    double x;
    double y;
    double z;
    int ref_anchor;
};

struct minmax{
    double xmin;
    double ymin;
    double zmin;

    double xmax;
    double ymax;
    double zmax;
};

struct ddist calculate_ddist(struct particle particles[M],struct anchor anchorMap[], int numAnchors);
int move_particle(struct particle particles[M], double acceleration, int timestamp);
int update_map(struct anchor anchorMap[]);
int normalize_weight(struct particle particles[M]);
double assign_weight(struct particle particles[M], struct anchor anchorMap[], int numAnchors, char measurment[]);
int low_variance_sampling(struct particle particles[M]);
int highest_weight(struct particle particles[M]);
int best_position(struct particle particles[M]);
int particle_filter(struct particle particles[M], struct anchor anchorMap[], int numAnchors, char dataPackage[]);
int init(struct particle particles[M], struct minmax minmax);
double multi_norm_pdf(double *x,double *mu,double *sigma,int numAnchorMeas);
struct anchor * read_map(char fileName[]);
struct minmax get_min_max(struct anchor anchorMap[], int numAnchors);

int main();

#endif