const int t = 200; //threshold 
int index = 14;    //led index
int n = 0;		  //buzzer loop
const int button1 = 6;
const int button2 = 5;
const int piezo = 4;

void setup() {
  Serial.begin(9600);
  for (int i = 13; i >= 7; i--) {
    pinMode(i, OUTPUT);
  }
  pinMode(piezo, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
}

void handleButton1Press() {
  if (digitalRead(button1) == HIGH) {
    while (true) {
      if (digitalRead(button1) == LOW) {
        digitalWrite(index, LOW);
        index--;
        n++;
        if (index == 6) {
          index = 13;
          n = 1;
        }
        break;
      }
    }
    digitalWrite(index, HIGH);
  }
}

void handleButton2Press() {
  if (digitalRead(button2) == HIGH) {
    while (true) {
      if (digitalRead(button2) == LOW) {
        for (int j = 0; j < n; j++) {
          delay(300);
          digitalWrite(piezo, HIGH);
          delay(500);
          digitalWrite(piezo, LOW);
        }
        break;
      }
    }
  }
}

void handleAnalogInput() {
  if (analogRead(A0) < t) {
    while (true) {
      if (analogRead(A0) > t) {
        digitalWrite(index, LOW);
        index--;
        n++;
        if (index == 6) {
          index = 13;
          n = 1;
        }
        break;
      }
    }
    digitalWrite(index, HIGH);
  }
}

void loop() {
  handleButton1Press();
  handleButton2Press();
  handleAnalogInput();
}
