#ifndef __SENSORS
#define __SENSOR
#include "main.h"
void update_white_values(uint16_t* values);
void update_black_values(uint16_t* values);
void get_black_values();
void get_white_values();
void save_to_eeprom();
void read_from_eeprom();
#endif