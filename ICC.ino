int inpin=7;
int selpin=6;//功能选择开关
int val,MARK,WINNER;
int x,i,j;
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];
//正确卡号
byte message[] = {0x6D,0xB5,0x19,0x2B,0x0B,0x7B,0x8D,0x85,0xD4,0xD7,0x8D,0x85};
byte message1[] = {0x6D,0xB5,0x19,0x2B,0x0B,0x7B,0x8D,0x85,0xD4,0xD7,0x8D,0x85};
byte answer[10][4];
byte answer1[10][4];

byte engmessage[] = {0x6D,0xB5,0x19,0x2B,0x0B,0x7B,0x8D,0x85,0xD4,0xD7,0x8D,0x85};
byte engmessage1[] = {0x6D,0xB5,0x19,0x2B,0x0B,0x7B,0x8D,0x85,0xD4,0xD7,0x8D,0x85};


String ask[10]={"相顾无相识","大漠孤烟直","仍怜故乡水","采菊东篱下","烽火连三月","攀条折其荣","岂不罹凝寒","八方各异气","海内存知己","坐观垂钓者"};
String ans[10]={"长歌怀采薇","长河落日圆","万里送行舟","悠然见南山","家书抵万金","将以遗所思","岂不罹凝寒","松柏有本性","天涯若比邻","徒有羡鱼情"};
//问题和答案
//英文问答
String engask[10]={"燕子","黄鼠狼","鳗鱼","螳螂","蜻蜓","蟋蟀","牡蛎","鳄鱼","海狸","蝴蝶"};
String engans[10]={"swallow","weasel","eel","mantis","dragonfly","cricket","oyster","crocodile","beaver","butterfly"};
String engintro0[10]={"swallow /ˈswɒləʊ /","weasel /ˈwiːzl /","eel / iːl /",
                      "mantis /ˈmæntɪs /","dragonfly /ˈdræɡənflaɪ /","cricket /ˈkrɪkɪt /",
                      "oyster /ˈɔɪstə(r) /","crocodile /ˈkrɒkədaɪl /","Beaver /ˈbiːvə(r)/",
                       "butterfly /ˈbʌtəflaɪ /"};
String engintro1[10]={"燕子","黄鼠狼","鳗鱼","螳螂","蜻蜓","蟋蟀","牡蛎","鳄鱼","海狸","蝴蝶"};
String engintro2[10]={"One swallow does not make a spring",
                       "When the weasel and the cat make a marriage, it is very ill presage.",
                       "That man can"t be trusted. He"s as slippery as an eel",
                       "Mantis arm when the car, do not measure their own strength",
                       "Dragonflies fly low. Get ready for raincoats.",
                       "Children are as merry as a cricket at Christmas.",  
                       "You can trust him with everything. He is as dumb as an oyster",
                       "The poor are homeless and the rich cry crocodile tears",                     
                       "He is working so hard that he is as busy as a beaver",
                       "I only ask you to lend me one dollar，Please do not break a butterfly on the wheel."};
String engintro3[10]={"孤燕不报春，表示凡事不能只凭一个例子下结论。",
                       "黄鼠狼和猫结亲，不是好事情.",
                       "那个人不可信，他非常油滑。（英语常用鳗鱼比喻油滑）",
                       "螳臂当车，自不量力。",
                       "蜻蜓飞得低，快快备雨衣。",
                       "圣诞节的时候，孩子们非常高兴。（英语常用蟋蟀比喻开心）",
                       "你可以信任他任何事，他是一个守口如瓶的人。\n (英语常用牡蛎比喻守口如瓶的人）",
                       "穷人们无家可归，富人们留下鳄鱼的眼泪。\n（英语常用鳄鱼的眼泪比喻假慈悲）",
                       "他没日没夜地工作，忙得团团转。（英语常用海狸比喻忙碌）",
                       "我只要你借给我一美元，请不要小题大做。"};
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
  Serial.println("@STR 10,140,VS竞技学习机");
  
  delay(1000);
  Serial.println("@CLR");
  Serial.println("@FONT 0x8003,Red");
  Serial.println("@STR 10,140,VS开机成功");
  delay(1000);
  Serial.println("@CLR");
  startplay();
  
  SPI.begin(); // Init SPI bus
  //Serial.println("@FONT 0x8003,Red\r@STR 10,140, Start--------------------");
  
  for (byte i = 0; i < 10; i++) { 
  for (byte j = 0; j < 4; j++)
  {
      answer[i][j] = message[4*i+j];
    }
} 
  for (byte i = 0; i < 10; i++) { 
  for (byte j = 0; j < 4; j++)
  {
      answer1[i][j] = message1[4*i+j];
    }
}
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

//  Serial.println("@FONT 0x8003,Red");
//  Serial.println("@STR 10,140, This code scan the MIFARE Classsic NUID.");
//  Serial.print("@FONT 0x8003,Red");
//  Serial.print("@STR 40,140,  Using the following key:");
//  Serial.println("@CLR");
  //printHex(key.keyByte, MFRC522::MF_KEY_SIZE); 
}
//寻卡函数
int findcard(int numid) {
  int res;
  int flag=0;
  int winner=0;
  if ( ! rfid.PICC_IsNewCardPresent())
    {//Serial.println("could not find");
    return 0;}

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    {//Serial.println("could not find");
    return 0;}
//  Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
//    Serial.println(rfid.PICC_ReadCardSerial());
//    Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.

//  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
//  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
//    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {   
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
//    Serial.println(F("The NUID tag is:"));
//    Serial.print(F("In hex: "));
//    printHex(rfid.uid.uidByte, rfid.uid.size);
//    Serial.println();
//    Serial.print(F("In dec: "));
//    printDec(rfid.uid.uidByte, rfid.uid.size);
//    Serial.println();
  }
  else
  {delay(300);}
 //Serial.println(F("Card read previously."));
  byte AS[4];
  for (byte t=0;t<4;t++){
    AS[t]=answer[numid][t];
  }
  if (rfid.uid.uidByte[0] == AS[0] && 
    rfid.uid.uidByte[1] == AS[1] && 
    rfid.uid.uidByte[2] == AS[2] && 
    rfid.uid.uidByte[3] == AS[3] ){
      Serial.println("@FONT 0x8003,Red");
        Serial.println("@STR 20,120,红方正确答案");
        delay(1000);
      flag=1;
      winner=1;}
  byte AS1[4];
  for (byte t=0;t<4;t++){
    AS1[t]=answer1[numid][t];
  }
  if (rfid.uid.uidByte[0] == AS1[0] && 
    rfid.uid.uidByte[1] == AS1[1] && 
    rfid.uid.uidByte[2] == AS1[2] && 
    rfid.uid.uidByte[3] == AS1[3] ){
        Serial.println("@FONT 0x8003,Red");
        Serial.println("@STR 360,120,蓝方正确答案");
        delay(1000);
      flag=1;
      winner=2;}

  // Halt PICC
  res=10*flag+winner;
  
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  //Serial.println(res);
  return res;}


unsigned char m_RunFlag=0; 
void loop() {//选择功能模式
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
  Serial.println("@STR 230,130,game over");
  delay(1000);
  }
  else
  { 
    
  for (byte i = 0; i < 10; i++) { 
  for (byte j = 0; j < 4; j++)
  {
      answer[i][j] = engmessage[4*i+j];
    }
} 
  for (byte i = 0; i < 10; i++) { 
  for (byte j = 0; j < 4; j++)
  {
      answer1[i][j] = engmessage1[4*i+j];
    }
}

    Serial.println("@PMODE 1,Cyan");
    Serial.println("@CLR");
    Serial.println("@PMODE 3,Black");
    Serial.println("@REC 10,10,450,260");
    delay(5000);
    wordseng();
    Serial.println("@PMODE 1,Cyan");
    Serial.println("@CLR");
  Serial.println("@FONT 0x8003,Red");
  Serial.println("@STR 230,130,game over");
  delay(1000);}
  
}
