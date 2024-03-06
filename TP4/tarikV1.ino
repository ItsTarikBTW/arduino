#include <Stepper.h>
#include <Servo.h>

Stepper s(100, 8, 10, 9, 11);

int buzzer = 6;

int b1 = 7;
int l1 = 5;
int b2 = 13;
int l2 = 4;
int b3 = 12;
int l3 = 3;

int FloreCount = 3;
int currentFlore = 1;

int distance = -1800;

void setup()
{
    pinMode(l1, OUTPUT);
    pinMode(l2, OUTPUT);
    pinMode(l3, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(b1, INPUT);
    pinMode(b2, INPUT);
    pinMode(b3, INPUT);
    ledOff();
    digitalWrite(l1, HIGH);
    Serial.begin(9600);
}

void loop()
{
    /*
    s.setSpeed(300);
    s.step(1800);
    delay(2000);
    */
    if (digitalRead(b1) || digitalRead(b2) || digitalRead(b3))
    {

        Serial.print("1:");
        Serial.print(digitalRead(b1));
        Serial.print("2:");
        Serial.print(digitalRead(b2));
        Serial.print("3:");
        Serial.println(digitalRead(b3));
    }
    if (digitalRead(b1) == HIGH && currentFlore!=1)
    {
        moveFlore(1);
        delay(2000);
        ledOff();
        digitalWrite(l1, HIGH);
        tone(buzzer, 1000, 200);
    }
    if (digitalRead(b2) == HIGH && currentFlore!=2)
    {
        moveFlore(2);
        delay(2000);
        ledOff();
        digitalWrite(l2, HIGH);
        tone(buzzer, 1000, 200);
    }
    if (digitalRead(b3) == HIGH && currentFlore!=3)
    {
        moveFlore(3);
        delay(2000);
        ledOff();
        digitalWrite(l3, HIGH);
        tone(buzzer, 1000, 200);
    }
}
void moveFlore(int flore)
{
    if (flore > currentFlore)
    {
        s.setSpeed(300);
        s.step(distance * (flore - currentFlore));
        currentFlore = flore;
    }
    else if (flore < currentFlore)
    {
        s.setSpeed(300);
        s.step(-distance * (currentFlore - flore));
        currentFlore = flore;
    }
}
void ledOff()
{
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
}