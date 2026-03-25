# 🔊 Active Noise Cancellation System using ESP32

![Status](https://img.shields.io/badge/Status-In%20Progress-yellow)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Language](https://img.shields.io/badge/Language-Embedded%20C-green)
![Domain](https://img.shields.io/badge/Domain-Signal%20Processing-orange)

> Real-time Environmental Noise Cancellation (ENC) system using dual microphones and ESP32,  
> designed to suppress background noise while preserving human speech.

---

## 📌 Table of Contents

- [Overview](#-overview)
- [How It Works](#-how-it-works)
- [Hardware Required](#-hardware-required)
- [Circuit Diagram](#-circuit-diagram)
- [Software & Tools](#-software--tools)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Current Progress](#-current-progress)
- [Future Scope](#-future-scope)
- [Author](#-author)

---

## 📖 Overview

This project implements an **Environmental Noise Cancellation (ENC)** system on an ESP32 microcontroller.  
The system uses **two MEMS microphones** — one to capture the environment (noise + speech) and one as a  
reference microphone (noise only) — and applies **adaptive signal processing** to cancel the noise in real time,  
outputting clean speech through a speaker.

This has applications in:
- Hands-free communication devices
- Industrial worker safety headsets
- Smart home voice assistants
- Defence communication equipment in high-noise environments

---

## ⚙️ How It Works

```
  [Mic 1 — Primary]   ──►  captures: SPEECH + NOISE
  [Mic 2 — Reference] ──►  captures: NOISE only
                               │
                               ▼
                     ┌─────────────────────┐
                     │   ESP32 Processor   │
                     │                     │
                     │  1. Read both mics  │
                     │     via I2S / ADC   │
                     │                     │
                     │  2. Apply Adaptive  │
                     │     LMS Filter      │
                     │                     │
                     │  3. Output = Mic1   │
                     │     minus filtered  │
                     │     noise estimate  │
                     └─────────┬───────────┘
                               │
                               ▼
                        [Speaker Output]
                        Clean Speech Only
```

### Adaptive LMS Filter (Least Mean Squares)
The LMS algorithm continuously adjusts filter coefficients to **model the noise path** and subtract it from the primary signal:

```
error(n)  = primary(n) - noise_estimate(n)
w(n+1)    = w(n) + 2 * mu * error(n) * reference(n)
```

Where:
- `w(n)` = filter weight vector
- `mu` = step size (controls adaptation speed vs stability)
- `error(n)` = residual signal (ideally = clean speech)

---

## 🛠 Hardware Required

| Component | Specification | Quantity |
|---|---|---|
| ESP32 Development Board | NodeMCU-32s / ESP32-WROOM-32 | 1 |
| MEMS Microphone | INMP441 (I2S) or MAX9814 (analog) | 2 |
| Audio Amplifier Module | MAX98357A (I2S) or PAM8403 | 1 |
| Speaker | 4Ω / 3W | 1 |
| Capacitors | 100nF decoupling caps | 4 |
| Resistors | 10kΩ pull-down | 2 |
| Breadboard + Jumper Wires | — | — |
| 5V Power Supply / USB | — | 1 |

---

## 🔌 Circuit Diagram

> 📁 See `/schematics/anc_circuit_diagram.png`

### Pin Connections (INMP441 I2S Microphone → ESP32)

| INMP441 Pin | ESP32 GPIO |
|---|---|
| VDD | 3.3V |
| GND | GND |
| SCK (Clock) | GPIO 14 |
| WS (Word Select) | GPIO 15 |
| SD (Data) | GPIO 32 |
| L/R Select | GND (Left) / 3.3V (Right) |

> Connect Mic 1 L/R to GND, Mic 2 L/R to 3.3V — this lets both share the same I2S bus on separate channels.

---

## 💻 Software & Tools

| Tool / Library | Purpose |
|---|---|
| Arduino IDE 2.x | Firmware development |
| Embedded C | Core programming language |
| ESP32 Arduino Core | Board support package |
| ESP-IDF I2S Driver | I2S audio acquisition |
| MATLAB (optional) | Signal simulation & filter design |
| LTspice (optional) | Analog front-end simulation |

### Dependencies (Arduino Libraries)
```
- driver/i2s.h       (ESP-IDF built-in — I2S audio)
- math.h             (LMS filter computation)
```

---

## 📁 Project Structure

```
esp32-active-noise-cancellation/
│
├── src/
│   ├── main.c                  # Main firmware entry point
│   ├── i2s_audio.c             # I2S mic init & audio read functions
│   ├── i2s_audio.h
│   ├── lms_filter.c            # Adaptive LMS filter implementation
│   └── lms_filter.h
│
├── schematics/
│   └── anc_circuit_diagram.png # Circuit diagram image
│
├── matlab_simulation/
│   └── lms_simulation.m        # MATLAB script to simulate LMS filter
│
├── docs/
│   └── project_report.pdf      # Detailed project documentation
│
├── README.md
└── LICENSE
```

---

## 🚀 Getting Started

### 1. Clone the Repository
```bash
git clone https://github.com/YOUR_USERNAME/esp32-active-noise-cancellation.git
cd esp32-active-noise-cancellation
```

### 2. Install ESP32 Board in Arduino IDE
- Open Arduino IDE → File → Preferences
- Add this URL to Additional Board Manager URLs:
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
- Go to Tools → Board Manager → search **esp32** → Install

### 3. Open the Firmware
- Open `src/main.c` in Arduino IDE
- Select board: **ESP32 Dev Module**
- Select correct COM port

### 4. Configure Parameters
In `lms_filter.h`, tune these values for your environment:
```c
#define FILTER_ORDER   32      // Number of filter taps
#define MU             0.01f   // Step size (0.001 to 0.1)
#define SAMPLE_RATE    16000   // Audio sample rate in Hz
#define BUFFER_SIZE    256     // Samples per processing block
```

### 5. Flash to ESP32
- Click **Upload** in Arduino IDE
- Open Serial Monitor at 115200 baud to see debug output

---

## 📊 Current Progress

| Task | Status |
|---|---|
| I2S dual microphone read | ✅ Done |
| Audio playback via I2S amplifier | ✅ Done |
| Basic noise subtraction (fixed filter) | ✅ Done |
| Adaptive LMS filter implementation | 🟡 In Progress |
| Speech preservation validation | 🔴 Pending |
| Real-time performance optimisation | 🔴 Pending |
| Hardware PCB design | 🔴 Pending |

---

## 🔭 Future Scope

- Implement **NLMS (Normalised LMS)** for faster convergence
- Add **Voice Activity Detection (VAD)** to pause adaptation during speech
- Port to **ESP-IDF** for better real-time performance and FreeRTOS task management
- Design a custom **PCB** for compact hardware integration
- Extend to **active noise cancelling headset** form factor
- Explore **deep learning-based noise suppression** on ESP32-S3 with AI acceleration

---

## 👨‍💻 Author

**Ayush Kumar**  
B.Tech — Electronics & Communication Engineering  
Vinoba Bhave University, Hazaribagh  
GATE 2025 Qualified (ECE) — Score: 428 | AIR: 5568

📧 ayushraj822124@gmail.com  
🔗 [LinkedIn]( www.linkedin.com/in/ayush-kumar7070 )

## 📄 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

*If you found this project useful or interesting, consider giving it a ⭐ on GitHub!*
