
#include <LCD_I2C.h>
#include "pitches.h"
#define BUZZER_PIN 9

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Initialize LCD
LCD_I2C lcd(0x27, 16, 2);

// Define pins for components
const int ledPins[] = {4, 6, 8};      // LED pins
const int buttonPins[] = {3, 5, 7};   // Button pins
const int onOffButtonPin = 2;         // On/Off button pin 

const int maxLevel = 30;
int level = 1;
long int gameDelay = 2000;
bool isGameOn = false;

void setup() {
  // Initialize components
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);  // Use internal pull-up resistors
  }
  pinMode(onOffButtonPin, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  
  // initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("LEVEL");
  printLevel(level);
  playPiratesOfTheCaribbeeanSound();
  delay(2000);
}

void loop() {
  // Check if the game is turned on
  if (digitalRead(onOffButtonPin) == HIGH) {
    isGameOn = !isGameOn;
    delay(200); // debounce delay
  }

  if (isGameOn) {
    // Generate a random LED to light up
    int randomLedIndex = random(0, 3);
    int randomLedPin = ledPins[randomLedIndex];
    digitalWrite(randomLedPin, HIGH);
    delay(1000);
    digitalWrite(randomLedPin, LOW);

    // Check if the player pressed the corresponding button
    int buttonPressed = waitForButtonPress(gameDelay); // Wait for 5 seconds (5000 milliseconds)
    
    if (buttonPressed == randomLedPin) {
      // Player pressed the correct button
      level++;
      gameDelay -= 100;
      lcd.clear();
      printLevel(level);
      tone(BUZZER_PIN, 800, 500);
    } else {
      // Player made a mistake or timed out
      resetGame();
      level = 1;
      lcd.clear();
      printLevel(level);
      tone(BUZZER_PIN, 500, 500);
    }

    // Check if the game is completed
    if (level > maxLevel) {
      level = 1;
      lcd.clear();
      lcd.print("Game done");
      if (isGameOn) {
        resetGame();
      }
    }

    // Wait before the next round
    delay(gameDelay);
  }
}

int waitForButtonPress(int timeoutMillis) {
  unsigned long startTime = millis();
  int i = 1;
  long int buzzerDelay = timeoutMillis / 4;

  while (millis() - startTime < timeoutMillis) {
    for (int i = 0; i < 3; i++) {
      if (digitalRead(buttonPins[i]) == HIGH) {
        return ledPins[i];
      }
    }
    if (digitalRead(onOffButtonPin) == HIGH) {
      isGameOn = !isGameOn;
      delay(200); // debounce delay
      return onOffButtonPin;
    }

    // Blink the buzzer
    if (millis() - startTime > i * buzzerDelay) {
      i++;
      tone(BUZZER_PIN, 800, buzzerDelay);
      delay(100);
    }
  }

  // If no button is pressed within the timeout, return -1
  return -1;
}


void resetGame(){
  Serial.println("Game over");
  gameDelay = 2000;
  playGameOverSound();
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        digitalWrite(ledPins[j],HIGH);
      }
       
      tone(BUZZER_PIN,500, 500);
      delay(500);
      for(int j = 0; j < 3; j++){
        digitalWrite(ledPins[j],LOW);
      }
      delay(500);
    }
}

void printLevel(int level){
  Serial.print("Level: ");
  Serial.println(level);
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