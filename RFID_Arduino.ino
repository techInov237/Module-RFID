#include <SPI.h>
#include <MFRC522.h>


#define RST_PIN 9
#define SS_PIN 10
MFRC522 module_rfid(SS_PIN, RST_PIN);

int buzzer = 7;
int led_rouge = 6;
int led_verte = 3;


void setup() {
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(buzzer, OUTPUT);
  SPI.begin();
  module_rfid.PCD_Init();
  Serial.begin(9600);
}

void loop() {
  
  if ( ! module_rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! module_rfid.PICC_ReadCardSerial()) 
  {
    return;
  }

  String UID = "";

  for (byte i = 0; i < module_rfid.uid.size; i++) {
    UID.concat(String(module_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UID.concat(String(module_rfid.uid.uidByte[i], HEX));
  }

  UID.toUpperCase();

  if (UID.substring(1) == "39 41 B1 B3") 
  {
    Serial.println("ACCES AUTORISE");
    digitalWrite(led_verte, HIGH);
    tone(buzzer, 200, 750);
    delay(125);
    tone(buzzer, 200, 750);
    delay(2000);
    digitalWrite(led_verte, LOW);
   
  }

  else {
    Serial.println("ACCES REFUSE");
    digitalWrite(led_rouge, HIGH);
    tone(buzzer, 200, 750);
    delay(2000);
    digitalWrite(led_rouge, LOW);
    
  }
}
