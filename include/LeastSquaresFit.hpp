#ifndef LEASTSQUARESFIT_HPP
#define LEASTSQUARESFIT_HPP

#include <vector>

struct LineFitResult
{
    double slope;
    double intercept;
    bool valid;
};

class LeastSquaresFit
{
public:
    static LineFitResult fitLine(const std::vector<double>& x,
                                 const std::vector<double>& y);
};

#endif