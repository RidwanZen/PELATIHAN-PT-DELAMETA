//INISIALISASI
#include <NewPing.h>

int triger=PA5;
int echo=PA6;
int batas=400;

int merah=PA2;
int kuning=PA3;
int hijau=PA4;

NewPing cm(triger,echo,batas);

void setup() {
  Serial.begin(9600);
  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaJarak=cm.ping_cm();
      
  //PRINT SERIAL
  Serial.print("DATA JARAK :");
  Serial.print(bacaJarak);
  Serial.print(" cm");
  Serial.println();

  //LOGIKA
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
}
