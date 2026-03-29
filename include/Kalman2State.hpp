#ifndef KALMAN2STATE_HPP
#define KALMAN2STATE_HPP

class Kalman2State
{
public:
    Kalman2State(double dt,
                 double process_noise_position,
                 double process_noise_velocity,
                 double measurement_noise);

    void initialize(double initial_position, double initial_velocity);

    void predict();
    void update(double measurement);

    double getPosition() const;
    double getVelocity() const;

private:
    double dt_;

    // State: [position, velocity]
    double x_pos_;
    double x_vel_;

    // Covariance matrix P
    double p00_;
    double p01_;
    double p10_;
    double p11_;

    // Process noise
    double q_pos_;
    double q_vel_;

    // Measurement noise
    double r_;

    bool initialized_;
};

#endif