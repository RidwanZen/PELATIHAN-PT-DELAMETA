/*/DATA PIN
 * A9  to RX USBTTL (Serial1 TX)
 * A10 to TX USBTTL (Serial1 RX)
 * PB6 to SCL LCD   (I2C SCL)
 * PB7 to SDA LCD   (I2C SDA)
 * PB0 to RESET (RFID)
 * PB1 to SDA / SS  (RFID)
 * PA5 to CLK (RFID)
 * PA6 to MISO  (RFID)
 * PA7 to MOSI  (RFID)
 * PA0 SERVO
 * PA1 LED MERAH
 * PA2 LED KUNING
 * PA3 LED HIJAU
 * PA4 SENSOR IR
 * Tekan Reset sebelum Upload
 * Pilih Board    :fake STM32F10 
 * Upload methode :Serial
 */

 //INISIALISASI
#include <LiquidCrystal_I2C.h>  //LIBRARY LCD
#include <SPI.h>
#include <MFRC522.h>  //LIBRARY RFID
#include <Servo.h>  //LIBRARY SERVO
#define SS_PIN PB1
#define RST_PIN PB0 //SEBAGAI RESET

//Inisialisasi pembuatan variable
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD
MFRC522 mfrc522(SS_PIN,RST_PIN);    //RFID
int outServo=PA0; //PIN SERVO
int merah=PA1;    //PIN LED MERAH
int kuning=PA2;   //PIN LED KUNING
int hijau=PA3;    //PIN LED HIJAU
int IR=PA4;       //PIN SENSOR IR
int kunci=0;   //Variable Pengunci Kondisi Awal 0
String uidString;  //Variable untuk ID RFID
Servo myservo;    //Variable Servo

void setup() {
  Serial.begin(9600); //baudrate yang digunakan untuk komunikasi microcontroller dengan komputer
  lcd.begin();
  SPI.begin();
  mfrc522.PCD_Init();
  myservo.attach(outServo);

  pinMode(merah,OUTPUT);
  pinMode(kuning,OUTPUT);
  pinMode(hijau,OUTPUT);
  pinMode(IR,INPUT);

  lcd.clear();
  lcd.setCursor(1,0); lcd.print("TEMPELKAN KARTU");
  digitalWrite(merah,HIGH);
  myservo.write(0);
  delay(1000);
}

void berhasil(){  //Void aktif Jika Kartu Terdaftar
  Serial.println("Selamat datang Ridwan Zen!!!");
  Serial.println("Silahkan Masuk!!");
  kunci=1;
  lcd.clear();
  lcd.setCursor(1,0); lcd.print("PALANG DIBUKA");
  lcd.setCursor(1,1); lcd.print("SILAHKAN MASUK");
  digitalWrite(merah,LOW);
  delay(500);
  digitalWrite(hijau,HIGH);
  myservo.write(90);
  delay(3000);
}
void gagal(){   //Void aktif Jika Kartu Tidak terdaftar
  Serial.println("Kartu Tidak Terdaftar!");
  kunci=0;
  digitalWrite(merah,LOW);
  delay(200);
  digitalWrite(merah,HIGH);
  lcd.clear();
  lcd.setCursor(6,0); lcd.print("MAAF");
  lcd.setCursor(3,1); lcd.print("KARTU GAGAL");
  delay(1000);
  Serial.println("Tempelkan Kartu!!");
  lcd.clear();
  lcd.setCursor(1,0); lcd.print("TEMPELKAN KARTU");
  delay(1000);
  
}

void readRFID(){  //PEMBACAAN DATA ID CARD
  mfrc522.PICC_ReadCardSerial();
  //Pembatas bisa dirubah sesuai keinginan, disini yang digunakan "-"
  uidString = String(mfrc522.uid.uidByte[0],HEX) + "-" +
              String(mfrc522.uid.uidByte[1],HEX) + "-" +
              String(mfrc522.uid.uidByte[2],HEX) + "-" +
              String(mfrc522.uid.uidByte[3],HEX);
              uidString.toUpperCase();
}
void loop() {
  //BACA DATA
  int bacaIR=digitalRead(IR);
  
  //LOGIKA BACA KARTU
  if (mfrc522.PICC_IsNewCardPresent() && kunci==0){
    readRFID();
    Serial.print("Tag UID: ");
    Serial.println(uidString);
    if(uidString=="4A-51-6E-AE"){ // Sesuaikan dengan ID Kartu 1
      berhasil();
    }
    else if(uidString=="4-11-75-42"){ // Sesuaikan dengan ID Kartu 2
      berhasil();
    }
    else{
      Serial.println("GAGAL");
      gagal();
    }
  }

  //LOGIKA PENUTUP PALANG
  else if(bacaIR==0 && kunci==1){
    kunci=0;
    Serial.println("PALANG DITUTUP");
    lcd.clear();
    lcd.setCursor(1,0); lcd.print("PALANG DITUTUP");
    digitalWrite(hijau,LOW);
    digitalWrite(kuning,HIGH);
    delay(500);
    myservo.write(0);
    delay(2000);
    digitalWrite(kuning,LOW);
    digitalWrite(merah,HIGH);
    Serial.println("Tempelkan Kartu!!");
    lcd.clear();
    lcd.setCursor(1,0); lcd.print("TEMPELKAN KARTU");
    delay(1000);
  }
  else{
    
  }
}
