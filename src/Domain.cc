// -----------------------------------------------------------------------------
// Domain (v2.0) 
// -----------------------------------------------------------------------------

#include "Domain.h"
#include "utils.h"

using namespace std;


Domain::
~Domain() {}

Domain::
Domain() {}

Domain::
Domain(double min, double max, int precision) {
    this->min       = min;
    this->max       = max;
    this->precision = precision;
    this->step      = (max - min) / (double) precision;
}
