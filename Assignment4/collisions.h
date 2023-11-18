#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Declare shared variables to be initialized in main
extern double R;
extern double Wall_x;
extern double Wall_y;
extern int n_particles;
extern int n_collisions;
extern double t_end;
extern double t_current; // current time
extern int particle_id_counter; // counter to assign particle ids


// Struct to hold particle information
typedef struct{
    double xpos;
    double ypos;
    double xvel;
    double yvel;
    double lastUpdateTime;
    int cwall; // # collisions with walls
    int cpart; // # collisions with other particles
    int id;
} Particle;

// Particle constructor
Particle * createParticle (double xpos, double ypos, double xvel, double yvel, double lastUpdateTime, int cwall, int cpart);


// Struct to hold collision information
typedef struct{
    Particle * particle_1; // pointer to particle 1 involved in collision
    Particle * particle_2; // pointer to particle 2 involved in collision - NULL if wall
    double time; // time of collision - expected
    int wall; //0 if no wall involved, else 1: left, 2:right, 3:top, 4:bottom 

} Collision;

// Collision constructor
Collision * createCollision(Particle * particle_1, Particle * particle_2, double time, int wall);


//  --------- Function Declarations -----------

/* Function that sorts a given Collision array by time using insertion sort*/
void sort_collisions(Collision ** collisions_array);

// Calculate a single particle-particle collision
double calculate_particle_collision_time(Collision * collision_ptr);

// Calculate a single particle-wall collision
double calculate_wall_collision_time(Particle * particle_1, int wall);


// Calculate collisions between particle and any walls
void calculate_all_wall_collisions(Particle ** particle_array, Collision ** collisions_array, int start_idx, int end_idx);

// Calculate collisions between all particle
void calculate_all_particle_collisions(Particle ** particle_array, Collision ** collisions_array,int start_idx, int end_idx);


// Process earliest colliisions and dmake relevant updates
void process_collision(Collision * collision_ptr);

// Update collision times after a collision is processed
void update_affected_particles(Particle * particle_1, Particle * particle_2, Collision ** collisions_array);


#endif