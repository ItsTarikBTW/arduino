// Pin definitions
const int GREEN_1_PIN = 6;
const int GREEN_2_PIN = 7;
const int ORANGE_1_PIN = 5;
const int ORANGE_2_PIN = 8;
const int RED_1_PIN = 4;
const int RED_2_PIN = 9;
const int BUTTON_PIN = 3;
const int LIGHT_SENSOR_PIN = A0;

// Timing constants
const unsigned long DELAY_TIME = 1000;
const int NIGHT_DEGREE = 400; // Depend on your light sensor

// Function prototypes
void setup();
void loop();
void nightPower();
void startSequence();
void turnOffLEDs();
void controlGreenLED();
void controlOrangeLED();
void controlRedLED();
void controlSecondOrangeLED();

void setup() {
  // Set pin modes for LEDs and button
  for (int pin = GREEN_1_PIN; pin <= RED_2_PIN; pin++) {
    pinMode(pin, OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Check light intensity
  while (analogRead(LIGHT_SENSOR_PIN) < NIGHT_DEGREE) {
    nightPower();
    Serial.println(analogRead(LIGHT_SENSOR_PIN));
  }

  // Check if both orange LEDs are on
  if (digitalRead(ORANGE_1_PIN) && digitalRead(ORANGE_2_PIN)) {
    turnOffLEDs();
  }

  // Start the LED sequence
  startSequence();
}

void nightPower() {
  // Turn off all LEDs and flash orange LEDs
  turnOffLEDs();
  digitalWrite(ORANGE_1_PIN, HIGH);
  digitalWrite(ORANGE_2_PIN, HIGH);
  delay(DELAY_TIME / 2);
  digitalWrite(ORANGE_1_PIN, LOW);
  digitalWrite(ORANGE_2_PIN, LOW);
  delay(DELAY_TIME / 2);
}

void startSequence() {
  // Control LED sequence based on light intensity
  controlGreenLED();
  if (analogRead(LIGHT_SENSOR_PIN) < NIGHT_DEGREE) return;
  controlOrangeLED();
  if (analogRead(LIGHT_SENSOR_PIN) < NIGHT_DEGREE) return;
  controlRedLED();
  if (analogRead(LIGHT_SENSOR_PIN) < NIGHT_DEGREE) return;
  controlSecondOrangeLED();
}

void turnOffLEDs() {
  // Turn off all LEDs
  for (int pin = GREEN_1_PIN; pin <= RED_2_PIN; pin++) {
    digitalWrite(pin, LOW);
  }
}

void controlGreenLED() {
  // Control green LED
  digitalWrite(RED_1_PIN, LOW);
  digitalWrite(GREEN_1_PIN, HIGH);
  digitalWrite(RED_2_PIN, HIGH);
  for (int i = 0; i < 12; i++) {
    if (digitalRead(BUTTON_PIN)) {
      digitalWrite(GREEN_1_PIN, LOW);
      break;
    }
    delay(DELAY_TIME / 4);
    if (analogRead(LIGHT_SENSOR_PIN) < NIGHT_DEGREE) break;
  }
  digitalWrite(GREEN_1_PIN, LOW);
}

void controlOrangeLED() {
  // Control orange LED
  digitalWrite(ORANGE_1_PIN, HIGH);
  for (int i = 0; i < 8; i++) {
    if (analogRead(LIGHT_SENSOR_PIN) < NIGHT_DEGREE) break;
    delay(DELAY_TIME / 4);
  }
  digitalWrite(ORANGE_1_PIN, LOW);
}

void controlRedLED() {
  // Control red LED
  digitalWrite(RED_1_PIN, HIGH);
  digitalWrite(RED_2_PIN, LOW);
  digitalWrite(GREEN_2_PIN, HIGH);
  for (int i = 0; i < 20; i++) {
    if (analogRead(LIGHT_SENSOR_PIN) < NIGHT_DEGREE) break;
    delay(DELAY_TIME / 4);
  }
  digitalWrite(GREEN_2_PIN, LOW);
}

void controlSecondOrangeLED() {
  // Control second orange LED
  digitalWrite(ORANGE_2_PIN, HIGH);
  delay(DELAY_TIME * 2);
  digitalWrite(ORANGE_2_PIN, LOW);
}
