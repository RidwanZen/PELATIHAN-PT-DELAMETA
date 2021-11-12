#include <NewPing.h>

int Flame=PA0;
int triger=PA5;
int echo=PA6;
int batas=200;

int merah=PA2;
int kuning=PA3;
int hijau=PA4;
int kunci=0;

NewPing cm(triger,echo,batas);

void setup() {
  Serial.begin(9600);
  pinMode(Flame,INPUT);
  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);

}



void loop() {
  int bacaFlame=digitalRead(Flame);
  int bacaJarak=cm.ping_cm();

  Serial.print("DATA PIR :");
  Serial.print(bacaFlame);
  Serial.print(" | DATA JARAK :");
  Serial.print(bacaJarak);
  Serial.print(" cm");
  Serial.println();

  if(bacaFlame==0 && kunci==0){
    kunci=1;
    delay(500);
  }
  else if(bacaFlame==1 && kunci==1){
    if(bacaJarak<=20 && bacaJarak!=0 && kunci==1){
      Serial.println("DEKAT");
      digitalWrite(merah,HIGH);
      digitalWrite(kuning,HIGH);
      digitalWrite(hijau,HIGH);
      delay(100);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,LOW);
      digitalWrite(hijau,LOW);
      delay(100);
    }
  else if(bacaJarak>=21 && bacaJarak<=60 && kunci==1){
      Serial.println("SEDANG");
      digitalWrite(merah,HIGH);
      digitalWrite(kuning,HIGH);
      digitalWrite(hijau,HIGH);
      delay(1000);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,LOW);
      digitalWrite(hijau,LOW);
      delay(1000);
  }
  else {
      Serial.println("JAUH");
      digitalWrite(merah,HIGH);
      digitalWrite(kuning,LOW);
      digitalWrite(hijau,LOW);
      delay(500);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,HIGH);
      digitalWrite(hijau,LOW);
      delay(500);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,LOW);
      digitalWrite(hijau,HIGH);
      delay(500);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,HIGH);
      digitalWrite(hijau,LOW);
      delay(500);
    }
  }
  else if(bacaFlame==0 && kunci==1){
    kunci=0;
    digitalWrite(merah,LOW);
    digitalWrite(kuning,LOW);
    digitalWrite(hijau,LOW);
    delay(500);
  }
  

}
