#include <Servo.h>


const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8;

int a0Night = 450;
int a1Night = 300;
int a0Value = 0;
int a1Value = 0;

int places = 9;
bool carInput = false;
bool carOutput = false;
int buzzer = 11;

Servo s;

int irPin = 10;
int pinData = 10;
int key=0;
int openPassword[3] = {12,24,94};
int closePassword[3] = {8,28,90};
String openPasswordValue = "122494";
String closePasswordValue = "82890";
String readPassword = "";



void setup(){
    Serial.begin(9600);
    s.attach(9);
    s.write(0);
    for (int i = segmentA; i <= segmentG; i++){
        pinMode(i, OUTPUT);
    }
    pinMode(irPin, INPUT);
    pinMode(buzzer, OUTPUT);
    turnOfSegments();
    places = 9;
    carInput = false;
    carOutput = false;
    printNumber(places);
}


void loop(){
    // while (true) {
    //   key = getIRKey();
    //   Serial.println(key);
    // }
    
    while((key = getIRKey()) == 0){
      a0Value = analogRead(A0);
      if (a0Value < a0Night){
          if (places > 0){
              s.write(90);
              carInput = true;
          }
      }
      while (carInput){
          while (analogRead(A1) > a1Night);
          delay(500);
          while (analogRead(A1) < a1Night);
          delay(500);
          s.write(0);
          places--;
          printNumber(places);
          carInput = false;
          delay(1000);
      }

      a1Value = analogRead(A1);
      if (a1Value < a1Night){
          if (places < 9){
              s.write(90);
              carOutput = true;
          }
      }
      while (carOutput){
          while (analogRead(A0) > a0Night);
          delay(500);
          while (analogRead(A0) < a0Night);
          delay(500);
          s.write(0);
          places++;
          printNumber(places);
          carOutput = false;
          delay(1000);
      }
    }

    int i = 0;
      while (i < 3) {
        if(key == 74){
          readPassword = "";
          break;
        }
        readPassword.concat(key);
        i++;
        if(i == 3){
          break;
        }
        while ((key = getIRKey()) == 0) {}
        Serial.println(key);
        
      }
      if(readPassword == openPasswordValue){
        Serial.println("Open");
        s.write(90);
        readPassword = "";
        tone(buzzer, 800,1000);
      }else if (readPassword == closePasswordValue) {
        Serial.println("Close");
        s.write(0);
         tone(buzzer, 500,1000);
        readPassword = "";
      }
      Serial.println(key);
}

void turnOfSegments(){
    for (int i = segmentA; i <= segmentG; i++){
        digitalWrite(i, LOW);
    }
}

void print1(){
    turnOfSegments();
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
}
void print2(){
    turnOfSegments();
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentG, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentD, HIGH);
}
void print3(){
    turnOfSegments();
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentG, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
}

void print4(){
    turnOfSegments();
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
}
void print5(){
    turnOfSegments();
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
}
void print6(){
    turnOfSegments();
    for (int i = segmentA; i <= segmentG; i++){
        if (i == segmentB){
            digitalWrite(i, LOW);
        }
        else{
            digitalWrite(i, HIGH);
        }
    }
}
void print7(){
    turnOfSegments();
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
}

void print8(){
    for (int i = segmentA; i <= segmentG; i++){
        digitalWrite(i, HIGH);
    }
}

void print9()
{
    for (int i = segmentA; i <= segmentG; i++){
        if (i == segmentE){
            digitalWrite(i, LOW);
        }
        else{
            digitalWrite(i, HIGH);
        }
    }
}

void print0(){
    for (int i = segmentA; i <= segmentG; i++){
        if (i == segmentG){
            digitalWrite(i, LOW);
        }
        else{
            digitalWrite(i, HIGH);
        }
    }
}

void printNumber(int i){
    switch (i){
    case 0: print0(); break;
    case 1: print1(); break;
    case 2: print2(); break;
    case 3: print3(); break;
    case 4: print4(); break;
    case 5: print5(); break;
    case 6: print6(); break;
    case 7: print7(); break;
    case 8: print8(); break;
    case 9: print9(); break;
    }
}


boolean checkValueExist(int items[], int value){
  for (int i = 0; i < 3; i++) {
    if(items[i] == value){
      return true;
    }
  }
  return false;
}




int getIRKey() {
  uint32_t pulseBitValue=0; // Value used for reading the PulseIn() 
  uint32_t bitValue=0; // Value used for converting the pulseBitValue to 1 or 0
  uint32_t pulseOne=1200; // Threshold for Binary Value=1
  uint32_t startPulse=2600; // Threshold for StartBit
  uint32_t thePulse = pulseIn(pinData, LOW); // Initialze pulse sent
  uint32_t resultValue=0; // Initalize resultValue Returned = 0
  uint32_t bitShiftValue=0; // Initialize the Binary Shift Value
  if(thePulse > startPulse) { // Ready To Receive value when thePulse >StartBit Threshold
    // digitalWrite(statLED,HIGH); // Status LED = ON
    for(uint8_t i = 1; i <= 32; i++) { // Loop to Get 32 Pulses
      pulseBitValue=pulseIn(pinData,HIGH,10000); // Get the pulseBit Value
      bitValue=(pulseBitValue>=pulseOne)?1:0; // If pulseBitValue > Binary 1 Threshold Value then bitValue=1 else bitValue=0
      if(i>16 && i<=24) { // If the bitPosition of the PulseIn Values are between 17 and 24 ...
        resultValue=resultValue+(bitValue <<(bitShiftValue++)); // then add bitValue*2^bitShiftValue to returnValue
      }
    }
  }
  return resultValue;
}
