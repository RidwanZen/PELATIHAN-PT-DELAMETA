//INISIALISASI
int IR=PA4;
int merah=PA1;
int kuning=PA2;
int hijau=PA3;
int kunci=0;


void setup() {
  Serial.begin(9600);
  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);

  pinMode(IR,INPUT);
}

void loop() {
  //BACA DATA
  int bacaIR=digitalRead(IR);

  //SERIAL PRINT
  Serial.print("DATA IR :");
  Serial.print(bacaIR);
  Serial.println();

  if(bacaIR==0 && kunci==0){
    digitalWrite(merah,LOW);
    digitalWrite(kuning,HIGH);
    kunci=1;
    delay(500);
  }else if(bacaIR==0 && kunci==1){
    digitalWrite(merah,HIGH);
    digitalWrite(kuning,LOW);
    kunci=0;
    delay(500);
  }
}
