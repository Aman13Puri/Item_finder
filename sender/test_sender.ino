#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<SoftwareSerial.h>

 
SoftwareSerial bt(0,1);
RF24 radio(7,8);

const byte address_trans[6] = "00001";
const byte address_recieve[6] = "00002";
const int button = 2;
const int lost_led = 4;
void setup() {
  radio.begin();
  pinMode(lost_led,OUTPUT);
  pinMode(button,INPUT);
  Serial.begin(9600);
  radio.openWritingPipe(address_trans);
  radio.openReadingPipe(0,address_recieve);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  bt.begin(9600);
}

void loop() {
  delay(5);
  radio.stopListening();
  //Serial.println("stopped LIs");
  //delay(2000);
  const char text[] = "nrftest";
  char ifAvail[32] = ""; 
  String input;
    
    if (bt.available()) 
{      input=bt.readString();
      Serial.println("keys");
      delay(200);
} 
  while(digitalRead(2) == 1 || input == "keys")
  { //delay(2000);
    Serial.println("Sending");
    radio.write(&text, sizeof(text));
    input="Null";
    delay(500);
  }
  
  delay(5);
  radio.startListening();
  if (radio.available()) {
    digitalWrite(lost_led,LOW);
    radio.read(&ifAvail, sizeof(ifAvail));
    String transData = String(ifAvail);
    if (transData == "in Range") {
        Serial.println(transData);
        delay(1000);
    }    
  }
  else if (!radio.available()){
    digitalWrite(lost_led,HIGH);
    Serial.println("not in range");
    delay(3000);
  }  
}
