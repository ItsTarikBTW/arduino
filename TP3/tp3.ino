#include <Servo.h>
Servo s;
const int s1=A0;
const int s2=A1;
int t1=10;
int t2=50;
bool sb1=false;
bool sb2=false;
int c=9;


void setup() {
  // put your setup code here, to run once:
  s.attach(9);
  s.write(0);
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  

  if (sb1==false){
    if(analogRead(s1)<t1){
      sb1=true;
    }
  }

  if (sb2==false){
    if(analogRead(s2)<t2){
      sb2=true;
      
    }
  }

   if(sb1==true && sb2==false )
  {   
      s.write(90);
      Serial.println("b");
    
  }
   if(sb1==true && sb2==true){
    
    s.write(0);
    sb1=false;
    sb2=false;
    Serial.println("c");
    delay(1000);
  }
  
   if(sb2==true && sb1==false )
  {   
      s.write(90);
      Serial.println("d");
    
  }
   if(sb1==false && sb2==false){
    
    Serial.println("e");

  }

}


