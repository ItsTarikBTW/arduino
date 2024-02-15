#include <Servo.h>

const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8;

int a0Night = 240;
int a1Night = 240;
int a0Value = 0;
int a1Value = 0;

int places = 9;
bool carInput = false;
bool carOutput = false;

Servo s;



void setup(){
    Serial.begin(9600);
    s.attach(9);
    s.write(0);
    for (int i = segmentA; i <= segmentG; i++){
        pinMode(i, OUTPUT);
    }
    turnOfSegments();
    places = 9;
    carInput = false;
    carOutput = false;
    printNumber(places);
}

void loop(){

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
