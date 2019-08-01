#ifndef PF_HEADER_FILE
#define PF_HEADER_FILE

#define M 100

struct particle {

    int prevParticle;
    int nextParticle;

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

struct ddist calculate_ddist(struct particle particles[M],struct anchorMap anchorMap);
void move_particle(struct particle particles[M], double acceleration, int timestamp);
void update_map(struct anchorMap anchorMap);
void normalize_weight(struct particle particles[M]);
double assign_weight(struct particle particles[M], struct anchorMap anchorMap, char * measurment);
void low_variance_sampling(struct particle particles[M]);
void highest_weight(struct particle particles[M]);
void best_position(struct particle particles[M]);
void particle_filter(struct particle particles[M], struct anchorMap anchorMap, char * dataPackage);
void init(struct particle particles[M], struct minmax);

int main();

#endif