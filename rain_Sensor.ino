#define RAIN_ANALOG_PIN 35  // Use any analog-capable GPIO pin
#define RAIN_DIGITAL_PIN 25 // Optional (if you connected D0 pin)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("🌧 Rain Sensor Test Starting...");
  
  pinMode(RAIN_DIGITAL_PIN, INPUT);
}

void loop() {
  int rainAnalog = analogRead(RAIN_ANALOG_PIN);
  int rainDigital = digitalRead(RAIN_DIGITAL_PIN);

  Serial.print("🌧 Analog Value: ");
  Serial.print(rainAnalog);

  Serial.print(" | ⚡ Digital State: ");
  Serial.println(rainDigital == LOW ? "🌧 Rain Detected" : "☀️ Dry");

  delay(1000);  // 1 second delay
}

