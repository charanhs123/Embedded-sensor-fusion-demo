#include "Kalman2State.hpp"

Kalman2State::Kalman2State(double dt,
                           double process_noise_position,
                           double process_noise_velocity,
                           double measurement_noise)
    : dt_(dt),
      x_pos_(0.0),
      x_vel_(0.0),
      p00_(1.0),
      p01_(0.0),
      p10_(0.0),
      p11_(1.0),
      q_pos_(process_noise_position),
      q_vel_(process_noise_velocity),
      r_(measurement_noise),
      initialized_(false)
{
}

void Kalman2State::initialize(double initial_position, double initial_velocity)
{
    x_pos_ = initial_position;
    x_vel_ = initial_velocity;

    p00_ = 1.0;
    p01_ = 0.0;
    p10_ = 0.0;
    p11_ = 1.0;

    initialized_ = true;
}

void Kalman2State::predict()
{
    if (!initialized_)
    {
        return;
    }

    // State prediction
    // x(k+1) = A*x(k), where A = [1 dt; 0 1]
    x_pos_ = x_pos_ + dt_ * x_vel_;
    x_vel_ = x_vel_;

    // Covariance prediction:
    // P' = A P A^T + Q
    const double new_p00 = p00_ + dt_ * (p10_ + p01_) + dt_ * dt_ * p11_ + q_pos_;
    const double new_p01 = p01_ + dt_ * p11_;
    const double new_p10 = p10_ + dt_ * p11_;
    const double new_p11 = p11_ + q_vel_;

    p00_ = new_p00;
    p01_ = new_p01;
    p10_ = new_p10;
    p11_ = new_p11;
}

void Kalman2State::update(double measurement)
{
    if (!initialized_)
    {
        initialize(measurement, 0.0);
        return;
    }

    // Measurement model: z = Hx, H = [1 0]
    const double y = measurement - x_pos_;     // innovation
    const double s = p00_ + r_;                // innovation covariance

    const double k0 = p00_ / s;                // Kalman gain
    const double k1 = p10_ / s;

    // State update
    x_pos_ = x_pos_ + k0 * y;
    x_vel_ = x_vel_ + k1 * y;

    // Covariance update
    const double new_p00 = (1.0 - k0) * p00_;
    const double new_p01 = (1.0 - k0) * p01_;
    const double new_p10 = p10_ - k1 * p00_;
    const double new_p11 = p11_ - k1 * p01_;

    p00_ = new_p00;
    p01_ = new_p01;
    p10_ = new_p10;
    p11_ = new_p11;
}

double Kalman2State::getPosition() const
{
    return x_pos_;
}

double Kalman2State::getVelocity() const
{
    return x_vel_;
}