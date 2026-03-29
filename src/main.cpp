#include <iomanip>
#include <iostream>
#include <vector>

#include "AppConfig.hpp"
#include "CsvLogger.hpp"
#include "Kalman2State.hpp"
#include "LeastSquaresFit.hpp"
#include "SignalGenerator.hpp"

int main(int argc, char* argv[])
{
    AppConfig config;

    if (!parseArguments(argc, argv, config))
    {
        return 1;
    }

    SignalGenerator signal(config.initial_position,
                           config.true_velocity,
                           config.measurement_noise_stddev,
                           config.seed);

    Kalman2State kalman(config.dt,
                        config.process_noise_position,
                        config.process_noise_velocity,
                        config.measurement_noise_variance);

    CsvLogger logger;
    if (config.enable_csv)
    {
        if (!logger.open(config.csv_path))
        {
            std::cerr << "Failed to open CSV file: " << config.csv_path << '\n';
            return 1;
        }
        logger.writeHeader();
    }

    std::vector<double> time_values;
    std::vector<double> measured_values;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Step\tTime\tTrue\tMeasured\tKalmanPos\tKalmanVel\n";

    for (int i = 0; i < config.steps; ++i)
    {
        const double time = static_cast<double>(i + 1) * config.dt;
        const double measured = signal.step(config.dt);

        kalman.predict();
        kalman.update(measured);

        time_values.push_back(time);
        measured_values.push_back(measured);

        std::cout
            << (i + 1) << '\t'
            << time << '\t'
            << signal.getTruePosition() << '\t'
            << measured << '\t'
            << kalman.getPosition() << '\t'
            << kalman.getVelocity() << '\n';

        if (logger.isOpen())
        {
            logger.writeRow(i + 1,
                            time,
                            signal.getTruePosition(),
                            measured,
                            kalman.getPosition(),
                            kalman.getVelocity());
        }
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