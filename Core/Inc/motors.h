#ifndef __MOTORS_H
#define __MOTORS_H
#include "main.h"
#define ENCODER_LEFT TIM3->CNT
#define ENCODER_RIGHT TIM4->CNT
/**
 * PID values
*/
#define LEFT_P 0.7
#define LEFT_I 0.2
#define LEFT_D 0


#define RIGHT_P 0.7
#define RIGHT_I 0.2
#define RIGHT_D 0

//Value to scale PV for feedforward
#define PWM_TO_VEL (1000/5500)

enum Motor{
    MOTOR_LEFT,
    MOTOR_RIGHT
};

enum Direction{
    FORWARD,
    BACKWARD
};
/**
  * @brief  Sets PWM on motor channel
  * @param  value PMW CCR, from 0 to 1000
  * @retval -1 if error value was to high else 0
  */
int set_PWM(enum Motor mot, uint16_t value);
/**
  * @brief  Sets motor direction
  * @retval -1 if error value was to high else 0
  */
int set_direction(enum Motor mot,enum Direction dir);
/**
  * @brief  Sets control from -1000 to 1000
*/
int set_control(enum Motor mot, int16_t value);

/**
  * @brief  updates global velocites.
*/
void update_velocity(int interrupt_time_frq);

void pid_global();
#endif