//
// jezdzik.ino
//
// Controlling self-driving robot based on Arduino Uno R3 connected with 
// Adafruit L293D Motor Shield. There are also two motors to drive and 
// single HC-SR04 ultrasonic sensor to navigate and avoiding obstacles.
//

#include <AFMotor.h> 
#include <stdlib.h>

// PINS
#define SENSOR_ECHO_PIN A0
#define SENSOR_TRIG_PIN A1
#define MOTOR_LEFT  1
#define MOTOR_RIGHT 2

// SENSOR
#define MAX_DISTANCE 400
#define MIN_DISTANCE 2
#define MEASUREMENTS 10   
#define MAGIC_VALUE 58
#define TIMEOUT (MAGIC_VALUE * MAX_DISTANCE)
#define ROTATE_DISTANCE 20 // in cm

// MOTORS
#define LEFT_SPEED 190
#define RIGHT_SPEED 200
#define FREQUENCY MOTOR12_2KHZ 
AF_DCMotor motor_left(MOTOR_LEFT);
AF_DCMotor motor_right(MOTOR_RIGHT);

// FUNCTIONS
float get_distance(); // get distance in cm from HC-SR04 sensor

void setup()
{    
  Serial.begin(9600);
  Serial.println("Hello Arduino!");
  
  pinMode(SENSOR_TRIG_PIN, OUTPUT);
  pinMode(SENSOR_ECHO_PIN, INPUT);

  motor_left.setSpeed(LEFT_SPEED);
  motor_right.setSpeed(RIGHT_SPEED);

  delay(1000);
  srand(get_distance());  
  Serial.println("Ready to work.");
}

// this function is so bad but works
void loop()
{ 
  if (get_distance() < ROTATE_DISTANCE)
  {
    int choice = rand() % 2;
    int rotations = 0;
    do
    {
      switch (rand() % 2)
      {
      case 0: motor_right.run(BACKWARD); motor_left.run(FORWARD); break;
      case 1: motor_left.run(BACKWARD); motor_right.run(FORWARD); break;
      }
      if (++rotations > 3)
      {
        delay(200);
        motor_left.run(RELEASE);  
        motor_right.run(RELEASE);
        delay(200);

        motor_left.run(FORWARD);  
        motor_right.run(FORWARD);
        delay(1000);
        rotations = 0;
        continue;
      }
      delay(300);
    } while (get_distance() < ROTATE_DISTANCE);
  }

  
  while (get_distance() >= ROTATE_DISTANCE)
  {
    motor_left.run(FORWARD);  
    motor_right.run(FORWARD);
    delay(500);
  }
    
    delay(200);
    motor_left.run(RELEASE);  
    motor_right.run(RELEASE);
    delay(200);
}

float get_distance()
{
  float distance;
  float average = 0;
  int bad_distances = 0;

  Serial.print("Measurement: ");
  for (int i = 0; i < MEASUREMENTS; i++)
  {
    digitalWrite(SENSOR_TRIG_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(SENSOR_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SENSOR_TRIG_PIN, LOW);

    distance = pulseIn(SENSOR_ECHO_PIN, HIGH, TIMEOUT) / MAGIC_VALUE;
    
    if (distance <= MAX_DISTANCE && distance >= MIN_DISTANCE)
    {
      average += distance;
    }
    else
    {
      if (++bad_distances == MEASUREMENTS >> 1) 
      {
        Serial.println("terminated");
        return 0.0;
      }
    }
  }
  average /= MEASUREMENTS;
  Serial.println(average);
  return average;
}
