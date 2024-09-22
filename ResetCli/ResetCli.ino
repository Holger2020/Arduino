int i = 0;

// Reset Arduino board as start counter
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Hello");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // run repeatedly

  // LED: HHHHH HH HH
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  delay(200);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);

  digitalWrite(LED_BUILTIN, LOW);
  delay(200);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  Serial.println(i);
  i++;
  delay(1000);
}


