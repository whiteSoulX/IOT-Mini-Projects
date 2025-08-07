#define BLYNK_TEMPLATE_ID "TMPL6HmQsM0cu"
#define BLYNK_TEMPLATE_NAME "Prototype"
#define BLYNK_AUTH_TOKEN "_nLLle1TJUpr9X3eIzSEc869nvXPaHwt"

#include <WiFi.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "SONY";
char pass[] = "its77000";

// Relay control pins
#define RELAY_DC 16   // GPIO16 for DC light
#define RELAY_AC 17   // GPIO17 for AC light

// Sensor Pins
#define DHTPIN 21
#define SOIL_PIN 34     // Analog pin for soil sensor
#define RAIN_PIN 35     // Analog pin for rain sensor

// Virtual pins
#define VP_DC V2
#define VP_AC V3
#define VP_TEMP V4
#define VP_HUMID V5
#define VP_SOIL V6
#define VP_RAIN V7

DHT dht(DHTPIN, DHT11);  // Use DHT11 or DHT22 depending on your model

void setup() {
  Serial.begin(115200);
  delay(1000); // Allow time for Serial Monitor to connect

  pinMode(RELAY_DC, OUTPUT);
  pinMode(RELAY_AC, OUTPUT);
  digitalWrite(RELAY_DC, HIGH); // Relay OFF
  digitalWrite(RELAY_AC, HIGH);

  Serial.println("🔌 System Initializing...");
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("✅ Connected to WiFi & Blynk");
}

// DC Light Control
BLYNK_WRITE(VP_DC) {
  int state = param.asInt();
  digitalWrite(RELAY_DC, state ? LOW : HIGH);
  Serial.println(state ? "🟢 [DC Light] Turned ON via Blynk" : "🔴 [DC Light] Turned OFF via Blynk");
}

// AC Light Control
BLYNK_WRITE(VP_AC) {
  int state = param.asInt();
  digitalWrite(RELAY_AC, state ? LOW : HIGH);
  Serial.println(state ? "🟢 [AC Light] Turned ON via Blynk" : "🔴 [AC Light] Turned OFF via Blynk");
}

void loop() {
  Blynk.run();

  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  int soil = analogRead(SOIL_PIN);
  int rain = analogRead(RAIN_PIN);

  Serial.println("\n========= 🌐 SENSOR DATA REPORT =========");

  if (!isnan(temp) && !isnan(humid)) {
    Serial.print("🌡️ Temperature : "); Serial.print(temp); Serial.println(" °C");
    Serial.print("💧 Humidity    : "); Serial.print(humid); Serial.println(" %");
    Blynk.virtualWrite(VP_TEMP, temp);
    Blynk.virtualWrite(VP_HUMID, humid);
  } else {
    Serial.println("❌ Failed to read from DHT sensor");
  }

  Serial.print("🌱 Soil Moisture: "); Serial.print(soil);
  Serial.println(" (0=Wet, 4095=Dry)");

  Serial.print("🌧️ Rain Sensor  : "); Serial.print(rain);
  Serial.println(" (0=Wet, 4095=Dry)");

  Blynk.virtualWrite(VP_SOIL, soil);
  Blynk.virtualWrite(VP_RAIN, rain);

  Serial.println("📤 Data sent to Blynk");
  Serial.println("========================================\n");

  delay(2000);
}
