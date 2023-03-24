#include "fsm_handler.h"
#include "sensors.h"
enum STATE current_state = STARTUP;
extern UART_HandleTypeDef huart1;
extern uint16_t sensor_readings[10];
extern uint16_t sensor_readings_filt[10];
extern uint16_t sensor_black_values[10];
extern uint16_t sensor_white_values[10];
extern int desired_left;
extern int desired_right;
void startup_handler(uint8_t command, int number){
    switch (command)
    {
    case 'm':
        current_state = STATE_SELECTOR;
        state_selector_handler(0,0);
        break;
    case 'b':
        get_black_values();
        break;
    case 'w':
        get_white_values();
        break;
    case 'r':
        read_from_eeprom();
        break;
    default:
        HAL_UART_Transmit_IT(&huart1, "STARTUP_MODE\nm - STATE_SELECTOR\nb - get black values\nw - get white values\nr - read from eeprom\n", 96);
        break;
    }
}
void sensor_auto_update_handler(uint8_t command, int number){
    switch (command)
    {
    case 'm':
        current_state = STATE_SELECTOR;
        state_selector_handler(0,0);
        break;
    case 'b':
        update_black_values(sensor_readings_filt);
        get_black_values();
        break;
    case 'w':
        update_white_values(sensor_readings_filt);
        get_white_values();
        break;
    case 's':
        save_to_eeprom();
        break;
    case 'x':
        get_black_values();
        break;
    case 'y':
        get_white_values();
        break;
    default:
        HAL_UART_Transmit_IT(&huart1, "STARTUP_MODE\nm - STATE_SELECTOR\nb - update black values\nw - update white values\ns - save to EEPROM\nx - get black values\ny - get white values\n", 142);
        break;
    }
}
void sensor_manual_update_handler(uint8_t command, int number){
    static char bw_flag = 'w';
    switch (command)
    {
    case 'm':
        current_state = STATE_SELECTOR;
        state_selector_handler(0,0);
        break;
    case 'a'...'j':
        if(bw_flag == 'w'){
            HAL_UART_Transmit_IT(&huart1, "setting white\n", 15);
            sensor_white_values[9-'j'+command ] = number;
        }
        if(bw_flag == 'b'){
            HAL_UART_Transmit_IT(&huart1, "setting black\n", 15);
            sensor_black_values[9-'j'+command] = number;
        }
        break;
    case 's':
        save_to_eeprom();
        break;
    case 'r':
        read_from_eeprom();
        break;
    case 'p':
        if(bw_flag == 'w')get_white_values();
        if(bw_flag == 'b')get_black_values();
        break;
    case 'w':
        bw_flag = 'w';
        HAL_UART_Transmit_IT(&huart1, "SETTING TO WHITE\n", 18);
        break;
    case 'x':
        bw_flag = 'b';
        HAL_UART_Transmit_IT(&huart1, "SETTING TO BLACK\n", 18);
        break;
    case 'y':
        if(bw_flag == 'w')HAL_UART_Transmit_IT(&huart1, "SET TO WHITE\n", 14);
        if(bw_flag == 'b')HAL_UART_Transmit_IT(&huart1, "SET TO BLACK\n", 14);
        break;
    default:
        HAL_UART_Transmit_IT(&huart1, "----SENSOR_MANUAL_UPDATE_MODE----\nm - STATE_SELECTOR\na-j + number - sets value to sensors\ns - saves all\nr - read_from_eeprom\np - print sensors values\ny - print chosen sensor values\nx,w - set to black or white\n", 210);
        break;
    }
}
void manual_control_handler(uint8_t command, int number){

    switch (command)
    {
    case 's':
        current_state = STATE_SELECTOR;
        desired_left = 0;
        desired_right = 0;
        state_selector_handler(0,0);
        break;
    case 'l':
        desired_left = number;
        break;
    case 'r':
        desired_right = number;
        break;
    default:
        HAL_UART_Transmit_IT(&huart1, "----MANUAL_MODE----\ns - STATE_SELECTOR\nl,r + number - sets left and right velocity\n", 84);
        break;
    }
    

}
void auto_control_handler(uint8_t command, int number){
    if(command == 'm'){
        current_state = STATE_SELECTOR;
        desired_left = 0;
        desired_right = 0;
        state_selector_handler(0,0);
    }

}

void state_selector_handler(uint8_t command, int number){
    switch (command)
    {
    case 's':
        current_state = STARTUP;
        startup_handler(0,0);
        break;
    case 'x':
        current_state = SENSOR_AUTO_UPDATE;
        sensor_auto_update_handler(0,0);
        break;
    case 'y':
        current_state = SENSOR_MANUAL_UPDATE;
        sensor_manual_update_handler(0,0);
        break;
    case 'm':
        current_state = MANUAL_CONTROL;
        manual_control_handler(0,0);
        break;
    case 'a':
        current_state = AUTO_CONTROL;
        auto_control_handler(0,0);
        break;
    default:
        HAL_UART_Transmit_IT(&huart1, "STATE SELECTOR MODE\ns - STARTUP\nx - SENSOR_AUTO_UPDATE\ny - SENSOR_MANUAL_UPDATE\nm - MANUAL_CONTROL\na - AUTO_CONTROL\n", 117);
        break;
    }

}
void all_handler(uint8_t command, int number){
    switch (current_state)
    {
    case STARTUP:
        startup_handler(command, number);
        break;
    case SENSOR_AUTO_UPDATE:
        sensor_auto_update_handler(command, number);
        break;
    case SENSOR_MANUAL_UPDATE:
        sensor_manual_update_handler(command, number);
        break;
    case MANUAL_CONTROL:
        manual_control_handler(command, number);
        break;
    case AUTO_CONTROL:
        auto_control_handler(command, number);
        break;
    case STATE_SELECTOR:
        state_selector_handler(command, number);
        break;
    default:
        break;
    }
}