/*
 * I2S Audio Driver — Header
 * Author: Ayush Kumar
 */

#ifndef I2S_AUDIO_H
#define I2S_AUDIO_H

#include "lms_filter.h"

// ── I2S Pin Definitions ────────────────────
#define I2S_SCK_PIN     14    // Bit clock
#define I2S_WS_PIN      15    // Word select (L/R)
#define I2S_SD_MIC1     32    // Primary mic data
#define I2S_SD_MIC2     33    // Reference mic data
#define I2S_SD_OUT      25    // Speaker output

// ── Function Declarations ──────────────────
void i2s_init(void);
void i2s_read_primary(float *buffer, int length);
void i2s_read_reference(float *buffer, int length);
void i2s_write_output(float *buffer, int length);
void i2s_deinit(void);

#endif // I2S_AUDIO_H
