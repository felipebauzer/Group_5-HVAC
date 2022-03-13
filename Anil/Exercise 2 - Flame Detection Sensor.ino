int Led = LED_BUILTIN; // Define LED pin
int sensorD0 = D1; // Define sensor digital output
int val; // Define digital variable val

void setup() 
{
  Serial.begin(9600);
  pinMode(Led,OUTPUT); // Define the LED pin as an output pin
  pinMode(sensorD0,OUTPUT); // Define the sensor D0 pin as an input pin
  
}

void loop() 
{
  delay(1500);
  val = digitalRead(sensorD0); // Read the sensor digital output
  if(val==HIGH) // When the digital output detects a flame, the LED is turned on 
  {
    digitalWrite(Led,LOW);
    Serial.print(val);
    Serial.print("      Fire Status: ");
    Serial.println("Fire Detected !!");
  }
  else 
  {
    digitalWrite(Led,HIGH);
     Serial.print(val);
    Serial.print("      Fire Status: ");
    Serial.println("No Fire Detected.");
  }
  
}
