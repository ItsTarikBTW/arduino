#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according
int b1 = 2;
int b2 = 3;
int b3 = 4;
int night = 70;

int LIGHT_SENSOR_PIN = A0;

int state = 0;
int mode = 1;
int line = 0;
int speed = 500;
int index = 0;
int areYouWiningSon = 1;

// array 2 String
String obs[2] = "";
int initG;
int timer = 3;

void setup()
{
    lcd.begin();

    pinMode(b1, INPUT);
    pinMode(b2, INPUT);
    pinMode(b3, INPUT);
    pinMode(LIGHT_SENSOR_PIN, INPUT);
    Serial.begin(9600);
    for (int i = 0; i < 20; i++)
    {
        obs[0] += train(obs[0]);
        obs[1] += train(obs[1]);
    }
}

void loop()
{
    // Serial.println(obs);
    lcd.clear();
    if (digitalRead(b1) == HIGH) // start/stop
    {
        if (state == 0)
        {
            lcd.backlight();
            state = 1;
        }
        else
        {
            lcd.noBacklight();
            state = 0;
        }
    }
    else if (digitalRead(b2) == HIGH) // mode switch
    {
        mode = !mode;
        initG = 1;
    }
    else if (digitalRead(b3) == HIGH) // move up/down
    {
        line = !line;
    }
    if (mode == 1)
    {
        lcd.setCursor(6, 0);                             // Or setting the cursor in the desired position.
        lcd.print(String(analogRead(LIGHT_SENSOR_PIN))); // You can make spaces using well... spaces
        lcd.setCursor(5, 1);                             // Or setting the cursor in the desired position.
        if (analogRead(LIGHT_SENSOR_PIN) < night)
        {
            lcd.print("night");
        }
        else
        {
            lcd.print(" day");
        }
    }
    else if (areYouWiningSon == 1)
    {
        if (initG == 1)
        {
            for (int i = 0; i < timer; i++)
            {
                lcd.setCursor(3, 0);
                lcd.print(String("Start in "));
                lcd.setCursor(6, 1);
                lcd.print(String(timer - i));
                delay(1000);
            }
            initG = 0;
        }
        lcd.setCursor(0, line);
        lcd.print("$");
        if (index < 15)
            lcd.setCursor(index, 0);
        else
            lcd.setCursor(0, 0);
        lcd.print(obs[0].substring(index, index + 16));
        if (index < 15)
            lcd.setCursor(index, 0);
        else
            lcd.setCursor(0, 0);
        lcd.print(obs[1].substring(index, index + 16));
        if (obs[line][index] == '@' && index > 16)
        {
            areYouWiningSon = 0;
        }
        index++;
    }
    else
    {
        // game over
        lcd.setCursor(6, 0);
        lcd.print("GAME");
        lcd.setCursor(6, 1);
        lcd.print("OVER");
    }
    delay(speed);
}

String CreateObject()
{
    String object = "";
    int random1 = random(1, 4);
    for (int i = 0; i < random1; i++)
    {
        object += "@";
    }
    return object;
}
String CreateSpace()
{
    String space = "";
    int random2 = random(8, 12);
    for (int i = 0; i < random2; i++)
    {
        space += " ";
    }
    return space;
}
String train(String obs)
{
    // generate object
    obs += CreateObject();
    obs += CreateSpace();
    return obs;
}