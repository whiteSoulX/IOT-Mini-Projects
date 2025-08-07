#define SOIL_SENSOR_PIN 34  // Use any analog pin like 32, 33, 34, 35

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("🌱 Soil Moisture Sensor Test Starting...");
}

void loop() {
  int soilValue = analogRead(SOIL_SENSOR_PIN);
  
  Serial.print("🔍 Soil Moisture Analog Value: ");
  Serial.println(soilValue);

  delay(1000);  // 1 second delay
}
