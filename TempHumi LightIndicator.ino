#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>  

#define DHT_PIN 2
#define DHT_TYPE DHT11

#define GREEN 18 // Green LED pin for humidity
#define RED 19   // Red LED pin for temperature

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(2000);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println("Can't initialize display!");
  }

  // Set LED pins as output
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  
  // Turn off LEDs initially
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
}

void loop() {
  float humid = dht.readHumidity();
  float tempre = dht.readTemperature();

  // Print/Display sensor values to the Serial Monitor
  Serial.print("HUMIDITY: ");
  Serial.println(humid);
  Serial.print("TEMPERATURE: ");
  Serial.println(tempre);
  
  // Control LEDs based on humidity and temperature
  if (humid > 70) {
    digitalWrite(GREEN, HIGH); // Turn on green LED
    delay(250); // Blink delay
    digitalWrite(GREEN, LOW);  // Turn off green LED
    delay(250);
  } else {
    digitalWrite(GREEN, LOW);  // Ensure green LED is off
  }

  if (tempre > 30) {
    digitalWrite(RED, HIGH);   // Turn on red LED
    delay(250); 
    digitalWrite(RED, LOW);    // Turn off red LED
    delay(250); 
  } else {
    digitalWrite(RED, LOW);    // Ensure red LED is off
  }

  // Display humidity and temperature on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.setTextColor(WHITE);

  display.println("Humidity: " + String(humid) + "%");
  display.println("Temperature: " + String(tempre) + "C");
  display.display();

  // Delay between readings
  delay(500);
}
