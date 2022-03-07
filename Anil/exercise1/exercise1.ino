byte receiveByte = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(230400);
  Serial.print(" Welcome to LED. LED is closed for this moment. Please, Press A to turn LED. Press L to turn it off");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  

}

// the loop function runs over and over again forever
void loop() {
  if(Serial.available()>0)// Is there any character coming through the serial port?
  {
  receiveByte=Serial.read();
  // If there is a character with following characteristic, read it
  if(receiveByte==65){//65 is the ASCII code for A
  digitalWrite(LED_BUILTIN, LOW);   
  //  Serial.println(receiveByte);
  Serial.println("LED is turned ON");
  }
 else if(receiveByte==76){//76 is the ASCII code for L
  digitalWrite(LED_BUILTIN, HIGH);   
  //  Serial.println(receiveByte);
  Serial.println("LED is turned OFF");
  }
  
 else{
  Serial.println("Invalid error, try again");  //wait for a second
 }
 } 
 }
  
