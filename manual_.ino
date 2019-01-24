/*-----libraries-----*/
#include <Wire.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoShield.h>

/*-----motion global variables-----*/
#define NORMAL_SPEED      100
#define REVERSE_SPEED     50
#define TURN_SPEED        100
#define REVERSE_DURATION  200
#define TURN_DURATION     150
#define TRIGGER_PIN
#define ECHO_PIN

/*-----hardware declarations-----*/
ZumoMotors motors;
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
Pushbutton button(ZUMO_BUTTON);

/*-----other global variables-----*/
unsigned int sensor_values[6];
char currentSetting; //determines which mode we are currently in ie. manual/autonomous 
bool wall;
char val;
int maxSensorValue[6];

/*-----setup-----*/
void setup() 
{
    Serial.begin(9600);

    //initialise reflectnace sensors module 
    sensors.init();
    // Wait for the user button to be pressed and released
    button.waitForButton();
    //automatic sensor calibration by rotating in place to sweep the sensors - similar 
    //to the Line Follower example
    for(int i = 0; i < 80; i++)
    {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
    sensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
    }
      motors.setSpeeds(0,0);
    for(int i = 0; i < 6; i++)
    {
      maxSensorValue[i] = sensors.calibratedMaximumOn[i];
    }

    motors.setSpeeds(0,0);

    currentSetting = 'a';
    button.waitForButton();
    
}

void loop() 
{

//    switch(currentSetting) {
//      
//        case 'm':
//          moveManually();
//          break;
//          
//        case 'a':
//          moveAutonomously();
//          break;
//        
//    }

    if(currentSetting == 'm') {
      moveManually();
    }
    else 
    {
      if(currentSetting == 'a') {
        moveAutonomously();
      }
    }
}

void moveManually() {
    val = Serial.read();

//    if(val == 'f') {
//      motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
//      delay(200);
//      motors.setSpeeds(0,0);
//    }

    switch(val) {

        case 'f':
          motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
          delay(200);
          motors.setSpeeds(0,0);
          Serial.print("Moved forward");
          break;

        case 'b':
          motors.setSpeeds(-NORMAL_SPEED, -NORMAL_SPEED);
          delay(200);
          motors.setSpeeds(0,0);
          Serial.print("Moved backward");
          break;
          
        case 'l':
          motors.setSpeeds(-NORMAL_SPEED, NORMAL_SPEED);
          delay(200);
          motors.setSpeeds(0,0);
          Serial.print("Moved left");
          break;
          
        case 'r': 
          motors.setSpeeds(NORMAL_SPEED, -NORMAL_SPEED);
          delay(200);
          motors.setSpeeds(0,0);
          Serial.print("Moved right");
          break;
          
        case 's':
          motors.setSpeeds(0,0);
          Serial.print("Stopped");
          break;
          
        case 'x':
          motors.setSpeeds(0,0);
          break;
          
        case 'y':
          motors.setSpeeds(0,0);
          break;
          
        case 'C':
          currentSetting = 'a';
          Serial.print("Going back to auto");
          break;
          
        case 'E':
          motors.setSpeeds(0,0);
          Serial.print("At end of corridor");
          break; 
    }

    //if(val == "LeRo") {
      //give room a number 
      //tell gui number and left 
      //turn left for the room 
      //scan room 
      //if object is detected, tell gui 
    //}
    //if(val == "RiRo") {
      //give the room a number
      //tell gui number and right 
      //turn right for the room 
      //scan room 
      //if object is detected, tell gui 
    //}
  
}

void moveAutonomously() {
  //move along the corridor keeping within the black lines until it reaches a corner
  val = Serial.read();
  sensors.read(sensor_values);

  if(val == 's')
  {
    motors.setSpeeds(0,0);
    Serial.print("Stopped");
  }
  else {
    if(val == 'x')
    {
      //go to manual mode 
      currentSetting = 'm';
    }
    else {
      if(val == 'y')
      {
        //go to manual mode
        currentSetting = 'm';
      }
      else {
        if(sensor_values[3] > maxSensorValue[3])
        {
          motors.setSpeeds(0,0);
          currentSetting = 'm';
          Serial.print("At a corner");
        }
        else {
          if(sensor_values[5] >= maxSensorValue[5])
          {
            motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
            delay(REVERSE_DURATION);
            motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
            delay(TURN_DURATION);
            motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
            currentSetting = 'a';
            Serial.print("Moved back to center");
          }
          else {
            if(sensor_values[0] >= maxSensorValue[0])
            {
              motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
              delay(REVERSE_DURATION);
              motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
              delay(TURN_DURATION);
              motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
              currentSetting = 'a';
              Serial.print("Move back to center");
            }
            else {
              motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
              currentSetting = 'a';
            }
          }
        }
      }
    }
  }
  
}
