// 
//  HC-SR04.c
//  This program is created for testing Arduino R3 board 
//  connected with HC-SR04 distance sensor.  
//

// Arduino pins
#define ECHO_PIN 7
#define TRIG_PIN 8
#define LED_PIN  13
 
const float MaxDistance = 400;
const float MinDistance = 2;
const unsigned Measurements = 10;   
  
//  Length of the ECHO_PIN signal multiplied by MagicValue returns distance
//  in centimeters
const float MagicValue = 58;  

//  It's the max length of ECHO_PIN signal that means the longest valid distance
const float Timeout = MagicValue * MaxDistance;

//  HC-SR04 sometimes returns weird and incorrect values so the function
//  checks the distance `Measurements` times, excludes ones higher than 
//  MaxDistance and lower than MinDistance. Then it returns an arithmetic
//  average of potentially correnct values.
float get_distance()
{
  float distance;
  float average = 0;

  Serial.print("Meansurement: ");
  for (int i = 0; i < Measurements; i++)
  {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    // gets the signal. The length of a signal means the distance If the signal is longer than Timeout, it must be invalid 
    distance = pulseIn(ECHO_PIN, HIGH, Timeout) / MagicValue;
    
    if (distance <= MaxDistance && distance >= MinDistance)
    {
      average += distance;
      Serial.print(distance); Serial.print(", ");
    }
    else
    {
      Serial.print("err, ");
    }
  }
  average /= Measurements;
  Serial.print("[");
  Serial.print(average);
  Serial.println("]");
  return average;
}


void setup() 
{
  Serial.begin(9600);
  Serial.println("Hello Arduino!");
  
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Ready to work");
}

void loop() 
{
  get_distance();
  delay(100);
}

