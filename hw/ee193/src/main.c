// Minimal example of using ESP-MQTT to publish messages to a broker
// Complete documentation is here:
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/protocols/mqtt.html
//
// See also the example code, which demonstrates how to receive messages:
// https://github.com/espressif/esp-idf/blob/5f4249357372f209fdd57288265741aaba21a2b1/examples/protocols/mqtt/tcp/main/app_main.c

#include "freertos/FreeRTOS.h"
#include "freertos/task.h" // Used for timer delay
#include "nvs_flash.h"
#include "esp_netif.h"
#include "mqtt_client.h"
#include "minimal_wifi.h"
#include "thermistor.h"
#include "esp_log.h"
#include "esp_mac.h"
#include <stdlib.h>
#include "simple_i2c.h"

#define WIFI_SSID      "Tufts_Wireless"
#define WIFI_PASS      ""

#define BROKER_URI "mqtt://en1-pi.eecs.tufts.edu"

static const char* TAG = "main";

// C:\Users\rren02\.platformio\packages\framework-espidf\examples\peripherals

void print_mac(const unsigned char *param_mac) {
    unsigned char *mac = param_mac;
	printf("%02X:%02X:%02X:%02X:%02X:%02X", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}

void app_main() {
    // unsigned char mac_base[6] = {0};
    // esp_efuse_mac_get_default(mac_base);
    // esp_read_mac(mac_base, ESP_MAC_WIFI_STA);
    // unsigned char mac_local_base[6] = {0};
    // unsigned char mac_uni_base[6] = {0};
    // esp_derive_local_mac(mac_local_base, mac_uni_base);
    // printf("Local Address: ");
    // print_mac(mac_local_base); 
    // printf("\nUni Address: ");
    // print_mac(mac_uni_base);
    // printf("\n\nMAC Address: ");
    // print_mac(mac_base);
    // printf("\n\n");

    // Enable Flash (aka non-volatile storage, NVS)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Normally we'd need to initialize the event loop and the network stack,
    // but both of these will be done when we connect to WiFi.
    printf("Connecting to WiFi...");
    wifi_connect(WIFI_SSID, WIFI_PASS);

    // Initialize the MQTT client
    // Read the documentation for more information on what you can configure:
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/protocols/mqtt.html
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = BROKER_URI,
    };
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

    printf("Sending MQTT message in 5 seconds...");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
   
    // You'll want to call esp_mqtt_client_publish(client, ...) to send your message.
    // See https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/protocols/mqtt.html#_CPPv423esp_mqtt_client_publish24esp_mqtt_client_handle_tPKcPKciii

    // printf("Done!\n");

    char* ic_topic = "rren02/hw5/ic_temp";
    char* thermistor_topic = "rren02/hw5/thermistor_temp";
    char* misc_topic = "rren02/hw5/misc";
    char* mqttdata = "( ͡° ͜ʖ ͡°)";


    // printf("Now try mqtt publish!");
    esp_mqtt_client_publish(client, misc_topic, "25", sizeof("25"), 0, 0);
    esp_mqtt_client_publish(client, thermistor_topic, "25", sizeof("25"), 0, 0);
    esp_mqtt_client_publish(client, ic_topic, "25", sizeof("25"), 0, 0);

    printf("Done!\n");

    ESP_LOGI(TAG, "Setting up ADC and thermistor...\n");
    thermistor_setup();
    ESP_LOGI(TAG, "Done!\n");
    ESP_LOGI(TAG, "Setting up I2C for PCT2075...\n");
    i2c_master_init();
    ESP_LOGI(TAG, "Done!\n");
    float thermistor_kelvins;
    uint8_t ic_data[2];
    memset(ic_data, 0,  2); // set data to 0s
    int16_t ic_celcius;
    uint8_t ic_msbit = 0;
    float ic_celcius_adjusted;
    while(1)
    {
        thermistor_kelvins = thermistor_delayed_read();
        int len = snprintf(NULL, 0, "%f", thermistor_kelvins);
        char* thermistor_celcius = malloc(len + 1);
        snprintf(thermistor_celcius, len + 1, "%f", thermistor_kelvins - 273.15);

        esp_mqtt_client_publish(client, thermistor_topic, thermistor_celcius, sizeof(thermistor_celcius), 0, 0);
        
        ESP_LOGI(TAG, "for thermistor -> temp in C: %f, temp in F: %f\n", thermistor_kelvins - 273.15, ((thermistor_kelvins - 273.15) * 9/5) + 32);

        pct2075_register_read(0x00, ic_data, 2);
        // https://www.nxp.com/docs/en/data-sheet/PCT2075.pdf
        // See Table 11, only the most significant 11 bits (MSByte and 3 bits from LSByte) matter.
        // Example (two's complement): +25 C = 0x0C8 = 0b000 1100 1000 = 0d200
        ic_msbit = (ic_data[1] >> 7); // Find the MSbit out of the 11 MSbits
        ic_celcius = ((uint16_t) ic_data[0] << 8); // Shift the MSByte into the correct spot
        ic_celcius += ((uint16_t) ic_data[1]); // Append the LSByte into correct position
        uint16_t preshift = ic_celcius; // DEBUG
        ic_celcius = (ic_celcius >> 5); // We only desire the 11 MSbits, so shift accordingly

        ic_celcius_adjusted = (ic_celcius * 1.0) * 0.125; // See 7.4.3 of PCT2075 data sheet for value to Celcius conversion

        ESP_LOGI(TAG, "ic_data: [0x%02hX, 0x%02hX], ic_msbit: 0x%hX, preshift: 0x%04hX, ic_celcius: 0x%04hX\nIC TEMP IN C: %f", ic_data[0], ic_data[1], ic_msbit, preshift, ic_celcius, ic_celcius_adjusted);

        int ic_len = snprintf(NULL, 0, "%f", ic_celcius_adjusted);
        char* ic_string = malloc(len + 1);
        snprintf(ic_string, len + 1, "%f", ic_celcius_adjusted);

        esp_mqtt_client_publish(client, ic_topic, ic_string, sizeof(ic_string), 0, 0);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

        printf("all send done!\n");

        vTaskDelay(1800 * 1000 / portTICK_PERIOD_MS); // 30 min delay
    }

}
// main at: 0x40137a
// AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDDEEEEEEEE
// AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDDEEEEEES
// AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDDEEEEEE0
//      0x|4 0|1 3|7 a
// char:    @ | BAD BAD USE OTHER MEANS
// \x40\x13\x7a
// printf "AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDDEEEEEEFFFFFFFF0\x40\x13\x7a"

// AAAA
// AAAA
// BBBB
// BBBB
// CCCC
// CCCC
// DDDD
// DDDD
// EEEE
// EEEE
// FFFF
// FFFF
// GGGG
// GGGG
// HHHH
// HHHH
// IIII
// IIII
// JJJJ
// JJJJ
// KKKK
// KKKK
// LLLL
// LLLL
// MMMM
// MMMM
// NNNN
// NNNN