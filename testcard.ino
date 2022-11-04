#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 9
#define RST_PIN 8
#define SS_PINs 3
#define RST_PINs 12

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522 rfid1(SS_PINs, RST_PINs); 
MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];
byte message[] = {0x6D,0xB5,0x19,0x2B,0x0B,0x7B,0x8D,0x85,0xD4,0xD7,0x8D,0x85};
byte answer[3][4];

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  Serial.println(F("Start--------------------"));
  pinMode(SS_PIN,OUTPUT);
  pinMode(SS_PINs,OUTPUT);
  digitalWrite(SS_PINs,HIGH);
  digitalWrite(SS_PIN,HIGH);
  for (byte i = 0; i < 3; i++) { 
  for (byte j = 0; j < 4; j++)
  {
      answer[i][j] = message[4*i+j];
    }
}
   rfid.PCD_Init();// Init MFRC522 
  rfid1.PCD_Init();
  Serial.println( ! rfid.PICC_IsNewCardPresent());
  Serial.println( ! rfid.PICC_ReadCardSerial());
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void loop() {
  delay(1000);
  digitalWrite(SS_PIN,LOW);
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  while((! rfid.PICC_IsNewCardPresent())and( ! rfid1.PICC_IsNewCardPresent()))
    return;
  Serial.println("1OK");
  while ((! rfid.PICC_ReadCardSerial())and( ! rfid1.PICC_ReadCardSerial()))
    return;
//    Serial.println ( ! rfid1.PICC_IsNewCardPresent());     //and( ! rfid1.PICC_IsNewCardPresent()))
//    return;
//  Serial.println("3OK");
 // Serial.println ( ! rfid1.PICC_ReadCardSerial());        //)and( ! rfid1.PICC_ReadCardSerial()))
//    return;
  
  Serial.println("4OK");
  Serial.println( ! rfid.PICC_IsNewCardPresent());
  Serial.println( ! rfid.PICC_ReadCardSerial());
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

//  Serial.print(F("PICC11111111111111 type: "));
//  MFRC522::PICC_Type piccType1 = rfid1.PICC_GetType(rfid1.uid.sak);
//  Serial.println(rfid1.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    
  }
//  if (piccType1 != MFRC522::PICC_TYPE_MIFARE_MINI &&  
//    piccType1 != MFRC522::PICC_TYPE_MIFARE_1K &&
//    piccType1 != MFRC522::PICC_TYPE_MIFARE_4K) {
//    Serial.println(F("Your tag is not of type MIFARE Classic."));
//    return;
//  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));
    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {   
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

  byte AS[4];
  for (byte t=0;t<4;t++){
    AS[t]=answer[0][t];
  }
  if (rfid.uid.uidByte[0] == AS[0] && 
    rfid.uid.uidByte[1] == AS[1] && 
    rfid.uid.uidByte[2] == AS[2] && 
    rfid.uid.uidByte[3] == AS[3] ){
      Serial.println("正确答案");}
  digitalWrite(SS_PIN,HIGH);
  digitalWrite(SS_PINs,LOW);
//
  if (rfid1.uid.uidByte[0] != nuidPICC[0] || 
    rfid1.uid.uidByte[1] != nuidPICC[1] || 
    rfid1.uid.uidByte[2] != nuidPICC[2] || 
    rfid1.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));
    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {   
      nuidPICC[i] = rfid1.uid.uidByte[i];
    }
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid1.uid.uidByte, rfid1.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid1.uid.uidByte, rfid1.uid.size);
    Serial.println();
  }
  else Serial.println(F("Card read previously."));

  if (rfid1.uid.uidByte[0] == AS[0] && 
    rfid1.uid.uidByte[1] == AS[1] && 
    rfid1.uid.uidByte[2] == AS[2] && 
    rfid1.uid.uidByte[3] == AS[3] ){
      Serial.println("正确答案");}
  digitalWrite(SS_PINs,HIGH);
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();


  rfid1.PICC_HaltA();

  // Stop encryption on PCD
  rfid1.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
