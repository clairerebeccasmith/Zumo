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
    //store data from calibration for difference in back/white 
    for(int i = 0; i < 6; i++)
    {
      maxSensorValue[i] = sensors.calibratedMaximumOn[i];
    }

    motors.setSpeeds(0,0);
    //start robot in autonomous mode 
    currentSetting = 'a';
    button.waitForButton();
    
}

void loop() 
{
    //check what mode the robot is currently in and move accordingly 
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

    //get user input from GUI
    val = Serial.read();

    //switch statement for each option available in the GUI 
    switch(val) {

        //move forward 
        case 'f':
          motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
          delay(200);
          motors.setSpeeds(0,0);
          Serial.print("Moved forward");
          break;

        //move backward
        case 'b':
          motors.setSpeeds(-NORMAL_SPEED, -NORMAL_SPEED);
          delay(200);
          motors.setSpeeds(0,0);
          Serial.print("Moved backward");
          break;

         //move to the left 
        case 'l':
          motors.setSpeeds(-NORMAL_SPEED, NORMAL_SPEED);
          delay(200);
          motors.setSpeeds(0,0);
          Serial.print("Moved left");
          break;

         //move to the right 
        case 'r': 
          motors.setSpeeds(NORMAL_SPEED, -NORMAL_SPEED);
          delay(200);
          motors.setSpeeds(0,0);
          Serial.print("Moved right");
          break;

        //stop 
        case 's':
          motors.setSpeeds(0,0);
          Serial.print("Stopped");
          break;
/*----task 4------*/
//        //room on the left 
//        case 'x':
//          motors.setSpeeds(0,0);
//          break;
//
//        //room on the right 
//        case 'y':
//          motors.setSpeeds(0,0);
//          break;

        //user input is complete, go back to auto 
        case 'C':
          currentSetting = 'a';
          Serial.print("Going back to auto");
          break;

        //robot at end of corridor 
        case 'E':
          motors.setSpeeds(0,0);
          Serial.print("At end of corridor");
          break; 
    }
}

void moveAutonomously() {
  //move along the corridor keeping within the black lines until it reaches a corner
  
  //get user input form GUI 
  val = Serial.read();
  //read values from sensors to see if on line 
  sensors.read(sensor_values);
  
  //if user tells robot to stop 
  if(val == 's')
  {
    motors.setSpeeds(0,0);
    Serial.print("Stopped");
  }
  else {
    //task 4 
    if(val == 'x')
    {
      //go to manual mode 
      currentSetting = 'm';
    }
    else {
      //task 4 
      if(val == 'y')
      {
        //go to manual mode
        currentSetting = 'm';
      }
      else {
        //if center sensor detects black line, must be at a corner 
        if(sensor_values[3] > maxSensorValue[3])
        {
          motors.setSpeeds(0,0);
          currentSetting = 'm';
          Serial.print("At a corner");
        }
        else {
          //if right most sensor detects black line, reverse and re-align 
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
            //if left most sensor detects black line, reverse and re-align 
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
              //otherwise, continue forward in auto mode 
              motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
              currentSetting = 'a';
            }
          }
        }
      }
    }
  }
  
}
