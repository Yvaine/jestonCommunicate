//   2 L = 左
//   3 R = 右
//   0 F = 前
//   1 B = 後
#include <Servo.h> 

typedef struct control_signal{
  int angle; // turn angle
  float distance;
  char turn; // turn to
}ControlSignal;

int pinEN = 13;
int pinF = 9;
int pinB = 6;

ControlSignal control;

void setup()
 {
  Serial.begin(9600);     // 定義輸出腳位 
  pinMode(pinEN, OUTPUT);
  pinMode(pinB,OUTPUT); // 腳位 6 (PWM)
  pinMode(pinF,OUTPUT); // 腳位 9 (PWM)
 }
 
 void myadvance(float s ){
     digitalWrite(pinEN, HIGH);
     digitalWrite(pinF,HIGH);  // 使馬達（前进）動作
     digitalWrite(pinB,LOW);
     analogWrite(pinF,250);
     analogWrite(pinB, 0);
     delay(1 * 1000); 
     analogWrite(pinF,200);
     analogWrite(pinB, 0);
     delay((s - 6) / 3.4); 
     analogWrite(pinF, 0);
     analogWrite(pinB, 0); 
     delay(1 * 1000);
 }
 
 void myback(int a ){
     digitalWrite(pinEN, HIGH);
     digitalWrite(pinF,LOW);  // 使馬達（前进）動作
     digitalWrite(pinB,HIGH);
     analogWrite(pinF,0);
     analogWrite(pinB, 120);
     delay(a * 1000); 
 }
 
 void mystop(int a ){
     digitalWrite(pinEN, LOW);
     digitalWrite(pinF,HIGH);  // 使馬達（前进）動作
     digitalWrite(pinB,LOW);
     delay(a * 1000); 
 }

void loop()
 {
   String buff_control = "";
   while(Serial.available() > 0){
     buff_control += char(Serial.read());
     delay(2);
   }
   control.angle = *(int*)(&buff_control[0]);
   control.distance = *(float*)(&buff_control[4]);
   control.turn = *(char*)(&buff_control[8]);
   switch(control.turn){
   case '0': 
             myadvance(control.distance);
             control.angle = 0;
             delay(1000);
             break;
   case '1': myback(1);                 // 正常后退  
             mystop(1);
             delay(1000);
             break;
   case '4': mystop(1000);
             delay(1000);
             break;
#if 0
   case '2': turnL(1);                // 双轮左转
             delay(1000);
             Serial.println(turn);
             //turn = '0 ';
             break;
             
   case '3': turnR(1);                // 双轮右转 
             delay(1000);
             Serial.println(turn);
             //turn = '0 ';
             break;
#endif
   }
   //Serial.write(atoi(turn));
}

