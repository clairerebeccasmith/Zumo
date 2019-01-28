

import controlP5.*;
import processing.serial.*;

ControlP5 jControl;
Serial port;
Textarea console;
String incoming;
StringList messages;
String display;

void setup() {
  size(600,1000);
  String portName = Serial.list()[1];
  port = new Serial(this, portName, 9600);
  
  jControl = new ControlP5(this);
  jControl.addButton("Left").setPosition(100, 50).setSize(100, 70);
  jControl.addButton("Right").setPosition(100, 150).setSize(100, 70);
  jControl.addButton("Forward").setPosition(100, 250).setSize(100, 70);
  jControl.addButton("Back").setPosition(100, 350).setSize(100, 70);
  jControl.addButton("Stop").setPosition(100, 450).setSize(100, 70);
  jControl.addButton("Room").setPosition(300, 50).setSize(100, 70);
  jControl.addButton("Left Room").setPosition(300, 150).setSize(100, 70);
  jControl.addButton("Right Room").setPosition(300, 250).setSize(100, 70);
  jControl.addButton("Complete").setPosition(300, 350).setSize(100, 70);
  jControl.addButton("End").setPosition(300, 450).setSize(100, 70);
  jControl.addButton("Close").setPosition(450, 650).setSize(100, 70);
  
  console = jControl.addTextarea("txt")
    .setPosition(100, 550)
    .setSize(300, 200)
    .setFont(createFont("arial", 12))
    .setLineHeight(14)
    .setColor(color(128))
    .setColorBackground(color(255, 100))
    .setColorForeground(color(255, 100));
  ;
  
  messages = new StringList();
  messages.append("Hello");
}

void draw() {
  background(0);
  if ( port.available() > 0) 
  {  // If data is available,
    incoming = port.readString();
    console.setText("");
    messages.append(incoming);
  } 
for(int i = 0; i < messages.size(); i++)
{
  display = display + messages.get(i) + "\n";
} 

console.setText(display);
}


void Left() {
  port.write('l');
  print("l");
}
void Right() {
  port.write('r');
  print("r");
}
void Forward() {
  port.write('f');
  print("f");
}
void Back() {
  port.write('b');
  print("b");
}
void Stop() {
  port.write('s');
  print("s");
}
void Room() {
  port.write('o');
  print("Ro");
}
void LeftRoom() {
  port.write("x");
  print("LeRo");
}
void RightRoom() {
  port.write("y");
  print("RiRo");
}
void Complete() {
  port.write("C");
  print("C");
}
void End() {
  port.write("E");
  print("E");
}
void Cancel() {
  port.write("z");
  print("z");
}
