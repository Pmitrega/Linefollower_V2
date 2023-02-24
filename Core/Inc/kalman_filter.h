#ifndef __KALMAN_FILTER
#define __KALMAN_FILTER
#define SAMPLING_TIME 0.001f
float update_kalman_left(float x_measurement);
float update_kalman_right(float x_measurement);
#endif