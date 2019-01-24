/*-----libraries-----*/
#include <Wire.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoShield.h>
#include <NewPing.h>

/*-----motion global variables-----*/
#define NORMAL_SPEED      100
#define REVERSE_SPEED     50
#define TURN_SPEED        100
#define REVERSE_DURATION  200
#define TURN_DURATION     150
#define TRIGGER_PIN       12
#define ECHO_PIN          11
#define MAX_DISTANCE      200 //max distance (in cm) to ping 

/*-----hardware declarations-----*/
ZumoMotors motors;
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
Pushbutton button(ZUMO_BUTTON);
NewPing uSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

/*-----other global variables-----*/
unsigned int sensor_values[6];
char currentSetting; //determines which mode we are currently in ie. manual/autonomous 
bool wall;
char val;
int maxSensorValue[6];
int roomNumber;

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
    roomNumber = 0;
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
    if(val == 'o')
    {
      motors.setSpeeds(0,0);
      val = Serial.read();
      if(val == 'x')
      {
        //room is on the left 
        Serial.print("Room on the left");
        //number the room 
        roomNumber = roomNumber + 1;
        //move manually to let the user turn into the room 
        enterRoom();
        //search room 
        searchRoom();
        //back to manual to let user move into corridor 
        currentSetting = 'm';
      }
      else{
        if(val == 'y')
        {
          //room is on the right
          Serial.print("Room on the right");
          //number the room  
          roomNUmber = roomNUmber + 1;
          //move manually to let the user turn into the room
          enterRoom();
          //search room 
          searchRoom();
          //back to manual to let user move into corridor 
          currentSetting = 'm';
        }
      }
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

void searchRoom() {
    //move into room
    motors.setSpeeds(NORMAL_SPEED, NORMAL_SPEED);
    delay(200);
    //stop 
    motors.setSpeeds(0,0);
    //scan around the room 
    
    //if object is present, tell the gui which room it is in
    //stop 
    //tell user to navigate out thr room and turn into corridor 

}

void enterRoom() {
  //while val != 'C' 
  //allow user to move manually 
  //when val is 'C'
  //leave function 
}
