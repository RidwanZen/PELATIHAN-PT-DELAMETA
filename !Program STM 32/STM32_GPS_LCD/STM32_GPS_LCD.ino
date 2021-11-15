/*/
 * A9  to RX USBTTL (Serial TX)
 * A10 to TX USBTTL (Serial1 RX)
 * A2  to RX GPS  (Serial2 TX)
 * A3  to TX GPS  (Serial2 RX)
 * PB6 to SCL LCD   (I2C SCL)
 * PB7 to SDA LCD   (I2C SDA)
 * Tekan Reset sebelum Upload
 * Pilih Board    :fake STM32F10 
 * Upload methode :Serial
 */
 
#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>

int GPSBaud = 9600;

//Inisialisasi pembuatan variable
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Create a TinyGPS++ object
TinyGPSPlus gps;
String latitude, longitude,km_ph;

void setup()
{
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);

  // Start the software serial port at the GPS's default baud
  Serial2.begin(GPSBaud);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(5,0); lcd.print("GPS");
  delay(1000);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    lcd.clear();
    lcd.setCursor(1,0); lcd.print("NO GPS DETECTED");
    delay(1000);
    while(true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    latitude = String(gps.location.lat(),6);
    longitude = String(gps.location.lng(),6);
    km_ph = String(gps.speed.kmph());
    String link = "www.google.com/maps/place/" + String(latitude) + "," + String(longitude) + " | " + String(km_ph) ;
    Serial.println(link);
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    //PRINT SERIAL
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
    
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  //PRINT LCD TANGGAL
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("Tgl:");
    lcd.print(gps.date.day());
    lcd.print("/");
    lcd.print(gps.date.month());
    lcd.print("/");
    lcd.print(gps.date.year());
    //PRINT LCD JAM
    lcd.setCursor(0,1); lcd.print("Jam:");
    lcd.print(gps.time.hour());
    lcd.print(":");
    lcd.print(gps.time.minute());
    lcd.print(":");
    lcd.print(gps.time.second());
    lcd.print(".");
    lcd.print(gps.time.centisecond());
    delay(1000);
}
