//INISIALISASI
#include <NewPing.h>

int triger=PA5;
int echo=PA6;
int batas=400;

int Flame=PA0;
int PIR=PA1;
int merah=PA2;
int kuning=PA3;
int hijau=PA4;

NewPing cm(triger,echo,batas);

void setup() {
  Serial.begin(9600);
  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);

  pinMode(PIR,INPUT);
  pinMode(Flame,INPUT);
}

void loop() {
  //BACA DATA
  int bacaJarak=cm.ping_cm();
  int bacaPIR=digitalRead(PIR);
  int bacaFlame=analogRead(Flame);
      bacaFlame=map(bacaFlame,200,4095,255,0);
          
  //PRINT SERIAL
  Serial.print("DATA JARAK :");
  Serial.print(bacaJarak);
  Serial.print("cm");
  Serial.print(" | DATA PIR :");
  Serial.print(bacaPIR);
  Serial.print(" | DATA FLAME :");
  Serial.print(bacaFlame);
  Serial.println();

  //LOGIKA
  /*
  if(bacaJarak<=20 && bacaJarak!=0){
    Serial.println("BERHENTI");
    digitalWrite(hijau,LOW);
    digitalWrite(kuning,LOW);
    digitalWrite(merah,HIGH);
    delay(100);
    digitalWrite(merah,LOW);
    delay(100);
  }
  else if(bacaJarak >=21 && bacaJarak <=70){
    Serial.println("HATI HATI");
    digitalWrite(hijau,LOW);
    digitalWrite(merah,LOW);
    digitalWrite(kuning,HIGH);
    delay(1000);
    digitalWrite(kuning,LOW);
    delay(1000);
  }else{
    Serial.println("KOSONG");
    digitalWrite(merah,LOW);
    digitalWrite(kuning,LOW);
    digitalWrite(hijau,HIGH);
    
  }
  */
}
