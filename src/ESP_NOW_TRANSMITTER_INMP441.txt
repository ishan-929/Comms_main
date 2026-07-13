#include <Arduino.h>
#include <driver/i2s.h>
#include <esp_now.h>
#include <WIFI.h>

uint8_t broadcastAddress[] = {0xF4, 0x2D, 0xC9, 0x6B, 0x07, 0x68};

#define I2S_PORT I2S_NUM_0
const int ws = 19;
const int sd = 23;
const int sck = 18;

typedef struct struct_message {
    int32_t audioBuffer[60];
} struct_message;

struct_message data;

esp_now_peer_info_t peers;

void setup() {
    Serial.begin(115200);
    delay(1000);
    WiFi.mode(WIFI_STA);
    esp_now_init();
    memcpy(peers.peer_addr, broadcastAddress, 6);
    peers.channel = 0;
    peers.encrypt = false;
    esp_now_add_peer(&peers);

    i2s_config_t config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = (I2S_COMM_FORMAT_STAND_I2S),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
    };

    i2s_pin_config_t pins = {
        .bck_io_num = sck,
        .ws_io_num = ws,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = sd,
    };

    i2s_driver_install(I2S_PORT, &config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pins);
}

void loop() {
    size_t bytes = 0;
    i2s_read(I2S_PORT, &data.audioBuffer, 240, &bytes, portMAX_DELAY);
    if (bytes == 240) {
        esp_now_send(broadcastAddress, (uint8_t *) &data, sizeof(data));
    }

}




