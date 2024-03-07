// Minimal code to initialize and read a value from the ADC
// Based on Espressif example: 
// https://github.com/espressif/esp-idf/blob/f68c131e5603feca21659e92ad85f0c3369692fe/examples/peripherals/adc/oneshot_read/main/oneshot_read_main.c
// Steven Bell <sbell@ece.tufts.edu>

#include "thermistor.h"
#include "esp_log.h"

/* Pick your ADC channel here.  Channels 0-4 correspond to GPIO 0-4, and are
 * on ADC 1. ADC 2 doesn't work on ESP32-C3 due to a silicon bug, so GPIO 5
 * isn't available. */
#define ADC_CHANNEL ADC_CHANNEL_0

adc_oneshot_unit_handle_t adc1_handle;
static const char* TAG = "Thermistor";

void thermistor_setup() {
    // Configure the ADC
    adc_oneshot_unit_init_cfg_t adc1_init_cfg = {
        .unit_id = ADC_UNIT_1
    };
    adc_oneshot_new_unit(&adc1_init_cfg, &adc1_handle);


    // Configure the channel within the ADC
    adc_oneshot_chan_cfg_t adc1_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT, // Default is 12 bits (max)
        .atten = ADC_ATTEN_DB_11
    };

    adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL, &adc1_cfg);

    // Skip calibration setup for now
}

// Requires a delay after. Any read from the ADC requires moving the watchdog.
float thermistor_delayed_read() {
    // Sample the ADC and save the result
    int adc_raw;
    adc_oneshot_read(adc1_handle, ADC_CHANNEL, &adc_raw);

    // Calibration process ideas: https://halvorsen.blog/documents/technology/iot/pico/pico_thermisor.php
    // Could also be: https://www.jameco.com/Jameco/workshop/TechTip/temperature-measurement-ntc-thermistors.html
    // https://github.com/jjsch-dev/esp32-thermistor/blob/master/components/esp32-thermistor/thermistor.c

    float v_in = 5.0;
    float resistor_ref = 10000.0; // 10k resistor
    float T0 = 25.0;
    float beta = 3380;

    float v_out = adc_raw * 5.00 / 4095.00; // https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/api-reference/peripherals/adc.html

    // Get Resistance of Thermistor
    float resistor_th = resistor_ref * (v_in / v_out - 1);
    float denominator = 1 / T0 + (1 / beta) * log(resistor_th / resistor_ref); // = 1/T0 + 1/betavalue * ln(R/Ro) ... credit to Tom idk why my math was so messed up

    // Steinhart-Hart Equation
    float temp_k = 1 / denominator + 273.15;

    ESP_LOGI(TAG, "adc_raw: %i, v_out: %f, resistor_th: %f, Kelvin: %f", adc_raw, v_out, resistor_th, temp_k);
    return temp_k;
}