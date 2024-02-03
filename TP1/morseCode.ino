#define TimeDot 200 
#define TimeDash TimeDot*3
#define TimeSpaceBC TimeDash //Between characters
#define TimeSpaceBW TimeDot*7 //Between words
int led;
int piezo;
char* input="tarik sos";
int i=0;

const char* morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

const char chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void trigger(int duration){
    digitalWrite(led, HIGH); 
    tone(piezo, 600,duration); 
    delay(duration); 
    digitalWrite(led, LOW);
}
void setup()
{
  led=9;
  piezo=6;
  pinMode(led, OUTPUT);
  pinMode(piezo, OUTPUT);
  Serial.begin(9600);
}

void toMorseCode(char c) {
  if (c == ' ') {
    delay(TimeSpaceBW);
  } else {
    int index = findCharIndex(c);
    if (index != -1) {
      Serial.println(morse[index]);
      playMorseCode(morse[index]);
    }
  }
}

int findCharIndex(char c) {
  for (int j = 0; j < 36; j++) {
    if (c == chars[j]) {
      return j;
    }
  }
  return -1;
}

void playMorseCode(const char* morseCode) {
  for (int k = 0; k < strlen(morseCode); k++) {
    if (morseCode[k] == '-') {
      trigger(TimeDash);
    } else if (morseCode[k] == '.') {
      trigger(TimeDot);
    }
    delay(TimeSpaceBC);
  }
}

void loop()
{
  if(i<strlen(input)){
    toMorseCode(toupper(input[i]));
    i++;
  }
}
