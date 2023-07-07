//include the wire library to communication between two arduino boards
#include <Wire.h>

//M4 motor pin define
int _m4ctrlpin1 = 4;
int _m4ctrlpin2 = 3;
int _m4spctrlpin = 5; // speed control pin of the motor 
int _m4ctrlspeed = 255; // speed of the motor M1(0-255)

//meaning of received data to the board
enum Messages{
  ONM4MOTOR,
  OFFM4MOTOR,//stamping part roller motor
  ONM5MOTOR,//step motor
};

void setup() {
  // put your setup code here, to run once:

  // make serial communication between serial monitor
  Serial.begin(9600);

  // initialize the pins of motors
  //M1 motor
  pinMode(_m4ctrlpin1,OUTPUT);
  pinMode(_m4ctrlpin2,OUTPUT);
  pinMode(_m4spctrlpin,OUTPUT);
  
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);

}

void receiveEvent(int bytes) {
  int _receivedmessage = Wire.read();    // read one character from the I2C
  Serial.println(_receivedmessage);
  delay(100);
  // send to on the M4 motor
  if(_receivedmessage==ONM4MOTOR){
    
    //power on the M4 motor 
    digitalWrite(_m4ctrlpin1,HIGH);
    digitalWrite(_m4ctrlpin2,LOW);
    analogWrite(_m4spctrlpin,_m4ctrlspeed);
  }

  // send to off the M4 motor
  if(_receivedmessage==OFFM4MOTOR){
    
    //power on the M4 motor 
    digitalWrite(_m4ctrlpin1,HIGH);
    digitalWrite(_m4ctrlpin2,LOW);
    analogWrite(_m4spctrlpin,_m4ctrlspeed);
  }

  //send to on the step motor
  if(_receivedmessage==ONM5MOTOR){
    
    //power on the step motor in one revolution 
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
