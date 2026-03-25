/*
 * LMS Adaptive Filter — Implementation
 * Author: Ayush Kumar
 */

#include "lms_filter.h"
#include <string.h>
#include <math.h>

// Filter weight vector (coefficients)
static float weights[FILTER_ORDER];

// ── Initialize filter ──────────────────────
void lms_filter_init(void) {
    memset(weights, 0, sizeof(weights));
}

// ── Reset filter weights to zero ──────────
void lms_filter_reset(void) {
    memset(weights, 0, sizeof(weights));
}

// ── Core LMS Processing ────────────────────
// primary  = mic1 (speech + noise)
// reference = mic2 (noise only)
// output   = clean speech
void lms_filter_process(float *primary,
                         float *reference,
                         float *output,
                         int    length) {

    static float ref_buffer[FILTER_ORDER] = {0};

    for (int n = 0; n < length; n++) {

        // Shift reference buffer
        for (int i = FILTER_ORDER - 1; i > 0; i--) {
            ref_buffer[i] = ref_buffer[i - 1];
        }
        ref_buffer[0] = reference[n];

        // Estimate noise using current weights
        float noise_estimate = 0.0f;
        for (int i = 0; i < FILTER_ORDER; i++) {
            noise_estimate += weights[i] * ref_buffer[i];
        }

        // Error = clean speech signal
        float error = primary[n] - noise_estimate;
        output[n]   = error;

        // Update weights — LMS rule:
        // w(n+1) = w(n) + 2 * mu * error * reference(n)
        for (int i = 0; i < FILTER_ORDER; i++) {
            weights[i] += 2.0f * MU * error * ref_buffer[i];
        }
    }
}
Add lms_filter.c - core LMS adaptive fi
