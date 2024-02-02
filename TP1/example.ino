int led;
int piezo;
void setup()
{
  led=9; // the pin that the LED is attached to
  piezo=6; // the pin that the piezo is attached to

  pinMode(led, OUTPUT); // Initialize the digital pin as an output.
  pinMode(piezo, OUTPUT); // Initialize the digital pin as an output.
}

void loop()
{
  digitalWrite(led, HIGH); // Turn the LED on (HIGH is a value of 1)
  tone(piezo, 1000); // Send 1KHz sound signal...(pin number, frequency in hertz, duration in milliseconds)

  delay(500); // Wait for 500 millisecond(s)
  
  
  digitalWrite(led, LOW); // Turn the LED off (LOW is a value of 0)
  noTone(piezo); // Stop sound... (pin number)
  
  delay(500); // Wait for 1000 millisecond(s)
}