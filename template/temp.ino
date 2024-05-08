int B1Pointer = 3;                        // First button pin
int BCount = 4;                           // Number of buttons
int LED1Pointer = 7;                      // First LED pin
int LEDCount = 4;                         // Number of LEDs
int lastLed = LED1Pointer + LEDCount - 1; // Last LED pin
int lastButton = B1Pointer + BCount - 1;  // Last button pin
int buzzer = 12;                          // Buzzer pin
int tones[] = {440, 494, 523};            // tone frequencies
int lightSensorPin = A0;                  // Analog pin for light sensor
int sunSet = 20;                          // Light sensor value for sunset

int state; // Current state of the system
int light;

void setup()
{
    state = 0;
    for (int i = 0; i < BCount; i++)
        pinMode(B1Pointer + i, INPUT);
    for (int i = 0; i < LEDCount; i++)
        pinMode(LED1Pointer + i, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(lightSensorPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    light = analogRead(lightSensorPin);
    Serial.print(state);
    Serial.print(" ");
    Serial.print(light);
    Serial.print(" ");
    Serial.println(lastButton);

    while (state == 0)
    {
        if (digitalRead(lastButton) == HIGH)
        {
            state = 1;
            digitalWrite(lastLed, HIGH);
            delay(2);
        }
    }

    for (int i = 0; i < BCount; i++)
    {
        if (digitalRead(B1Pointer + i) == HIGH)
        {
            if (i == BCount - 1)
            {
                state = 0;
                digitalWrite(lastLed, LOW);
            }
            else
            {
                digitalWrite(LED1Pointer + i, HIGH);
                tone(buzzer, tones[i], 100);
                delay(100);
                leds(LOW);
            }
            delay(2);
        }
    }
    delay(5);
}

void leds(int state)
{
    for (int i = 0; i < LEDCount - 1; i++)
        digitalWrite(LED1Pointer + i, state);
}
void allBlink(int delayTime)
{
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < LEDCount; i++)
            digitalWrite(LED1Pointer + i, HIGH);
        delay(delayTime);
        for (int i = 0; i < LEDCount; i++)
            digitalWrite(LED1Pointer + i, LOW);
        delay(delayTime);
    }
}
void blink(int pin, int delayTime)
{
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
}
//game over
