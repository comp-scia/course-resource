/*
* Required Libraries:
* - "LiquidCrystal" : Standard Arduino-AdaFruit Library
* - "DHT Sensor Library" : https://github.com/adafruit/DHT-sensor-library
*/

// LCD Display (PIN)(LCD1602 Module)
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  
// DHT-11 Temperature and Humidity Sensor
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Message constants
#define ERROR_MSG "SENSOR ERROR"
#define TEMP_MSG "Temp(F): "
#define HUMID_MSG "Humid: "

void setup() {
    // Serial Monitor
    Serial.begin(9600);
    // LCD Display (16x2)
    lcd.begin(16, 2);

    for(int i = 0; i < 4; i += 1) { 
        lcd.clear();
        lcd.setCursor(i, 0);
        lcd.print("Welcome to");
        delay(150);
    }
    lcd.setCursor(1,1);
    lcd.print("Thermostat 1.0");
    Serial.println("   Welcome to   ");
    Serial.println(" Thermostat 1.0 \n");
    delay(5000);

    lcd.clear();

    dht.begin();
    delay(1500);
}


void loop() {
    // Farenheit Temp and Humidity (g/cm^3)
    float temp = dht.readTemperature(true);
    float humid = dht.readHumidity();

    if (isnan(humid) && temp) {
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print(ERROR_MSG);
        Serial.print("  ");
        Serial.println(ERROR_MSG);
        delay(1000);
        return;
    }

    // LCD Display (Temp and Humidity)
    lcd.setCursor(0,0);
    lcd.print(TEMP_MSG);
    lcd.print(temp);

    lcd.setCursor(0,1);
    lcd.print(HUMID_MSG);
    lcd.print(humid);

    // Serial Monitor Output
    Serial.print(TEMP_MSG);
    Serial.println(temp);

    Serial.print(HUMID_MSG);
    Serial.println(humid);

    delay(2000);
}
