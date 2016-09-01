// -----------------------------------------------------------------------------
// Domain (v2.0)
//
// Describes a domain where a parameter can evolve
//  * min : the minimum of the domain
//  * max : the maximum of the domain
//  * precision : the number of values that the parameter can take (allows 
//      discretization)
//  * step : amount that separates each consecutive values took by the parameter
// -----------------------------------------------------------------------------

using namespace std;


#ifndef _Domain
#define _Domain

class Domain {
    public :
        double  min;
        double  max;
        int     precision;
        double  step;

        ~   Domain();
            Domain();
            Domain(double min, double max, int precision);
};

#endif
