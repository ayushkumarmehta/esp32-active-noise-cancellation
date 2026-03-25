/*
 * LMS Adaptive Filter — Header
 * Author: Ayush Kumar
 */

#ifndef LMS_FILTER_H
#define LMS_FILTER_H

// ── Configuration ─────────────────────────
#define FILTER_ORDER   32       // Number of filter taps
#define MU             0.01f    // Step size (adaptation rate)
#define SAMPLE_RATE    16000    // Audio sample rate in Hz
#define BUFFER_SIZE    256      // Samples per processing block

// ── Function Declarations ──────────────────
void  lms_filter_init(void);
void  lms_filter_process(float *primary,
                          float *reference,
                          float *output,
                          int    length);
void  lms_filter_reset(void);

#endif // LMS_FILTER_H
