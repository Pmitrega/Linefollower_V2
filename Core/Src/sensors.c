#include "sensors.h"
#include "stdio.h"
#include "memory.h"
extern UART_HandleTypeDef huart1;
uint16_t sensor_readings[10];
uint16_t sensor_black_values[10];
uint16_t sensor_white_values[10];
uint8_t uart_buffer[100];
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