int led1 = 5;
int led2 = 7;
int led3 = 9;
int buttonLed1 = 4;
int buttonLed2 = 6;
int buttonLed3 = 8;
int buttonOI = 10;
int buzzer = 3;
int level;
int isOn = 0;

void setup()
{
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(buttonLed1, INPUT);
    pinMode(buttonLed2, INPUT);
    pinMode(buttonLed3, INPUT);
    pinMode(buttonOI, INPUT);
    initLevel();
    Serial.begin(9600);
}
void loop()
{
    // blinkAll(500);
    while (!isOn)
    {
        if (digitalRead(buttonOI) == HIGH)
        {
            isOn = 1;
            initLevel();
        }
    }
    int randLed = random(1, 4);
    blink(randLed, 600);
    unsigned long currentTimeStamp = millis();
    int didYouPress = 0;
    // for(int i = 0; i < level*10; i++)
    unsigned long tmp;
    int q = 1;
    unsigned long quarterTime = level * 25;
    while ((tmp = millis()) <= currentTimeStamp + level * 100 && didYouPress == 0 && isOn == 1)
    {
        if (tmp <= currentTimeStamp + quarterTime * q)
        {
            tone(buzzer, 1200, 100);
            q++;
        }

        Serial.println("Level: " + String(level));
        if (digitalRead(buttonLed1) == HIGH)
        {
            buttonPressed(1, randLed);
            didYouPress = 1;
        }
        if (digitalRead(buttonLed2) == HIGH)
        {
            buttonPressed(2, randLed);
            didYouPress = 1;
        }
        if (digitalRead(buttonLed3) == HIGH)
        {
            buttonPressed(3, randLed);
            didYouPress = 1;
        }
        if (digitalRead(buttonOI) == HIGH)
        {
            isOn = 0;
            delay(500);
            didYouPress = 1;
            playBuzzer(100);
        }
    }
    Serial.println(isOn);
    if (!didYouPress)
    {
        playBuzzer(100);
        blinkAll(500);
        initLevel();
    }
    if (level == 0)
    {
        Serial.println("You are the chosen one");
        blinkAll(500);
        delay(1000);
        blinkAll(500);
    }
}
void initLevel()
{
    level = 20;
    delay(1000);
}
void blink(int led, int time)
{
    allLeds(LOW);
    ledControl(led, HIGH);
    delay(time);
    ledControl(led, LOW);
    delay(time);
}
void blinkAll(int time)
{
    allLeds(HIGH);
    delay(time);
    allLeds(LOW);
    delay(time);
}
void buttonPressed(int button, int randLed)
{
    if (button == randLed)
    {
        level--;
        playBuzzer(200);
    }
    else
    {
        playBuzzer(100);
        blinkAll(500);
        initLevel();
    }
}
void ledControl(int led, int state)
{
    switch (led)
    {
    case 1:
        digitalWrite(led1, state);
        break;
    case 2:
        digitalWrite(led2, state);
        break;
    case 3:
        digitalWrite(led3, state);
        break;
    default:
        break;
    }
}
void allLeds(int state)
{
    digitalWrite(led1, state);
    digitalWrite(led2, state);
    digitalWrite(led3, state);
}
void playBuzzer(int time)
{
    tone(buzzer, 1000, time);
}