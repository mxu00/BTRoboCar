/*************************************************************
Motor Shield 2-Channel DC Motor Demo
by Randy Sarafan

For more information see:
http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/

/*************************************************************
Function        Channel A   Channel B
Direction        Digital 12  Digital 13
Speed (PWM)      Digital 3   Digital 11
Brake            Digital 9   Digital 8
Current Sensing  Analog  0   Analog  1
*************************************************************/

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial BTSerial(5, 6); // RX | TX

// Buffer to store incoming commands from serial port
String inData;
bool signal_start = false;
bool signal_end = false;

void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin

  //Setup Bluetooth
  Serial.begin(9600);
  
  // INIT INFORMATION
  Serial.println("Arduino Started");
  
  // Start the software serial - baud rate for AT mode is 9600
  BTSerial.begin(9600);  // HC-05 default speed in AT command more

}

void loop(){
  // Memory pool for JSON object tree.
  //
  // Inside the brackets, 200 is the size of the pool in bytes,
  // If the JSON object is more complex, you need to increase that value.
  StaticJsonBuffer<512> jsonBuffer;
  
  ////////////////////////////////////////////////////////////
  // Get BT command
  ////////////////////////////////////////////////////////////
  while (BTSerial.available()){
    inData = BTSerial.readStringUntil('\n');
    Serial.println(inData);
  }
  
  ////////////////////////////////////////////////////////////
  // Parse BT command
  ////////////////////////////////////////////////////////////
  // Root of the object tree.
  //
  // It's a reference to the JsonObject, the actual bytes are inside the
  // JsonBuffer with all the other nodes of the object tree.
  // Memory is freed when jsonBuffer goes out of scope.
  JsonObject& root = jsonBuffer.parseObject(inData);

  // Test if parsing succeeds.
  if (!root.success()) {
    // clear buffer
    
    Serial.println("parseObject() failed");
    inData = "";
    
    // brack
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    
    return;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do root["time"].as<long>();
  if(root.success()){
  int X_val = root["X"];
  int Y_val = root["Y"];
  int up_button = root["UP"];
  int down_button = root["DOWN"];
  int left_button = root["LEFT"];
  int right_button = root["RIGHT"];
  int select_button = root["SELECT"];
  int start_button = root["START"];
  int analog_button = root["ANALOG"];

  // Print values.
  Serial.println("Y= " + String(Y_val));

  ////////////////////////////////////////////////////////////
  // Drive motor
  ////////////////////////////////////////////////////////////
  // default: brack
  if (down_button == 1){
    // brack
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }else{
  
  // forward
  int left_motor = 0;
  int right_motor = 0;
  bool direction = HIGH;
  
  if ((Y_val >= 0) && (X_val >= 0)){
    left_motor = max(Y_val, X_val);
    right_motor = Y_val;
    direction = HIGH;
  }

  if ((Y_val >= 0) && (X_val < 0)){
    left_motor = abs(Y_val);
    right_motor = max(abs(Y_val), abs(X_val));
    direction = HIGH;
  }

  if ((Y_val < 0) && (X_val >= 0)){
    left_motor = max(abs(Y_val), abs(X_val));
    right_motor = abs(Y_val);
    direction = LOW;
  }

  if ((Y_val < 0) && (X_val < 0)){
    left_motor = abs(Y_val);
    right_motor = max(abs(Y_val), abs(X_val));
    direction = LOW;
  }
  
    // Motor A
    digitalWrite(13, direction); //Establishes  direction of Channel A
    digitalWrite(8, LOW);   //Disengage the Brake for Channel A
    analogWrite(11, left_motor);   //Spins the motor on Channel A at full speed

    // Motor B
    digitalWrite(12, direction);  //Establishes  direction of Channel B
    digitalWrite(9, LOW);   //Disengage the Brake for Channel B
    analogWrite(3, right_motor);    //Spins the motor on Channel B at half speed
  

  

  // backward
  if (0){
    int left_motor = min((-Y_val + X_val), 255);
    int right_motor = min((-Y_val - X_val), 255);
    
    // Motor A
    digitalWrite(13, LOW); //Establishes backward direction of Channel A
    digitalWrite(8, LOW);   //Disengage the Brake for Channel A
    analogWrite(11, left_motor);   //Spins the motor on Channel A at full speed

    // Motor B
    digitalWrite(12, LOW);  //Establishes backward direction of Channel B
    digitalWrite(9, LOW);   //Disengage the Brake for Channel B
    analogWrite(3, right_motor);    //Spins the motor on Channel B at half speed
  }
  }
  ////////////////////////////////////////////////////////////
  // Clear BT command
  ////////////////////////////////////////////////////////////
  inData = "";
  signal_start = false;
  signal_end = false;
  
  }

  ////////////////////////////////////////////////////////////
  // Drive motor
  ////////////////////////////////////////////////////////////

  if (0){
  ////////////////////////////////////////////////////////////
  // forward
  //Motor A forward @ half speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 125);   //Spins the motor on Channel A at full speed

  //delay(2000);
  
  //Motor B backward @ half speed
  digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 125);    //Spins the motor on Channel B at half speed

  // brack
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delay(1000);
  
  ////////////////////////////////////////////////////////////
  // then backward
  //Motor A forward @ half speed
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 125);   //Spins the motor on Channel A at full speed

  //delay(2000);
  
  //Motor B backward @ half speed
  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 125);    //Spins the motor on Channel B at half speed

  delay(2000);
  ////////////////////////////////////////////////////////////

  // brack
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delay(1000);

  ////////////////////////////////////////////////////////////
  // then rotate
  //Motor A forward @ half speed
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 125);   //Spins the motor on Channel A at full speed

  //delay(2000);
  
  //Motor B backward @ half speed
  digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 125);    //Spins the motor on Channel B at half speed

  delay(1500);
  ////////////////////////////////////////////////////////////

  // brack
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delay(1000);
  }
}
/*************************************************************
void loop(){
  //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B backward @ half speed
  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 123);    //Spins the motor on Channel B at half speed

  
  delay(3000);

  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(9, HIGH);  //Engage the Brake for Channel B


  delay(1000);
  
  
  //Motor A forward @ full speed
  digitalWrite(12, LOW);  //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 123);    //Spins the motor on Channel A at half speed
  
  //Motor B forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
  
  
  delay(3000);
  
  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(9, HIGH);  //Engage the Brake for Channel B
  
  
  delay(1000);
  
}
*************************************************************/
