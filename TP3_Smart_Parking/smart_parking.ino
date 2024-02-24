#include <Servo.h>

#define ON HIGH // If you are using a common anode display, change this to LOW
#define OFF LOW // If you are using a common anode display, change this to HIGH
#define irSize 11
#define PI_LENGTH 3
#define PO_LENGTH 3

const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8;

int a0Night = 240; // Depend on your LDR sensor
int a1Night = 240; // Depend on your LDR sensor
int a0Value = 0;
int a1Value = 0;

int places = 9;
bool carInput = false;
bool carOutput = false;
int buzzer = 11;
int irPin = 10;
int pinData = 10;
int key=0;

int irRow[irSize]={12,16,17,18,20,21,22,24,25,26,14};
char* irEquivalence[irSize]={"0","1","2","3","4","5","6","7","8","9","reset"};
char* PASSWORD_I[PI_LENGTH]={"1","2","3"};
char* PASSWORD_O[PO_LENGTH]={"4","5","6"};
int indexI=0;
int indexO=0;

Servo s;

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
    indexI = 0;
    indexO = 0;
    printNumber(places);
}


void loop(){
  
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
  
  
  int press = findIndex(irRow,irSize,key);
  char* eq=getEquivalence(press);

  if(press != -1){
    if(press<10){
    String(eq).equals(String(PASSWORD_I[indexI]))?indexI++ : indexI=0;
    String(eq).equals(String(PASSWORD_O[indexO]))?indexO++ : indexO=0;
    }else if(String(eq).equals(String("reset"))){
      indexI=0;
      indexO=0;
      tone(buzzer, 800,200);
    }
    Serial.print(key);
    Serial.print(" : ");
    Serial.println(press);
    printNumber(press);
    if(indexI == PI_LENGTH ){
      indexI=0;
      Serial.println("password is correct,THE GATE IS OPENED");
      s.write(90);
      printNumber(places);
      tone(buzzer, 500,200);
    }
    if(indexO == PO_LENGTH ){
      indexO=0;
      Serial.println("password is correct,THE GATE IS CLOSED");
      s.write(0);
      printNumber(places);
      tone(buzzer, 800,200);
    }
  }
}

int findIndex(int* T,int lentgh,int c) {
  for (int j = 0; j < lentgh; j++) {
    if (c == T[j]) {
      return j;
    }
  }
  return -1;
}

char* getEquivalence(int index){
  if(index != -1)
	return irEquivalence[index];
  else
    return "-1";
}

void turnOfSegments(){
    for (int i = segmentA; i <= segmentG; i++){
        digitalWrite(i, OFF);
    }
}

void print1(){
    turnOfSegments();
    digitalWrite(segmentB, ON);
    digitalWrite(segmentC, ON);
}

void print2(){
    turnOfSegments();
    digitalWrite(segmentA, ON);
    digitalWrite(segmentB, ON);
    digitalWrite(segmentG, ON);
    digitalWrite(segmentE, ON);
    digitalWrite(segmentD, ON);
}

void print3(){
    turnOfSegments();
    digitalWrite(segmentA, ON);
    digitalWrite(segmentB, ON);
    digitalWrite(segmentG, ON);
    digitalWrite(segmentC, ON);
    digitalWrite(segmentD, ON);
}

void print4(){
    turnOfSegments();
    digitalWrite(segmentF, ON);
    digitalWrite(segmentG, ON);
    digitalWrite(segmentB, ON);
    digitalWrite(segmentC, ON);
}

void print5(){
    turnOfSegments();
    digitalWrite(segmentA, ON);
    digitalWrite(segmentF, ON);
    digitalWrite(segmentG, ON);
    digitalWrite(segmentC, ON);
    digitalWrite(segmentD, ON);
}

void print6(){
    turnOfSegments();
    for (int i = segmentA; i <= segmentG; i++){
        if (i == segmentB){
            digitalWrite(i, OFF);
        }
        else{
            digitalWrite(i, ON);
        }
    }
}

void print7(){
    turnOfSegments();
    digitalWrite(segmentA, ON);
    digitalWrite(segmentB, ON);
    digitalWrite(segmentC, ON);
}

void print8(){
    for (int i = segmentA; i <= segmentG; i++){
        digitalWrite(i, ON);
    }
}

void print9(){
    for (int i = segmentA; i <= segmentG; i++){
        if (i == segmentE){
            digitalWrite(i, OFF);
        }
        else{
            digitalWrite(i, ON);
        }
    }
}

void print0(){
    for (int i = segmentA; i <= segmentG; i++){
        if (i == segmentG){
            digitalWrite(i, OFF);
        }
        else{
            digitalWrite(i, ON);
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
