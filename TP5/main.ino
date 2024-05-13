int b1 = 3;
int l1 = 6;
int b2 = 4;
int l2 = 7;
int b3 = 5;
int l3 = 8; 
  int b[3] = {3,4,5};
   int l[3] = {6,7,8};
int buz=9;
    int level = 1;
    int pos[3] = {0,1,2};
    int areYouWiningSon=1;

void setup()
{
    pinMode(b1, INPUT);
    pinMode(l1, OUTPUT);
    pinMode(b2, INPUT);
    pinMode(l2, OUTPUT);
    pinMode(b3, INPUT);
    pinMode(l3, OUTPUT);
        pinMode(buz, OUTPUT);

    Serial.begin(9600);
}
void loop()
{
  areYouWiningSon=1;
    level=1;
  while (areYouWiningSon) {
    //! TODO: generate random number 0 to 2
    int goals[12];
    goals[level-1] = random(3);
    //int goal = random(3);
    //Serial.println(goal);
      Serial.print("level");
      Serial.println(level);
    for (int i =0; i<level; i++) {
      Serial.print("goals[i]=");
      Serial.println(goals[i]);
      ledOff();
      delay(500);
      digitalWrite(l[goals[i]], HIGH);
      tone(buz, 300);
      delay(1000);
      noTone(buz);
      digitalWrite(l[goals[i]], LOW);
      delay(600);
    }
    for (int k=0; k<level; k++) {
      int danger[2] = {3,3};
      int j = 0;
      for(int i=0;i<3;i++){
        if(i!=goals[k]){
          danger[j]= i;
          j++;
        }
      }
      while (true)
      {
        if(digitalRead(b[goals[k]])){
          ledIndex(goals[k]);
          Serial.println("ouga bouga");
          break;
        }
        else if(digitalRead(b[danger[0]]) ){
          ledIndex(danger[0]);
          gameOver();
          break;
        }
        else if(digitalRead(b[danger[1]])){
          ledIndex(danger[1]);
          gameOver();
          break;
        }
      }
      Serial.println("exit while");
    }
    level++;
    delay(500);
  }
}
//! TODO:
void gameOver()
{
  for (int i=0; i<3; i++) {
    ledOn();
    tone(buz, 500);
    delay(350);
    noTone(buz);
    ledOff();
    delay(350);
  }
  Serial.println("bad monky");
  areYouWiningSon=0;
}
void ledOff()
{
    digitalWrite(l3, LOW);
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
}
void ledOn()
{
    digitalWrite(l3, HIGH);
    digitalWrite(l1, HIGH);
    digitalWrite(l2, HIGH);
}
void ledIndex(int g)
{
  ledOff();
    digitalWrite(l[g], HIGH);
    delay(500);
    digitalWrite(l[g], LOW);
    delay(500);
}