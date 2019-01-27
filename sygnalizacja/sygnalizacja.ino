
#define RED 9
#define YELLOW 8
#define GREEN 7


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  
  digitalWrite(RED, HIGH);
  delay(3000);
  digitalWrite(YELLOW, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(3000);
  digitalWrite(YELLOW, LOW);
}
