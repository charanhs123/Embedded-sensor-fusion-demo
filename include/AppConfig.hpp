#ifndef APPCONFIG_HPP
#define APPCONFIG_HPP

#include <string>

struct AppConfig
{
    int steps = 20;
    double dt = 1.0;
    double initial_position = 0.0;
    double true_velocity = 1.2;
    double measurement_noise_stddev = 0.8;
    double process_noise_position = 0.01;
    double process_noise_velocity = 0.01;
    double measurement_noise_variance = 0.64;
    unsigned int seed = 42U;
    bool enable_csv = false;
    std::string csv_path = "simulation.csv";
};

bool parseArguments(int argc, char* argv[], AppConfig& config);
void printUsage(const char* program_name);

#endif