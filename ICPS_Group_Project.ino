//Setting up for Occupancy Sensor
#include <NewPingESP8266.h>
#define TRIGGER_PIN  D1
#define ECHO_PIN     D2
#define MAX_DISTANCE 200

NewPingESP8266 sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//Setting up for Air quality Sensor
#define anInput                   A0
#define co2Zero                   55.0
#define co                        1
#define Rl_Value                  5     
#define Ro_Clean_Air_Factor       9.83  

float  coCurve[3] = {2.3,0.72,-0.34};
float  Ro         = 10;


//Setting up for Temperature, Humidity and Buzzer Sensor
#define DHTTYPE DHT11
#define dht_dpin D3
#define Buzzer D4
#include "DHT.h" 
#include "pitches.h"


DHT dht(dht_dpin, DHTTYPE);

int melody[]={
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5};
  int duration = 500;


//Setting up Internet
#include "dweetESP8266.h"
#define THING_NAME "SEAS40-group5-HVAC" 
const char* ssid = "dfa4fe";
const char* password = "271435942";
dweet DweetClient;

char *key = "Temperature"; // this is the name of the parameter sent to dweet.io
char *key1= "Humidity"; // this is the name of the parameter sent to dweet.io
char *key2= "CO2"; // this is the name of the parameter sent to dweet.io
char *key3= "CO"; // this is the name of the parameter sent to dweet.io
char *key4= "Occupancy"; // this is the name of the parameter sent to dweet.io
char *key5= "Alarm"; // this is the name of the parameter sent to dweet.io

void setup() {
  dht.begin();
  pinMode(anInput, INPUT);
  Serial.begin(9600);
  Serial.print("Calibrating...\n");                
  Ro = MQCalibration(anInput);   //Calibrating the sensor. Please make sure the sensor is in clean air                                                                                       
  Serial.print("Calibration is done...\n"); 
 

//Checking for occupied or Unoccupied
  unsigned int uS = sonar.ping();
  Serial.print("Calculating distance: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.print("cm");
  Serial.print("\n"); 
  Serial.print("\n");

   if((uS / US_ROUNDTRIP_CM)>200)
  {
  Serial.println("Unoccupied");
  Serial.print("\n"); 
  }
  else if ((uS / US_ROUNDTRIP_CM)<199)
  {
  Serial.println("Occupied");
  Serial.print("\n"); 
  }

   // Connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
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


char val[16]; 
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)Rl_Value*(1023-raw_adc)/raw_adc));
}
float MQCalibration(int mq_pin)
{
  int i;
  float val=0;
 
  for (i=0;i<50;i++) {            
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(100);
  }
  val = val/50;                   
  val = val/Ro_Clean_Air_Factor;                         
  return val; 
}
float MQRead(int mq_pin)
{
  int i;
  float rs=0;
 
  for (i=0;i<5;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(50);
  }
 
  rs = rs/5;
 
  return rs;  
}
  
int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
   if ( gas_id == co )
  {
     return MQGetPercentage(rs_ro_ratio,coCurve);
  }
 
  return 0;
}
 
int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}

void loop() 
{
  delay(500);
  
  float h= dht.readHumidity();
  float t= dht.readTemperature();
  
  int co2now[10];
  int co2raw = 0;
  int co2comp = 0;
  int co2ppm = 0;
  int co2avg = 0;
  
  for (int x= 0;x<10.0;x++){
    co2now[x]=analogRead(A0);
    delay(200);
  }

  for (int x = 0;x<10.0;x++){
    co2avg=co2avg + co2now[x];
  }

  co2raw = co2avg/10.0;
  co2comp = co2raw - co2Zero;
  co2ppm = map(co2comp,0.0,1023.0,400.0,5000.0);
  
  unsigned int uS = sonar.ping();
  
  
  if((uS / US_ROUNDTRIP_CM)>200)
  {
  delay(1000);
  Serial.print("\n");
  Serial.print("Current humidity= ");
  Serial.print(h);
  Serial.print("% ");
  Serial.print("temperature= ");
  Serial.print(t);
  Serial.println("C ");
  Serial.print("\n");
  

  if(h<40)
    {
    Serial.println("Humidity is below 40% !");
    for(int thisNote = 0; thisNote <8; thisNote++) {
    tone(D4, melody[thisNote], duration);
    delay(500);
   // Serial.println("\n");
   // Serial.println("\n");
    //Serial.println("Humidifier Activated!.... increasing humidity to Ideal");
    delay(1000);
    }
    }
    
     else if (h>70)
    {
    Serial.println("Humidity is above 70% !");
   for(int thisNote = 0; thisNote <8; thisNote++) {
    tone(D4, melody[thisNote], duration);
    delay(500);
   // Serial.println("\n");
   // Serial.println("\n");
    //Serial.println("Dehumidifier Activated!.... decreasing humidity to Ideal");
    delay(1000);
    }
    }

    else
    {
    noTone(Buzzer);     
    }
    
 if(t<18)
    {
    Serial.println("Temperature is below 18C !");
    tone(Buzzer, 3000); 
    delay(500);
    //Serial.println("\n");
    //Serial.println("\n");
    //Serial.println("Heater Activated!.... increasing temperature to Ideal");
    }
    
     else if (t>25)
    {
    Serial.println("Temperature is above 25C !");
    tone(Buzzer, 3000); 
    delay(500);
    //Serial.println("\n");
    //Serial.println("\n");
    //Serial.println ("Air-Cooler Activated!.... decreasing temperature to Ideal");
    //Serial.println("\n");
    //Serial.println("\n");
    }
      else
    {
    noTone(Buzzer);   
    }
  delay(20000);
  Serial.println("Unoccupied");
  Serial.print("\n");  
  }
  
  else if ((uS / US_ROUNDTRIP_CM)<199)
  {
  delay(1000);
  Serial.print("\n");
  Serial.print("Current humidity= ");
  Serial.print(h);
  Serial.print("% ");
  Serial.print("temperature= ");
  Serial.print(t);
  Serial.println("C ");
 
  if(h<40)
    {
    Serial.println("Humidity is below 40% !");
    for(int thisNote = 0; thisNote <8; thisNote++) {
    tone(D4, melody[thisNote], duration);
    delay(500);
    //Serial.println("\n");
    //Serial.println("\n");
    //Serial.println("Humidifier Activated!.... increasing humidity to Ideal");
    //Serial.println("\n");
    delay(1000);
    }
    }
    
     else if (h>70)
    {
    Serial.println("Humidity is above 70% !");
   for(int thisNote = 0; thisNote <8; thisNote++) {
    tone(D4, melody[thisNote], duration);
    delay(500);
    //Serial.println("\n");
    //Serial.println("\n");
    //Serial.println("Dehumidifier Activated!.... decreasing humidity to Ideal");
    //Serial.println("\n");
    delay(1000);
    }
    }

    else
    {
    noTone(Buzzer);   
    }
    
 if(t<18)
   {
    Serial.println("Temperature is below 18C !");
    tone(Buzzer, 3000);
    delay(500);
    //Serial.println ("Heater Activated!.... Increasing temperature to Ideal");
    Serial.println("\n");
    }
    
     else if (t>25)
    {
    Serial.println("Temperature is above 25C !");
    tone(Buzzer, 3000); 
    delay(500);
    //Serial.println ("Air-Cooler Activated!.... decreasing temperature to Ideal");
    //Serial.println("\n");
    }
      else
    {
    noTone(Buzzer);     
    }
    
    delay(1000);
    Serial.print("CO2:");
    Serial.print(co2ppm);
    Serial.print(" ppm");
    Serial.print("    "); 
    
    if(co2ppm>999.9)
  {
   Serial.println(" Level is above threshold!");
   tone(Buzzer, 5000); 
    delay(500);
   // Serial.println("\n");
  //  Serial.println("\n");
    //Serial.println("True HEPA filter Activated!.... Improving Air-Quality");
  }
  else
  {
    Serial.println(" Level is within acceptable range");
    noTone(Buzzer);   
  }

  delay(1000);
  Serial.print("CO:"); 
  Serial.print(MQGetGasPercentage(MQRead(anInput)/Ro,co) );
  Serial.print(" ppm" );
  Serial.print("  ");
   if(MQGetGasPercentage(MQRead(anInput)/Ro,co)>9)
  {
   Serial.println(" Level is above threshold!");
   tone(Buzzer, 5000); 
   delay(500);
  //  Serial.println("\n");
  //  Serial.println("\n");
  //  Serial.println("True HEPA filter Activated!.... Improving Air-Quality");
  }
  else
  {
   Serial.println(" Level is within acceptable range");
   Serial.print("\n");
   noTone(Buzzer);     
  }
  
  Serial.print("\n"); 
  delay(20000);
  Serial.println("Occupied");
  Serial.print("\n");  
}

  String temp = String(t,2); 
    temp.toCharArray(val, 16); 
    Serial.println(val);
    DweetClient.add(key,val);
    DweetClient.sendAll(THING_NAME);
    
   
   String humd = String(h,2); 
    humd.toCharArray(val, 16); 
    Serial.println(val);
    DweetClient.add(key1,val);
    DweetClient.sendAll(THING_NAME);
    

    itoa(co2ppm, val, 10); 
    Serial.println(val);
    DweetClient.add(key2, val);
    DweetClient.sendAll(THING_NAME);
   

    String c = String(MQGetGasPercentage(MQRead(anInput)/Ro,co),2); 
    c.toCharArray(val, 16); 
    Serial.println(val);
    DweetClient.add(key3,val);
    DweetClient.sendAll(THING_NAME);

    
    int a = (uS / US_ROUNDTRIP_CM);
    int hol = a<=200; 
  
    itoa(hol, val, 10); 
    Serial.println(val);
    DweetClient.add(key4, val);
    DweetClient.sendAll(THING_NAME);


    
    boolean(Bal)= (h>70) || (h<40) || (t<18) || (t>25) || (co2ppm>999.9) || (MQGetGasPercentage(MQRead(anInput)/Ro,co)>9);
   
    itoa(Bal, val, 10); 
    Serial.println(val);
    DweetClient.add(key5, val);
    DweetClient.sendAll(THING_NAME);
    
    delay(3000);


}
