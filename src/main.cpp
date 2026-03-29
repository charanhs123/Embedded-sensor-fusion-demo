#include <iomanip>
#include <iostream>
#include <vector>

#include "Kalman2State.hpp"
#include "LeastSquaresFit.hpp"
#include "SignalGenerator.hpp"

int main()
{
    const double dt = 1.0;
    const int steps = 20;

    SignalGenerator signal(0.0, 1.2, 0.8);
    Kalman2State kalman(dt, 0.01, 0.01, 0.64);

    std::vector<double> time_values;
    std::vector<double> measured_values;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Step\tTrue\tMeasured\tKalmanPos\tKalmanVel\n";

    for (int i = 0; i < steps; ++i)
    {
        const double measured = signal.step(dt);

        kalman.predict();
        kalman.update(measured);

        time_values.push_back(static_cast<double>(i + 1));
        measured_values.push_back(measured);

        std::cout
            << (i + 1) << '\t'
            << signal.getTruePosition() << '\t'
            << measured << '\t'
            << kalman.getPosition() << '\t'
            << kalman.getVelocity() << '\n';
    }

    const LineFitResult fit = LeastSquaresFit::fitLine(time_values, measured_values);

    if (fit.valid)
    {
        std::cout << "\nLeast Squares Fit:\n";
        std::cout << "y = " << fit.slope << " * t + " << fit.intercept << '\n';
    }
    else
    {
        std::cout << "\nLeast Squares Fit failed.\n";
    }

    return 0;
}