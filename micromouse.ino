#include <Servo.h>          // Servo motor library
#include <NewPing.h>        // Ultrasonic sensor function library

// Motor control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

bool detected = false;

// Sensor pins
#define trig_pin A1 // Analog input 1
#define echo_pin A2 // Analog input 2
#define maximum_distance 1000
boolean goesForward = false;
int distance = 100;
NewPing sonar(trig_pin, echo_pin, maximum_distance); // Sensor function
Servo servo_motor; // Servo name

void setup() {
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  servo_motor.attach(10); // Servo pin
  servo_motor.write(90);  // Center the servo
  delay(2000);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  distance = readPing();
  if (distance <= 10) {
    detected = true;
    moveStop();
    delay(300);
    moveBackward();
    delay(100); // Reduced backward movement delay
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    if (distanceRight >= distanceLeft) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
}

int lookRight() {
  delay(200);
  servo_motor.write(0); // Turn the servo 90 degrees to the right
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90); // Center the servo
  return distance;
}

int lookLeft() {
  delay(500);
  servo_motor.write(180); // Turn the servo 90 degrees to the left
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90); // Center the servo
  return distance;
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
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
  delay(150); // Reduced delay for turning
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
  delay(150); // Reduced delay for turning
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
