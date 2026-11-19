// Your firmware. Edit it, push to GitHub, and every linked device updates itself.
//
// Nothing in here is needed for OTA: the OTA-Forever loader installs updates on
// every power-on/reset no matter what this sketch does. The OTAForever library
// below is optional and adds:
//   - connectWiFi(): reuse the WiFi you entered on the setup page
//   - begin(minutes): also check GitHub while running, and restart into the
//     loader when a new build is published (no power-cycle needed)

#include <OTAForever.h>

const int LED_PIN = 2;               // change for your board
const uint32_t BREATH_MS = 3000;     // one full fade in + fade out

void setup() {
  Serial.begin(115200);

  if (OTAForever.connectWiFi()) {
    Serial.printf("WiFi connected. Running build #%lu from %s\n",
                  (unsigned long)OTAForever.installedBuild(), OTAForever.repo().c_str());
    OTAForever.begin(5);  // check for new builds every 5 minutes
  }
}

void loop() {
  // Smooth "breathing" fade: brightness follows a cosine wave (0 -> 1 -> 0).
  // Squaring it makes the fade look even to the eye (LEDs look too bright at low PWM).
  float phase = (millis() % BREATH_MS) / (float)BREATH_MS * TWO_PI;
  float level = (1.0f - cosf(phase)) / 2.0f;
  analogWrite(LED_PIN, (int)(level * level * 255));
  delay(10);
}
