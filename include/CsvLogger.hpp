#ifndef CSVLOGGER_HPP
#define CSVLOGGER_HPP

#include <fstream>
#include <string>

class CsvLogger
{
public:
    CsvLogger();
    ~CsvLogger();

    bool open(const std::string& path);
    void writeHeader();
    void writeRow(int step,
                  double time,
                  double true_position,
                  double measured_position,
                  double kalman_position,
                  double kalman_velocity);
    bool isOpen() const;

private:
    std::ofstream file_;
};

#endif