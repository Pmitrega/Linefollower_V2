#include "fsm_handler.h"
#include "sensors.h"
enum STATE current_state = STARTUP;
extern UART_HandleTypeDef huart1;
extern uint16_t sensor_readings[10];
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
        update_black_values(sensor_readings);
        get_black_values();
        break;
    case 'w':
        update_white_values(sensor_readings);
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

}
void manual_control_handler(uint8_t command, int number){

}
void auto_control_handler(uint8_t command, int number){
    if(command == 'm'){
        current_state = STATE_SELECTOR;
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