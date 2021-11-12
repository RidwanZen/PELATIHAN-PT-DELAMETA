//INISIALISASI
int Flame=PA0;
int merah=PA2;
int kuning=PA3;
int hijau=PA4;

void setup() {
  Serial.begin(9600);
  pinMode(Flame,INPUT);
  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaFlame=analogRead(Flame);
      bacaFlame=map(bacaFlame,200,4095,255,0);
      
  //PRINT SERIAL
  Serial.print("DATA FLAME :");
  Serial.print(bacaFlame);
  Serial.println();

  //LOGIKA
  if(bacaFlame==0 && bacaFlame<=50){
    Serial.println("AMAN");
    digitalWrite(merah,LOW);
    digitalWrite(kuning,LOW);
    digitalWrite(hijau,HIGH);
  }
  else if(bacaFlame<=51 && bacaFlame<=150){
    Serial.println("HATI-HATI");
    digitalWrite(merah,LOW);
    digitalWrite(kuning,HIGH);
    digitalWrite(hijau,LOW);
  }
  else{
    Serial.println("BAHAYA");
    digitalWrite(merah,HIGH);
    digitalWrite(kuning,LOW);
    digitalWrite(hijau,LOW);
  }
}
