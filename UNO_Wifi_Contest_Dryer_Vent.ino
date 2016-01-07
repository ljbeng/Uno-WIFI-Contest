
/*
by Luke Barker

This is a project for the UNO Wifi Contest that circulates heat from a running 
clothes dryer into the house when the humidity of the hot air is below a set value.
This project uses an UNO, at TMP36 temperature sensor, an HIH-5030-001 Humidity 
sensor, a servo, a potentiometer and a Dryer Vent Heat Deflector 
similar to: http://www.acehardware.com/product/index.jsp?productId=1273159&KPID=964390&pla=pla_964390
An Electric Imp was also used to log data to data.sparkfun.com through the home WIFI. 
The temperature and humidity can then be viewed and graphed on a web page developed 
for the Electric Imp.

These dryer vent heat deflectors work by deflecting the heat from a dryer during 
winter months into the house. The problem is it's not a good idea to deflect the heat 
into the house if the humidity of the air is high. This project keeps the door of the 
vent closed until both the temperature is >100 and the humidity is < a set point. 
The set point is a potentiometer but could be set from the Electric Imp web page as well.
Here is a video of the servo moving the door open and closed: https://youtu.be/COTz70SJQqE
 */

#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;  // create servo object to control the servo that opens the door

SoftwareSerial mySerial(10, 11); // RX, TX

int HumsensorPin = A0;  // select the input pin for the Humidity Sensor
int TempsensorPin = A1; // select the input pin for the TMP36 Temperature sensor
int HumSettingPin = A2; // select the input pin for the potentiometer
int RoomTempPin = A3;

int led = 13;      // select the pin for the LED

float TempF = 0;
float Humidity = 0;
float RoomTemp = 0;

int HumSetting = 0;
int HumAnalogIn = 0;
int TempAnalogIn = 0; 
int RoomTempAnalogIn = 0;
int TriggerHum = 0;
float TempTrigger = 100;
int ServoLoc = 90;
int OpenLoc = 30;
int CloseLoc = 90;
int cnt = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
float temp,voltage;

  // read the value from the temperature sensor:
  TempAnalogIn = analogRead(TempsensorPin);
  // read the value from the humidity sensor:
  HumAnalogIn = analogRead(HumsensorPin);
  RoomTempAnalogIn = analogRead(RoomTempPin);

  
  //convert the analog to temperature and humidity
  temp = (float)TempAnalogIn * 5.0 / 1024.0;
  TempF = (temp - 0.5) * 180  + 32;
  
  temp = (float)RoomTempAnalogIn * 5.0 / 1024.0;
  RoomTemp = (temp - 0.5) * 180  + 32;
  
  voltage = (float)HumAnalogIn * 5.0 / 1024.0;
  Humidity = 161.0 * voltage / 5.0 - 25.8;
  
  //the potentiometer is scaled to 20% to 80% humidity range
  HumSetting = map(analogRead(HumSettingPin),0,1023,20,80); 

  //logic to open or close the door based on Temperature and Humidity of the air
  if (TriggerHum == 0 && TempF >= TempTrigger){
      TriggerHum = 1;
  }
  if (TriggerHum == 1 && Humidity < HumSetting){
      ServoLoc = OpenLoc;
      digitalWrite(led, HIGH);
  }
  if (TriggerHum == 1 && Humidity > (HumSetting + 5)){
      ServoLoc = CloseLoc;
      digitalWrite(led, LOW);
  }
  if (TempF < TempTrigger){
      ServoLoc = CloseLoc;
      TriggerHum = 0;
  }

  myservo.write(ServoLoc);
  delay(100);
  cnt++;
  
  if (cnt >= 20){//every 2 seconds send the data to the Electric Imp.
    //This should be replaced with an UNO Wifi board... :)
    cnt = 0;
    mySerial.print(TempF);
    mySerial.print(",");
    mySerial.print(RoomTemp);
    mySerial.print(",");
    mySerial.print(Humidity);
    mySerial.print(",");
    mySerial.print(ServoLoc);
    mySerial.print(';');
  }
}
