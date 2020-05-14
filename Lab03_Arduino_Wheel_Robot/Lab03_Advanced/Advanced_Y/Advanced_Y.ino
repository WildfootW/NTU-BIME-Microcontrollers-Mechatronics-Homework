void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  digitalWrite(5, HIGH);// go forward 50
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(2400);
  digitalWrite(5, LOW);// turn left 45 angle
  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(170);
  digitalWrite(5, HIGH);// go forward 50
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(2400);
  digitalWrite(5, LOW);// go backward 50
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(2400);
  digitalWrite(5, HIGH);// turn right 90 angle
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(350);
  digitalWrite(5, HIGH);// go forward 50
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(2400);
  digitalWrite(5, LOW);// stop
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(3000);
  

}
