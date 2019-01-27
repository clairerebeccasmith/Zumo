# Zumo
Programming Things Module - Individual Assignment 

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
  * **Description:** 
  * **Problems faced:**
  * **Solution:** 
  * **Completed:**
