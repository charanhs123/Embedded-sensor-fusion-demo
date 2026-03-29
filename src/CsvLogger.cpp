#include "CsvLogger.hpp"

#include <iomanip>

CsvLogger::CsvLogger() = default;
CsvLogger::~CsvLogger() = default;

bool CsvLogger::open(const std::string& path)
{
    file_.open(path);
    return file_.is_open();
}

void CsvLogger::writeHeader()
{
    if (!file_.is_open())
    {
        return;
    }

    file_ << "step,time,true_position,measured_position,kalman_position,kalman_velocity\n";
}

void CsvLogger::writeRow(int step,
                         double time,
                         double true_position,
                         double measured_position,
                         double kalman_position,
                         double kalman_velocity)
{
    if (!file_.is_open())
    {
        return;
    }

    file_ << step << ','
          << std::fixed << std::setprecision(6)
          << time << ','
          << true_position << ','
          << measured_position << ','
          << kalman_position << ','
          << kalman_velocity << '\n';
}

bool CsvLogger::isOpen() const
{
    return file_.is_open();
}