#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>

#define n_body 10
#define n_steps 100000

/*
Verlet intergation:
x' = 2x - x* + a·Δt^2
Velocity: from the mean value theorem:
v = [ x' - x* ] / 2·Δt
-----------------------------------
x'  - Next position
v   - Current Velocity
x*  - Previous Position
x   - Current Position
a   - Accelration based on F = m·a
Δt  - Time step

Newton's laws of Gravtiy:
F = G·[ m1·m2 / r^2 ]
-----------------------------------
F   - Force
G   - Gravitational Consant
m   - Masses of the two bodies
r   - Distance between the two bodies

Mechanical Energy:
-----------------------------------
Kinetic   - Sum[n] 0.5·m·v^2
Potential - Sum[i != j] -0.5·m(i)·m(j)|r(i) - r(j)|
          - Need to do a mutlipole expansion for tree method!

Simulation Steps:
-----------------------------------
  1. Enter intital positions for each body [current and previous]!
  2. Enter masses for each body
  3. Itteration step: for (each itteration of time step - Δt):
  4. Itegration step: for (each body (i)):
    a. calculate (a) for this particle -> F = m·a -> F comes from Newton
    b. new_x[i] = 2·current_x[i] - old_x[i]·a·Δt^2
    c. current_x[i] = new_x[i]
    d. old_x[i] = current_x[i]
*/

char hline[50] = "--------------------------------------\n";

// CoM variables
double cen_x;
double cen_y;
double tot_m;

// Position Vectors
double new_x[n_body];
double cur_x[n_body];
double old_x[n_body];

double new_y[n_body];
double cur_y[n_body];
double old_y[n_body];

// Velocity Bectors
double old_v_x[n_body];
double old_v_y[n_body];

// Mass vector
double mass[n_body];
// Force Vector
double force_vec[n_body][2];

double potential[n_steps];
double kinetic[n_steps];

double G = 6.67408e-11;
// double G = 66391.85240128;
double dt = 0.5;      // seconds

void gen_mass_pos(char sim);

int main(int argc, char* argv[]) {
  if ( argc != 3 ) {
    printf("Expected One Argument\n");
    printf("Usage: [Output File Name] [Simulation number: (1) or (2)]\n");
    printf("  Simulation 1 - Satellite In Geosnyc Orbit range\n")
    printf("  Simulation 2 - n_bodies, with close to same masses, and random positions within a range\n")
    printf("Be sure to change #define n_body in code to correspond with simultaation number or how many bodies you want\n")
  } else {
    // char sim = argv[1];
    printf("Running Simulation: [%s]\n", argv[2]);

    FILE *fp;
    fp = fopen(argv[1], "w");

    // Seed the random number genrator
    srand(time(NULL) * 4);
    // Generate the iniitla conditions based on the simultation chosen
    gen_mass_pos(*argv[2]);

    // Print Initial Condtions for each body
    for (int j = 0; j < n_body; j++) {
      printf("Initial position for Body[%d]: (%f, %f)\n", j, old_x[j], old_y[j]);
      force_vec[j][0] = 0;
      force_vec[j][1] = 0;
      old_v_x[j] = 0;
      old_v_y[j] = 0;
    }

    // Time step itteration outer loop
    for (int i = 1; i < n_steps; i++) {
      // printf("%s", hline);
      cen_x = 0;
      cen_y = 0;
      // Verlet integration - for each body
      for (int j = 0; j < n_body; j++) {
        old_v_x[j] = 0;
        old_v_y[j] = 0;
        // Calculate Force Vectors and Potential for each body
        for (int k = 0; k < n_body; k++) {
          if (k == j) {
            // do nothing!
          } else {
            // Calculate euclidian distance between bodies [k] and [j]
            double euclid = sqrt( pow(cur_x[j] - cur_x[k],2) + pow(cur_y[j] - cur_y[k],2) );
            // Calculate X component of Force, and Accumalte
            force_vec[j][0] += ( -G * ( ( mass[k] * mass[j] * (cur_x[j] - cur_x[k]) ) / pow(euclid,3) ) );
            // Calculate Y component of Force, and Accumalte
            force_vec[j][1] += ( -G * ( ( mass[k] * mass[j] * (cur_y[j] - cur_y[k]) ) / pow(euclid,3) ) );
            // Accumalte Potential for current itteration, no duplicates i.e. only all unique interactions
            if (k > j) {
              potential[i] += ( ( -0.5 * G * mass[k] * mass[j] ) / euclid );
              // potential[i] += (euclid);
            }
          }
        }

        // Calculate new positions and old velocities
        new_x[j] = (2.0*cur_x[j]) - (old_x[j]) + ( (force_vec[j][0] / mass[j]) *dt*dt);
        new_y[j] = (2.0*cur_y[j]) - (old_y[j]) + ( (force_vec[j][1] / mass[j]) *dt*dt);
        old_v_x[j] = (new_x[j] - old_x[j]) / (2*dt);
        old_v_y[j] = (new_y[j] - old_y[j]) / (2*dt);

        // Accumalte total KE for this time step, based on KE of each individiual particle
        kinetic[i] += ( 0.5 * mass[j] * ( pow(old_v_x[j],2) + pow(old_v_y[j],2) ) );

        // update positions for next itteration
        old_x[j] = cur_x[j];
        old_y[j] = cur_y[j];

        cur_x[j] = new_x[j];
        cur_y[j] = new_y[j];

        // Write Position Data to out file
        fprintf(fp, "%1.20f\t%1.20f\t%1.20f\n", new_x[j], new_x[j], new_y[j]);
      }
      // Write Energy Data to out file
      fprintf(fp, "%1.20f\t%1.20f\t%1.20f\n", kinetic[i] + potential[i], kinetic[i], potential[i]);
    }
    // Print Final Positions
    printf("%s", hline);
    for (int i = 0; i < n_body; i++) {
      printf("Final position for Body[%d]: (%f, %f)\n", i, new_x[i], new_y[i]);
    }
    // Clean Up
    fclose(fp);
    return(0);
  }
}

void gen_mass_pos(char sim) {
  if (sim == '2') {
    for (int i = 0; i < n_body; i++) {
      // Range = 0 - 100 meters
      cur_x[i] = old_x[i] = (double)(rand() % 100);
      cur_y[i] = old_y[i] = (double)(rand() % 100);
      // cur_x[i] += (double)(rand() % 50);
      // cur_y[i] += (double)(rand() % 50);

      // Range = 10 - 110 kg
      mass[i] = (double)(rand() % 100) + 10;

      // Calculate center of mass
      cen_x += mass[i]*cur_x[i];
      cen_y += mass[i]*cur_y[i];
      tot_m += mass[i];
    }
    // Shift Center of Mass to the origin
    cen_x /= tot_m;
    cen_y /= tot_m;
    for (int i = 0; i < n_body; i++) {
      cur_x[i] -= cen_x;
      cur_y[i] -= cen_y;
      old_x[i] -= cen_x;
      old_y[i] -= cen_y;
    }
  } else {
    cur_x[0] = cur_y[0] = old_x[0] = old_y[0] = 0;
    cur_x[1] = 35784000;
    cur_y[1] = 31000;
    old_x[1] = 35786000;;
    old_y[1] = 0;
    mass[0] = 5.972E24;
    mass[1] = 1000;
  }
}
