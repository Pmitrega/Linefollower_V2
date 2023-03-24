#include "sensors.h"
#include "stdio.h"
#include "memory.h"
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
uint16_t sensor_readings[10];
uint16_t sensor_readings_filt[10];
uint16_t sensor_black_values[10];
uint16_t sensor_white_values[10];
uint8_t active_sens[10];
uint8_t uart_buffer[100];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    static uint64_t i = 0;
    if(i == 0){
        for(int k=0;k<10;k++){
            sensor_readings_filt[k] = sensor_readings[k];
        }
        i++;
    }
    else{
    for(int k=0;k<10;k++){
            sensor_readings_filt[k] = (uint16_t)((float)sensor_readings[k]*ALPHA_FACT + (1.f - ALPHA_FACT)*(float)sensor_readings_filt[k]);//
            // //faster version for alpha = 1/4
            // sensor_readings_filt[k] = (uint16_t)((sensor_readings[k]/4) + (sensor_readings_filt[k]*3)/4);
        }
    }
    i++;
}
void get_black_values(){
    int l = sprintf(uart_buffer, "%d %d %d %d %d %d %d %d %d %d\n", sensor_black_values[0], sensor_black_values[1], sensor_black_values[2], sensor_black_values[3],sensor_black_values[4], sensor_black_values[5], sensor_black_values[6], sensor_black_values[7], sensor_black_values[8], sensor_black_values[9]);
    HAL_UART_Transmit_IT(&huart1, uart_buffer, l);
}
void get_white_values(){
    int l = sprintf(uart_buffer, "%d %d %d %d %d %d %d %d %d %d\n", sensor_white_values[0], sensor_white_values[1], sensor_white_values[2], sensor_white_values[3],sensor_white_values[4], sensor_white_values[5], sensor_white_values[6], sensor_white_values[7], sensor_white_values[8], sensor_white_values[9]);
    HAL_UART_Transmit_IT(&huart1, uart_buffer, l);
}

void update_white_values(uint16_t* values){
    for(int i = 0; i<10; i++){
        sensor_white_values[i] = values[i];
    }
}
void update_black_values(uint16_t* values){
    for(int i = 0; i<10; i++){
        sensor_black_values[i] = values[i];
    }
}

float estimate_angle(){
    static float angle_st = 0;
    float angle_temp = 0;
    int no_detections = 0;
    for(int i = 0; i<10;i++){
        if(sensor_readings_filt[i] > (sensor_white_values[i] + LINE_THRE)){
            angle_temp += ((float)i-5.f) * (MAX_ANGLE/5.f);
            active_sens[i] = 1;
            no_detections += 1;
        }
        else{
            active_sens[i] = 0;
        }
    }
    if(no_detections !=0)
        angle_st = angle_temp/(float)no_detections;
    return angle_st;
}
void save_to_eeprom(){
    for(int i = 0; i<10; i++){
        write_uint16(WHITE_VALUES_ADDR + (uint8_t)(2*i), sensor_white_values[i]);
        for(int i =0; i<200000; i++){}//blocking for write to keep up
        write_uint16(BLACK_VALUES_ADDR + (uint8_t)(2*i), sensor_black_values[i]);
        for(int i =0; i<200000; i++){}//blocking for write to keep up
    }
}

void read_from_eeprom(){
    for(int i = 0; i<10; i++){
        sensor_white_values[i] = read_uint16(WHITE_VALUES_ADDR + 2*i);
        sensor_black_values[i] = read_uint16(BLACK_VALUES_ADDR + 2*i);
    }
}