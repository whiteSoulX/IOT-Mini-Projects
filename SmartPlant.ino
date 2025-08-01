#define BLYNK_TEMPLATE_ID "TMPL6HmQsM0cu"
#define BLYNK_TEMPLATE_NAME "Prototype"
#define BLYNK_AUTH_TOKEN "_nLLle1TJUpr9X3eIzSEc869nvXPaHwt"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "SONY";
char pass[] = "its77000";

// Relay control pins
#define RELAY_DC 16   // GPIO16 for DC light
#define RELAY_AC 17   // GPIO17 for AC light

// Virtual pins
#define VP_DC V2
#define VP_AC V3

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_DC, OUTPUT);
  pinMode(RELAY_AC, OUTPUT);

  // Turn off both relays initially (assuming LOW-active relays)
  digitalWrite(RELAY_DC, HIGH); // Relay OFF
  digitalWrite(RELAY_AC, HIGH);

  // Connect to WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

// DC Light Control
BLYNK_WRITE(VP_DC) {
  int state = param.asInt();  // 1 = ON, 0 = OFF

  digitalWrite(RELAY_DC, state ? LOW : HIGH); // LOW = ON (for relay)

  if (state) {
    Serial.println("🟢 DC Light: ON");
  } else {
    Serial.println("🔴 DC Light: OFF");
  }
}

// AC Light Control
BLYNK_WRITE(VP_AC) {
  int state = param.asInt();  // 1 = ON, 0 = OFF

  digitalWrite(RELAY_AC, state ? LOW : HIGH); // LOW = ON (for relay)

  if (state) {
    Serial.println("🟢 AC Light: ON");
  } else {
    Serial.println("🔴 AC Light: OFF");
  }
}

void loop() {
  Blynk.run();
}
