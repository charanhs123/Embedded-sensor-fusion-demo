# FreeRTOS-oriented Version

This folder contains an RTOS-style variant of the sensor fusion application.

## Goal

Demonstrate how the estimation pipeline can be organized into real-time tasks:

- SensorTask
- EstimationTask
- DiagnosticsTask

## Current State

The main CMake build on Linux/WSL compiles a **stub version** that mimics task separation while remaining desktop-buildable.

A real embedded port would replace the stub with:

- actual FreeRTOS kernel sources
- board-specific startup code
- FreeRTOS port layer
- UART/ITM/SEGGER logging or equivalent diagnostics transport

## Suggested Embedded Target

- STM32 + FreeRTOS
- ESP32 + FreeRTOS
- Xilinx/SoC environment with RTOS support