# Zumo
Programming Things Module - Individual Assignment 

### Overview
Modify and code a Pololu Zumo robot to perform a simulated search and rescue operation involving people trapped in a single floor of a buiding filled with smoke. 

### Objectives
Task 1: 
  * **Description:** The Zumo can be driven down the corridor by the user using a GUI.
  * **Problems faced:** Couldn't get a connection between Arduino IDE and Processing. 
  * **Solution:** Wasn't using the correct portname. Needed to use Serial.list()[1] instead of Serial.list()[0].
  * **Completed:** YES
  
Task 2:
  * **Description:** The Zumo can move automatically down the corridor, turning away from the walls when detected by the 
  * **Problems faced:** Altering BorderDetect so that it detects a black line on a white background instead of a white line on black background. 
  Stopping at a corner rather than trying to correct itself to continue straight. 
  * **Solution:**
  * **Completed:** YES

Task 3:
  * **Description:** User manually moves the Zumo around the corner and then signals when it is complete so the Zumo can continue down the coridor automatically. 
  * **Problems faced:**
  * **Solution:**
  * **Completed:** YES

Task 4:
  * **Description:** User tells the Zumo it has arrived at a room, manually turns the Zumo towards the room so that it can then scan the room itself automatically. If a person is found within the room 
  * **Problems faced:** Getting the Zumo to scan around the whole room not just in front of it. 
  * **Solution:** Sweep from left to right on the spot, like during calibration at the start, so the sensor passes over the whole room.
  * **Completed:** YES

Task 5:
  * **Description:** User turns Zumo when it gets the T-junction to go down one of the corridors. When the Zumo reaches the end of the corridor, it stops and waits for the user to tell it has reached the end. The Zumo then goes to the other half of the corridor, searching autonomously ignoring any user input until it reaches the other end. 
  * **Problems faced:** Didn't leave myself enough time to finish this task. 
  * **Solution:** 
  * **Completed:** NO 
  
  ### Acknowledgements 
  * For my GUI I used the ControlP5 library.
  * I used the BorderDetect and MazeFollower examples within the ZumoShield library as a starting point for navigating the Zumo down the corridor between the lines. 
  * To use the ultrasonic sensor I used the NewPing library. 
  
  ### Personal Reflection 
  I feel I started this project well with tasks one through to three, however I slowed down progress after that which meant I quickly ran out of time for the remaining three tasks. I did manage to complete task four and start five but did not get onto six. My time management needed to be a lot better. If I were to do this project again, I would maintain the work flow I had for the first tasks throughtout the whole project to ensure a successful outcome. 
  
  I feel I faced the problems I encountered while programming and testing the robot well, finding solutions for all of them. 
  
