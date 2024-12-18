#define one 15
#define two 2
#define thr 4
#define fou 5
#define fiv 18
#define six 19
#define sev 21
#define eig 23
#define btn1 12
#define btn2 14
#define btn3 27
void setup() {
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(thr, OUTPUT);
  pinMode(fou, OUTPUT);
  pinMode(fiv, OUTPUT);
  pinMode(six, OUTPUT);
  pinMode(sev, OUTPUT);
  pinMode(eig, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
}
bool btnState1 = false;
bool btnState2 = false;
bool btnState3 = false;
void btnOne() {
  digitalWrite(one, HIGH);
  delay(100);
  digitalWrite(one, LOW);
  digitalWrite(two, HIGH);
  delay(100);
  digitalWrite(two, LOW);
  digitalWrite(thr, HIGH);
  delay(100);
  digitalWrite(thr, LOW);
  digitalWrite(fou, HIGH);
  delay(100);
  digitalWrite(fou, LOW);
  digitalWrite(fiv, HIGH);
  delay(100);
  digitalWrite(fiv, LOW);
  digitalWrite(six, HIGH);
  delay(100);
  digitalWrite(six, LOW);
  digitalWrite(sev, HIGH);
  delay(100);
  digitalWrite(sev, LOW);
  digitalWrite(eig, HIGH);
  delay(100);
  digitalWrite(eig, LOW);
}

void btnTwo() {
  digitalWrite(fou, HIGH);
  digitalWrite(fiv, HIGH);
  delay(100);
  digitalWrite(fou, LOW);
  digitalWrite(fiv, LOW);
  digitalWrite(thr, HIGH);
  digitalWrite(six, HIGH);
  delay(100);
  digitalWrite(thr, LOW);
  digitalWrite(six, LOW);
  digitalWrite(two, HIGH);
  digitalWrite(sev, HIGH);
  delay(100);
  digitalWrite(two, LOW);
  digitalWrite(sev, LOW);
  digitalWrite(one, HIGH);
  digitalWrite(eig, HIGH);
  delay(100);
  digitalWrite(one, LOW);
  digitalWrite(eig, LOW);
}

void btnThr() {
  digitalWrite(one, HIGH);
  digitalWrite(two, HIGH);
  delay(100);
  digitalWrite(one, LOW);
  digitalWrite(two, LOW);
  digitalWrite(thr, HIGH);
  digitalWrite(fou, HIGH);
  delay(100);
  digitalWrite(thr, LOW);
  digitalWrite(fou, LOW);
  digitalWrite(fiv, HIGH);
  digitalWrite(six, HIGH);
  delay(100);
  digitalWrite(fiv, LOW);
  digitalWrite(six, LOW);
  digitalWrite(sev, HIGH);
  digitalWrite(eig, HIGH);
  delay(100);
  digitalWrite(sev, LOW);
  digitalWrite(eig, LOW);
}
void loop() {
  if (digitalRead(btn1) == HIGH) {
    btnState1 = true;
    btnState2 = false;
    btnState3 = false;
    while (btnState1) {
      btnOne();
      if (digitalRead(btn2) == HIGH) {
        btnState1 = false;
        btnState2 = true;
        break;  
      }
      if (digitalRead(btn3) == HIGH) {
        btnState1 = false;
        btnState3 = true;
        break; 
      }
    }
  }
  else if (digitalRead(btn2) == HIGH) {
    btnState1 = false;
    btnState2 = true;
    btnState3 = false;
    while (btnState2) {
      btnTwo();
      if (digitalRead(btn1) == HIGH) {
        btnState2 = false;
        btnState1 = true;
        break; 
      }
      if (digitalRead(btn3) == HIGH) {
        btnState2 = false;
        btnState3 = true;
        break; 
      }
    }
  }
  else if (digitalRead(btn3) == HIGH) {
    btnState1 = false;
    btnState2 = false;
    btnState3 = true;
    while (btnState3) {
      btnThr();
      if (digitalRead(btn1) == HIGH) {
        btnState3 = false;
        btnState1 = true;
        break;  
      }
      if (digitalRead(btn2) == HIGH) {
        btnState3 = false;
        btnState2 = true;
        break;  
      }
    }
  }
}
