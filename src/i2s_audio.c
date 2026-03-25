/*
 * I2S Audio Driver — Implementation
 * Author: Ayush Kumar
 */

#include "i2s_audio.h"
#include "driver/i2s.h"
#include <string.h>

#define I2S_PORT_MIC    I2S_NUM_0   // Microphone port
#define I2S_PORT_SPK    I2S_NUM_1   // Speaker port

// ── Initialize I2S for mic input & speaker output ──
void i2s_init(void) {

    // Microphone I2S config
    i2s_config_t mic_config = {
        .mode                 = I2S_MODE_MASTER | I2S_MODE_RX,
        .sample_rate          = SAMPLE_RATE,
        .bits_per_sample      = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count        = 4,
        .dma_buf_len          = BUFFER_SIZE,
        .use_apll             = false,
    };

    i2s_pin_config_t mic_pins = {
        .bck_io_num   = I2S_SCK_PIN,
        .ws_io_num    = I2S_WS_PIN,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num  = I2S_SD_MIC1,
    };

    i2s_driver_install(I2S_PORT_MIC, &mic_config, 0, NULL);
    i2s_set_pin(I2S_PORT_MIC, &mic_pins);

    // Speaker I2S config
    i2s_config_t spk_config = {
        .mode                 = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate          = SAMPLE_RATE,
        .bits_per_sample      = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format       = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count        = 4,
        .dma_buf_len          = BUFFER_SIZE,
        .use_apll             = false,
    };

    i2s_pin_config_t spk_pins = {
        .bck_io_num   = I2S_SCK_PIN,
        .ws_io_num    = I2S_WS_PIN,
        .data_out_num = I2S_SD_OUT,
        .data_in_num  = I2S_PIN_NO_CHANGE,
    };

    i2s_driver_install(I2S_PORT_SPK, &spk_config, 0, NULL);
    i2s_set_pin(I2S_PORT_SPK, &spk_pins);
}

// ── Read primary microphone (speech + noise) ──
void i2s_read_primary(float *buffer, int length) {
    int32_t raw[BUFFER_SIZE];
    size_t bytes_read = 0;
    i2s_read(I2S_PORT_MIC, raw, length * sizeof(int32_t), &bytes_read, portMAX_DELAY);
    for (int i = 0; i < length; i++) {
        buffer[i] = (float)(raw[i] >> 14) / 131072.0f;  // Normalize to -1.0 to 1.0
    }
}

// ── Read reference microphone (noise only) ──
void i2s_read_reference(float *buffer, int length) {
    int32_t raw[BUFFER_SIZE];
    size_t bytes_read = 0;
    i2s_read(I2S_PORT_MIC, raw, length * sizeof(int32_t), &bytes_read, portMAX_DELAY);
    for (int i = 0; i < length; i++) {
        buffer[i] = (float)(raw[i] & 0x3FFF) / 131072.0f;  // Right channel
    }
}

// ── Write clean audio to speaker ──────────
void i2s_write_output(float *buffer, int length) {
    int32_t raw[BUFFER_SIZE];
    size_t bytes_written = 0;
    for (int i = 0; i < length; i++) {
        raw[i] = (int32_t)(buffer[i] * 131072.0f) << 14;
    }
    i2s_write(I2S_PORT_SPK, raw, length * sizeof(int32_t), &bytes_written, portMAX_DELAY);
}

// ── Deinitialize I2S ───────────────────────
void i2s_deinit(void) {
    i2s_driver_uninstall(I2S_PORT_MIC);
    i2s_driver_uninstall(I2S_PORT_SPK);
}
Add i2s_audio.c - I2S driver for dual mic input and speaker output
