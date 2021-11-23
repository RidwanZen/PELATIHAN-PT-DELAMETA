#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
#include "SoftwareSerial.h"
#include <PubSubClient.h>


char ssid[] = "delameta";            // your network SSID (name)
char pass[] = "bilano1407";        // your network password
int status = WL_IDLE_STATUS; // the Wifi radio's status
unsigned long lastSend;

// Initialize the Ethernet client object
WiFiEspClient espClient;
PubSubClient client(espClient);

SoftwareSerial Serialx(2,3); // RX, TX   //ESP8266 RX,TX connected to these pins

int merah=5;
int kuning=6;
int hijau=7;
int Flame=A0;
int LDR=A1;

void setup() {
// initialize serial for debugging
Serial.begin(115200);
// initialize serial for ESP module
Serialx.begin(9600);
// initialize ESP module
WiFi.init(&Serialx);
pinMode(merah,OUTPUT);
pinMode(kuning,OUTPUT);
pinMode(hijau,OUTPUT);


// check for the presence of the shield
if (WiFi.status() == WL_NO_SHIELD) {
Serial.println("WiFi shield not present");
// don't continue
while (true);
}

// attempt to connect to WiFi network
while ( status != WL_CONNECTED) {
Serial.print("Attempting to connect to WPA SSID: ");
Serial.println(ssid);
// Connect to WPA/WPA2 network
status = WiFi.begin(ssid, pass);
lastSend = 0;
}

// you're connected now, so print out the data
Serial.println("You're connected to the network");

//connect to MQTT server
client.setServer("broker.hivemq.com", 1883);
client.setCallback(callback);
}

//print any message received for subscribed topic
void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("Pesan diterima [");
  Serial.print(topic);
  Serial.println("] ");
  //==============================================================
  if (strcmp(topic, "zen69/lampu1") == 0) //Membandingkan 2 buah String
  { 
    for (int i=0;i<length;i++) {
    char receivedChar = (char)payload[i];
    if (receivedChar == "on"){
       //Jalankan Perintah1
       Serial.println("LAMPU MERAH ON");
       digitalWrite(merah,HIGH);
    }
    if (receivedChar == "off"){
       //Jalankan Perintah0
       Serial.println("LAMPU MERAH OFF");
       digitalWrite(merah,LOW);
    }
  }
  }
  //==============================================================

  else if (strcmp(topic, "zen69/lampu2") == 0) //Membandingkan 2 buah String
  { 
    for (int i=0;i<length;i++) {
    char receivedChar = (char)payload[i];
    if (receivedChar == '1'){
       //Jalankan Perintah1
       Serial.println("LAMPU KUNING ON");
       digitalWrite(kuning,HIGH);
    }
    if (receivedChar == '0'){
       //Jalankan Perintah0
       Serial.println("LAMPU KUNING OFF");
       digitalWrite(kuning,LOW);
    }
  }
  }
  //==============================================================

  else if (strcmp(topic, "zen69/lampu3") == 0) //Membandingkan 2 buah String
  { 
    for (int i=0;i<length;i++) {
    char receivedChar = (char)payload[i];
    if (receivedChar == 'on'){
       //Jalankan Perintah1
       Serial.println("LAMPU HIJAU ON");
       digitalWrite(hijau,HIGH);
    }
    if (receivedChar == 'off'){
       //Jalankan Perintah0
       Serial.println("LAMPU HIJAU OFF");
       digitalWrite(hijau,LOW);
    }
  }
  }
  //==============================================================
}

void pushdata(){
  //Ambil Data / Baca Sensor
  char msgBuffer[20];
  //int datax=random(10,100);
  int dataFlame=analogRead(Flame);
      dataFlame=map(dataFlame,1024,0,0,100);
  int dataLDR=analogRead(LDR);
      dataLDR=map(dataLDR,900,70,100,0);
      
  
  //POST TO SERIAL
  Serial.print("Sensor Flame :");Serial.print(dataFlame);
  Serial.print(" | Sensor LDR :");Serial.print(dataLDR);
  Serial.println();
  
  //POST TO MQTT
  //client.publish("zen69/datax", dtostrf(datax, 6, 2, msgBuffer)); //Convert to String 
  client.publish("zen69/dataFlame", String(dataFlame).c_str()); //Convert to String
  client.publish("zen69/dataLDR", String(dataLDR).c_str());
}

void loop() {
// put your main code here, to run repeatedly:
if (!client.connected()) {
reconnect();
}
if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
    pushdata();
    lastSend = millis();
 }
client.loop();
}

void reconnect() {
// Loop until we're reconnected
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
// Attempt to connect, just a name to identify the client
if (client.connect("zen69")) {
Serial.println("connected");

//client.publish("outpic","Hello World");
client.subscribe("zen69/lampu1",0);
client.subscribe("zen69/lampu2",0);
client.subscribe("zen69/lampu3",0);

} else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
}
}
}
