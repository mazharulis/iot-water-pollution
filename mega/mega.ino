//------------pH----------------
#define SensorpinpH A0          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;
//------------pH----------------

//-----------TDS----------------
#include <EEPROM.h>
#include "GravityTDS.h"
#define TdsSensorPin A1
GravityTDS gravityTds;
float temperature = 25.00,tdsValue = 0.00;
//-------------TDS-------------------


void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(13,OUTPUT);    
  Serial.println("Ready");    //Test the serial monitor

  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
}

void loop()
{
//--------------Temperature-------------  

float temperature1 = random(21.00,32.00);

//--------------Temperature-------------

//float sensor2 = random(30,50);
//float sensor3 = random(60,100);

//---------------pH----------------

for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorpinpH);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024.0/6.0; //convert the analog into millivolt
  phValue=-6.75*phValue+31.0;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(phValue);
  Serial.println(" ");
  digitalWrite(13, HIGH);       
  digitalWrite(13, LOW); 

  //-----------------pH--------------------

  //----------------TDS--------------------

    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    
    //-------------TDS----------------------

   Serial1.print(temperature1);
   Serial1.print(";");
//   Serial.print(temp1);
   Serial1.print(phValue);
   Serial1.print(";");
//   Serial.print(temp2);
   Serial1.print(tdsValue);
   Serial1.print(";");
   delay(1000);
  
}
