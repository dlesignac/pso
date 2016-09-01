// -----------------------------------------------------------------------------
// Particle (v2.0)
//
// Explores randomly the domains and keeps the optimum found
//  * problem : the problem that should be optimized
//  * current : last position took by the particle (set of parameters' values)
//  * optimum : optimum found for the problem
//  * opt_coords : coordinates of the optimum found
// -----------------------------------------------------------------------------

#include "Optimizable.h"
#include "utils.h"

using namespace std;


#ifndef _Particle
#define _Particle

class Particle {
    public :
        Optimizable     problem;
        int *           current;
        double          optimum;
        int *           opt_coords;

        ~   Particle();
            Particle();
            Particle(Optimizable o, int * current);

        void explore();
};

#endif
