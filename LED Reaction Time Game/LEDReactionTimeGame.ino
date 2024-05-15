
#define NIGHT_VALUE 60
#define GAME_DELAY 1000
int redLedPin = 2;
int ledPins[] = {3,4,5,6,7,8,9};
int buttonsPins[] = {10,11};
unsigned long gameLedDelay = GAME_DELAY;

bool gameOver = false;
int level = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(redLedPin, LOW);
  
  // Init buttons pins
  for (int i = 0; i < 2; i++) {
    pinMode(buttonsPins[i], INPUT);
  }

  // Init leds pins
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  level = 1;

}

void loop() {
  // put your main code here, to run repeatedly:


  // while (true) {
  //     Serial.println(digitalRead(10));
  // }
  if(digitalRead(buttonsPins[0]) == 1){

    while (digitalRead(buttonsPins[0]) == 1) {
    }
    // init game
    digitalWrite(redLedPin, HIGH);
    delay(500);
    int ledIndex = 0;
    // unsigned long newGameDelay = gameLedDelay;
    int buttonPrevious1 = 0;
    int buttonPrevious2 = 0;
    
    while(true){
      digitalWrite(ledPins[ledIndex], HIGH);
      
      for(int i = 0; i < gameLedDelay; i++){
        bool buttonClicked = false;
        delay(1);

        if(digitalRead(buttonsPins[0]) == 1){
          // Reset game and turn of game;
          resetGame();
          digitalWrite(redLedPin, LOW);
          digitalWrite(ledPins[ledIndex], LOW);
          delay(200);
          return;
        }


        buttonPrevious2 = buttonPrevious1;
        buttonPrevious1 = digitalRead(buttonsPins[1]);



        // if(digitalRead(buttonsPins[1]) == 1 || analogRead(A0) < NIGHT_VALUE){
          
        //   Serial.println("DOWN");
        //    if(digitalRead(buttonsPins[1]) != 1 && analogRead(A0) > NIGHT_VALUE){
        //     Serial.println("UP");
        //       buttonClicked = true;
        //       // delay(200);
        //    }else{
        //     buttonClicked = false;
        //    }
        // }


        if(buttonPrevious2 > buttonPrevious1){
          // if(buttonClicked){
          if(ledIndex < 2){
            Serial.println("Level UP");
            gameLedDelay -= 100;
            if(gameLedDelay < 200){
              gameLedDelay = 100;
            }
            level++;
            Serial.print("New game delay: ");
            Serial.println(gameLedDelay);
          }else{
            gameOver = true;
            Serial.println("Game over");
          }
          buttonClicked = false;
        }
      }
      digitalWrite(ledPins[ledIndex], LOW);

      if(gameOver){
        resetGame();
        gameLedDelay = GAME_DELAY;
        ledIndex = 0;
        Serial.println("Game over");
        gameOverBlink();
        continue;
      }
      ledIndex++;
      if(ledIndex == 7){
        ledIndex = 0;
        // gameLedDelay = newGameDelay;
      }
    }

  }



}

void resetGame(){
  level = 1;
  gameLedDelay = GAME_DELAY;
  gameOver = false;
}

void gameOverBlink(){

    for (int i = 0 ; i < 3; i++) {
        for (int i = 0; i < 7; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(300);
    for (int i = 0; i < 7; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(300);
  }

}
