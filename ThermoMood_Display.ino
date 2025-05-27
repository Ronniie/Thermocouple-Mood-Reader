// ThermoMood Display Integration (Circular Layout, Mood-Centric)
// Uses MAX6675 thermocouple and GC9A01A round TFT to display temperature-based moods

#include <max6675.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

// Thermocouple SPI pin definitions
#define SO_PIN D4
#define CS_PIN D5
#define SCK_PIN D6
MAX6675 thermocouple(SCK_PIN, CS_PIN, SO_PIN);

// TFT display pin definitions
#define TFT_DC D7
#define TFT_CS D10
#define TFT_RST D8
Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

// Track last displayed stable temperature
float lastDisplayedTemp = -999.0;

// Return background color based on mood content
uint16_t getMoodColor(const char* mood) {
  if (strstr(mood, "alive") || strstr(mood, "Frozen")) return GC9A01A_NAVY;
  if (strstr(mood, "spiraling") || strstr(mood, "low")) return GC9A01A_BLUE;
  if (strstr(mood, "meh") || strstr(mood, "core")) return GC9A01A_DARKGREY;
  if (strstr(mood, "deadline") || strstr(mood, "present")) return GC9A01A_ORANGE;
  if (strstr(mood, "existential") || strstr(mood, "panic")) return GC9A01A_TEAL;
  if (strstr(mood, "TIME FOR YOU") || strstr(mood, "martyr")) return GC9A01A_RED;
  if (strstr(mood, "CRASHING OUT") || strstr(mood, "overheated")) return GC9A01A_MAROON;
  return GC9A01A_PURPLE;
}

// Choose mood text based on input temperature (Fahrenheit)
const char* getMood(float tempF) {
  if (tempF < 85) {
    const char* moods[] = {"Are you even alive?", "Frozen in apathy", "Intern from the underworld", "Just cold hands or cold heart?", "CRASHING OUT"}; return moods[random(0, 5)];
  } else if (tempF < 88) {
    const char* moods[] = {"Quietly spiraling", "Coffee might help, but not really", "Low-power mode engaged", "Social battery: low", "Flatline on enthusiasm"}; return moods[random(0, 5)];
  } else if (tempF < 90) {
    const char* moods[] = {"Classic cubicle-core", "Meh. Just meh.", "Functioning introvert mode", "Emotionally beige", "Dead inside, but on time"}; return moods[random(0, 5)];
  } else if (tempF < 92) {
    const char* moods[] = {"One deadline away from losing it", "Focused panic detected", "Productivity-induced suffering", "Almost emotionally present", "Running on fumes"}; return moods[random(0, 5)];
  } else if (tempF < 94) {
    const char* moods[] = {"Buzzing with existential dread", "Running on caffeine and vibes", "Possibly unraveling", "Caffeinated and dangerous", "Deadline ninja"}; return moods[random(0, 5)];
  } else if (tempF < 96) {
    const char* moods[] = {"Overclocked human processor", "Might spontaneously combust", "TIME FOR YOU TO GO HOME", "Stop. Breathe. Panic again.", "Corporate martyr detected"}; return moods[random(0, 5)];
  } else {
    const char* moods[] = {"Go touch grass. Immediately.", "Check for open flames", "Thermally unstable coworker", "CRASHING OUT", "Return to sender (overheated)"}; return moods[random(0, 5)];
  }
}

void setup() {
  Serial.begin(9600);       // Start serial for debugging
  delay(500);
  tft.begin();              // Initialize TFT display
  tft.setRotation(0);
  tft.fillScreen(GC9A01A_BLACK);  // Start with black screen
  randomSeed(analogRead(A0));     // Seed RNG for mood randomness
}

void loop() {
  static float lastStableTemp = -999;
  static float tempSum = 0;
  static int sampleCount = 0;

  float tempF = thermocouple.readFahrenheit(); // Read current temperature
  tempSum += tempF;
  sampleCount++;

  // Average temp every 10 readings to reduce noise
  if (sampleCount >= 10) {
    float avgTemp = tempSum / sampleCount;
    tempSum = 0;
    sampleCount = 0;

    // Only update display if temperature changes significantly
    if (abs(avgTemp - lastStableTemp) >= 1.0) {
      lastStableTemp = avgTemp;
      const char* mood = getMood(avgTemp);
      uint16_t moodColor = getMoodColor(mood);

      Serial.print("Temp: "); Serial.print(avgTemp); Serial.print(" F | Mood: "); Serial.println(mood);

      tft.fillScreen(moodColor);  // Set background to mood color
      tft.drawCircle(120, 120, 119, GC9A01A_BLACK);  // Thin border ring
      tft.drawCircle(120, 120, 118, GC9A01A_BLACK);

      // Draw mood message, word-wrapped in center
      tft.setTextColor(GC9A01A_WHITE);
      tft.setTextSize(2);
      int y = 100;
      char buffer[128];
      strncpy(buffer, mood, sizeof(buffer));
      buffer[sizeof(buffer) - 1] = '\0';
      char* line = strtok(buffer, " ");
      String currentLine = "";

      while (line != NULL) {
        if (currentLine.length() + strlen(line) + 1 < 15) {
          currentLine += line;
          currentLine += " ";
        } else {
          int x = (240 - currentLine.length() * 12) / 2;
          tft.setCursor(x, y);
          tft.print(currentLine);
          y += 20;
          currentLine = String(line) + " ";
        }
        line = strtok(NULL, " ");
      }
      if (currentLine.length() > 0) {
        int x = (240 - currentLine.length() * 12) / 2;
        tft.setCursor(x, y);
        tft.print(currentLine);
      }

      // Draw temperature at bottom
      tft.setTextColor(GC9A01A_WHITE);
      tft.setTextSize(2);
      char tempStr[10];
      sprintf(tempStr, "%d F", (int)avgTemp);
      int tempWidth = strlen(tempStr) * 12;
      int tempX = (240 - tempWidth) / 2;
      tft.setCursor(tempX, 210);
      tft.print(tempStr);
    }
  }
  delay(500);  // Sample delay
}
