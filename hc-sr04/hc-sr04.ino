// 
//  HC-SR04.c
//  This program is created for testing Arduino R3 board 
//  connected with the HC-SR04 distance sensor.  
//

// Arduino pins
#define SENSOR_ECHO_PIN A0
#define SENSOR_TRIG_PIN A1
#define LED_PIN  13
 
#define MAX_DISTANCE 400
#define MIN_DISTANCE 2
#define MEASUREMENTS 20
  
//  Length of the ECHO_PIN signal multiplied by MagicValue returns a distance
//  in centimeters
#define MAGIC_VALUE 58  

//  It's the max length of ECHO_PIN signal that means the longest valid distance
#define TIMEOUT (MAGIC_VALUE * MAX_DISTANCE)

//  HC-SR04 sometimes returns weird and incorrect values so the function
//  checks the distance `Measurements` times, excludes ones higher than 
//  MaxDistance and lower than MinDistance. Then it returns an arithmetic
//  average of potentially correnct values.
float get_distance()
{
  float distance;
  float average = 0;
  int bad_distances = 0;

  Serial.print("Measurement: ");
  for (int i = 0; i < MEASUREMENTS; i++)
  {
    digitalWrite(SENSOR_TRIG_PIN, LOW);
    delayMicroseconds(100);
    digitalWrite(SENSOR_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SENSOR_TRIG_PIN, LOW);

    // Gets the signal. The length of a signal multiplied by MagicValue
    // returns the distance in cm. 
    // If the signal is longer than Timeout, it must be invalid. 
    distance = pulseIn(SENSOR_ECHO_PIN, HIGH, TIMEOUT) / MAGIC_VALUE;

    average += distance;
  }
  average /= MEASUREMENTS;
  Serial.print("[");
  Serial.print(average);
  Serial.println("]");
  return average;
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("Hello Arduino!");
  
  pinMode(SENSOR_ECHO_PIN, INPUT);
  pinMode(SENSOR_TRIG_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Ready to work");
}

void loop() 
{
  get_distance();
  delay(100);
}

