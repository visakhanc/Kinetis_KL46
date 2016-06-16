This project sses Kinetis SDK v2.0 for KL46Z, which is heavily modified from SDK v1.3.
Notable difference from SDK v1.3
1. No Platform libraries to build. All the available drivers are copied to project folder.
2. Simplified driver source. No seperate HAL and Driver abstraction.
3. RTOS abstraction layer is removed. Need to use RTOS API itself. Whole RTOS source is also copied to project.

This is the original RemoteGPS project adapted for SDK v2.0
RTOS is changed from uC-OSIII to FreeRTOS (to checkout that RTOS!)



