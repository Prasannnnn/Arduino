#include <Servo.h>

Servo servo;
const int trigPin = 7;
const int echoPin = 6;

void setup() {
  servo.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  // Send an ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration / 58;  // Speed of sound is 343 m/s, so distance = (time * speed) / 2
  
  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an object is too close (replace the threshold value as needed)
  if (distance < 15) {
    // Open the lid (assuming 90 degrees is open)
    servo.write(90);
    delay(2000);  // Keep the lid open for 2 seconds
    // Close the lid (0 degrees)
    servo.write(0);
  }
  delay(500);  // Add a delay for stability
}
