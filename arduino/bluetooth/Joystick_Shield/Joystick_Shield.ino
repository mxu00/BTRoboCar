/* 6th December 2013 - By Kyle Fieldus

This example sketch is designed to show the inputs and outputs of the Funduino Joystick Shield V1.A
The shield this sketch was developed with was provded by ICStation http://www.icstation.com/
*/
#include <ArduinoJson.h>

int up_button = 2;
int down_button = 4;
int left_button = 5;
int right_button = 3;
int start_button = 6;
int select_button = 7;
int analog_button = 8;
int x_axis = A0;
int y_axis = A1;
int buttons[] = {up_button, down_button, left_button, right_button, start_button, select_button, analog_button};

void setup() {
  for (int i; i < 7; i++)
  {
   pinMode(buttons[i], INPUT);
   digitalWrite(buttons[i], HIGH);
  }
  Serial.begin(9600);
}

void loop() {
  //========================================================//
  // Read Joystick input, Format in JSON, Print to serial
  //========================================================//
  // Memory pool for JSON object tree.
  //
  // Inside the brackets, 200 is the size of the pool in bytes.
  // If the JSON object is more complex, you need to increase that value.
  StaticJsonBuffer<200> jsonBuffer;

  // StaticJsonBuffer allocates memory on the stack, it can be
  // replaced by DynamicJsonBuffer which allocates in the heap.
  // It's simpler but less efficient.
  //
  // DynamicJsonBuffer  jsonBuffer;

  // Create the root of the object tree.
  //
  // It's a reference to the JsonObject, the actual bytes are inside the
  // JsonBuffer with all the other nodes of the object tree.
  // Memory is freed when jsonBuffer goes out of scope.
  JsonObject& root = jsonBuffer.createObject();

  // Add values in the object
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do root.set<long>("time", 1351824120);

  // Map analog X, Y before 
  int X_base = 495;
  int Y_base = 509;
  // Normalize X, Y against their base values, then map to the range of -255 ~ 255
  int X_val = analogRead(x_axis);
  if (X_val <= X_base){
    X_val = map(X_val, 0, X_base, -255, 0);
  }else{
    X_val = map(X_val, X_base, 1023, 0, 255);
  };

  int Y_val = analogRead(y_axis);
  if (Y_val <= Y_base){
    Y_val = map(Y_val, 0, Y_base, -255, 0);
  }else{
    Y_val = map(Y_val, Y_base, 1023, 0, 255);
  };
  
  // print to serial
  Serial.print("UP = "),Serial.print(digitalRead(up_button)),Serial.print("\t");
  
  root["X"] = X_val;
  root["Y"] = Y_val;
  root["UP"] = abs(digitalRead(up_button) - 1);
  root["DOWN"] = abs(digitalRead(down_button) - 1);
  root["LEFT"] = abs(digitalRead(left_button) - 1);
  root["RIGHT"] = abs(digitalRead(right_button) - 1);
  root["SELECT"] = abs(digitalRead(select_button) - 1);
  root["START"] = abs(digitalRead(start_button) - 1);
  root["ANALOG"] = analogRead(analog_button);
  
  root.printTo(Serial);
  // This prints json format data

  Serial.println();
  //delay(100);
  
  
  
 }
/*
  Serial.print("UP = "),Serial.print(digitalRead(up_button)),Serial.print("\t");
  Serial.print("DOWN = "),Serial.print(digitalRead(down_button)),Serial.print("\t");
  Serial.print("LEFT = "),Serial.print(digitalRead(left_button)),Serial.print("\t");
  Serial.print("RIGHT = "),Serial.print(digitalRead(right_button)),Serial.print("\t");
  Serial.print("START = "),Serial.print(digitalRead(start_button)),Serial.print("\t");
  Serial.print("SELECT = "),Serial.print(digitalRead(select_button)),Serial.print("\t");
  Serial.print("ANALOG = "),Serial.print(digitalRead(analog_button)),Serial.print("\t");
  //Serial.print("X = "),Serial.print(map(analogRead(x_axis), 0, 950, -1, 1));Serial.print("\t");
  //Serial.print("Y = "),Serial.print(map(analogRead(y_axis), 0, 1000, -1, 1));Serial.print("\n");  
  Serial.print("X = "),Serial.print(analogRead(x_axis) - 495);Serial.print("\t");
  Serial.print("Y = "),Serial.print(analogRead(y_axis) - 509);Serial.print("\n");  
  delay(100);
  */

