#ifndef THERMISTOR_H
#define THERMISTOR_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h" // Used for timer delay
#include "esp_adc/adc_oneshot.h"
#include <math.h> // Used in Steinhart-Hart Equation, logarithm.

void thermistor_setup();
float thermistor_delayed_read();

#endif