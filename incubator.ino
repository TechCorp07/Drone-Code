// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
// include the library code:
#include <LiquidCrystal.h>

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
// initialize the library with the numbers of the interface pins
const int rs = 8, en = 7, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() 
{
  Serial.begin(9600); 
  dht.begin();
  lcd.begin(20,4);
  
  lcd.setCursor(0,0);
  lcd.print("MICROWAVE SYSTEM");

  lcd.setCursor(0,1);
  lcd.print("FOOD PROCESSING");

  lcd.setCursor(0,2);
  lcd.print("TECHNOLOGY");

  lcd.setCursor(0,3);
  lcd.print("Capstone Project");
}

void loop() 
{
  // Wait a few seconds between measurements.
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.print("Humidity:"); 
  lcd.print("Humidity:"); 
  Serial.print(h);
  lcd.print(h);
  Serial.print(" % ");
  lcd.print(" % ");
  lcd.setCursor(0,1);
  Serial.print("Temperature: "); 
  lcd.print("Temperature:"); 
  Serial.print(t);
  lcd.print(t);
  Serial.print(" *C ");
  lcd.print(" *C ");
}
