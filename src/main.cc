// -----------------------------------------------------------------------------
// Particle Swarm Optimization (v2.0)
// By Yves Colin De Verdiere, Celine Lepicard and Damien Lesignac
// -----------------------------------------------------------------------------


#define OS_LINUX


#include <cmath>
#include <ctgmath>

#include "Optimizable.h"
#include "Particle.h"
#include "utils.h"

using namespace std;


/*
    Test function
    Returns the sum of the parameters

    @param int n_param : number of parameters
    @param double * param : parameters
*/
double f(int n_param, double * param) {
    if (n_param) return f(n_param -1, param) + param[n_param - 1];

    return 0.;
}



int main(int argc, char * argv[]) {
	clock_t tstart, tstop;

	// Initialization
		Domain * p_x	= new Domain(-1000., 1000., 5000);
		Domain * p_y	= new Domain(-1000., 1000., 5000);
		Domain * p_z    = new Domain(-1000., 1000., 5000);

		Domain * d      = new Domain[3];
		d[0]            = *p_x;
		d[1]            = *p_y;
		d[2]            = *p_z;

		Optimizable *   p_o = new Optimizable(f, 3, d, ProblemType::MAX);

	// Sequential
		tstart  = clock();
		p_o->optimize(100, 100);
		tstop   = clock();

		cout << "  Seq found " << p_o->optimum << " in "
			<< (double) (tstop - tstart) << " ticks\n";

	// With OMP
		tstart  = clock();
		p_o->optimize_omp(100, 100);
		tstop   = clock();

		cout << "  OMP found " << p_o->optimum << " in "
			<< (double) (tstop - tstart) << " ticks\n";

	return 0;
}
