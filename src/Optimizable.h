// -----------------------------------------------------------------------------
// Class Optimizable (v2.0)
//
// Contains a problem to solve
//  * objective : min or max
//  * a two unknowns equation to optimize
//  * domains of unknowns
//  * precisions : arbitrary mesures used to discretize domains
// -----------------------------------------------------------------------------

#include <iostream>

#include "Domain.h"
#include "utils.h"

using namespace std;


#ifndef _Optimizable
#define _Optimizable

class Optimizable {
    public:
        double      (*inner_f)(int, double *);
        int         n_param;
        Domain *    domains;

        double      optimum;
        bool        optimized;
        ProblemType problem_type;

        ~   Optimizable();
            Optimizable();
            Optimizable(
                double      (*f)(int, double *),
                int         n_param,
                Domain *    d,
                ProblemType pt
            );

        void optimize(int n_particles, int n_moves);
        void optimize_omp(int n_particles, int n_moves);
};

#endif
