# 🌡️ ThermoMood Display

**A circular mood visualizer based on skin temperature — perfect for your desk or cubicle.**  
Touch the thermocouple, and the GC9A01A round display reveals a mood with color and snarky commentary.

---

## 📦 Features

- Displays Fahrenheit temperature at the bottom of a circular screen
- Mood is selected based on skin temperature ranges
- Background color changes dynamically with mood
- Funny, sarcastic, cubicle-safe mood labels
- Word-wrapped, auto-centered text
- Smooth average filtering to avoid noisy updates

---

## 🛠️ Hardware Requirements

| Component | Details |
|----------|---------|
| **Microcontroller** | Arduino Nano ESP32 |
| **Display** | 1.28" Round TFT GC9A01A (240x240) |
| **Thermocouple** | Type K Thermocouple |
| **Converter Module** | MAX6675 Thermocouple Amplifier |
| **Wiring** | 4-Wire SPI (Display) + 3-Wire SPI (MAX6675) |

---

## 📷 Pinout (Example Wiring)

| Signal | Arduino Nano ESP32 | Module |
|--------|--------------------|--------|
| **SO** (Thermocouple) | `D4` | MAX6675 SO |
| **CS** (Thermocouple) | `D5` | MAX6675 CS |
| **SCK** | `D6` | MAX6675 SCK |
| **TFT DC** | `D7` | GC9A01A DC |
| **TFT CS** | `D10` | GC9A01A CS |
| **TFT RST** | `D8` | GC9A01A RST |
| **TFT SCK/MOSI** | Default SPI | GC9A01A SCK/MOSI |

---

## 🎨 Mood Mapping (Temperature → Mood)

| Temp Range (°F) | Example Moods |
|-----------------|----------------|
| `< 85` | "Are you even alive?", "CRASHING OUT" |
| `85–87` | "Quietly spiraling", "Flatline on enthusiasm" |
| `88–89` | "Classic cubicle-core", "Emotionally beige" |
| `90–91` | "Deadline panic", "Running on fumes" |
| `92–93` | "Unraveling", "Caffeinated and dangerous" |
| `94–95` | "TIME FOR YOU TO GO HOME", "Corporate martyr detected" |
| `> 96` | "Go touch grass", "Return to sender (overheated)" |

---

## 💻 Libraries Required

Install these via the Arduino Library Manager:

- `Adafruit_GFX`
- `Adafruit_GC9A01A`
- `MAX6675` (Adafruit version recommended)

---

## 🚀 To Run

1. Wire up your components as listed.
2. Upload `ThermoMood_Display.ino` using Arduino IDE (board: **Arduino Nano ESP32**).
3. Touch the thermocouple — your mood will appear!

---

## 🤝 Contributions Welcome

Want to add emoji, animations, or finger detection? Submit a pull request or suggest ideas!

---

## 🧠 License

This project is open source under the MIT License.
