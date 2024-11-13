#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define DHT_PIN 4
#define DHT_TYPE DHT22
#define tempred 34
#define humidgreen 35


DHT dht (DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(128,64,&Wire,-1)
void setup() {
  
  Serial.begin(9600);
  dht.begin();
  delay(2000);
  if(!display.begin(SSD1306_SWITCHCAPVCC)){
    Serial.println("CANT READ DETAILS");
  }
 
}

void loop() {
 float humid = dht.readHumidity();
 float temp = dht.readTempreture();

 Serial.println("HUMINIDITY");
 Serial.println(humid);
 Serial.println("TEMPRETURE");
 Serial.println( temp);
 delay(1000);

if(temp >= 30){
  digitalWrite;(tempred,HIGH)

}else{
   digitalWrite;(tempred,LOW)

}
if(humid <= 50){
  digitalWrite;(humidgreen,HIGH)

}else{
   digitalWrite;(humidgreen,LOW)

}



}