#include <ESP8266WiFi.h>

//WiFi network parameters

const char* ssid = "MOVISTAR_0440";
const char* password = "CsN3wjEMnQBPGNGBTg6H";

//Host to connect to and WiFi client parameters

const char* host = "postman-echo.com";  //checking process


WiFiClient client;              //checking process
const int httpPort = 80;        //checking process

void setup() {
  // Start Serial
  Serial.begin(115200);

  // a small delay is added to initialize the serial port
  delay(10);

  // Connecting to a WiFi
  Serial.println();
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // a 5second delay is added for Wifi initalization and avoid continious request
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);

  // A connection to the website is openned

  if(!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }

  // The specific URL is indicated and the connection request is sent

  String url = "/get";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  // We wait 5 second for the server responde

  unsigned long timeout = millis();
  while(client.available() == 0){
    if(millis() - timeout > 5000){
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

while(client.available()){ // the server responde is processed
  String line = client.readStringUntil('\r');
  Serial.print(line);
}

Serial.println();
Serial.println("closing connection");
}
