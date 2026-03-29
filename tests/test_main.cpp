#include <cmath>
#include <vector>

#include <gtest/gtest.h>

#include "Kalman2State.hpp"
#include "LeastSquaresFit.hpp"

TEST(LeastSquaresFitTest, PerfectLineFit)
{
    const std::vector<double> x{1.0, 2.0, 3.0, 4.0};
    const std::vector<double> y{3.0, 5.0, 7.0, 9.0}; // y = 2x + 1

    const LineFitResult result = LeastSquaresFit::fitLine(x, y);

    EXPECT_TRUE(result.valid);
    EXPECT_NEAR(result.slope, 2.0, 1e-6);
    EXPECT_NEAR(result.intercept, 1.0, 1e-6);
}

TEST(LeastSquaresFitTest, InvalidInput)
{
    const std::vector<double> x{1.0};
    const std::vector<double> y{2.0};

    const LineFitResult result = LeastSquaresFit::fitLine(x, y);

    EXPECT_FALSE(result.valid);
}

TEST(Kalman2StateTest, InitializesFromFirstMeasurement)
{
    Kalman2State kalman(1.0, 0.01, 0.01, 0.25);

    kalman.update(10.0);

    EXPECT_NEAR(kalman.getPosition(), 10.0, 1e-6);
    EXPECT_NEAR(kalman.getVelocity(), 0.0, 1e-6);
}

TEST(Kalman2StateTest, TracksConstantVelocityTrend)
{
    Kalman2State kalman(1.0, 0.01, 0.01, 0.25);

    const std::vector<double> measurements{1.0, 2.0, 3.0, 4.0, 5.0};

    for (double z : measurements)
    {
        kalman.predict();
        kalman.update(z);
    }

    EXPECT_NEAR(kalman.getPosition(), 5.0, 0.5);
    EXPECT_NEAR(kalman.getVelocity(), 1.0, 0.5);
}