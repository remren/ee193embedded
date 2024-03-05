// Minimal code to initialize and read a value from the ADC
// Based on Espressif example: 
// https://github.com/espressif/esp-idf/blob/f68c131e5603feca21659e92ad85f0c3369692fe/examples/peripherals/adc/oneshot_read/main/oneshot_read_main.c
// Steven Bell <sbell@ece.tufts.edu>

#include "thermistor.h"

/* Pick your ADC channel here.  Channels 0-4 correspond to GPIO 0-4, and are
 * on ADC 1. ADC 2 doesn't work on ESP32-C3 due to a silicon bug, so GPIO 5
 * isn't available. */
#define ADC_CHANNEL ADC_CHANNEL_0

adc_oneshot_unit_handle_t adc1_handle;

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

// float thermistor_delayed_read() {
//     // Sample the ADC and save the result
//     int adc_raw;
//     adc_oneshot_read(adc1_handle, ADC_CHANNEL, &adc_raw);

//     printf("ADC raw: %d\t", adc_raw);

//     // Calibration process using: https://halvorsen.blog/documents/technology/iot/pico/pico_thermisor.php
//     // Could also be: https://www.jameco.com/Jameco/workshop/TechTip/temperature-measurement-ntc-thermistors.html
//     float v_in = 5.0;
//     float resistor_out = 10000.0; // 10k resistor

//     // Steinhart Constants
//     float A = 0.001129148;
//     float B = 0.000234125;
//     float C = 0.0000000876741;

//     float v_out = adc_raw / 3380.0 * 5;

//     // Get Resistance of Thermistor
//     float resistor_th = (v_out * resistor_out) / (v_in - v_out);
//     // float resistor_th = 10000;
//     float natural_log_th = log(resistor_th);
//     float denominator = A + (B * natural_log_th) + (C * pow(natural_log_th, 3));

//     // Steinhart-Hart Equation
//     float temp_k = 1 / denominator;

//     printf("v_out: %f, resistor_th: %f, natural_log_th: %f, denominator: %f, ", v_out, resistor_th, natural_log_th, denominator);

//     printf("temperature in k: %f\n", temp_k);

//     // int Vo = adc_raw;
//     // float R1 = 10000;
//     // float R2 = R1 * ((65535) / (float) Vo);
//     // printf("R2: %f,\t", R2);
//     // float logR2 = log(R2);
//     // float c1 = 0.001129148;
//     // float c2 = 0.000234125;
//     // float c3 = 0.0000000876741;
//     // printf("logR2: %f,\t", logR2);
//     // float T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
//     // // T = T - 273.15;
//     // // T = (T * 9.0)/ 5.0 + 32.0; 
//     // printf("temp in k: %f\t", T);

//     vTaskDelay(1000 / portTICK_PERIOD_MS);

//     return temp_k;

//     // If we had other things to do with the ADC, we could release it with
//     // adc_oneshot_del_unit(adc1_handle);
// }

float thermistor_delayed_read() {
    // Sample the ADC and save the result
    int adc_raw;
    // adc_oneshot_read(adc1_handle, ADC_CHANNEL, &adc_raw);

    // printf("ADC raw: %d\t", adc_raw);

    // Calibration process using: https://halvorsen.blog/documents/technology/iot/pico/pico_thermisor.php
    // Could also be: https://www.jameco.com/Jameco/workshop/TechTip/temperature-measurement-ntc-thermistors.html

    const float invBeta = 1.00 / 3380.00;   // Denom. is Beta value of Thermistor

    const float adcMax = 4095.00;  // ESP32 max adc value 4095
    const float invT0 = 1.00 / 298.15;   // room temp in Kelvin

    int adcVal = 5;
    float  K, C, F;

    int numSamples = 5;
    for (int i = 0; i < numSamples; i++)
   {
     adc_oneshot_read(adc1_handle, ADC_CHANNEL, &adc_raw);
     adcVal = adcVal + adc_raw;
     vTaskDelay(100 / portTICK_PERIOD_MS);
   }

    adcVal = adcVal/5;

      printf("ADC raw: %d\t", adcVal);
    K = 1.00 / (invT0 + invBeta*(log ( adcMax / (float) adcVal - 1.00)));
    C = K - 273.15;                      // convert to Celsius
    F = ((9.0*C)/5.00) + 32.00;   // convert to Fahrenheit

    printf("k: %f, c: %f, f: %f\n", K, C, F);

    return K;
    
}