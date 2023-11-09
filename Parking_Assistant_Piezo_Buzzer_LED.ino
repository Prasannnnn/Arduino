#define trigPin 9
#define echoPin 10
#define buzzerPin 11
#define ledPin 13

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;  // Convert to cm

  if (distance < 25) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    tone(buzzerPin, 1000);     // Generate a sound
    delay(500);                // Sound duration
    noTone(buzzerPin);          // Turn off the sound
  } else {
    digitalWrite(ledPin, LOW); // Turn off the LED
    noTone(buzzerPin);         // Make sure the buzzer is off
  }

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(200); // Delay for stability
}