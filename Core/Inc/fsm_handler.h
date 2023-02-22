#ifndef __FSM_HANDLER
#define __FSM_HANDLER
#include "main.h"
/**
 * @brief Contains functions to control robot as Finite State Machine.  
*/
enum STATE{
    STARTUP,
    SENSOR_AUTO_UPDATE,
    SENSOR_MANUAL_UPDATE,
    MANUAL_CONTROL,
    AUTO_CONTROL,
    STATE_SELECTOR
};


void startup_handler(uint8_t command, int number);
void sensor_auto_update_handler(uint8_t command, int number);
void sensor_manual_update_handler(uint8_t command, int number);
void manual_control_handler(uint8_t command, int number);
void auto_control_handler(uint8_t command, int number);
void state_selector_handler(uint8_t command, int number);

/**
 * @fn all_handler
 * function that calls desired handler, dependent on current state.  
*/
void all_handler(uint8_t command, int number);
#endif