int B1Pointer = 5;       // First button pin
int BCount = 2;          // Number of buttons
int LED1Pointer = 7;     // First LED pin
int LEDCount = 7;        // Number of LEDs
int buzzer = 4;          // Buzzer pin
int lightSensorPin = A0; // Analog pin for light sensor
int sunSet = 100;        // Light sensor value for sunset

int index; // Current index of the system
int light;

void setup()
{
    index = -1;
    for (int i = 0; i < BCount; i++)
        pinMode(B1Pointer + i, INPUT);
    for (int i = 0; i < LEDCount; i++)
        pinMode(LED1Pointer + i, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(A0, INPUT);
    Serial.begin(9600);
    leds(LOW);
}

void loop()
{
    light = analogRead(A0);

    for (int i = 0; i < BCount; i++)
    {
        if (digitalRead(B1Pointer + i) == HIGH)
        {
            if (i == 0)
            {
                index = (index + 1) % LEDCount;
                leds(LOW);
                digitalWrite(LED1Pointer + index, HIGH);
            }
            else if (i == 1)
            {
                for (int k = 0; k <= index; k++)
                {
                    tone(buzzer, 400);
                    delay(200);
                    noTone(buzzer);
                    delay(150);
                }
            }
            delay(200);
        }
    }
    if (light < sunSet)
    {
        while (analogRead(A0) < sunSet);
        index = (index + 1) % LEDCount;
        leds(LOW);
        digitalWrite(LED1Pointer + index, HIGH);
    }
    delay(200);
}

void leds(int state)
{
    for (int i = 0; i < LEDCount; i++)
        digitalWrite(LED1Pointer + i, state);
}