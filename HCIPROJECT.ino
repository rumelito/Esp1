#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "PLDTHOMEFIBRw6trb"
#define WIFI_PASSWORD "Hanzhixiu_10"
#define API_KEY "AIzaSyCNf8M15wonHCYJp8cXTpLZjrjFoRxI1jI" 
#define DATABASE_URL "https://apps-esp32-ecd10-default-rtdb.firebaseio.com/" 

#define irSensor 23 // Pin for the IR sensor
#define btn 19      // Button pin
#define buzzer 18   // Buzzer pin

Adafruit_SSD1306 display(128, 64, &Wire, -1);

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int value = 0;
unsigned long sendDataPrevMillis = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Firebase authentication
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase Sign Up Successful");
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectWiFi(true);
  config.timeout.serverResponse = 10 * 1000;

  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);

  pinMode(irSensor, INPUT);
  pinMode(btn, INPUT);
  pinMode(buzzer, OUTPUT);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println("Can't initialize display!");
  }
}

void loop() {
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 100)) { // Update every second

    // Check for Firebase reset command
    checkFirebaseReset();

    // Check button press for resetting the count
    if (digitalRead(btn) == HIGH) {
      value=0;
      resetCount(); // Reset the count
      
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }

    // Read IR sensor value
    int irvalue = digitalRead(irSensor);
    if (irvalue == LOW) { // If IR sensor is triggered
      value++;  // Increment the count
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }

    // Print/Display sensor values to the Serial Monitor
    Serial.print("COUNT: ");
    Serial.println(value); 
  
    // Display count on OLED
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.setTextColor(WHITE);
    display.println("Count: " + String(value));
    display.display();

    // Update Firebase with the current count
    if (Firebase.RTDB.setInt(&fbdo, F("Count"), value)) {
      Serial.println("Count updated successfully.");
    } else {
      Serial.printf("Error updating count: %s\n", fbdo.errorReason().c_str());
    }

    sendDataPrevMillis = millis(); // Update the previous millis
  }
}

void resetCount() {
  value = 0;  // Reset the count
  Serial.println("Count reset to 0");
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.setTextColor(WHITE);
  display.println("Count: 0");
  display.display();
}

void checkFirebaseReset() {
  // Check for reset command from Firebase
  if (Firebase.RTDB.getInt(&fbdo, F("reset"))) {
    if (fbdo.dataType() == "int" && fbdo.intData() == 1) {
      resetCount(); // Reset the count if reset command is received
      Firebase.RTDB.setInt(&fbdo, F("reset"), 0); // Clear the reset command
    }
  }
}