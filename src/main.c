/*
 * Active Noise Cancellation System
 * Platform : ESP32 (NodeMCU-32s)
 * Author   : Ayush Kumar
 * Date     : 2025
 */

#include "i2s_audio.h"
#include "lms_filter.h"

void app_main(void) {
    // Initialize I2S for dual microphone input
    i2s_init();

    // Initialize LMS adaptive filter
    lms_filter_init();

    while (1) {
        // Read primary mic (speech + noise)
        float primary[BUFFER_SIZE];
        i2s_read_primary(primary, BUFFER_SIZE);

        // Read reference mic (noise only)
        float reference[BUFFER_SIZE];
        i2s_read_reference(reference, BUFFER_SIZE);

        // Apply LMS filter — output is clean speech
        float output[BUFFER_SIZE];
        lms_filter_process(primary, reference, output, BUFFER_SIZE);

        // Play clean audio output
        i2s_write_output(output, BUFFER_SIZE);
    }
}
