#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <HttpClient.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "lm35-13884.firebaseio.com"
#define FIREBASE_AUTH "4fPFOmHm3JSy8ZYpdyUQufSi9oELd5MHHgfegVcq"

//-----------------Temperature----------
#define temp1 "normal"

//------------------pH-------------------
#define pH_type1 "very_acid"
#define pH_type2 "slightly_acid"
#define pH_type3 "natural_water"
#define pH_type4 "slightly_alkaline"
#define pH_type5 "very_alkaline"

//------------------TDS------------------
#define tds1 "excellent"
#define tds2 "good"
#define tds3 "fair"
#define tds4 "poor"
#define tds5 "unacceptable"

//------------------Decision-------------
#define decision1 "drinkable_water"
#define decision2 "not_drinkable"

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.43.20/iotbasedwq/post-esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

SoftwareSerial datalog(13,15);// RX, TX

String value;
String value1;
String value2;
String value3;

float sensor1;
float sensor2;
float sensor3;

String temperature;
String pH;
String TDS;
String decision;

String apiWritekey = "D7B4HIMUFC0EUAIX"; 

//---------------wifi----------------------
const char* ssid = "mazhar";
const char* password = "mazhar202" ;

const char* server = "api.thingspeak.com";
float resolution=3.3/1023;
WiFiClient client;

void setup() {
  Serial.begin(115200);

  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

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
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
  
  datalog.begin(115200);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
 
  void loop() {
  if (datalog.available() > 0) {
  value = datalog.readString();
  Serial.println(value);

//------------Temperature----------------
  Serial.print("0: ");
//  Serial.println(getStringPartByNr(value, ';', 0));  // the first part - return "192"
  value1= getStringPartByNr(value, ';', 0);
  sensor1= value1.toFloat();
  Serial.println(sensor1);

  if(sensor1 >= 20 && sensor1 <= 35){
    temperature = temp1;    
  }
//------------Temperature----------------


//------------pH----------------
  Serial.print("1: ");
//  Serial.println(getStringPartByNr(value, ';', 1));  // the 2. part - return "168"
  value2= getStringPartByNr(value, ';', 1);
  sensor2= value2.toFloat();
  Serial.println(sensor2);
  
  if(sensor2 >= 6.5 && sensor2 <= 9.0){
    pH = pH_type3;
  }
  else if(sensor2 <= 6.5 && sensor2 >= 4.5){
    pH = pH_type2;
  }
  else if(sensor2 <= 4.5 && sensor2 >= 0.0){
    pH = pH_type1;
  }
  else if(sensor2 >= 9.0 && sensor2 <= 11.5){
    pH = pH_type4;
  }
  else if(sensor2 >= 11.5){
    pH = pH_type5;
  }
//------------pH----------------


//------------TDS----------------
  Serial.print("2: ");
//  Serial.println(getStringPartByNr(value, ';', 2));  // the 3. part - return "10"
  value3= getStringPartByNr(value, ';', 2);
  sensor3= value3.toFloat();
  Serial.println(sensor3);

  if(sensor3 <= 400){
    TDS = tds1;
  }
  else if(sensor3 <= 600 && sensor3 >= 400){
    TDS = tds2;
  }
  else if(sensor3 <= 900 && sensor3 >= 600){
    TDS = tds3;
  }
  else if(sensor3 <= 1200 && sensor3 >= 900){
    TDS = tds4;
  }
  else if(sensor3 >= 1200){
    TDS = tds5;
  }
//------------TDS----------------

//-----------Decision------------
if(sensor2 >= 6.5 && sensor2 <= 9.00 && sensor3 <= 400){
  decision = decision1;
}
else{
  decision = decision2;
}
  
  delay(500);
  }

//--------------thingspeak.com----------------------
   if (client.connect(server,80)) {
    String tsData = apiWritekey;
    tsData +="&field1=";
    tsData += String (sensor1);
    tsData +="&field2=";
    tsData += String (sensor2);
    tsData +="&field3=";
    tsData += String (sensor3);
    tsData += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);

    Serial.print("Temperature1: ");
    Serial.println(sensor1);
    Serial.print("Temperature2: ");
    Serial.println(sensor2);
    Serial.print("Temperature3: ");
    Serial.println(sensor3);
    Serial.println("uploaded to Thingspeak server....");
  }
    client.stop();

    Serial.println("Waiting to upload next reading...");
    Serial.println();
    //---------------------thingspeak.com-------------

    //---------------------firebase-------------------

    Firebase.setFloat("sensor1",sensor1);
    Firebase.setFloat("sensor2",sensor2);
    Firebase.setFloat("sensor3",sensor3);
    Firebase.setString("message1",temperature);
    Firebase.setString("message2",pH);
    Firebase.setString("message3",TDS);
    Firebase.setString("message4",decision);
    
  if (Firebase.failed()){ // Check for errors 
  Serial.print("setting /number failed:");
  Serial.println(Firebase.error());
  }
  
  float t1 = Firebase.getFloat("sensor1");
  Serial.println(t1);
  float t2 = Firebase.getFloat("sensor2");
  Serial.println(t2);
  float t3 = Firebase.getFloat("sensor3");
  Serial.println(t3);

//---------------------------MySQL DataBase---------------------------------
    HTTPClient http;
// Your Domain name with URL path or IP address with path
    http.begin(serverName);

// Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor1=" + String(sensor1) + "&temperature=" + String(temperature) 
                          + "&sensor2=" + String(sensor2) + "&pH=" + String(pH) + "&sensor3=" + String(sensor3) + "&TDS=" + String(TDS)
                          + "&decision=" + String(decision) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }

String getStringPartByNr(String data, char separator, int index)
{
    // spliting a string and return the part nr index
    // split by separator
    
    int stringData = 0;        //variable to count data part nr 
    String dataPart = "";      //variable to hole the return text
    
    for(int i = 0; i<data.length(); i++) {    //Walk through the text one letter at a time
      
      if(data[i]==separator) {
        //Count the number of times separator character appears in the text
        stringData++;
        
      }else if(stringData==index) {
        //get the text when separator is the rignt one
        dataPart.concat(data[i]);
        
      }else if(stringData>index) {
        //return text and stop if the next separator appears - to save CPU-time
        return dataPart;
        break;        
      }
    }
    //return text if this is the last part
    return dataPart;
}
