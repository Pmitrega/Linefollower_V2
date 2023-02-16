#ifndef __FSM_HANDLER
#define __FSM_HANDLER
#include "main.h"
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
void all_handler(uint8_t command, int number);
#endif