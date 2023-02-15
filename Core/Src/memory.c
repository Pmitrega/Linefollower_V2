#include "memory.h"
#include "main.h"
extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart1;
uint8_t message_buffer[30];
uint8_t startup_counter[2];
uint16_t startups;
void update_counter(){
    if(HAL_I2C_Mem_Read(&hi2c2,MEM_DEV_ADDR, MEM_STARTUP_ADDR, 1, startup_counter, 2, 100) != HAL_OK){
        HAL_UART_Transmit(&huart1, "MEM ERROR\n", 11, 1000);
    }
    else{
        startups = (uint16_t)(startup_counter[0] << 8) + (uint16_t)startup_counter[1];
        int l = sprintf(message_buffer, "No of resets: %d\n", (int)startups);
        HAL_UART_Transmit(&huart1, message_buffer, l, 1000);
        startups +=1;
        startup_counter[0] = startups >> 8;
        startup_counter[1] = (startups << 8) >> 8;
        if(HAL_I2C_Mem_Write(&hi2c2, MEM_DEV_ADDR, MEM_STARTUP_ADDR, 1, startup_counter, 2, 1000)!= HAL_OK){
            HAL_UART_Transmit(&huart1, "MEM ERROR\n", 11, 1000);
        }
    }

}