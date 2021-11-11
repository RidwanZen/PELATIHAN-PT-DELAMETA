#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

int triger=3;
int echo=2;
int batas=400;
int LDR =A0;

NewPing cm(triger,echo,batas);
//Inisialisasi pembuatan variable
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  Serial.begin(9600);
  lcd.begin();
  //lcd.clear();
  //lcd.setCursor(4,0); lcd.print("SENSOR");
  //lcd.setCursor(2,1); lcd.print("ULTRASONIK");
  //delay(500);
}

void loop(){
  int bacaJarak=cm.ping_cm();
  int bacaLDR=analogRead(LDR);
      bacaLDR=map(bacaLDR,12,1020,0,255);
      
  //PRINT SERIAL
  Serial.print("DATA JARAK :");
  Serial.print(bacaJarak);
  Serial.print(" cm");
  Serial.print(" | NILAI LDR :");
  Serial.print(bacaLDR);
  Serial.println();  

  //PRINT TO LCD
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("DATA JARAK:");
  lcd.print(bacaJarak);
  lcd.print("cm");
  lcd.setCursor(0,1); lcd.print("DATA LDR  :");
  lcd.print(bacaLDR);
  delay(1000);
  
}
