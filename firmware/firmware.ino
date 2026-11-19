// Your firmware. Edit it, push to GitHub, and every linked device updates itself.
//
// Nothing in here is needed for OTA: the OTA-Forever loader installs updates on
// every power-on/reset no matter what this sketch does. The OTAForever library
// below is optional and adds:
//   - connectWiFi(): reuse the WiFi you entered on the setup page
//   - begin(minutes): also check GitHub while running, and restart into the
//     loader when a new build is published (no power-cycle needed)

#include <OTAForever.h>

const int LED_PIN = 2;  // change for your board

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  if (OTAForever.connectWiFi()) {
    Serial.printf("WiFi connected. Running build #%lu from %s\n",
                  (unsigned long)OTAForever.installedBuild(), OTAForever.repo().c_str());
    OTAForever.begin(5);  // check for new builds every 5 minutes
  }
}

void loop() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  delay(100);  // fast blink = build #2 arrived over the air
}
