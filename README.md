<<<<<<< HEAD
# Sensor Fusion using Kalman Filter and Least Squares Fit

This project demonstrates a simple embedded-style signal processing pipeline in C++14.

## Features

- 2-state Kalman filter for position and velocity estimation
- Least Squares line fitting for trend estimation
- Noisy sensor simulation
- Unit tests using GoogleTest
- CMake-based build system

## Project Structure

- `include/` → headers
- `src/` → implementation
- `tests/` → unit tests

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
=======
# Embedded-sensor-fusion-demo
Embedded C++ sensor fusion demo implementing Kalman filtering and least-squares estimation with unit testing and CMake-based build system.


# Embedded Sensor Fusion Demo (C++)

This project demonstrates a clean, modular implementation of a **sensor fusion pipeline** using:

* **Kalman Filter (2-state: position + velocity)**
* **Least Squares Line Fit (trend estimation)**
* **Noisy signal simulation (Gaussian noise)**

---

In embedded systems (especially automotive and robotics), raw sensor data is often noisy and unreliable.

This project demonstrates how to:

* Filter noisy measurements using a **Kalman filter**
* Extract system trends using **least-squares estimation**
* Structure estimation algorithms in a **clean, testable C++ design**

This is directly applicable to:

* Battery Management Systems (BMS)
* Radar / sensor signal processing
* Embedded control systems
* Real-time estimation problems

---

## System Overview

The system simulates a moving object with constant velocity:

* True signal → ideal motion
* Measured signal → noisy sensor data
* Kalman filter → real-time estimation
* Least squares → global trend estimation

---

## Architecture

```
SignalGenerator  →  Kalman2State  →  Output
        ↓
   Raw Measurements → LeastSquaresFit
```

### Modules

* `SignalGenerator`

  * Simulates noisy sensor measurements using Gaussian noise

* `Kalman2State`

  * 2-state Kalman filter:

    * Position
    * Velocity
  * Predict + Update cycle

* `LeastSquaresFit`

  * Computes linear trend:

    * slope (rate)
    * intercept

---

## Build Instructions

### Requirements

* Linux / WSL
* CMake ≥ 3.14
* GCC / Clang

### Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Run Demo

```bash
./sensor_fusion_demo
```

Example output:

```
Step    True    Measured    KalmanPos   KalmanVel
1       1.20    0.75        0.75        0.00
2       2.40    2.81        2.31        0.77
...
```

---

## Results

* Kalman filter smooths noisy measurements
* Velocity estimate converges to true value
* Least squares approximates global trend:

```
y = 1.19 * t - 0.07
```

(Actual velocity ≈ 1.2)

---

## Unit Testing

Tests are implemented using **GoogleTest**.

Run:

```bash
ctest --output-on-failure
```

Test coverage includes:

* Least squares correctness
* Kalman initialization
* Kalman convergence behavior

---

## Tech Stack

* C++14
* CMake
* GoogleTest
* Linux / WSL

## Future Improvements //TODO

* CSV logging + Python visualization
* Fixed-point Kalman filter (embedded optimization)
* Real sensor integration (I2C / SPI)
* RTOS-based version (FreeRTOS)
* CAN-based distributed estimation

---


>>>>>>> 951462b57063869f01c7741b33bfec4656ad6f2d
