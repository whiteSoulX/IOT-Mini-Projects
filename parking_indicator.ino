#define TRIG_PIN 5
#define ECHO_PIN 18

#define GREEN_LED 13
#define RED_LED 12

const int THRESHOLD = 7 + 10;  // 7 + 10
long duration;
float distance_cm;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  // Trigger sonar
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  duration = pulseIn(ECHO_PIN, HIGH);
  distance_cm = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if (distance_cm > THRESHOLD) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    Serial.println("Parking Available");

  } else {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.println("Parking Not Available");
  }

  delay(1000);
}
