# Documentation

This folder contains detailed documentation for the ANC project.

## Files
- `project_report.pdf`  — Full project report with theory and results
- `lms_algorithm.md`    — Detailed explanation of LMS filter math
- `testing_results.md`  — Hardware testing observations and data

## Project Summary

| Parameter        | Value              |
|------------------|--------------------|
| Platform         | ESP32 (NodeMCU-32s)|
| Sample Rate      | 16000 Hz           |
| Filter Order     | 32 taps            |
| Step Size (mu)   | 0.01               |
| Buffer Size      | 256 samples        |
| Input Mics       | 2x INMP441 (I2S)   |
| Output           | MAX98357A Speaker  |

## References
- Widrow & Stearns — Adaptive Signal Processing (1985)
- ESP32 Technical Reference Manual — Espressif Systems
- INMP441 Datasheet — TDK InvenSense

> Full project report will be uploaded upon project completion.
```

4. Scroll down → Commit message:
```
Add docs folder with project parameters and references
