#define red 23
#define yellow 19
#define green 21
#define buzzer 2
#define btn 22


void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(btn, INPUT);

}

void loop() {
 if(digitalRead(btn) == LOW) {
  digitalWrite(buzzer, LOW);
  

  digitalWrite(red, HIGH);
   delay(5000);
    digitalWrite(red, LOW);

  digitalWrite(yellow, HIGH);
     delay(5000);
digitalWrite(yellow, LOW);

  digitalWrite(green, HIGH);
delay(5000);
digitalWrite(green, LOW);
 }
 else
 {
digitalWrite(red, LOW);
digitalWrite(yellow, LOW);
digitalWrite(green, LOW);
digitalWrite(buzzer, HIGH);
 }

}