#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//nano
RF24 radio(6,7);
const int buzzer = 3;
//uno
//RF24 radio(7,8);
//pro mini
//RF24 radio(3,7);
const byte address_trans[6] = "10002";
const byte address_recieve[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0,address_recieve);
  radio.openWritingPipe(address_trans);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  Serial.begin(9600);
}

void loop() {
  char text[32] = "";
  const char ifAvail[] = "in Range";
  Serial.println("ssup");
  delay(5);
  radio.startListening();
  delay(50);
  if (radio.available()) {
    radio.read(&text, sizeof(text));
    String transData = String(text);
    Serial.println(transData);
    if (transData == "nrftest") {
        digitalWrite(buzzer,HIGH);
        delay(5000);
        digitalWrite(buzzer,LOW);
      }    
  }
  else if(!radio.available())
    Serial.println("No signal");
  delay(5);
  radio.stopListening();
  radio.write(&ifAvail, sizeof(ifAvail));
  delay(50);
  }
