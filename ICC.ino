#define inpin 7
#define selpin 6  //功能选择开关

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
//正确卡号
 
void setup() 
{ // put your setup code here, to runonce: 
  Serial.begin(9600); 
  //delay(3000);
  Serial.println("@PRINTM 0");
  //开始清屏
  Serial.println("@PMODE 1,Cyan");
  Serial.println("@CLR");
  //清屏结束
  delay(2000);
  pinMode(inpin,INPUT_PULLUP);
  pinMode(selpin,INPUT);
  Serial.println("@FONT 0x8003,Red");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 10,140,VS竞技学习机");
  
  delay(1000);
  Serial.println("@CLR");
  Serial.println("@FONT 0x8003,Red");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 10,140,VS开机成功");
  delay(1000);
  Serial.println("@CLR");
  startplay();
  
  SPI.begin(); // Init SPI bus
  pinMode(SS_PIN,OUTPUT);
  pinMode(SS_PINs,OUTPUT);
  digitalWrite(SS_PINs,HIGH);
  digitalWrite(SS_PIN,HIGH);
  rfid.PCD_Init(); // Init MFRC522
  rfid1.PCD_Init();
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

}

void loop() {//选择功能模式
  int val;
  val=digitalRead(selpin);
  if(val){
    Serial.println("@PMODE 1,Cyan");
    Serial.println("@CLR");
    Serial.println("@PMODE 3,Black");
    Serial.println("@REC 10,10,450,260");
    delay(5000);
    //Serial.println("gushiwen");
  gushiwen();
  Serial.println("@PMODE 1,Cyan");
    Serial.println("@CLR");
  Serial.println("@FONT 0x8003,Red");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 230,130,game over");
  delay(3000);
  }
  else
  { 
    Serial.println("@PMODE 1,Cyan");
    Serial.println("@CLR");
    Serial.println("@PMODE 3,Black");
    Serial.println("@REC 10,10,450,260");
    delay(5000);
    wordseng();
    Serial.println("@PMODE 1,Cyan");
    Serial.println("@CLR");
  Serial.println("@FONT 0x8003,Red");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 230,130,game over");
  delay(3000);}
  
}
