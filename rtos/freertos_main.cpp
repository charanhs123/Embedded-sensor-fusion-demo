#include <cstdio>
#include <vector>

#include "Kalman2State.hpp"
#include "LeastSquaresFit.hpp"
#include "SignalGenerator.hpp"

#if defined(FREERTOS_STUB_BUILD)

// Stub build for desktop compilation.
// This keeps the project buildable on WSL while showing RTOS-oriented structure.

namespace
{
struct SharedData
{
    double latest_time = 0.0;
    double latest_true_position = 0.0;
    double latest_measurement = 0.0;
    double latest_kalman_position = 0.0;
    double latest_kalman_velocity = 0.0;
    bool new_sample_available = false;
};

SharedData g_data;

void SensorTask()
{
    static const double dt = 1.0;
    static SignalGenerator signal(0.0, 1.2, 0.8, 42U);
    static int step = 0;

    ++step;
    g_data.latest_time = step * dt;
    g_data.latest_measurement = signal.step(dt);
    g_data.latest_true_position = signal.getTruePosition();
    g_data.new_sample_available = true;
}

void EstimationTask()
{
    static Kalman2State kalman(1.0, 0.01, 0.01, 0.64);

    if (!g_data.new_sample_available)
    {
        return;
    }

    kalman.predict();
    kalman.update(g_data.latest_measurement);

    g_data.latest_kalman_position = kalman.getPosition();
    g_data.latest_kalman_velocity = kalman.getVelocity();
}

void DiagnosticsTask()
{
    static std::vector<double> time_values;
    static std::vector<double> measured_values;

    if (!g_data.new_sample_available)
    {
        return;
    }

    std::printf("RTOS Step | t=%.2f true=%.4f measured=%.4f est_pos=%.4f est_vel=%.4f\n",
                g_data.latest_time,
                g_data.latest_true_position,
                g_data.latest_measurement,
                g_data.latest_kalman_position,
                g_data.latest_kalman_velocity);

    time_values.push_back(g_data.latest_time);
    measured_values.push_back(g_data.latest_measurement);

    if (time_values.size() >= 10U)
    {
        const LineFitResult fit = LeastSquaresFit::fitLine(time_values, measured_values);
        if (fit.valid)
        {
            std::printf("RTOS LS Fit | y = %.4f * t + %.4f\n", fit.slope, fit.intercept);
        }

        time_values.clear();
        measured_values.clear();
    }

    g_data.new_sample_available = false;
}
}

int main()
{
    std::puts("FreeRTOS-style estimator stub build");
    std::puts("This demonstrates task separation for a future embedded FreeRTOS port.\n");

    for (int i = 0; i < 20; ++i)
    {
        SensorTask();
        EstimationTask();
        DiagnosticsTask();
    }

    return 0;
}

#else

// Real FreeRTOS version skeleton.
// To use this, replace the stub build with actual FreeRTOS integration.

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

struct SensorSample
{
    double time;
    double true_position;
    double measurement;
};

struct EstimateSample
{
    double time;
    double true_position;
    double measurement;
    double kalman_position;
    double kalman_velocity;
};

static QueueHandle_t g_sensor_queue = nullptr;
static QueueHandle_t g_estimate_queue = nullptr;

void SensorTask(void* /*params*/)
{
    SignalGenerator signal(0.0, 1.2, 0.8, 42U);
    const double dt = 1.0;
    int step = 0;

    while (true)
    {
        ++step;

        SensorSample sample;
        sample.time = step * dt;
        sample.measurement = signal.step(dt);
        sample.true_position = signal.getTruePosition();

        xQueueSend(g_sensor_queue, &sample, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void EstimationTask(void* /*params*/)
{
    Kalman2State kalman(1.0, 0.01, 0.01, 0.64);
    SensorSample sensor_sample;

    while (true)
    {
        if (xQueueReceive(g_sensor_queue, &sensor_sample, portMAX_DELAY) == pdPASS)
        {
            kalman.predict();
            kalman.update(sensor_sample.measurement);

            EstimateSample est;
            est.time = sensor_sample.time;
            est.true_position = sensor_sample.true_position;
            est.measurement = sensor_sample.measurement;
            est.kalman_position = kalman.getPosition();
            est.kalman_velocity = kalman.getVelocity();

            xQueueSend(g_estimate_queue, &est, portMAX_DELAY);
        }
    }
}

void DiagnosticsTask(void* /*params*/)
{
    EstimateSample est;

    while (true)
    {
        if (xQueueReceive(g_estimate_queue, &est, portMAX_DELAY) == pdPASS)
        {
            std::printf("t=%.2f true=%.3f meas=%.3f est=%.3f vel=%.3f\n",
                        est.time,
                        est.true_position,
                        est.measurement,
                        est.kalman_position,
                        est.kalman_velocity);
        }
    }
}

int main()
{
    g_sensor_queue = xQueueCreate(8, sizeof(SensorSample));
    g_estimate_queue = xQueueCreate(8, sizeof(EstimateSample));

    xTaskCreate(SensorTask, "SensorTask", 1024, nullptr, 2, nullptr);
    xTaskCreate(EstimationTask, "EstimationTask", 1024, nullptr, 2, nullptr);
    xTaskCreate(DiagnosticsTask, "DiagnosticsTask", 1024, nullptr, 1, nullptr);

    vTaskStartScheduler();

    while (true)
    {
    }
}

#endif