#include "LeastSquaresFit.hpp"

LineFitResult LeastSquaresFit::fitLine(const std::vector<double>& x,
                                       const std::vector<double>& y)
{
    LineFitResult result{0.0, 0.0, false};

    if (x.size() != y.size() || x.size() < 2)
    {
        return result;
    }

    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_x2 = 0.0;

    const std::size_t n = x.size();

    for (std::size_t i = 0; i < n; ++i)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    const double denominator = (static_cast<double>(n) * sum_x2) - (sum_x * sum_x);

    if (denominator == 0.0)
    {
        return result;
    }

    result.slope =
        ((static_cast<double>(n) * sum_xy) - (sum_x * sum_y)) / denominator;

    result.intercept =
        (sum_y - result.slope * sum_x) / static_cast<double>(n);

    result.valid = true;
    return result;
}