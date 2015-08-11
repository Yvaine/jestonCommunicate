#include "DFMobile.h"

typedef struct control_{
  int LeftWheelSpeed;
  int RightWheelSpeed;
}Control;

Control tk1_control = {0,0};

DFMobile Robot(4,5,7,6);


void setup(){
  Serial.begin(19200);
  //Serial.begin(115200);
  //Robot.Direction(true, true);
}

//tk1_control.LeftWheelSpeed = 0;
//tk1_control.RightWheelSpeed = 0;

void loop(){
   static char buff_control[8];
   static int number_serial = 0;
 
  while(Serial.available() > 0 && number_serial < 8){
    buff_control[number_serial] = char(Serial.read());
    number_serial++;
    delay(2);
  }
  
  if(number_serial == 8){
  tk1_control.LeftWheelSpeed = *(int *)(&buff_control[0]);
  tk1_control.RightWheelSpeed = *(int *)(&buff_control[4]);
  Robot.Speed(tk1_control.LeftWheelSpeed,tk1_control.RightWheelSpeed);
  delay(1000);
  number_serial = 0;
  //buff_control ="";
  }
  else{
  Robot.Speed(0,0);
  }
}
