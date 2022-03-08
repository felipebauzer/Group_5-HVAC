#define anInput                   A0
#define co2Zero                   55.0
#define co                        1
#define Rl_Value                  5     
#define Ro_Clean_Air_Factor       9.83  
 

float  coCurve[3] = {2.3,0.72,-0.34};
float  Ro         = 10;

void setup() {
  pinMode(anInput, INPUT);
  Serial.begin(9600);
  Serial.print("Calibrating...\n");                
  Ro = MQCalibration(anInput);         //Calibrating the sensor. Please make sure the sensor is in clean air                                                                                       
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
}

void loop() {
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
  Serial.print("CO2:");
  Serial.print(co2ppm);
  Serial.print(" ppm");
  Serial.print("    "); 
    if(co2ppm>999.9)
  {
   Serial.println(" Level is above threshold!");
  }
  else
  {
    Serial.println(" Level is within acceptable range");
  }
  Serial.print("CO:"); 
  Serial.print(MQGetGasPercentage(MQRead(anInput)/Ro,co) );
  Serial.print(" ppm" );
  Serial.print("  ");
   if(MQGetGasPercentage(MQRead(anInput)/Ro,co)>9)
  {
   Serial.println(" Level is above threshold!");
  }
  else
  {
   Serial.println(" Level is within acceptable range");
  }  
}

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
