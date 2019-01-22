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
int maxSensorValue[6];

/*-----setup-----*/
void setup() 
{
    Serial.begin(9600);
    val = Serial.read();

    //initialise reflectnace sensors module 
    sensors.init();
    //automatic sensor calibration by rotating in place to sweep the sensors - similar 
    //to the Line Follower example
    for(int i = 0; i < 80; i++)
    {
      if((i>10 && i<=30) || (i>50 && i <=70))
      {
        motors.setSpeeds(-NORMAL_SPEED, NORMAL_SPEED);
      }
      else 
      {
        motors.setSpeeds(NORMAL_SPEED, -NORMAL_SPEED);
      }
    }
    sensors.calibrate();
    delay(20);
    for(int i = 0; i < 6; i++)
    {
      maxSensorValue[i] = sensors.calibrateMaximumOn[i];
    }

    motors.setSpeeds(0,0);

    while(val != "z")
    {
      val = Serial.read();
    }
    
}

void loop() 
{
    switch(currentSetting) {
      
        case 'm':
          moveManually();
          break;
          
        case 'a':
          moveAutonomously();
          break;
        
        case 's':
          search();
          break;
    }
}

void moveManually() {
  if(Serial.available() > 0) {
    String val = Serial.read();

    switch(val) {

        case "f":
          motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
          delay(2000);
          motors.setSpeeds(0,0);
          break;

        case "b":
          motors.setSpeeds(-NORMAL_SPEED, -NORMAL_SPEED);
          delay(2000);
          motors.setSpeeds(0,0);
          break;
          
        case "l":
          motors.setSpeeds(NORMAL_SPEED, -NORMAL_SPEED);
          delay(2000);
          motors.setSpeeds(0,0);
          break;
          
        case "r": 
          motors.setSpeeds(-NORMAL_SPEED, NORMAL_SPEED);
          delay(2000);
          motors.setSpeeds(0,0);
          break;
          
        case "s":
          motors.setSpeeds(0,0);
          break;
          
        case "LeRo":
          motors.setSpeeds(0,0);
          break;
          
        case "RiRo":
          motors.setSpeeds(0,0);
          break;
          
        case "C":
          currentSetting = 'a';
          break;
          
        case "E":
          motors.setSpeeds(0,0);
          break; 
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
  }
}

void moveAutonomously() {
  //move along the corridor keeping within the black lines until it reaches a corner
  val = Serial.read();
  sensors.read(sensor_values);

  if(val = "s")
  {
    motors.setSpeeds(0,0);
  }
  else {
    if(val = "LeRo")
    {
      //go to manual mode 
    }
    else {
      if(val = "RiRo")
      {
        //go to manual mode
      }
      else {
        if(sensor_values[3] > maxSensorValue[3])
        {
          motors.setSpeed(0,0);
          currentSetting = 'm';
        }
        else {
          if(sensor_values[5] >= maxSensorValue[5])
          {
            motors.setSpeeds(-REVERSE_SPEED, _REVERSE_SPEED);
            delay(REVERSE_DURATION);
            motor.setSpeeds(TURN_SPEED, -TURN_SPEED);
            delay(TURN_DURATION);
            motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
          }
          else {
            if(sensor_values[0] >= maxSensorValue[0])
            {
              motors.setSpeeds(-REVERSE_SPEED, _REVERSE_SPEED);
              delay(REVERSE_DURATION);
              motor.setSpeeds(-TURN_SPEED, TURN_SPEED);
              delay(TURN_DURATION);
              motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
            }
            else {
              motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
            }
          }
        }
      }
    }
  }
  
}
