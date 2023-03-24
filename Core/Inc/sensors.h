#ifndef __SENSORS
#define __SENSOR
#define MAX_ANGLE 24.f
#define LINE_THRE 80
#define ALPHA_FACT 0.25f
#include "main.h"
void update_white_values(uint16_t* values);
void update_black_values(uint16_t* values);
void get_black_values();
void get_white_values();
float estimate_angle();
void save_to_eeprom();
void read_from_eeprom();
#endif