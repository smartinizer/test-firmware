# base-firmware
Test-firmware for ESP32 which implements a test-usecase

Firmware is based on base firmware, but additionaly listens on mqtt messages and makes gpio output.
Every 10 seconds a alive message is published.