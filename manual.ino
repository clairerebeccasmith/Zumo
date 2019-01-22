/*-----libraries-----*/
#include <Wire.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

/*-----motion global variables-----*/
#define NORMAL_SPEED      150
#define REVERSE_SPEED     50
#define TURN_SPEED        100
#define REVERSE_DURATION  200
#define TURN_DURATION     150
#define TRIGGER_PIN
#define ECHO_PIN

/*-----hardware declarations-----*/
ZumoMotors motors;
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);


/*-----other global variables-----*/
unsigned int sensor_values[6];
char currentSetting; //determines which mode we are currently in ie. manual/autonomous 
bool wall;
String val;

/*-----setup-----*/
void setup() 
{
    Serial.begin(9600);
    val = Serial.read();
    while(val != "z")
    {
      val = Serial.read();
    }
    
}

void loop() 
{
  if(Serial.available() > 0) {
    String val = Serial.read();

    if(val == "f") {
      motors.setSpeeds(MAX_SPEED, MAX_SPEED);
      delay(500);
      motors.setSpeeds(0,0);
    }

    if(val == "b") {
      motors.setSpeeds(-MAX_SPEED, -MAX_SPEED);
      delay(500);
      motors.setSpeeds(0,0);
    }

    if(val == "l") {
      motors.setSpeeds(MAX_SPEED, -MAX_SPEED);
      delay(500);
      motors.setSpeeds(0,0);
    }

    if(val == "r") {
      motors.setSpeeds(-MAX_SPEED, MAX_SPEED);
      delay(500);
      motors.setSpeeds(0,0);
    }
    if(val == "s") {
      motors.setSpeeds(0,0);
      delay(500);
    }
    if(val == "LeRo") {
      //give room a number 
      //tell gui number and left 
      //turn left for the room 
      //scan room 
      //if object is detected, tell gui 
    }
    if(val == "RiRo") {
      //give the room a number
      //tell gui number and right 
      //turn right for the room 
      //scan room 
      //if object is detected, tell gui 
    }
    if(val == "C") {
      //turn back to autonomous 
    }
  }
}
