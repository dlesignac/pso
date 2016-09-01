// -----------------------------------------------------------------------------
// Class Optimizable (v2.0)
// -----------------------------------------------------------------------------

#include <iostream>
#include <omp.h>

#include "Domain.h"
#include "Optimizable.h"
#include "Particle.h"
#include "utils.h"

using namespace std;


Optimizable::
~Optimizable() {}

Optimizable::
Optimizable() {}

Optimizable::
Optimizable(
    double      (*f)(int, double *),
    int         n_param,
    Domain *    d,
    ProblemType pt
) {
    inner_f		    = f;
    this->n_param   = n_param;
    this->domains   = d;
    problem_type    = pt;
    optimum		    = 0.0;
    optimized	    = false;
}


/*
    Uses our PSO to find an approximated solution of the Optimizable problem

    @param int n_particles  : defines the number of particles used to search
    @param int n_moves      : defines the number of moves that a particle can do
*/
void Optimizable::
optimize(int n_particles, int n_moves) {
    int         i, j;
    int *       rand_coords;
    Particle *  particle;
    Particle *  particles;

    rand_coords     = new int[this->n_param];
    particles       = new Particle[n_particles];

    srand(int(time(NULL)));

    // Particles are given random coordinates so they do not start at the same
    // position 
    for (i = 0; i < n_particles; i++) {
        for (j = 0; j < this->n_param; j++)
            rand_coords[j]  = rand() % (this->domains[j].precision + 1);

        particle        = new Particle(*this, rand_coords);
        particles[i]    = *particle;
    }

    // Particles are asked to explore (move randomly around their current
    // position and update their optimum if necessary)
    for (i = 0; i < n_moves; i++)
        for (j = 0; j < n_particles; j++)
            particles[j].explore();

    // Our optimizable problem should now be given an optimum, which is the
    // optimum of the optima of the particles
    for (i = 0; i < n_particles; i++)
        if (optimized) {
            if ((particles[i].optimum > optimum
            && problem_type == ProblemType::MAX)
            || (particles[i].optimum < optimum
            && problem_type == ProblemType::MIN))
                optimum = particles[i].optimum;
        } else {
            optimum     = particles[i].optimum;
            optimized   = true;
        }
}


/*
    Uses our PSO to find an approximated solution of the Optimizable problem
    OMP version

    @param int n_particles  : defines the number of particles used to search
    @param int n_moves      : defines the number of moves that a particle can do
*/
void Optimizable::
optimize_omp(int n_particles, int n_moves) {
    int         i, j;
    int *       rand_coords;
    double      opt;
    Particle *  particle;
    Particle *  particles;

    rand_coords     = new int[this->n_param];
    particles       = new Particle[n_particles];
    opt             = 0.;

    omp_set_num_threads(4);

    #pragma omp parallel private(j)
    {
        srand(int(time(NULL)) ^ omp_get_thread_num());

        // Particles are given random coordinates so they do not start at the
        // same position
        #pragma omp for
        for (i = 0; i < n_particles; i++) {
            for (j = 0; j < this->n_param; j++)
                rand_coords[j]  = rand() % (this->domains[j].precision + 1);

            particle        = new Particle(*this, rand_coords);
            particles[i]    = *particle;
        }

        // Particles are asked to explore (move randomly around their current
        // position and update their optimum if necessary)
        #pragma omp for
        for (i = 0; i < n_moves; i++)
            for (j = 0; j < n_particles; j++)
                particles[j].explore();

        // Our optimizable problem should now be given an optimum, which is the
        // optimum of the optima of the particles
        #pragma omp for
        for (i = 0; i < n_particles; i++)
            if (optimized) {
                if ((particles[i].optimum > opt
                && problem_type == ProblemType::MAX)
                || (particles[i].optimum < opt
                && problem_type == ProblemType::MIN))
                    opt = particles[i].optimum;
            } else {
                opt         = particles[i].optimum;
                optimized   = true;
            }
    }

    optimum = opt;
}
