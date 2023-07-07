//include the wire library to communication between two arduino boards
#include <Wire.h>
//include lcd display library
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,1);  


//Times to setup
int _timeM1leave = 1000;//time to leave the paper from the M1 in milliseconds
int _timeM2leave = 1000;//time to leave the paper from the M1 in milliseconds
int _time2setup = 1000;//time to setup the paper on the stamping 
int _timp2stamp = 2000;//time to stamp in the paper

//Switches to contorl the states
int _papersfull = A1; //this tap switch on when the papers are fully adjusted
int _papersfullst;
int _maxfedderdown =A2;//this tap switch HIGH when the stage went max down position
int _paperemptybtn = A3; //paper empty indicator
int _onoffbtn = A0;//on off switch working state
int _setbtn = 6;//set the machine stage to relevent height

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

//M3 motor pin define
int _m3ctrlpin1 = 11;
int _m3ctrlpin2 = 12;
int _m3spctrlpin = 10; // speed control pin of the motor 
int _m3ctrlspeed = 255; // speed of the motor M4(0-255)

//cout the loop and cout the papers
int _loopcount = 1;

//machine states works in different conditions
enum MachineStates{
  SETTING,
  PAPERFILL,
  WORKING,
  PAPEREMPTY
};

//datas that send to power on and off the M4 and M5
enum Messages{
  ONM4MOTOR,
  OFFM4MOTOR,//stamping part roller motor
  ONM5MOTOR//step motor
};

//current state holder
MachineStates _currentstate;


void setup() {
  // put your setup code here, to run once:

  //start the communication between receive arduino board
  Wire.begin(); 


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

  //M3 motor
  pinMode(_m3ctrlpin1,OUTPUT);
  pinMode(_m3ctrlpin2,OUTPUT);
  pinMode(_m3spctrlpin,OUTPUT);
  
  //initialize lcd display
  lcd.init();
  lcd.backlight(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  //sample communication between arduino
    // Wire.beginTransmission(9); // transmit to device #9
    // Wire.write(2);              // sends x 
    // Wire.endTransmission();    // stop transmitting

  
  //checking the inputs 
  //check the turn on button to and get the value
  _onoff =analogRead(_onoffbtn);
  _papersfullst =analogRead(_papersfull);
  //and update the state of the machine
  if(_onoff == 1023){
    _currentstate = WORKING; 
  }
  //check reset
  if(_setbtn==1023){
    _currentstate = SETTING;
  }

  //turn on the machine in WORKING state and WORKING state condition
  if(_currentstate == WORKING){
    
    //first loop of the working state 
      if(_loopcount ==1){
        //fist statement to display 
        lcd.print("Machine Starting");
        delay(1000);
        lcd.clear();
      }
      if(_loopcount > 0){
        Serial.println("Power on the machine");
        delay(500);
        
        //power on the M1 motor 
        digitalWrite(_m1ctrlpin1,HIGH);
        digitalWrite(_m1ctrlpin2,LOW);
        analogWrite(_m1spctrlpin,_m1ctrlspeed);
        delay(_gndelaytime);
        
        //power on the M2 motor
        digitalWrite(_m2ctrlpin1,HIGH);
        digitalWrite(_m2ctrlpin2,LOW);
        analogWrite(_m2spctrlpin,_m2ctrlspeed);
        delay(_gndelaytime);

        //power on the M4 motor
        // send message to on the M4 motor 
        Serial.println("Begin transmission");
        delay(_gndelaytime);
        Wire.beginTransmission(9); 
        Wire.write(ONM4MOTOR);             
        Wire.endTransmission(9);
        Serial.println("End transmission");
        delay(_gndelaytime);
        

        delay(_timeM1leave);//delay..............................................................
      
        //power off the M1 motor 
        Serial.println("power off the M1 motor");
        digitalWrite(_m1ctrlpin1,LOW);
        digitalWrite(_m1ctrlpin2,LOW);
        analogWrite(_m1spctrlpin,_m1ctrlspeed);
        delay(_gndelaytime);
        //M2 and M4 are on 

        delay(_timeM2leave);//delay..............................................................
        
        //power off the M2 motor

        digitalWrite(_m2ctrlpin1,LOW);
        digitalWrite(_m2ctrlpin2,LOW);
        analogWrite(_m2spctrlpin,_m1ctrlspeed);
        delay(_gndelaytime);

        delay(_time2setup);//delay................................................................
        
        //send message to off the M4 motor 
        Wire.beginTransmission(9); 
        Wire.write(OFFM4MOTOR);             
        Wire.endTransmission();
        delay(_gndelaytime);

        //send message to off the M5 motor 
        Wire.beginTransmission(9); 
        Wire.write(ONM5MOTOR);             
        Wire.endTransmission();
        delay(_gndelaytime);

        if(analogRead(_paperemptybtn)==1023){
          _currentstate = PAPEREMPTY;
        }
        
        
        //bring upword the paper fedder stage
        do{
        //power on the M3 motor to go upword stage
        digitalWrite(_m3ctrlpin1,HIGH);
        digitalWrite(_m3ctrlpin2,LOW);
        analogWrite(_m3spctrlpin,_m1ctrlspeed);
        delay(100);
        }while(_papersfull == HIGH);
        
        //power off the M3 motor to stop going upword stage
        digitalWrite(_m3ctrlpin1,LOW);
        digitalWrite(_m3ctrlpin2,LOW);
        analogWrite(_m3spctrlpin,_m1ctrlspeed);


        //increase the counter variable
        _loopcount+=1;
      }
    }

    //navigate to the PAPEREMPTY state and wait 5s and navigate to paperfill state 
    if(_currentstate == PAPEREMPTY){
      Serial.println("Papers are empty!");
      delay(5000);
      _currentstate = PAPERFILL;
    }

    //navigate to the SETTING state 
    if(_currentstate == SETTING){
      do{
        _papersfullst =analogRead(_papersfull);

        //rotate M3 motor to upword till touch the paper roller
        digitalWrite(_m3ctrlpin1,HIGH);
        digitalWrite(_m3ctrlpin2,LOW);
        analogWrite(_m3spctrlpin,_m1ctrlspeed);
        delay(100);
      }while( _papersfullst == 1023);

      //power off the M3 motor to stop going upword stage
        digitalWrite(_m3ctrlpin1,LOW);
        digitalWrite(_m3ctrlpin2,LOW);
        analogWrite(_m3spctrlpin,_m1ctrlspeed);

    }
}

