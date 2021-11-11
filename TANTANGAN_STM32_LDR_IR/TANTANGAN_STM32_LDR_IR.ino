//INISIALISASI
int LDR=PA5;
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
  int bacaLDR=analogRead(LDR);
      bacaLDR=map(bacaLDR,0,4095,0,100);

  int bacaIR=digitalRead(IR);

  //print serial
  Serial.print("DATA IR :");
  Serial.print(bacaIR);
  Serial.print(" | DATA LDR :");
  Serial.print(bacaLDR);
  Serial.println();
  
  //LOGIKA
  if(bacaIR==0 && kunci==0){  //JIKA LEWAT LDR AKTIF
    kunci=1;
    delay(100);
  }
  else if(bacaIR==1 && kunci==1){ //AKTIF SETELAH LEWAT SENSOR IR
    if(bacaLDR<=30 && kunci==1){  //LAMPU HIJAU MENYALA SAAT TERANG
      digitalWrite(hijau,HIGH);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,LOW);
    }else if(bacaLDR>=31 && bacaLDR<=60 && kunci==1){ //LAMPU KUNING MENYALA SAAT SETENGAH GELAP
      digitalWrite(hijau,LOW);
      digitalWrite(merah,LOW);
      digitalWrite(kuning,HIGH);
    }else if(bacaLDR>=61 or bacaLDR==100 && kunci==1){  //LAMPU MERAH MENYALA SAAT GELAP
      digitalWrite(hijau,LOW);
      digitalWrite(merah,HIGH);
      digitalWrite(kuning,LOW);
    }
  }
  else if(bacaIR==0 && kunci==1){ //LDR&LED MATI SAAT LEWAT SENSOR IR LAGI
    kunci=0;
    digitalWrite(hijau,LOW);
    digitalWrite(merah,LOW);
    digitalWrite(kuning,LOW);
    delay(500);
  }
  else{
    
  }

}
