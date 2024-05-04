#define l1 7
#define l2 8
#define l3 9

char caracter;

void setup() { 
  Serial.begin(9600);
  pinMode(l1, OUTPUT);
}

void loop() { 
  
  if(Serial.available()) {
  caracter = Serial.read();
  
    if(caracter == 'a'){ digitalWrite(l1, HIGH);}
    if(caracter == 'b'){ digitalWrite(l1, LOW);} 
    if(caracter == 'c'){ digitalWrite(l2, HIGH);}
    if(caracter == 'd'){ digitalWrite(l2, LOW);}
    if(caracter == 'e'){ digitalWrite(l3, HIGH);}
    if(caracter == 'f'){ digitalWrite(l3, LOW);}
  } 

} 
