#include <NewPing.h> // Ultrasonic sensor function library. You must install this library

const int LeftMotorForward = 8;
const int LeftMotorBackward = 9;
const int RightMotorForward = 10;
const int RightMotorBackward = 11;
const int ledPin = 12; // Digital pin to control the LED

#define trig_pin1 A0 // Analog input 0
#define echo_pin1 A3 // Analog input 1
#define trig_pin2 A1 // Analog input 2
#define echo_pin2 A4 // Analog input 3
#define trig_pin3 A2 // Analog input 4
#define echo_pin3 A5 // Analog input 5

#define maximum_distance 200
const int safe_distance = 30; // Adjust this value according to your desired safe distance

boolean goesForward = false;
int distance = 100;

NewPing sonar1(trig_pin1, echo_pin1, maximum_distance); // Sensor 1 function
NewPing sonar2(trig_pin2, echo_pin2, maximum_distance); // Sensor 2 function
NewPing sonar3(trig_pin3, echo_pin3, maximum_distance); // Sensor 3 function

// ... (rest of the code remains the same)

void setup() {
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(ledPin, OUTPUT); // Set the LED pin as output

  Serial.begin(9600); // Initialize Serial Monitor

  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= safe_distance) {
    moveStop();
    Serial.println("Obstacle detected! Stopping and backing up.");
    blinkLED(); // Blink the LED when an obstacle is detected
    delay(500);
    moveBackward();
    delay(1000);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(3000);
    distanceLeft = lookLeft();
    delay(3000);

    if (distance >= distanceLeft) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
  distance = readPing();
}


int lookRight() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(500);
  int distance = readPing();
  delay(100);
  return distance;
}

int lookLeft() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(500);
  int distance = readPing();
  delay(100);
  return distance;
}

int readPing() {
  delay(70);
  int cm1 = sonar1.ping_cm();
  int cm2 = sonar2.ping_cm();
  int cm3 = sonar3.ping_cm();
  
  int cm = min(min(cm1, cm2), cm3); // Choose the minimum distance from three sensors
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }
}

void moveBackward() {
  goesForward = false;
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(500);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void turnLeft() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(500);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void blinkLED() {
  // Blink the LED three times quickly
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}
