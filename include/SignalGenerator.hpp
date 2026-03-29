#ifndef SIGNALGENERATOR_HPP
#define SIGNALGENERATOR_HPP

#include <random>

class SignalGenerator
{
public:
    SignalGenerator(double true_initial_position,
                    double true_velocity,
                    double measurement_noise_stddev,
                    unsigned int seed = 42U);

    double step(double dt);
    double getTruePosition() const;

private:
    double true_position_;
    double true_velocity_;

    std::mt19937 rng_;
    std::normal_distribution<double> noise_dist_;
};

#endif