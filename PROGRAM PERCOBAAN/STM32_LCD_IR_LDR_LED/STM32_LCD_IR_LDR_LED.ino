#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//INISIALISASI
int LDR=PA5;
int IR=PA4;
int merah=PA1;
int kuning=PA2;
int hijau=PA3;

int kunci=0;

void setup() {
  Serial.begin(9600); 
  lcd.begin();
  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);

  pinMode(IR,INPUT);
}

void loop() {
  int bacaIR=digitalRead(IR);
  int bacaLDR=analogRead(LDR);
      bacaLDR=map(bacaLDR,0,4095,0,100);

  //lcd.clear();
  //lcd.setCursor(0,0); lcd.print("DATA IR :");
  //lcd.print(bacaIR);
  //delay(500);

  //LOGIKA
  if(bacaIR==0 && kunci==0){  //JIKA LEWAT LDR AKTIF
    kunci=1;
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("DATA IR :");
    lcd.print(bacaIR);
    delay(200);
  }
  else if(bacaIR==1 && kunci==1){ //AKTIF SETELAH LEWAT SENSOR IR
    if(bacaLDR<=30 && kunci==1){  //LAMPU HIJAU MENYALA SAAT TERANG
      digitalWrite(hijau,HIGH);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,LOW);
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("DATA LDR :");
      lcd.print(bacaLDR);
      lcd.setCursor(0,1); lcd.print("LAMPU HIJAU");
      delay(2000);
      
    }else if(bacaLDR>=31 && bacaLDR<=60 && kunci==1){ //LAMPU KUNING MENYALA SAAT SETENGAH GELAP
      digitalWrite(hijau,LOW);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,HIGH);
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("DATA LDR :");
      lcd.print(bacaLDR);
      lcd.setCursor(0,1); lcd.print("LAMPU KUNING");
      delay(2000);
      
    }else if(bacaLDR>=61 or bacaLDR==100 && kunci==1){  //LAMPU MERAH MENYALA SAAT GELAP
      digitalWrite(hijau,LOW);
      digitalWrite(merah,HIGH);
      digitalWrite(kuning,LOW);
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("DATA LDR :");
      lcd.print(bacaLDR);
      lcd.setCursor(0,1); lcd.print("LAMPU MERAH");
      delay(2000);
    }
  }
  else if(bacaIR==0 && kunci==1){ //LDR&LED MATI SAAT LEWAT SENSOR IR LAGI
    kunci=0;
    digitalWrite(hijau,LOW);
    digitalWrite(merah,LOW);
    digitalWrite(kuning,LOW);
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("DATA LDR :");
    lcd.print(bacaLDR);
    lcd.setCursor(0,1); lcd.print("LAMPU MATI");
    delay(2000);
  }
  else{
    
  }
  

}
