unsigned char m_RunFlags=0;
String strs;
//开机界面
void startplay() {
  // put your main code here, to run repeatedly:
  Serial.println("@FONT 0x8003,Yellow");
  Serial.println("@STR 230,90,请选择游戏模式  ");
  Serial.println("@STR 200,120,古诗文拼写  ");
  Serial.println("@STR 200,150,英语翻译对答  ");
  delay(4000);
  Serial.println("@CLR");
  
  //Serial.println("@REC 10,10,310,110");
  Serial.println("@PMODE 5,Red");
  for (i=0;i<100;i++){
    int a=5*i;
    int b=300-3*i;
    strs="@LINE "+String(a)+","+String(0)+","+String(500)+","+String(b);
    Serial.println(strs);
  }
  delay(3000);
  //Serial.println("@PMODE 1,Cyan");
  //Serial.println("@CLR");
  Serial.println("@PMODE 5,Blue");
  Serial.println("@LINE 0,0,450,260");
  Serial.println("@FONT 0x8003,Yellow");
  Serial.println("@STR 220,140,V");
  Serial.println("@STR 280,140,S");
  delay(4000);
  Serial.println("@PMODE 1,Cyan");
  Serial.println("@CLR");
}
void wordseng(){
  //Serial.println("英语翻译问答");
  unsigned short n_TempPoss,i;
  if(m_RunFlag==1)return;
  int sum=0;
  int sum1=0;
  int kcc=10;
  while(kcc>0)
  { 
    kcc=kcc-1;
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
    Serial.println("@STR 10,40,红方： ");
    Serial.println("@STR 230,40,vs");
    Serial.println("@STR 430,40,蓝方：");
    Serial.println("@STR 170,100,填写单词:"+engask[10-kcc]+",_____");
    
   //每题20秒
  int counti=20;
   while(counti>0)
   {
    counti=counti-1;
  Serial.println("@FONT 0x8003,Black");
  Serial.println("@STR 210,70,倒计时:"+String(counti/10)+String(counti%10));
  delay(1000);
  
  R=findcard(10-kcc);
  MARK=int(R/10);
  WINNER=R%10;
    if(MARK==1)
    { Serial.println("@FONT 0x8003,Green");
      Serial.println("@STR 220,150,抢答成功");
      delay(1000);
      if (WINNER==1)
      {sum=sum+1;}
      if (WINNER==2)
      {sum1=sum1+1;}
      counti=0;
    }
    Serial.println("@FONT 0x8003,Purple");
    Serial.println("@STR 10,140,红方当前分数为"+String(sum));
    Serial.println("@STR 350,140,蓝方当前分数为"+String(sum1));
  }
  Serial.println("@FONT 0x8003,Silver");
  Serial.println("@STR 170,180,正确答案是  "+engans[10-kcc]);
  Serial.println("@PMODE 1,Green");
  Serial.println("@CLR");
  Serial.println("@FONT 0x8002,White");
  Serial.println("@STR 170,180,"+engintro0[10-kcc]);
  Serial.println("@STR 170,200,"+engintro1[10-kcc]);
  Serial.println("@STR 140,220,"+engintro2[10-kcc]);
  Serial.println("@STR 150,140,"+engintro3[10-kcc]);
  delay(1000);
  } 
}
//rfid.PCD_StopCrypto1();
Serial.println("@PMODE 1,Cyan");
Serial.println("@CLR");
Serial.println("@PMODE 3,Green");
Serial.println("@LINE 235,0,235,300");
delay(3);
Serial.println("@FONT 0x8003,Red");
Serial.println("@STR 10,40,红方： ");
Serial.println("@STR 230,40,vs");
Serial.println("@STR 430,40,蓝方：");
Serial.println("@FONT 0x8003,Green");
Serial.println("@STR 180,210,"+String(sum));
Serial.println("@STR 260,210,"+String(sum1));
if(sum>sum1){
  Serial.println("@FONT 0x8001,Orange");
    Serial.println("@STR 30,240,红方获胜");
    delay(2000);
}
else if(sum==sum1){
  Serial.println("@FONT 0x8001,Orange");
    Serial.println("@STR 320,240,平局");
    Serial.println("@STR 30,240,平局");
    delay(2000);
}
else if(sum>sum1){
  Serial.println("@FONT 0x8001,Orange");
    Serial.println("@STR 320,240,蓝方获胜");
    delay(2000);
}
}
void gushiwen() {
  // 古诗文:
  unsigned short n_TempPos,i;
  if(m_RunFlag==1)return;
  //m_RunFlag=1;
  int sum=0;
  int sum1=0;
  int kcc=10;
  while(kcc>0)
  { 
    kcc=kcc-1;
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
    Serial.println("@STR 10,40,红方： ");
    Serial.println("@STR 230,40,vs");
    Serial.println("@STR 430,40,蓝方：");
    Serial.println("@STR 170,100,补全诗文:"+ask[10-kcc]+",_____");
    
    //Serial.println("@PRINTM ,0");
//  //Serial.println("@PMODE 1,Cyan"); 
//  Serial.println("@PMODE 1,Green");
//  Serial.println("@REC 10,10,470,262");
//  Serial.println("@PMODE 3,Green");
//  Serial.println("@REC 15,15,465,257");
   //每题20秒
  int counti=20;
   while(counti>0)
   {
    counti=counti-1;
  Serial.println("@FONT 0x8003,Black");
  Serial.println("@STR 210,70,倒计时:"+String(counti/10)+String(counti%10));
  delay(1000);
  //Serial.println("@CLR");
  
  R=findcard(10-kcc);
  MARK=int(R/10);
  WINNER=R%10;
  //Serial.println("**********************************");
  //Serial.println(MARK);
  //Serial.println(WINNER);
    if(MARK==1)
    { Serial.println("@FONT 0x8003,Green");
      Serial.println("@STR 220,150,抢答成功");
      delay(1000);
      if (WINNER==1)
      {sum=sum+1;}
      if (WINNER==2)
      {sum1=sum1+1;}
      counti=0;
    }
    Serial.println("@FONT 0x8003,Purple");
    Serial.println("@STR 10,140,红方当前分数为"+String(sum));
    Serial.println("@STR 350,140,蓝方当前分数为"+String(sum1));
  }
  Serial.println("@FONT 0x8003,Silver");
  Serial.println("@STR 170,180,正确答案是  "+ans[10-kcc]);
  delay(1000);
  //Serial.println("@CLR");
  //Serial.println(kcc);
  } 
}
//rfid.PCD_StopCrypto1();
Serial.println("@FONT 0x8003,Green");
Serial.println("@STR 180,210,"+String(sum));
Serial.println("@STR 260,210,"+String(sum1));
if(sum>sum1){
  Serial.println("@FONT 0x8001,Orange");
    Serial.println("@STR 30,240,红方获胜");
    delay(2000);
}
else if(sum==sum1){
  Serial.println("@FONT 0x8001,Orange");
    Serial.println("@STR 320,240,平局");
    Serial.println("@STR 30,240,平局");
    delay(2000);
}
else if(sum>sum1){
  Serial.println("@FONT 0x8001,Orange");
    Serial.println("@STR 320,240,蓝方获胜");
    delay(2000);
}
}
