int B1Pointer = 10;    // First button pin
int BCount = 3;        // Number of buttons
int LED1Pointer = 3;   // First LED pin
int LEDCount = 7;      // Number of LEDs

int state=0;

void setup()
{
    for (int i = 0; i < BCount; i++)
        pinMode(B1Pointer + i, INPUT);
    for (int i = 0; i < LEDCount; i++)
        pinMode(LED1Pointer + i, OUTPUT);
    allBlink(200);
    Serial.begin(9600);
}

void loop()
{

  for (int i = 0; i < BCount; i++)
    {
        if (digitalRead(B1Pointer + i) == HIGH)
        {
          if(i==0){
            Serial.print("Dic   :");
            Serial.println(state);
            state=(state*2)%128;
            Serial.print("binary:");
            Serial.println(reverseString(toBinary(state)));
            Serial.print("Dic *2:");
            Serial.println(state);
            Serial.println("----------------");
            bineryToLED(toBinary(state));
          }else if(i==1){
            if(state==0)
              state=127;
            else
              state--;
            bineryToLED(toBinary(state));
          }else if(i==2){
            state=(state+1)%128;
            bineryToLED(toBinary(state));
          }
          
        }
    }
    delay(300);
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
String toBinary(int number){
  String output="";
  for (int i =0; i<7;i++) {
    output=output+String(number%2);
    number=number/2;
    delay(30);
  }
  return output;
}
void bineryToLED(String num){
  for (int i=0; i<LEDCount; i++) {
    if(num.charAt(i)=='1'){
      digitalWrite(LED1Pointer+i, HIGH);
    }
    else{
      digitalWrite(LED1Pointer+i, LOW);
    }

  }
}
String reverseString(String s){
  String tmp="";
  for (int i=LEDCount-1; i>0; i--) {
    tmp+=s.charAt(i);
  }
  return tmp;
}
