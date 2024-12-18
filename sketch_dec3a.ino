#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

int Trig_pin = 23;
int Echo_pin = 4;
long duration;
float Speed_of_sound = 0.034;
float dist_in_cm;

void setup() {
   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println("Can't initialize display!");
  }
  Serial.begin(115200); 
  pinMode(Trig_pin, OUTPUT); 
  pinMode(Echo_pin, INPUT);

}

void loop() {
  digitalWrite(Trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_pin, LOW);
    duration = pulseIn(Echo_pin, HIGH);
    dist_in_cm = duration * Speed_of_sound / 2; 

    Serial.print("DISTANCE IN CM: ");
    Serial.println(dist_in_cm);

    // Display humidity and temperature on OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.setTextColor(WHITE);

    display.println("Distance in cm: " + String(dist_in_cm));
    display.display();

    delay(500);

}