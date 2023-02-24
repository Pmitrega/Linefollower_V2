#include "kalman_filter.h"

#include <stdio.h>
#include "main.h"
#define CONTROL_LEFT TIM11->CCR1 
#define CONTROL_RIGHT TIM10->CCR1
#define SOMESHIT_COEFFICIENT 40.f;
extern int velocity_left;
extern int velocity_right;
extern int global_control_left;
extern int global_control_right;
float A[2][2] = {{1,SAMPLING_TIME},{0,1}};
float H[1][2] = {{1,2}};
float Q[2][2] = {{0.01,0}, {0,1}};
float x[2][1]={{32000},{0}};
float x_p[2][1] = {{0},{0}};
float P[2][2] = {{0,0}, {0,0}};
float P_p[2][2] = {{0,0}, {0,0}};
float S;
float K[2][1] = {{0},{0}};
float R = 1;
float update_kalman_left(float x_measurement){
    //predict x_p
    x_p[0][0] = A[0][0] * x[0][0] + A[0][1]*x[1][0];
    x_p[1][0] = A[1][1] * x[1][0] + ((float)global_control_left*5.5 - (float)velocity_left) * SAMPLING_TIME * SOMESHIT_COEFFICIENT;
    //predict P_p
    P_p[0][0] = P[0][0] + 2*SAMPLING_TIME*P[0][1] + P[1][1]*SAMPLING_TIME*SAMPLING_TIME +Q[0][0];
    P_p[0][1] = P[0][1] + SAMPLING_TIME*P[1][1] + Q[0][1];
    P_p[1][0] = P[0][1] + SAMPLING_TIME*P[1][1] + Q[1][0];
    P_p[1][1] = P[1][1] + Q[1][1];
    //Calculate S
    S = P[0][0] + R;
    //Update K
    K[0][0] = P[0][0]/S;
    K[1][0] = P[1][0]/S;
    x[0][0] = x_p[0][0] + K[0][0]*(x_measurement - x_p[0][0]);
    x[1][0] = x_p[1][0] + K[1][0] *(x_measurement - x_p[0][0]);
    P[0][0] = P_p[0][0]  - K[0][0] * P_p[0][0];
    P[0][1] = P_p[0][1]  - K[0][0] * P_p[0][1];
    P[1][0] = P_p[1][0]  - K[1][0] * P_p[0][0];
    P[1][1] = P_p[1][1]  - K[1][0] * P_p[0][1];
    return x[1][0];
}


float A_r[2][2] = {{1,SAMPLING_TIME},{0,1}};
float H_r[1][2] = {{1,2}};
float Q_r[2][2] = {{0.01,0}, {0,1}};
float x_r[2][1]={{32000},{0}};
float x_p_r[2][1] = {{0},{0}};
float P_r[2][2] = {{0,0}, {0,0}};
float P_p_r[2][2] = {{0,0}, {0,0}};
float S_r;
float K_r[2][1] = {{0},{0}};
float R_r = 1;
float update_kalman_right(float x_measurement){
    //predict x_p
    x_p_r[0][0] = A_r[0][0] * x_r[0][0] + A_r[0][1]*x_r[1][0];
    x_p_r[1][0] = A_r[1][1] * x_r[1][0] + ((float)global_control_right*5.5 - (float)velocity_right) * SAMPLING_TIME * SOMESHIT_COEFFICIENT;
    //predict P_p
    P_p_r[0][0] = P_r[0][0] + 2*SAMPLING_TIME*P_r[0][1] + P_r[1][1]*SAMPLING_TIME*SAMPLING_TIME +Q_r[0][0];
    P_p_r[0][1] = P_r[0][1] + SAMPLING_TIME*P_r[1][1] + Q_r[0][1];
    P_p_r[1][0] = P_r[0][1] + SAMPLING_TIME*P_r[1][1] + Q_r[1][0];
    P_p_r[1][1] = P_r[1][1] + Q_r[1][1];
    //Calculate S
    S_r = P_r[0][0] + R_r;
    //Update K
    K_r[0][0] = P_r[0][0]/S_r;
    K_r[1][0] = P_r[1][0]/S_r;
    x_r[0][0] = x_p_r[0][0] + K_r[0][0]*(x_measurement - x_p_r[0][0]);
    x_r[1][0] = x_p_r[1][0] + K_r[1][0] *(x_measurement - x_p_r[0][0]);
    P_r[0][0] = P_p_r[0][0]  - K_r[0][0] * P_p_r[0][0];
    P_r[0][1] = P_p_r[0][1]  - K_r[0][0] * P_p_r[0][1];
    P_r[1][0] = P_p_r[1][0]  - K_r[1][0] * P_p_r[0][0];
    P_r[1][1] = P_p_r[1][1]  - K_r[1][0] * P_p_r[0][1];
    return x_r[1][0];
}