#include <SerialCommand.h>

#define PIN_LED 8

SerialCommand sCmd;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(9600);

  sCmd.addCommand("ON", LED_on);
  sCmd.addCommand("OFF", LED_off);
  sCmd.addCommand("ON2", LED2_on);
  sCmd.addCommand("OFF2", LED2_off);
  sCmd.setDefaultHandler(unknown);

  Serial.println("Ready");
}

void loop() {
  sCmd.readSerial();
}

void LED_on()
{
  digitalWrite(PIN_LED, HIGH);
  Serial.println("LED On");  
}

void LED_off()
{
  digitalWrite(PIN_LED, LOW);
  Serial.println("LED Off");  
}


void LED2_on()
{
  digitalWrite(7, HIGH);
  Serial.println("LED On");  
}

void LED2_off()
{
  digitalWrite(7, LOW);
  Serial.println("LED Off");  
}

void unknown(const char *command) {
  Serial.println(command);
}


