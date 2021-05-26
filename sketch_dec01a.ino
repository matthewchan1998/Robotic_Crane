#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BTserial(2,3);
const long BTbaudRate = 9600;
Servo rotational_servo_left;
Servo string_servo_left;
int fsrAnalogPin=1;
double fsrReading;
int StringMotor=0;
int RotateMotor=0;
int i;
int val;
int irpinP=A0;;

void setup() {
  rotational_servo_left.attach(13);
  rotational_servo_left.write(90);
  delay(100);
  string_servo_left.attach(12);
  string_servo_left.write(90);
  delay(1000);
  Serial.begin(9600);
  BTserial.begin(BTbaudRate);
  BTserial.print("AT");
  delay(2000);
  pinMode(irpinP,OUTPUT);
  if(BTserial.available()>0)
  {
    while(BTserial.available()>0)
    {
      char c=BTserial.read();
      Serial.write(c);
    }
  }
  BTserial.print("AT+NAMETeam_3");
  delay(2000);
  if(BTserial.available()>0)
  {
    while(BTserial.available()>0)
    {
      char c=BTserial.read();
      Serial.write(c);
    }
  }
  BTserial.print("AT+PIN1234");
  delay(2000);
  if(BTserial.available()>0)
  {
     while(BTserial.available()>0)
    {
      char c=BTserial.read();
      Serial.write(c);
    }
  }
}

void loop() {
  int ok;
  ok=1;
  
  char input;
  int PlatDist,i0;
  fsrReading=100*analogRead(fsrAnalogPin);
  i0=analogRead(0);
  PlatDist=i0;
//  BTserial.println("PlatDist=");
//  BTserial.println(PlatDist);
//  BTserial.println("FSR=");
//  BTserial.println(fsrReading);
//  delay(200);

    if(PlatDist>15)
        ok=0;
    else ok=1;
  
  delay(500);

  int value;
  if(BTserial.available()>0)
  {
       input=BTserial.read();
       if(input=='p')
       {
          StringMotor=0;
          RotateMotor=0;
          BTserial.println("pause");
       }
       if(input=='q')
       {
            StringMotor=0;
            RotateMotor=-1;          
       }
       if(input=='e')
       {
            StringMotor=0;
            RotateMotor=1;
       }
       if(input=='w')
       {
            StringMotor=1;
            RotateMotor=0;
       }
       if(input=='s')
       {
          StringMotor=-1;
          RotateMotor=0;
       }
  }
  
  delay(100);
  
  if(RotateMotor>0)
  {
   if(ok==1)
        string_servo_left.write(92);
  }
  else
  {
    if(RotateMotor<0)
    {
      if(ok==1)
        string_servo_left.write(88);
    }
    else
    {
      string_servo_left.write(90);
    }
  }
  if(StringMotor>0)
  {
    if(fsrReading<30000 && fsrReading>=0)
    {
      
      rotational_servo_left.write(100);
      BTserial.println(fsrReading);
    }
  }
  else
  {
    if(StringMotor<0)
    {
      if(fsrReading<30000 && fsrReading>=0)
      {
        
        rotational_servo_left.write(80);
        BTserial.println(fsrReading);
      }
    }
    else
    {
      rotational_servo_left.write(90);
    }
  }
    delay(100);
  }
