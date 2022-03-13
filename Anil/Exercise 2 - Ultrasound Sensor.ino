#include <NewPingESP8266.h>

#define TRIGGER_PIN D1
#define ECHO_PIN    D2
#define MAX_DISTANCE 200 // maximum distance we want to ping for (in centimeters). Maximum sensor distance is 400-500cm.

NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //Initialization of the sonar


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  delay(500); // Wait 500ms between pings (about 2pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside MAX_DISTANCE, no ping echo)
  Serial.println("cm");
  // put your main code here, to run repeatedly:

  if((uS / US_ROUNDTRIP_CM)>200)
  {
  Serial.println("Unoccupied");
  Serial.print("\n"); 
  }
  else if ((uS / US_ROUNDTRIP_CM)<200)
  {
  Serial.println("Occupied");
  Serial.print("\n"); 
  }

}
