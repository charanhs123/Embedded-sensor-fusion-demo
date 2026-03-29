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