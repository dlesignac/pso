// -----------------------------------------------------------------------------
// Particle (v2.0)
// -----------------------------------------------------------------------------

#include <cmath>
#include <ctgmath>
#include <ctime>
#include <omp.h>

#include "Particle.h"
#include "Optimizable.h"
#include "utils.h"

using namespace std;


Particle::
~Particle() {}


Particle::
Particle() {}

Particle::
Particle(Optimizable o, int * current) {
    int         i;
    double *    param_values;

    param_values    = new double[o.n_param];

    // Parameters' values are calculated using the coordinates given to the
    // constructor. This way, the problem is discretized and can be optimized
    // more easily
    for (i = 0; i < o.n_param; i++)
        param_values[i]
            = o.domains[i]. min + o.domains[i].step * (double) current[i];

    // The particle's optimum is set by default as the value got for the current
    // parameters' values
    this->problem       = o;
    this->current       = current;
    this->optimum       = o.inner_f(o.n_param, param_values);
    this->opt_coords    = current;
}


/*
    Moves randomly to a neighbour and updates the optimum
*/
void Particle::
explore() {
    int         i;
    float       random;
    double      tmp;
    double *    param_values;

    param_values    = new double[problem.n_param];

    // For each parameter, we choose randomly to keep the current value, to take
    // the directly higher value or the directly lower value
    for (i = 0; i < problem.n_param; i++) {
        random = rand() % 3;

        if ((random == 0) && (current[i] > 0))
            current[i]--;
        if ((random == 1) && (current[i] < problem.domains[i].precision))
            current[i]++;

        param_values[i]
            = problem.domains[i].min
                + problem.domains[i].step * (double) current[i];
    }

    // The particle should now compare the current value with its previous
    // found optimum and update it if necessary
    tmp = problem.inner_f(problem.n_param, param_values);

    if ((problem.problem_type == ProblemType::MAX && optimum < tmp)
    || (problem.problem_type == ProblemType::MIN && optimum > tmp)) {
        optimum     = tmp;
        opt_coords  = current;
    }
}
