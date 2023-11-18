#include "collisions.h"



/* 
Creates a Particle struct, initializes its attributes and returns a pointer to it
Handles memory allocation for the object
- Inputs: xpos, ypos, xvel, yvel, lastUpdateTime, cwall, cpart
- Outputs: Pointer to the newly created Particle struct.
*/
Particle * createParticle(double xpos, double ypos, double xvel, double yvel, double lastUpdateTime, int cwall, int cpart)
{
    Particle * particle_ptr = (Particle *) malloc(sizeof(Particle)); // allocate memory 
    
    // Check if allocation was succesfull : ptr will be NULL if not
    if (!particle_ptr) { 
        printf("Memory allocation failed for particle\n");
        exit(1);
    }

    particle_ptr->xpos = xpos;
    particle_ptr->ypos = ypos;
    particle_ptr->xvel = xvel;
    particle_ptr->yvel = yvel;
    particle_ptr->lastUpdateTime = lastUpdateTime;
    particle_ptr->cwall = cwall;
    particle_ptr->cpart = cpart;

    particle_ptr->id = particle_id_counter++;

    return particle_ptr; // return pointer
};



/* 
Creates a Collision struct, initializes its attributes and returns a pointer to it
Handles the malloc for the object
- Inputs: involved particles, set particle_2 to Null if wall, time of collision, wall number
- Outputs: Pointer to the newly created Collision struct
*/
Collision * createCollision(Particle * particle1, Particle * particle2, double time, int wall){
    Collision * collision_ptr = (Collision *) malloc(sizeof(Collision)); // allocate memory

    // Check if allocation was succesfull : ptr will be NULL if not
    if (!collision_ptr) { 
        printf("Memory allocation failed for collision\n");
        exit(1);
    }

    collision_ptr->particle_1 = particle1;
    collision_ptr->particle_2 = particle2;
    collision_ptr->time = time;
    collision_ptr->wall = wall;

    return collision_ptr; // return pointer
};


/* 
Sort a given Collision array by time using insertion sort
- Inputs: collisions_array
- Outputs: Sorted collisions_array (inplace)
*/
void sort_collisions(Collision ** collisions_array){

    int i;
    for (i = 1; i < n_collisions; i++){

        Collision * key = collisions_array[i];
        int j;

        for(j = i-1 ; j > -1; j--) // go down to zero
        { 
            if (key->time < collisions_array[j]->time) 
            {
                // move element one to the right
                collisions_array[j+1] = collisions_array[j]; // no need to track j as we will use key at the end
            } else { break; }
        }
            collisions_array[j + 1] = key; // update key
        }
}



/*
Calculates the time of a single particle-particle collision
Inputs: Pointer to the collision struct
Outputs: Time of collision (double)
*/
double calculate_particle_collision_time(Collision * collision_ptr){
       
        // Get particles
        Particle * particle_1 = collision_ptr->particle_1;
        Particle * particle_2 = collision_ptr->particle_2;

        // Get velocities
        double u1 = particle_1->xvel;
        double v1 = particle_1->yvel;
        double u2 = particle_2->xvel;
        double v2 = particle_2->yvel;

        // Update positions by setting them to whatever they should be at current time 
        // -- Get time passed
        double time_passed_1 = t_current - particle_1->lastUpdateTime;
        double time_passed_2 = t_current - particle_2->lastUpdateTime;

        // -- Update positions
        particle_1->xpos = particle_1->xpos + u1 * time_passed_1;
        particle_1->ypos = particle_1->ypos + v1 * time_passed_1;
        particle_2->xpos = particle_2->xpos + u2 * time_passed_2;
        particle_2->ypos = particle_2->ypos + v2 * time_passed_2;

        // Get the most up to date positions
        double x1 = particle_1->xpos;
        double y1 = particle_1->ypos;
        double x2 = particle_2->xpos;
        double y2 = particle_2->ypos;

        // Update last update time
        particle_1->lastUpdateTime = t_current;
        particle_2->lastUpdateTime = t_current;

        // Calculate time of collision

        double a,b,c, t_c; // coefficients of quadratic equation and collision time


        // Calculate a,b,c
        a = (u1 - u2) * (u1 - u2) + (v1 - v2) * (v1 - v2); 
        b = 2 * (x1 - x2) * (u1 - u2) + 2 * (y1 - y2) * (v1 - v2); 
        c = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) - 4 * R * R; // Calculating c

        // Check discriminant
        double discriminant = (b * b) - (4 * a * c);

        if (discriminant <0){
            //No collision
            t_c = t_end +1;
        } else {
            double t_c_1 = t_current + ( -b + sqrt(discriminant) ) / (2 * a);
            double t_c_2 = t_current + ( -b - sqrt(discriminant) ) / (2 * a);

            // Pick the smaller of the two that is positive

            if ((t_c_1 <= t_c_2) && (t_c_1 > t_current)){ // t_c_1 in the future and smaller
                t_c = t_c_1;
            } else if ((t_c_2 < t_c_1) && (t_c_2 > t_current)) { // t_c_2 in the future and smaller
                t_c = t_c_2;
            } else{ // both in the past
                t_c = t_end + 1;  // no collision possible
            }
        }

        if (t_c == 0){
            printf("Error: Particle collision time is 0\n"); 
            printf("Particle 1: %d , particle 2: %d ", particle_1->id, particle_2->id);
            t_c = t_end + 1;
        }

        return t_c;
}



/* 
Calculates the time of a single particle-wall collision
Inputs: Pointer to the particle struct, int indicating wall number ( [1,2,3,4])
Outputs: Time of collision (double)
*/
double calculate_wall_collision_time(Particle * particle_1, int wall){

    double t_c = t_end; // time of collision - just initialize to end time

    // calculate time based on wall : 1: left, 2:right, 3:top, 4:bottom 

    if (wall == 0){
        printf("Error: Wall collision time called with wall number 0\n");
    }

    // Get velocities
    double u1 = particle_1->xvel;
    double v1 = particle_1->yvel;

    // Update positions by setting them to whatever they should be at current time 

    // -- Get time passed
    double time_passed_1 = t_current - particle_1->lastUpdateTime;

    // -- Update positions
    particle_1->xpos = particle_1->xpos + u1 * time_passed_1;
    particle_1->ypos = particle_1->ypos + v1 * time_passed_1;

    // -- Get the most up to date positions
    double x1 = particle_1->xpos;
    double y1 = particle_1->ypos;

    // -- Update last update time
    particle_1->lastUpdateTime = t_current;

    // Calculate time to hit the wall, checking for non zero velocities

    if(wall == 1){ //left
        if(u1 >= 0){
            t_c = t_end + 1; // impossible
        } else {
            t_c = (R - x1) / u1;
        }
    
    } else if (wall == 2){ // right
        if(u1 <= 0){
            t_c = t_end + 1; // impossible
        } else {
            t_c = ((Wall_x - R) - x1) / u1;
        }

    } else if (wall == 3){ // top
        if( v1 <= 0){
            t_c = t_end + 1; // impossible
        } else {
            t_c = ((Wall_y - R) - y1) / v1;
        }

    } else if (wall == 4){ // bottom
        if (v1 >= 0){
            t_c = t_end + 1; // impossible
        } else {
            t_c = (R - y1) / v1;
        }
    }

    t_c = t_c + t_current; // add current time to get absolute time

    // Set to impossible if the time of collision is in the past
    if (t_c<=t_current){
        t_c = t_end + 1; 
    }

    return t_c;
}





/* 
Calculates all wall collisions for each particle and stores this in the given collisions_array between start and end indices
- Inputs: Array of pointers to particles, Array of pointers to collisions, start_idx (int), end_idx (int)
- Outputs: Updates collisions_array inplace with new Collision structs for all wall collisions
*/
void calculate_all_wall_collisions(Particle ** particle_array, Collision ** collisions_array,int start_idx, int end_idx){

    int idx = start_idx;
    double t_c; // collision time
    for(int i=0; i < n_particles; i++){

        Particle * particle_ptr = particle_array[i];

        // Add the collisions
        Collision * new_collision;
        for (int j =1; j <5 ; j ++){
            t_c = calculate_wall_collision_time(particle_ptr, j);
            new_collision = createCollision(particle_ptr, NULL, t_c, j); // 1 for left wall
            collisions_array[idx++] = new_collision;
        }
    }
}


/* 
Calculates all particle-particle collisions for each particle and store this in the given collisions_array between start and end indices
- Inputs: Array of pointers to particles, Array of pointers to collisions, start_idx (int), end_idx (int)
- Outputs: Updates collisions_array inplace with new Collision structs for all particle-particle collisions
*/
void calculate_all_particle_collisions(Particle ** particle_array, Collision ** collisions_array, int start_idx, int end_idx){

    int idx = start_idx;
    double t_c; // collision time

    // loop through each particle - and check each other particle as well 
    for(int i= 0; i< n_particles; i++){
        Particle * particle_1 = particle_array[i]; 

        for(int j=i+1; j<n_particles; j++){
            Particle * particle_2 = particle_array[j];
            // printf("Calculating particle collision between %d and %d\n", i, j);

            // Create collision, calculate it's time, append it to list
            Collision * new_collision = createCollision(particle_1, particle_2, t_end, 0); // 0 for no wall
            t_c = calculate_particle_collision_time(new_collision);
            new_collision->time = t_c;        
            collisions_array[idx++] = new_collision; 
        }
    }
}



/* 
Processes the given (earliest) collision and updates the velocities and positions of the involved particles
Inputs: Pointer to the collision struct
Outputs: Updates the velocities and positions of particles involved in the collision inplace
*/
void process_collision(Collision * collision_ptr){

    // Update particle 1 position and time
    Particle * particle_1 = collision_ptr->particle_1;
    
    particle_1->xpos = particle_1->xpos + particle_1->xvel * (t_current - particle_1->lastUpdateTime);
    particle_1->ypos = particle_1->ypos + particle_1->yvel * (t_current- particle_1->lastUpdateTime);
    particle_1->lastUpdateTime = t_current;
    

    int wall_num = collision_ptr->wall;

    if(wall_num == 0) // particle-particle collision
    { 
        Particle * particle_2 = collision_ptr->particle_2;

        // Update particle 2 position and time
        particle_2->xpos = particle_2->xpos + particle_2->xvel * (t_current - particle_2->lastUpdateTime);
        particle_2->ypos = particle_2->ypos + particle_2->yvel * (t_current- particle_2->lastUpdateTime);
        collision_ptr->particle_2->lastUpdateTime = t_current;

        // Get current velocities
        double u1 = particle_1->xvel;
        double v1 = particle_1->yvel;
        double u2 = particle_2->xvel;
        double v2 = particle_2->yvel;

        // Update velocities
        particle_1->xvel = u2;
        particle_1->yvel = v2;
        particle_2->xvel = u1;
        particle_2->yvel = v1;

        // Update Colliison counts for each particle
        particle_1->cpart += 1;
        particle_2->cpart += 1;
    } 
    else // Collision is with a wall
    { 
        // printf("Processing wall collision for particle %d with wall %d \n", particle_1->id, wall_num);

        if(wall_num < 3) { // right or left wall
            particle_1->xvel = -1 * particle_1->xvel;
        } else { // top or bottom wall
            particle_1->yvel = -1 * particle_1->yvel;

        }
        // Update collision count
        particle_1->cwall += 1;
    }
}


/* 
Updates collision times for affected particles after a collision is processed
- Inputs: Pointers to particles involved in the collision (second particle is NULL for wall collisions), and collisions_array
- Outputs: Update collision times in the collisions_array in place for all collisions involving the particles specified
*/
void update_affected_particles(Particle * particle_1, Particle * particle_2, Collision ** collisions_array){

    // Calculate wow many collisions we need to update so we can terminate early
    int n_relevant_collisions;  
    int counter = 0;
    int wall_num;

    if (particle_2 == NULL){ // We had a wall collision
        n_relevant_collisions = n_particles + 3; // n-1 + 4
    } else { // Particle - particle collision
        n_relevant_collisions = 2 * n_particles + 5; // n-1 + 4 + n-2 + 4 
    }

    Collision * collision_ptr;

    // Loop through all collisions
    for (int i = 0; i < n_collisions; i ++)
    {
        collision_ptr = collisions_array[i];
        wall_num = collision_ptr->wall;

        if (collision_ptr->particle_1 == particle_1 || collision_ptr->particle_2 == particle_1  
            || ((collision_ptr->particle_1 == particle_2) && (particle_2 != NULL)) || ( (collision_ptr->particle_2 == particle_2) && (particle_2 != NULL)) )
        {

            // Check type of collision and update collision time
            if (wall_num == 0)// Particle - particle collision
            { 
                collision_ptr->time = calculate_particle_collision_time(collision_ptr);
            } else // Particle - Wall collision
            {   
                collision_ptr->time = calculate_wall_collision_time(collision_ptr->particle_1, wall_num);
            }

            if (++counter == n_relevant_collisions)
            {
            break; 
            }
        }
    }

}


