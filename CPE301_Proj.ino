#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11

#define ENABLE 8
#define DIRA 9

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht (DHTPIN, DHT11); 

int resval = 0;  
int respin = A5; 
  
void setup() { 
  dht.begin();
  lcd.begin(16, 2);

  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  Serial.begin(9600);
} 
  
void loop() { 
  float humi = dht.readHumidity();
  float tempC = dht.readTemperature();
  
  lcd.clear();
  if (isnan(humi) || isnan(tempC)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    lcd.setCursor(0, 0); 
    lcd.print("Temp:");
    lcd.print(tempC);     
    lcd.print((char)223); 
    lcd.print("C");

    lcd.setCursor(0, 1);  
    lcd.print("Humi:");
    lcd.print(humi);    
    lcd.print("%");
  }

  if (tempC >= 23.5){
  digitalWrite(ENABLE, HIGH);
  digitalWrite(DIRA, HIGH);
  }
  else{
    digitalWrite(ENABLE, LOW);  
  }
  
  lcd.setCursor(12, 1); 
  resval = analogRead(respin); 
  if (resval<=195){ lcd.println("EMPT"); 
  } 
  else if (resval>195 && resval<=270){ lcd.println(" LOW"); 
  } 
  else if (resval>270 && resval<=310){ lcd.println(" MED"); 
  } else if (resval>310){ 
    lcd.println("HIGH"); 
  }
  delay(1000); 
}
