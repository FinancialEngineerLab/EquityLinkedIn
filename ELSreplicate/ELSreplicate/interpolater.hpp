
#ifndef INTERPOLATOR_HPP
#define INTERPOLATOR_HPP
#include <vector>

class interpolator
{
public:
    interpolator(){};
    double intp1d(std::vector<double> v, std::vector<double> axis, double target) const;
    
};
#endif
