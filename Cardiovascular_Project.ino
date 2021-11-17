//Including Libraries
#include <LiquidCrystal_I2C.h>
#include <MPU6050_tockn.h>
#include <Adafruit_MLX90614.h>
#include <GSMSim.h> 
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9,10);
char msg;
char call;
int buttonpin=12;

//Declaring ECG pins
int ecgPin1 = 5;
int ecgPin2 = 6;

//Defining Global Variables
LiquidCrystal_I2C lcd(0x3F, 16, 2);//Defining LCD address
MPU6050 mpu6050(Wire);
GSMSim gsm;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


void setup() {
  pinMode(ecgPin1,INPUT);
  pinMode(ecgPin2,INPUT);
  pinMode(buttonpin,INPUT);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module
  Serial.begin(9600);//Turning on serial port
  Wire.begin();
  mpu6050.begin();// initialize the MPU6050
  mpu6050.calcGyroOffsets(true);  
  lcd.begin();// initialize the LCD   
  lcd.backlight();// Turn on the blacklight
  mlx.begin();// initialize the Temperature sensor
  
}

void loop() {
 Serial.println(" ");
lcd.clear();
if (mlx.readObjectTempC() >= 36.1 && mlx.readObjectTempC() <= 38.2){
  Serial.println("Body Temp is Normal");
  lcd.print("Temp is Normal");
  Serial.println(mlx.readObjectTempC());
  lcd.setCursor(0,1);
  lcd.print(mlx.readObjectTempC());
  lcd.print("*C");
  }
else if (mlx.readObjectTempC() > 38.2){
  Serial.println("Body Temp High!");
  lcd.print("Temp is High!");
  Serial.println(mlx.readObjectTempC());
  lcd.setCursor(0,1);
  lcd.print(mlx.readObjectTempC());
  lcd.print("*C");
  }
else {
  Serial.println("Body Temp is Low!");
  lcd.print("Temp is Low!");
  Serial.println(mlx.readObjectTempC());
  lcd.setCursor(0,1);
  lcd.print(mlx.readObjectTempC());
  lcd.print("*C");
  }
delay(5000);
lcd.clear();
if(mpu6050.getAccAngleX() > 0.0 && mpu6050.getAccAngleX() < 30.0 || mpu6050.getAccAngleY() > 0.0 && mpu6050.getAccAngleY() < 30. 
||  mpu6050.getAccAngleX() < -0.0 && mpu6050.getAccAngleX() > -30.0 || mpu6050.getAccAngleY() <= -0.0 && mpu6050.getAccAngleY() > -30.){
  mpu6050.update();
  Serial.println("Standing");
  Serial.print(mpu6050.getAccAngleX());
  Serial.print(",");
  Serial.println(mpu6050.getAccAngleY());
  lcd.print("Standing");
  delay(250);
  lcd.clear();
   mpu6050.update();
  Serial.println("Standing");
  Serial.print(mpu6050.getAccAngleX());
  Serial.print(",");
  Serial.println(mpu6050.getAccAngleY());
  lcd.print("Standing");
  delay(250);
  lcd.clear();
   mpu6050.update();
  Serial.println("Standing");
  Serial.print(mpu6050.getAccAngleX());
  Serial.print(",");
  Serial.println(mpu6050.getAccAngleY());
  lcd.print("Standing");
  }
 else{
  mpu6050.update();
  Serial.print("Lying Down");
  Serial.print(mpu6050.getAccAngleX());
  Serial.print(",");
  Serial.println(mpu6050.getAccAngleY());
  lcd.print("Lying Down");
delay(250);
lcd.clear();
  mpu6050.update();
  Serial.print("Lying Down");
  Serial.print(mpu6050.getAccAngleX());
  Serial.print(",");
  Serial.println(mpu6050.getAccAngleY());
  lcd.print("Lying Down");
delay(250);
lcd.clear();
  mpu6050.update();
  Serial.print("Lying Down");
  Serial.print(mpu6050.getAngleX());
  Serial.print(",");
  Serial.println(mpu6050.getAngleY());
  lcd.print("Lying Down");
  }
 delay(5000);
lcd.clear();
if((digitalRead(ecgPin1)==1)||(digitalRead(ecgPin2)==1)){
      Serial.println("No ECG Signal!");
      lcd.setCursor(0,0);
      lcd.print("No ECG Signal! ");
      
  }
  else{
      Serial.print("Heart Rate: ");
      Serial.println(analogRead(A0));
      lcd.setCursor(0,0);
      lcd.print("Heart Rate: ");
      lcd.setCursor(0,1);
      lcd.print(analogRead(A0));
  }
  delay(5000);
  if(mlx.readObjectTempC() < 36.0)
  {
    
    Serial.println("Emergency!");
    delay(2000);
    SendMessage();  
  }

 if (mySerial.available()>0)
 Serial.write(mySerial.read());
}
