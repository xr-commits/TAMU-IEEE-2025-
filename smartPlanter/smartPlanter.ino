#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8
#define TFT_MOSI 11  // Data out
#define TFT_SCLK 13  // Clock out
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


Adafruit_AM2320 am2320 = Adafruit_AM2320();
int waterpumpsignal = 5;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10); // hang out until serial port opens
  }
  am2320.begin();
  pinMode(waterpumpsignal, OUTPUT);
  tft.init(240, 320);    
}

void loop() {
 
  int lightVal = analogRead(A0); //light level
  int moistureVal = analogRead(A1); // moisture
  // 0-300: dry soil, 300-700 humid, 700-950 in water.
  int temp = am2320.readTemperature(); //temp
  int hum = am2320.readHumidity(); //humitity
  
  //Serial.print("temp: ");  Serial.println(temp);
  //Serial.print("Moisture: ");  Serial.println(moistureVal);
  //Serial.print("Humidity: "); Serial.println(hum);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  delay(15000);
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_BLUE);
  tft.print("Moisture: ");
  tft.println(moistureVal);

  tft.setTextColor(ST77XX_RED);
  tft.print("Temperature: ");
  tft.print(temp);
  tft.println(" Degrees C");

  tft.setTextColor(ST77XX_GREEN);
  tft.print("Humidity: ");
  tft.println(hum);

  tft.setTextColor(ST77XX_YELLOW);
  tft.print("Light Level: ");
  tft.println(lightVal);

  delay(15000);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);

  if(moistureVal <= 350)
  {
    tft.setTextSize(3);
    tft.setTextColor(ST77XX_BLUE);
    tft.print("Watering");
    digitalWrite(waterpumpsignal, HIGH); // this should turn the water pump on
    delay(10000);
    digitalWrite(waterpumpsignal, LOW); // turn off pump
  }
  else
  {
    digitalWrite(waterpumpsignal, LOW); // turn off pump
  }
}