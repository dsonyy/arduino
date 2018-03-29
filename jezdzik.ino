#include <AFMotor.h>

#define TRIG_PIN    A1
#define ECHO_PIN    A0
#define LED_PIN     13
#define MOTOR_LEFT  3
#define MOTOR_RIGHT 2

AF_DCMotor motor_left(MOTOR_LEFT);
AF_DCMotor motor_right(MOTOR_RIGHT);

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello Arduino!");
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  motor_left.setSpeed(180);
  motor_right.setSpeed(180);

  Serial.println("Ready to work.");
}

void loop()
{
  if (check_distance() >= 10)
  {
    motor_left.run(FORWARD);
    motor_right.run(FORWARD);
    delay(1000);
  }
  else
  {
    motor_left.run(FORWARD);
    motor_right.run(BACKWARD);
    delay(2000);
  }
}

float check_distance()
{
  unsigned long duration;
  float distance;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);

  distance = (float)duration / 58.2f;
  Serial.println(distance);

  return distance;
}
