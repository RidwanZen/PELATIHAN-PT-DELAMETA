/*/
 * A9  to RX USBTTL (Serial1 TX)
 * A10 to TX USBTTL (Serial1 RX)
 * PB6 to SCL LCD   (I2C SCL)
 * PB7 to SDA LCD   (I2C SDA)
 * PB0 to RESET
 * PB1 to SDA / SS
 * PA5 to CLK
 * PA6 to MISO
 * PA7 to MOSI
 * Tekan Reset sebelum Upload
 * Pilih Board    :fake STM32F10 
 * Upload methode :Serial
 */

 //INISIALISASI
//Download Library LiquidCrystal_I2C
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN PB1
#define RST_PIN PB0

//Inisialisasi pembuatan variable
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN,RST_PIN);

void setup() {
  Serial.begin(9600); //baudrate yang digunakan untuk komunikasi microcontroller dengan komputer
  lcd.begin();
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if(!mfrc522.PICC_IsNewCardPresent()){return;}
  if(!mfrc522.PICC_ReadCardSerial()){return;}

  Serial.print("UID tag :");String content="";
  byte letter;
  for (byte i=0;i<mfrc522.uid.size;i++)
  {
    Serial.print(mfrc522.uid.uidByte[i]<0x10?"0":"");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content== "4A516EAE") //Sesuaikan dengan ID kartu anda
  {
  Serial.println("Selamat datang Ridwan Zen!!!");
  delay(100);
  lcd.clear();
  lcd.setCursor(3,0); lcd.print("BERHASIL 1");
  lcd.setCursor(1,1); lcd.print("SILAHKAN MASUK");
  delay(1000);
  }
  else if(content=="0AA89015"){
    Serial.println("Selamat datang COK!!!");
    delay(100);
    lcd.clear();
    lcd.setCursor(3,0); lcd.print("BERHASIL 2");
    lcd.setCursor(1,1); lcd.print("SILAHKAN MASUK");
    delay(1000);
  }
  else{
  Serial.println("Kartu Tidak Terdaftar!");
  lcd.clear();
  lcd.setCursor(6,0); lcd.print("MAAF");
  lcd.setCursor(3,1); lcd.print("KARTU GAGAL");
  delay(1000);
  }
 
  Serial.println("Tempelkan Kartu!");
  delay(500); //Jeda waktu perulagan seama 500 mili detik
}
