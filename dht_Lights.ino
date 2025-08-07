#define BLYNK_TEMPLATE_ID "TMPL6HmQsM0cu"
#define BLYNK_TEMPLATE_NAME "Prototype"
#define BLYNK_AUTH_TOKEN "_nLLle1TJUpr9X3eIzSEc869nvXPaHwt"

#include <WiFi.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "SONY";
char pass[] = "its77000";

// DHT Sensor
#define DHTPIN 21
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Relay pins
#define RELAY_DC 16   // DC light
#define RELAY_AC 17   // AC light

// Virtual Pins
#define VP_DC V2
#define VP_AC V3
#define VP_TEMP V4
#define VP_HUMID V5

BlynkTimer timer;

void sendSensorData() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();

  if (isnan(temp) || isnan(humi)) {
    Serial.println("❌ Failed to read from DHT22 sensor!");
    return;
  }

  Serial.print("✅ Temperature: ");
  Serial.print(temp);
  Serial.print("°C | Humidity: ");
  Serial.print(humi);
  Serial.println("%");

  Blynk.virtualWrite(VP_TEMP, temp);
  Blynk.virtualWrite(VP_HUMID, humi);
}

// Control DC Light
BLYNK_WRITE(VP_DC) {
  int state = param.asInt();
  digitalWrite(RELAY_DC, state ? LOW : HIGH);
  Serial.println(state ? "DC Light: ON" : "DC Light: OFF");
}

// Control AC Light
BLYNK_WRITE(VP_AC) {
  int state = param.asInt();
  digitalWrite(RELAY_AC, state ? LOW : HIGH);
  Serial.println(state ? "AC Light: ON" : "AC Light: OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_DC, OUTPUT);
  pinMode(RELAY_AC, OUTPUT);
  digitalWrite(RELAY_DC, HIGH); // off
  digitalWrite(RELAY_AC, HIGH); // off

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Send sensor data every 5 seconds
  timer.setInterval(5000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
