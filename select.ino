

//开机界面
void startplay() {  
  String strs;
  Serial.println("@FONT 0x8003,Yellow");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 230,90,请选择游戏模式  ");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 200,120,古诗文拼写  ");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 200,150,英语翻译对答  ");
  delay(4000);
  Serial.println("@CLR");
  
  Serial.println("@PMODE 5,Red");
  for (byte i=0;i<100;i++){
    int a=5*i;
    int b=300-3*i;
    strs="@LINE "+String(a)+","+String(0)+","+String(500)+","+String(b);
    Serial.println(strs);
  }
  delay(3000);
  Serial.println("@PMODE 5,Blue");
  Serial.println("@LINE 0,0,450,260");
  Serial.println("@FONT 0x8003,Yellow");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 220,140,V");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 280,140,S");
  delay(4000);
  Serial.println("@PMODE 1,Cyan");
  Serial.println("@CLR");
}

byte nuidPICC[4];
//寻卡函数
int findcard(int numid,int s) {
int res;
int flag=0;
int winner=0;
digitalWrite(SS_PIN,LOW);
byte answer[40]={0xBA,0x34,0x67,0x9F,0x6A,0x44,0x66,0x9F,0x2A,0xBC,0x6E,0x9F,0x4A,0xD3,0x0F,0x9F,0xEA,0xF5,0x13,0x9F,0x2A,0x4D,0x10,0x9F,0x0A,0xE4,0x23,0x9F,0x7A,0xCC,0x17,0x9F,0x1A,0x98,0x11,0x9F,0x9A,0xC4,0x11,0x9F};
byte answer1[40]={0x8A,0xB4,0x22,0x9F,0x1A,0xAC,0x21,0x9F,0xAA,0x61,0x18,0x9F,0xDA,0x95,0x18,0x9F,0xAA,0xE8,0x12,0x9F,0x5A,0x40,0x1E,0x9F,0x7A,0x99,0x16,0x9F,0xBA,0xF1,0x14,0x9F,0x6A,0x48,0x66,0x9F,0x8A,0xDB,0x71,0x9F};
byte answer2[40]={0x0A,0xA3,0xBA,0x9E,0x3A,0x92,0x11,0x9F,0x1A,0xF6,0x19,0x9F,0x9A,0x63,0x1C,0x9F,0xEA,0x99,0x1E,0x9F,0x9A,0xAF,0x1B,0x9F,0xAA,0xA5,0x15,0x9F,0x4A,0x7B,0x1D,0x9F,0xBA,0x99,0x19,0x9F,0xEA,0xFD,0x14,0x9F};
byte answer3[40]={0x4A,0x6E,0xCB,0x9E,0xBA,0x07,0x66,0x9F,0x5A,0xC5,0x72,0x9F,0x5A,0x7B,0x65,0x9F,0xCA,0xEE,0x6C,0x9F,0x7A,0x6F,0x70,0x9F,0xDA,0x15,0x6E,0x9F,0x6A,0x40,0x6D,0x9F,0x5A,0xD3,0x69,0x9F,0xDA,0x0D,0xCC,0x9E};

  while((! rfid.PICC_IsNewCardPresent())and( ! rfid1.PICC_IsNewCardPresent()))
    return;
  Serial.println("1OK");
  while ((! rfid.PICC_ReadCardSerial())and( ! rfid1.PICC_ReadCardSerial()))
    return;
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  //MFRC522::PICC_Type piccType1 = rfid1.PICC_GetType(rfid1.uid.sak);
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
  Serial.println(F("A card has been detected."));
  
  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {   
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
  }
  else
  {delay(300);}
  
  byte AS[4];
  if(s==0){
  for (byte t=0;t<4;t++){
    AS[t]=answer[4*numid+t];
  }
  }
  else{
    for (byte t=0;t<4;t++){
    AS[t]=answer2[4*numid+t];
  }
  }
  if (rfid.uid.uidByte[0] == AS[0] && 
    rfid.uid.uidByte[1] == AS[1] && 
    rfid.uid.uidByte[2] == AS[2] && 
    rfid.uid.uidByte[3] == AS[3] ){
      Serial.println("@FONT 0x8003,Red");
      Serial.println("@FMODE 1,Lime");
        Serial.println("@STR 20,120,红方正确答案");
        delay(1000);
      flag=1;
      winner=1;}

   digitalWrite(SS_PIN,HIGH);
   digitalWrite(SS_PINs,LOW);
   if (rfid1.uid.uidByte[0] != nuidPICC[0] || 
    rfid1.uid.uidByte[1] != nuidPICC[1] || 
    rfid1.uid.uidByte[2] != nuidPICC[2] || 
    rfid1.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {   
      nuidPICC[i] = rfid1.uid.uidByte[i];
    }
  }
  else
  {delay(300);}
     
  byte AS1[4];
  if(s==0){
  for (byte t=0;t<4;t++){
    AS1[t]=answer1[4*numid+t];
  }
  }
  if(s==1){
    for (byte t=0;t<4;t++){
    AS1[t]=answer3[4*numid+t];
  }
  }
  if (rfid1.uid.uidByte[0] == AS1[0] && 
    rfid1.uid.uidByte[1] == AS1[1] && 
    rfid1.uid.uidByte[2] == AS1[2] && 
    rfid1.uid.uidByte[3] == AS1[3]){
        Serial.println("@FONT 0x8003,Red");
        Serial.println("@FMODE 1,Lime");
        Serial.println("@STR 360,120,蓝方正确答案");
        delay(1000);
      flag=1;
      winner=2;}
  digitalWrite(SS_PINs,HIGH);
  // Halt PICC
  res=10*flag+winner;
  // Halt PICC
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  rfid1.PICC_HaltA();
  // Stop encryption on PCD  
  rfid1.PCD_StopCrypto1();
  return res;}

  
void wordseng(){
  //英文问答
  int val,MARK,WINNER,x;
  String strs;
String engask[10]={"燕子","黄鼠狼","鳗鱼","螳螂","蜻蜓","蟋蟀","牡蛎","鳄鱼","海狸","蝴蝶"};
String engans[10]={"swallow","weasel","eel","mantis","dragonfly","cricket","oyster","crocodile","beaver","butterfly"};
String engintro0[10]={"swallow /ˈswɒləʊ /","weasel /ˈwiːzl /","eel / iːl /",
                      "mantis /ˈmæntɪs /","dragonfly /ˈdræɡənflaɪ /","cricket /ˈkrɪkɪt /",
                      "oyster /ˈɔɪstə(r) /","crocodile /ˈkrɒkədaɪl /","Beaver /ˈbiːvə(r)/",
                       "butterfly /ˈbʌtəflaɪ /"};
String engintro1[10]={"燕子","黄鼠狼","鳗鱼","螳螂","蜻蜓","蟋蟀","牡蛎","鳄鱼","海狸","蝴蝶"};
String engintro2[10]={"One swallow does not make a spring",
                       "When the weasel and the cat make a marriage, it is very ill presage.",
                       "That man can not be trusted. He is as slippery as an eel",
                       "Mantis arm when the car, do not measure their own strength",
                       "Dragonflies fly low. Get ready for raincoats.",
                       "Children are as merry as a cricket at Christmas.",  
                       "You can trust him with everything. He is as dumb as an oyster",
                       "The poor are homeless and the rich cry crocodile tears",                     
                       "He is working so hard that he is as busy as a beaver",
                       "I only ask you to lend me one dollar，Please do not break a butterfly on the wheel."};
String engintro3[10]={"孤燕不报春，表示凡事不能只凭一个例子下结论。","黄鼠狼和猫结亲，不是好事情.",
                       "那个人不可信，他非常油滑。（英语常用鳗鱼比喻油滑）",
                       "螳臂当车，自不量力。",
                       "蜻蜓飞得低，快快备雨衣。",
                       "圣诞节的时候，孩子们非常高兴。（英语常用蟋蟀比喻开心）",
                       "你可以信任他任何事，他是一个守口如瓶的人。\n (英语常用牡蛎比喻守口如瓶的人）",
                       "穷人们无家可归，富人们留下鳄鱼的眼泪。\n（英语常用鳄鱼的眼泪比喻假慈悲）",
                       "他没日没夜地工作，忙得团团转。（英语常用海狸比喻忙碌）",
                       "我只要你借给我一美元，请不要小题大做。"};
  //Serial.println("英语翻译问答");
  int sum=0;
  int sum1=0;
  int kcc=10;
  while(kcc>0)
  { 
  int R;
    val=digitalRead(inpin);    
    Serial.println(val);    
  if(val==LOW)
  {
  delay(3);
  Serial.println("@PMODE 3,Green");
  Serial.println("@LINE 235,0,235,300");
  delay(5);
  }
  else{
    Serial.println("@PMODE 1,Cyan");
    Serial.println("@CLR");
    Serial.println("@PMODE 3,Green");
    Serial.println("@LINE 235,0,235,300");
    delay(3);
    Serial.println("@FONT 0x8003,Red");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 10,40,红方： ");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 230,40,vs");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 430,40,蓝方：");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 170,100,填写单词:"+engask[10-kcc]+",_____");
    
   //每题20秒
  int counti=20;
   while(counti>0)
   {
    counti=counti-1;
  Serial.println("@FONT 0x8003,Black");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 210,70,倒计时:"+String(counti/10)+String(counti%10));
  delay(1000);
  
  R=findcard(10-kcc,1);
  MARK=int(R/10);
  WINNER=R%10;
    if(MARK==1)
    { Serial.println("@FONT 0x8003,Green");
      Serial.println("@FMODE 1,Cyan");
      Serial.println("@STR 220,150,抢答成功");
      delay(1000);
      if (WINNER==1)
      {sum=sum+1;}
      if (WINNER==2)
      {sum1=sum1+1;}
      counti=0;
    }
    Serial.println("@FONT 0x8003,Purple");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 10,140,红方当前分数为"+String(sum));
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 350,140,蓝方当前分数为"+String(sum1));
  }
  Serial.println("@FONT 0x8003,Blue");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 170,180,正确答案是  "+engans[10-kcc]);
  Serial.println("@PMODE 1,Green");
  Serial.println("@CLR");
  Serial.println("@FONT 0x8002,Red");
  Serial.println("@FMODE 1,Green");
  Serial.println("@STR 160,180,"+engintro0[10-kcc]);
  Serial.println("@FMODE 1,Green");
  Serial.println("@STR 160,200,"+engintro1[10-kcc]);
  Serial.println("@FMODE 1,Green");
  Serial.println("@STR 140,220,"+engintro2[10-kcc]);
  Serial.println("@FMODE 1,Green");
  Serial.println("@STR 150,240,"+engintro3[10-kcc]);
  delay(3000);
  } 
  kcc=kcc-1;
}
//rfid.PCD_StopCrypto1();
Serial.println("@PMODE 1,Cyan");
Serial.println("@CLR");
Serial.println("@PMODE 3,Green");
Serial.println("@LINE 235,0,235,300");
delay(3);
Serial.println("@FONT 0x8003,Red");
Serial.println("@FMODE 1,Cyan");
Serial.println("@STR 10,40,红方： ");
Serial.println("@FMODE 1,Cyan");
Serial.println("@STR 230,40,vs");
Serial.println("@FMODE 1,Cyan");
Serial.println("@STR 430,40,蓝方：");
Serial.println("@FONT 0x8003,Green");
Serial.println("@FMODE 1,Cyan");
Serial.println("@STR 180,210,"+String(sum));
Serial.println("@FMODE 1,Cyan");
Serial.println("@STR 260,210,"+String(sum1));
if(sum>sum1){
  Serial.println("@FONT 0x8001,Orange");
  Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 30,240,红方获胜");
    delay(2000);
}
else if(sum==sum1){
  Serial.println("@FONT 0x8001,Orange");
  Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 320,240,平局");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 30,240,平局");
    delay(2000);
}
else if(sum>sum1){
  Serial.println("@FONT 0x8001,Orange");
  Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 320,240,蓝方获胜");
    delay(2000);
}
}


void gushiwen() {
  int val,MARK,WINNER,x;
 String strs;
 String ask[10]={"相顾无相识","大漠孤烟直","仍怜故乡水","采菊东篱下","烽火连三月","攀条折其荣","岂不罹凝寒","八方各异气","海内存知己","坐观垂钓者"};
 String ans[10]={"长歌怀采薇","长河落日圆","万里送行舟","悠然见南山","家书抵万金","将以遗所思","岂不罹凝寒","松柏有本性","天涯若比邻","徒有羡鱼情"};
  // 古诗文:
  unsigned short n_TempPos,i;
  //m_RunFlag=1;
  int sum=0;
  int sum1=0;
  int kcc=10;
  while(kcc>0)
  { 
  int R;
    val=digitalRead(inpin);
    
    Serial.println(val);
    
  if(val==LOW)
  {
  //Serial.println("@PRINTM 0");
  //Serial.println("@PMODE 1,Cyan"); 
  delay(3);
  //Serial.println("@PMODE 1,Cyan");
  //Serial.println("@CLR");
  Serial.println("@PMODE 3,Green");
  Serial.println("@LINE 235,0,235,300");
  delay(3);
  //Serial.println("@CLR");
  delay(5);
  }
  else{
    Serial.println("@PMODE 1,Cyan");
    Serial.println("@CLR");
    Serial.println("@PMODE 3,Green");
    Serial.println("@LINE 235,0,235,300");
    delay(3);
    Serial.println("@FONT 0x8003,Red");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 10,40,红方： ");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 230,40,vs");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 430,40,蓝方：");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 170,100,补全诗文:"+ask[10-kcc]+",_____");
    
   //每题20秒
  int counti=20;
   while(counti>0)
   {
    counti=counti-1;
  Serial.println("@FONT 0x8003,Black");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 210,70,倒计时:"+String(counti/10)+String(counti%10));
  delay(1000);
  
  R=findcard(10-kcc,0);
  MARK=int(R/10);
  WINNER=R%10;
    if(MARK==1)
    { Serial.println("@FONT 0x8003,Green");
      Serial.println("@FMODE 1,Cyan");
      Serial.println("@STR 220,150,抢答成功");
      delay(1000);
      if (WINNER==1)
      {sum=sum+1;}
      if (WINNER==2)
      {sum1=sum1+1;}
      counti=0;
    }
    Serial.println("@FONT 0x8003,Purple");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 10,140,红方当前分数为"+String(sum));
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 350,140,蓝方当前分数为"+String(sum1));
  }
  Serial.println("@FONT 0x8003,Silver");
  Serial.println("@FMODE 1,Cyan");
  Serial.println("@STR 170,180,正确答案是  "+ans[10-kcc]);
  delay(1000);
  } 
  kcc=kcc-1;
}
//rfid.PCD_StopCrypto1();
Serial.println("@FONT 0x8003,Green");
Serial.println("@FMODE 1,Cyan");
Serial.println("@STR 180,210,"+String(sum));
Serial.println("@FMODE 1,Cyan");
Serial.println("@STR 260,210,"+String(sum1));
if(sum>sum1){
  Serial.println("@FONT 0x8001,Orange");
  Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 30,240,红方获胜");
    delay(2000);
}
else if(sum==sum1){
  Serial.println("@FONT 0x8001,Orange");
  Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 320,240,平局");
    Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 30,240,平局");
    delay(2000);
}
else if(sum>sum1){
  Serial.println("@FONT 0x8001,Orange");
  Serial.println("@FMODE 1,Cyan");
    Serial.println("@STR 320,240,蓝方获胜");
    delay(2000);
}
}
