//on off switch 
int _onoffbtn = A0;
//on or off state of the machine
int _onoff = 0;

//general delay time to start a motor
int _gndelaytime = 200; //time in milliseconds

//M1 motor pin define
int _m1ctrlpin1 = 4;
int _m1ctrlpin2 = 3;
int _m1spctrlpin = 5; // speed control pin of the motor 
int _m1ctrlspeed = 255; // speed of the motor M1(0-255)

//M2 motor pin define
int _m2ctrlpin1 = 7;
int _m2ctrlpin2 = 8;
int _m2spctrlpin = 9; // speed control pin of the motor 
int _m2ctrlspeed = 255; // speed of the motor M2(0-255)

//M4 motor pin define
int _m4ctrlpin1 = 11;
int _m4ctrlpin2 = 12;
int _m4spctrlpin = 10; // speed control pin of the motor 
int _m4ctrlspeed = 255; // speed of the motor M4(0-255)

//cout the loop and cout the papers
int _loopcount = 1;


void setup() {
  // put your setup code here, to run once:
  //start serial communication
  Serial.begin(9600);
  //initialize on off button
  pinMode(_onoffbtn,INPUT);

  // initialize the pins of motors
  //M1 motor
  pinMode(_m1ctrlpin1,OUTPUT);
  pinMode(_m1ctrlpin2,OUTPUT);
  pinMode(_m1spctrlpin,OUTPUT);

  //M2 motor
  pinMode(_m2ctrlpin1,OUTPUT);
  pinMode(_m2ctrlpin2,OUTPUT);
  pinMode(_m2spctrlpin,OUTPUT);

  //M4 motor
  pinMode(_m4ctrlpin1,OUTPUT);
  pinMode(_m4ctrlpin2,OUTPUT);
  pinMode(_m4spctrlpin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  //check the turn on button to and get the value
  _onoff =analogRead(_onoffbtn);
  Serial.println(_onoff);


  //check to turn on the machine
  if(_onoff == 1023){
      if(_loopcount == 1){
        Serial.println("Power on the machine");
        digitalWrite(_m2ctrlpin1,HIGH);
        digitalWrite(_m2ctrlpin2,LOW);
        analogWrite(_m2spctrlpin,255);
        delay(500);
      }
    
    //when the machine 

  }else{
        //turn off the M2 motor
        digitalWrite(_m2ctrlpin1,LOW);
        digitalWrite(_m2ctrlpin2,LOW);
        
  }
  delay(500);
}
