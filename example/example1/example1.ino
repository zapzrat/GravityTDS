#include <EEPROM.h>
#include "GravityTDS.h"

#define TdsSensorPin A1
GravityTDS gravityTds;

float temperature = 25, tdsValue = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Micro Project Thailand ~^.^~ ");
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);      //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024); //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();           //initialization

  pinMode(13, OUTPUT);
}


int count_c = 0;

void loop()
{
  //temperature = readTemperature();  //add your temperature sensor and read it
  gravityTds.setTemperature(temperature); // set the temperature and execute temperature compensation
  gravityTds.update();                    //sample and calculate
  tdsValue = gravityTds.getTdsValue();    // then get the value
  Serial.print(tdsValue, 0);
  Serial.println("ppm");


  if (tdsValue >= 200) {
    count_c++;
    digitalWrite(13, HIGH);
    Serial.print("count_c : "); Serial.println(count_c);
  }
  else if (tdsValue < 200) {
    digitalWrite(13, LOW);
  }

  delay(1000);
}

