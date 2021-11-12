//INISIALISASI
int PIR=PA1;
int merah=PA2;
int kuning=PA3;
int hijau=PA4;

void setup() {
  Serial.begin(9600);
  pinMode(PIR,INPUT);
  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);
}

void loop() {
  //BACA DATA
  int bacaPIR=digitalRead(PIR);
      
  //PRINT SERIAL
  Serial.print("DATA PIR :");
  Serial.print(bacaPIR);
  Serial.println();

  //LOGIKA
  if(bacaPIR==1){
    Serial.println("ADA ORANG");
    digitalWrite(merah,HIGH);
    delay(100);
    digitalWrite(merah,LOW);
    delay(100);
  }
  else{
    Serial.println("KOSONG");
    digitalWrite(merah,LOW);
    
  }
}
