#include "motors.h"
#include "string.h"
#include "stdio.h"
#include "main.h"

int velocity_left;
int velocity_right;
int desired_left = 0;
int desired_right = 0;
int set_PWM(enum Motor mot, uint16_t value){
    if(value>1000){
        return -1;
    }
    if(mot == MOTOR_LEFT){
        TIM11->CCR1 = value;
    }
    else if (mot == MOTOR_RIGHT)
    {
        TIM10->CCR1 = value;
    }
    return 0;
}

int set_direction(enum Motor mot,enum Direction dir){

    if(mot == MOTOR_LEFT){
        if(dir == BACKWARD){
            HAL_GPIO_WritePin(A_IN1_GPIO_Port, A_IN1_Pin, 0);
            HAL_GPIO_WritePin(A_IN2_GPIO_Port, A_IN2_Pin, 1);
        }
        else if(dir == FORWARD){
            HAL_GPIO_WritePin(A_IN1_GPIO_Port, A_IN1_Pin, 1);
            HAL_GPIO_WritePin(A_IN2_GPIO_Port, A_IN2_Pin, 0);
        }
    }
    else if(mot == MOTOR_RIGHT){
        if(dir == BACKWARD){
            HAL_GPIO_WritePin(B_IN1_GPIO_Port, B_IN1_Pin,0);
            HAL_GPIO_WritePin(B_IN2_GPIO_Port, B_IN2_Pin,1);
        }
        else if(dir == FORWARD){
            HAL_GPIO_WritePin(B_IN1_GPIO_Port, B_IN1_Pin,1);
            HAL_GPIO_WritePin(B_IN2_GPIO_Port, B_IN2_Pin,0);
        }
    }
    return 0;
};

int set_control(enum Motor mot, int16_t value){
    //SATURATION
    if(value > 1000)
        value = 1000;
    if(value < -1000)
        value = -1000;

    if (value < 0)
        set_direction(mot, BACKWARD);
    else
        set_direction(mot, FORWARD);
    if(value < 0)
        value = -value;
    
    set_PWM(mot, value);

};

void update_velocity(int interrupt_frq){
    static int last_left = 32000;
    static int last_right = 32000;
    velocity_left = (ENCODER_LEFT - last_left);
    if(velocity_left < - 10000){
        velocity_left += 65535;
    }
    if(velocity_left > 10000){
        velocity_left -= 65535;
    }
    velocity_right = (ENCODER_RIGHT - last_right);
    if(velocity_right < - 10000){
        velocity_right += 65535;
    }
    if(velocity_right > 10000){
        velocity_right -= 65535;
    }
    last_left = ENCODER_LEFT;
    last_right = ENCODER_RIGHT;
}

void pid_left(){
    static float integral = 0;
    static float last_error = 0;
    float error = (float)desired_left - (float)velocity_left;
    integral +=error;
    if(integral > 300){
        integral = 300;
    }
    else if (integral < -300)
    {
        integral = -300;
    }
    float control_value = LEFT_P*error + PWM_TO_VEL*desired_left+ LEFT_I*integral + (error-last_error)*LEFT_D;
    last_error = error;
    set_control(MOTOR_LEFT, (int)control_value);
}

void pid_right(){
    static float integral = 0;
    static float last_error = 0;
    float error = (float)desired_right - (float)velocity_right;
    integral +=error;
    if(integral > 300){
        integral = 300;
    }
    else if (integral < -300)
    {
        integral = -300;
    }
    float control_value = RIGHT_P*error+ PWM_TO_VEL*desired_right + RIGHT_I*integral + (error-last_error)*RIGHT_D;
    last_error = error;
    set_control(MOTOR_RIGHT, (int)control_value);
}

void pid_global(){
    pid_left();
    pid_right();
}