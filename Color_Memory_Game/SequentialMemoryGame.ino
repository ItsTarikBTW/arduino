
#include <LCD_I2C.h>
#include "pitches.h"
#define BUZZER_PIN 8

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LCD_I2C lcd(0x27, 16, 2);

int led1 = 2;
int led2 = 3;
int led3 = 4;
int buttonLed1 = 5;
int buttonLed2 = 6;
int buttonLed3 = 7;
int buzzer = 8;
int level = 1;

const int maxLevel = 30;
int solution[maxLevel];
int answers[maxLevel];
int delayTime = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonLed1, INPUT);
  pinMode(buttonLed2, INPUT);
  pinMode(buttonLed3, INPUT);
  Serial.begin(9600);
    // initialize the LCD
	lcd.begin();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("LEVEL");
  printLevel(level);
  playPiratesOfTheCaribbeeanSound();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < level; i++) {
    int randomLed = random(led1, led3+1);
    if(i == level-1){
      solution[i] = randomLed;
    }
    turnOffLed(solution[i], delayTime);
  }

  
  bool rightRound = true;
  for (int i = 0; i < level; i++) {
    unsigned long startTime = millis();
    int buttonClicked1;
    int buttonClicked2;
    int buttonClicked3;
    while ((buttonClicked1 = digitalRead(buttonLed1) )!=1 && (buttonClicked2 = digitalRead(buttonLed2)) !=1 &&(buttonClicked3 = digitalRead(buttonLed3) )!=1 ){
      if(millis() - startTime > 5000){
        Serial.println("Game over");
        level = 1;
        printLevel(level);
        rightRound = false;
        break;
      }
    }

    if (buttonClicked1) {
      Serial.println("Button 1");
      answers[i] = led1;
    }else if(buttonClicked2){
      Serial.println("Button 2");
      answers[i] = led2;
    }else if(buttonClicked3){
      Serial.println("Button 3");
      answers[i] = led3;
    }
    turnOffLed(answers[i], delayTime/2);
    if(answers[i] != solution[i]){
      Serial.println(answers[i]);
      Serial.println(solution[i]);
      Serial.println("Game over");
      rightRound = false;
      break;
    }
  }
  
  for (int i = 0; i < level; i++) {
    if(solution[i] != answers[i]){
      rightRound = false;
      break;
    }
  }

  if(rightRound){
    level++;
    Serial.print("New level: ");
    Serial.println(level);
    tone(buzzer,800, 500);
  }
  if (level > maxLevel ) {
    level = 1;
    Serial.println("Game done");
    if(rightRound)
    resetGame();
  }
  if(!rightRound){
    resetGame();
    level = 1;
    tone(buzzer,500, 500);
  }
  printLevel(level);
  delay(delayTime * 2);
}


void turnOffLed(int led, unsigned long delayTime){
  	tone(buzzer,led*100,300);
  digitalWrite(led, HIGH);
  delay(delayTime);
  digitalWrite(led, LOW);
  delay(delayTime);
}

void resetGame(){
  Serial.println("Game over");
    for (int i = 0; i < maxLevel; i++) {
      solution[i] = 0;
      answers[i] = 0;
    }
  playGameOverSound();
    for(int i = 0; i < 3; i++){
      tone(buzzer,500, 500);
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH); 
      delay(500);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      delay(500);
    }
}

void printLevel(int level){
  
  for(int i = 0; i < 16; i++){
    lcd.setCursor(i, 1);
    lcd.print("");
  }
  lcd.setCursor(7, 1);
  lcd.print(level);
}



void playGameOverSound(){

  int melody[] = {
  // Game over sound
  NOTE_C5, NOTE_G4, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_AS4, NOTE_GS4,
  NOTE_G4, NOTE_D4, NOTE_E4
};


int durations[] = {
  //game over sound
  4, 4, 4,
  8, 8, 8, 8, 8, 8,
  8, 8, 2
};

  
int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}



void playPiratesOfTheCaribbeeanSound(){
	int melody[] = {
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
  NOTE_A4, NOTE_G4, NOTE_A4, REST,
  
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,
  
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
  NOTE_D5, NOTE_E5, NOTE_A4, REST,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
  NOTE_C5, NOTE_A4, NOTE_B4, REST,
  
  NOTE_A4, NOTE_A4,
 
};

int durations[] = {
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 8, 8,
  8, 8, 8, 4, 8,
  
  8, 8, 4, 8, 8,
  4, 8, 4, 8,
  8, 8, 4, 8, 8,
  8, 8, 4, 4,
  
  4, 8,

};
  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}


void playMilody(int* melody, int* durations){

  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}