#include "Wire.h" // This library allows you to communicate with I2C devices.

#include <Adafruit_BMP085.h> //需要下载库
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
int ledpin=10;//相当于开关，继电器
int ledpin1=7;//氧气开关
int ledpin2=13;//指示灯开关
int ledpin3=9;//气压模拟开关
Adafruit_BMP085 bmp;
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
     Serial.println("Could not find a valid BMP085 sensor, check wiring!");
     //while (1) {}
   }
  Wire.begin();
  pinMode(ledpin,OUTPUT);
  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  digitalWrite(ledpin1,LOW);
  pinMode(ledpin3,INPUT);
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
int pressval() {
  //digitalWrite(ledpin2,LOW);
  Serial.print("Temperature = "); 
  Serial.print(bmp.readTemperature()); // 输出温度
  Serial.println(" *C");

  Serial.print("Pressure = "); 
  Serial.print(bmp.readPressure()); // 输出气压
  Serial.println(" Pa");
  //if (bmp.readPressure()<101510)
  //{digitalWrite(ledpin1,HIGH);//开
   //delay(3000);
   //digitalWrite(ledpin1,LOW); //关
   //delay(1000);}

  Serial.print("Altitude = "); 
  Serial.print(bmp.readAltitude()); // 输出海拔
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = "); 
  Serial.print(bmp.readSealevelPressure()); //输出密封面的压力(计算后)
  Serial.println(" Pa");

  Serial.print("Real altitude = "); 
  Serial.print(bmp.readAltitude(101500)); // 输出通过指定海平面气压值计算的实际高度 
  Serial.println(" meters");

  Serial.println();
  delay(500);
  return bmp.readSealevelPressure();
 }
void loop() {
  digitalWrite(ledpin2,HIGH);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  
  // print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();
  //条件判断
  //digitalWrite(ledpin1,HIGH);
  int16_t height;
  height=pressval();
  Serial.print(" | Height = "); //Serial.print(gyro_x>-500);
  Serial.println();
  Serial.println();
  
  //az:16000
  
  if (digitalRead(ledpin3)){
    digitalWrite(ledpin1,HIGH);
    Serial.println("空难!!!");
    if(gyro_x>-500){
    if(accelerometer_y>10000){
      if(accelerometer_z>-16000){
        Serial.println("OPEN!!!");
        Serial.println();
        digitalWrite(ledpin2,LOW); //关
        delay(1000);
        digitalWrite(ledpin,HIGH);//开
        delay(3000);
        digitalWrite(ledpin,LOW); //关
        delay(1000);
      }
    }
  }
  }
  else{
    digitalWrite(ledpin1,LOW);
  }
  //if(height<=30000){
    //Serial.println("HEllo world");
    //digitalWrite(ledpin,HIGH);  //开
    //delay(1000);
    //digitalWrite(ledpin,LOW);  //关
    //delay(1000);
  //}
  
  // delay
  delay(1000);
}