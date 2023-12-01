#include "collisions.h"

// Declare shared variables
double R;
double Wall_x;
double Wall_y;
int n_particles;
int n_collisions;
double t_end;
double t_current;
int particle_id_counter; 


int main(int argc, char *argv[]) {
    
    // Read command line arguements
    char *inputFile = argv[1]; // input file name
    t_end = atof(argv[2]); // end time : convert to float
    t_current = 0; // current time


    // ----- 1. Initialize particles -----

    // Access file with a file pointer 
    FILE *fp = fopen(inputFile, "r"); 
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    // Read first line to get number of particles - store in global variable n_particles
    fscanf(fp, "%d", &n_particles);
    // Second line specifies radius of particles - store this in global variable r
    fscanf(fp, "%lf", &R);
    // Third line specifies x and y position of wall - store in global variables wall_x and wall_y
    fscanf(fp, "%lf %lf", &Wall_x, &Wall_y);

    // Allocate memory for particle array
    Particle ** particles_array = (Particle **) malloc(sizeof(Particle *) * n_particles);
    if (particles_array == NULL) {
        perror("Error allocating memory for particles array");
        return -1;
    } 
    
    particle_id_counter = 0;
    // Loop through rest of the file to get particle information
    for (int i=0; i<n_particles; i ++){
        // Read off particle information
        double xpos, ypos, xvel, yvel;
        fscanf(fp, "%lf %lf %lf %lf", &xpos, &ypos, &xvel, &yvel);
        // Create the particle - note that createParticle function does memory allocation
        particles_array[i] = createParticle(xpos, ypos, xvel, yvel, 0, 0, 0); // create particle and add to array
    }

    fclose(fp); // close file pointer



    // Initialize collisions
    // Calculate number of possible collisions : between each particle pair and walls
    int n_particle_collisions = n_particles * (n_particles - 1)/2;
    int n_wall_collisions = 4 * n_particles;
    n_collisions = n_particle_collisions + n_wall_collisions;
   
    Collision ** collisions_array= (Collision **) malloc(sizeof(Collision *) * n_collisions); // allocate memory for collision array
    if (collisions_array == NULL) {
        perror("Error allocating memory for collisions array");
        return -1;
    }

    // Append all particle collisions to this array
    calculate_all_particle_collisions(particles_array, collisions_array, 0, n_particle_collisions);

    // Append all wall collisions to this array
    calculate_all_wall_collisions(particles_array, collisions_array, n_particle_collisions, n_collisions);


    // Loop until end time is reached
    while (t_current < t_end) { 
        // Sort collisions by time
        sort_collisions(collisions_array);
        // Get next collision
        Collision * next_collision = collisions_array[0];

        // Update time and break if needed
        t_current = next_collision->time;
        if( t_current > t_end){ break;}
        
        // Process collisions - update the particle's position and their velocities
        process_collision(next_collision);
        // Update affected particles' collisions
        Particle * particle_1 = next_collision->particle_1;
        Particle * particle_2 = next_collision->particle_2;
        update_affected_particles(particle_1, particle_2, collisions_array);
    }

    // Update particles to final positions
    for (int i=0; i<n_particles; i++){
        Particle * particle = particles_array[i];
        particle->xpos = particle->xpos + particle->xvel * (t_end - particle->lastUpdateTime);
        particle->ypos = particle->ypos + particle->yvel * (t_end - particle->lastUpdateTime);
    }

    // Print desired output
    for (int i=0; i<n_particles; i++){
        printf("%.6f, %.6f, %d, %d\n", particles_array[i]->xpos, particles_array[i]->ypos, particles_array[i]->cwall, particles_array[i]->cpart);
    }

    // Free memory 
    for (int i=0; i<n_particles; i++){
        free(particles_array[i]);
    }
    free(particles_array);
    for (int i=0; i<n_collisions; i++){
        free(collisions_array[i]);
    }
    free(collisions_array);
    
    return 0;
}


