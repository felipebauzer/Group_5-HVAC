byte receivedByte = 0;
int N= 78;
int R= 82;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(230400);

}

void loop() {
  if ( Serial.available() > 0) 
  {
    receivedByte = Serial.read();
    
    if(receivedByte==N)
    {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on
    Serial.println("ON");
    }
    
     else if (receivedByte==R)
    {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off 
    Serial.println("OFF");
    }

  }
             }
