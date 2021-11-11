//INISIALISASI
int LDR=PA4;
int merah=PA1;
int kuning=PA2;
int hijau=PA3;



void setup() {
  Serial.begin(9600);
  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);

}

void loop() {
  //BACA DATA
  int bacaLDR=analogRead(LDR);
      //bacaLDR=map(bacaLDR,0,4095,255,0);

  //SERIAL PRINT
  Serial.print("DATA LDR :");
  Serial.print(bacaLDR);
  
  Serial.println();

  analogWrite(merah,bacaLDR);
}
