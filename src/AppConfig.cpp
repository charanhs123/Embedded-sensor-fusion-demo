#include "AppConfig.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace
{
bool parseInt(const std::string& value, int& out)
{
    try
    {
        std::size_t idx = 0;
        const int parsed = std::stoi(value, &idx);
        if (idx != value.size())
        {
            return false;
        }
        out = parsed;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool parseUnsigned(const std::string& value, unsigned int& out)
{
    try
    {
        std::size_t idx = 0;
        const unsigned long parsed = std::stoul(value, &idx);
        if (idx != value.size())
        {
            return false;
        }
        out = static_cast<unsigned int>(parsed);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool parseDouble(const std::string& value, double& out)
{
    try
    {
        std::size_t idx = 0;
        const double parsed = std::stod(value, &idx);
        if (idx != value.size())
        {
            return false;
        }
        out = parsed;
        return true;
    }
    catch (...)
    {
        return false;
    }
}
}

void printUsage(const char* program_name)
{
    std::cout
        << "Usage: " << program_name << " [options]\n\n"
        << "Options:\n"
        << "  --steps <int>             Number of simulation steps\n"
        << "  --dt <double>             Time step\n"
        << "  --initial-pos <double>    Initial true position\n"
        << "  --velocity <double>       True velocity of simulated signal\n"
        << "  --noise-std <double>      Measurement noise standard deviation\n"
        << "  --q-pos <double>          Kalman process noise for position\n"
        << "  --q-vel <double>          Kalman process noise for velocity\n"
        << "  --r <double>              Kalman measurement noise variance\n"
        << "  --seed <uint>             RNG seed\n"
        << "  --csv <path>              Enable CSV logging to given file\n"
        << "  --help                    Show this help message\n";
}

bool parseArguments(int argc, char* argv[], AppConfig& config)
{
    for (int i = 1; i < argc; ++i)
    {
        const std::string arg = argv[i];

        if (arg == "--help")
        {
            printUsage(argv[0]);
            return false;
        }
        else if (arg == "--steps" && i + 1 < argc)
        {
            if (!parseInt(argv[++i], config.steps))
            {
                std::cerr << "Invalid value for --steps\n";
                return false;
            }
        }
        else if (arg == "--dt" && i + 1 < argc)
        {
            if (!parseDouble(argv[++i], config.dt))
            {
                std::cerr << "Invalid value for --dt\n";
                return false;
            }
        }
        else if (arg == "--initial-pos" && i + 1 < argc)
        {
            if (!parseDouble(argv[++i], config.initial_position))
            {
                std::cerr << "Invalid value for --initial-pos\n";
                return false;
            }
        }
        else if (arg == "--velocity" && i + 1 < argc)
        {
            if (!parseDouble(argv[++i], config.true_velocity))
            {
                std::cerr << "Invalid value for --velocity\n";
                return false;
            }
        }
        else if (arg == "--noise-std" && i + 1 < argc)
        {
            if (!parseDouble(argv[++i], config.measurement_noise_stddev))
            {
                std::cerr << "Invalid value for --noise-std\n";
                return false;
            }
        }
        else if (arg == "--q-pos" && i + 1 < argc)
        {
            if (!parseDouble(argv[++i], config.process_noise_position))
            {
                std::cerr << "Invalid value for --q-pos\n";
                return false;
            }
        }
        else if (arg == "--q-vel" && i + 1 < argc)
        {
            if (!parseDouble(argv[++i], config.process_noise_velocity))
            {
                std::cerr << "Invalid value for --q-vel\n";
                return false;
            }
        }
        else if (arg == "--r" && i + 1 < argc)
        {
            if (!parseDouble(argv[++i], config.measurement_noise_variance))
            {
                std::cerr << "Invalid value for --r\n";
                return false;
            }
        }
        else if (arg == "--seed" && i + 1 < argc)
        {
            if (!parseUnsigned(argv[++i], config.seed))
            {
                std::cerr << "Invalid value for --seed\n";
                return false;
            }
        }
        else if (arg == "--csv" && i + 1 < argc)
        {
            config.enable_csv = true;
            config.csv_path = argv[++i];
        }
        else
        {
            std::cerr << "Unknown or incomplete argument: " << arg << '\n';
            printUsage(argv[0]);
            return false;
        }
    }

    if (config.steps <= 0)
    {
        std::cerr << "--steps must be > 0\n";
        return false;
    }

    if (config.dt <= 0.0)
    {
        std::cerr << "--dt must be > 0\n";
        return false;
    }

    if (config.measurement_noise_stddev < 0.0)
    {
        std::cerr << "--noise-std must be >= 0\n";
        return false;
    }

    if (config.measurement_noise_variance < 0.0)
    {
        std::cerr << "--r must be >= 0\n";
        return false;
    }

    return true;
}