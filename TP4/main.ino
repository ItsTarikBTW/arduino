#include<Stepper.h>
#include<Servo.h>

Stepper stepper(100,8,10,9,11);
Servo servo;


int night = 100;

int stageLed0 = 0;
int stageLed1 = 2;
int stageLed2 = 4;
int stageLed3 = 6;
int stageButton0 = 1; 
int stageButton1 = 3; 
int stageButton2 = 5; 
int stageButton3 = 7; 
int servoPin = 12;
int buzzer = 13;


int stageHeight0 = 6000;
int stageHeight1 = 6000;
int stageHeight2 = 12000;
int stageHeight3 = 6000;
int stage = 0;

void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(300);
  servo.attach(servoPin);
  pinMode(buzzer, OUTPUT);
  pinMode(stageLed0, OUTPUT);
  pinMode(stageLed1, OUTPUT);
  pinMode(stageLed2, OUTPUT);
  pinMode(stageLed3, OUTPUT);
  pinMode(stageButton0, INPUT);
  pinMode(stageButton1, INPUT);
  pinMode(stageButton2, INPUT);
  pinMode(stageButton3, INPUT);
  servo.write(0);
  stage = 0;
  digitalWrite(stageLed0, HIGH);
  // Serial.begin(9600);
}

void loop() {


  // while(true){
  //   Serial.println(analogRead(A0));
  //   delay(500);
  // }

  int buttonRead0;
  int buttonRead1;
  int buttonRead2;
  int buttonRead3;

  while((buttonRead0 = digitalRead(stageButton0)) == 0 && (buttonRead1 = digitalRead(stageButton1))==0 && (buttonRead2 = digitalRead(stageButton2))==0 && (buttonRead3 = digitalRead(stageButton3)) == 0);
  turnOffLeds();
  
  int oldStage = stage;

  if(buttonRead0){
    digitalWrite(stageLed0, HIGH);
    stage = 0;
    buttonRead0 = 0;
  }else if(buttonRead1){
    digitalWrite(stageLed1, HIGH);
    stage = 1;
    buttonRead1 = 0;
  }else if(buttonRead2){
    digitalWrite(stageLed2, HIGH);
    stage = 2;
    buttonRead2 = 0;
  }else if(buttonRead3){
    digitalWrite(stageLed3, HIGH);
    stage = 3;
    buttonRead3 = 0;
  }
  int upOrDown = oldStage > stage ? -1: 1;
  int step = oldStage-stage;

  step = step > 0 ? step : -step;
  stepper.step(upOrDown * stageHeight0*(step));
  openDor(digitalRead(servoPin),90);
  tone(buzzer,1000 ,800);
  delay(5000);
  closeDor();




  // put your main code here, to run repeatedly:
  // stepper.step(stageHeight2);
  // delay(2000);
  // stepper.step(-stageHeight2);
  // delay(2000);
}


void turnOffLeds(){
  digitalWrite(stageLed0, LOW);
  digitalWrite(stageLed1, LOW);
  digitalWrite(stageLed2, LOW);
  digitalWrite(stageLed3, LOW);
}

void openDor(int from, int to){
  for(int i = from; i <= to; i++){
    servo.write(i);
    delay(25);
  }
}

void closeDor(){
    for(int i = 90; i >= 0; i--){
    servo.write(i);
    if(analogRead(A0) < night){
      openDor(i, 90);
      break;
    }
    delay(25);
  }
  if(servo.read() != 0){
    delay(1000);
    closeDor();
  }
}