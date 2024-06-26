//Tulis Ulang library di bawah ini
//#include <AFMotor.h>
//#include <NewPing.h>
//#include <Servo.h>
//Mulai dari bawah sini:
...
...
...

#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 200

//Tentukan max speednya, dari 0 s/d 255
#define MAX_SPEED  // sets speed of DC  motors


#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

//Deklarasikan pin motor mana yang dipakai
//AF_DCMotor motor1(1, MOTOR12_1KHZ); atau AF_DCMotor motor1(2, MOTOR12_1KHZ); <=== Ini untuk motor1
//AF_DCMotor motor2(3, MOTOR12_1KHZ); atau AF_DCMotor motor2(4, MOTOR12_1KHZ); <=== Ini untuk motor2
//Mulai dari bawah sini:
//Motor 1
...
//Motor 2
...

Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
//  Pin Servo mana yang benar?
//  myservo.attach(9);
//  atau
//  myservo.attach(10);
// Mulai dari bawah sini:
  ...
  myservo.write(115);
  delay(2000);
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
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  if (distance <= 15)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL)
    {
      turnRight();
      moveStop();
    } else
    {
      turnLeft();
      moveStop();
    }
  } else
  {
    moveForward();
  }
  distance = readPing();
}

int lookRight()
{
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}

int lookLeft()
{
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void moveForward() {

  if (!goesForward)
  {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
    delay(5);
  }
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(500);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
