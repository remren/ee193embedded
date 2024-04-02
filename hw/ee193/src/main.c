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

#define WIFI_SSID      "KaReMi"
#define WIFI_PASS      "bingchillin"

#define BROKER_URI "mqtt://en1-pi.eecs.tufts.edu"

void app_main() {

    // // Enable Flash (aka non-volatile storage, NVS)
    // esp_err_t ret = nvs_flash_init();
    // if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    //   ESP_ERROR_CHECK(nvs_flash_erase());
    //   ret = nvs_flash_init();
    // }
    // ESP_ERROR_CHECK(ret);

    // // Normally we'd need to initialize the event loop and the network stack,
    // // but both of these will be done when we connect to WiFi.
    // printf("Connecting to WiFi...");
    // wifi_connect(WIFI_SSID, WIFI_PASS);

    // // Initialize the MQTT client
    // // Read the documentation for more information on what you can configure:
    // // https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/protocols/mqtt.html
    // esp_mqtt_client_config_t mqtt_cfg = {
    //     .broker.address.uri = BROKER_URI,
    // };
    // esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    // esp_mqtt_client_start(client);

    // printf("Sending MQTT message in 5 seconds...");
    // vTaskDelay(5000 / portTICK_PERIOD_MS);
   
    // // You'll want to call esp_mqtt_client_publish(client, ...) to send your message.
    // // See https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/protocols/mqtt.html#_CPPv423esp_mqtt_client_publish24esp_mqtt_client_handle_tPKcPKciii

    // printf("Done!\n");

    char* ic_topic = "rren02/hw5/ic_temp";
    char* thermistor_topic = "rren02/hw5/thermistor_temp";
    char* mqttdata = "( ͡° ͜ʖ ͡°)";


    // printf("Now... mqtt publish!");
    // esp_mqtt_client_publish(client, ic_topic, mqttdata, 0, 0, 0);
    // printf("Done!\n");

    thermistor_setup();
    float thermistor_kelvins;
    while(1){
        thermistor_kelvins = thermistor_delayed_read();
        printf("temp in C: %f\t", thermistor_kelvins - 273.15);
        printf("temp in F: %f\n", ((thermistor_kelvins - 273.15) * 9/5) + 32);
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