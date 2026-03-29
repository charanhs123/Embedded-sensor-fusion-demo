#include "SignalGenerator.hpp"

SignalGenerator::SignalGenerator(double true_initial_position,
                                 double true_velocity,
                                 double measurement_noise_stddev,
                                 unsigned int seed)
    : true_position_(true_initial_position),
      true_velocity_(true_velocity),
      rng_(seed),
      noise_dist_(0.0, measurement_noise_stddev)
{
}

double SignalGenerator::step(double dt)
{
    true_position_ += true_velocity_ * dt;
    return true_position_ + noise_dist_(rng_);
}

double SignalGenerator::getTruePosition() const
{
    return true_position_;
}