#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <FS.h>
String debugStr;

ESP8266WebServer server(80);
HTTPClient http;
int jumpCount = 1;
//String readInput = "";

void handleNote(){
  //Notes go here!
    if(server.arg("Nachricht")!= NULL){
  String message = server.arg("Nachricht");
  Serial.println(message);
   server.send(400, "text/plain", "Bitte keinen leeren Spam");
  }else
  server.send(200);
}


void setup() {

  
  Serial.begin(74400);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(15000);
  WiFi.mode(WIFI_STA);
  Serial.println("Test");

  IPAddress ip(192, 168, 137, 181); // where xx is the desired IP Address
  IPAddress gateway(192, 168, 137, 1); // set gateway to match your network
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  
  WiFi.begin("Aire_Tam_07","materia777");
  
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //Serial.println("###########Connecting...########");
    }
    //Serial.println(WiFi.localIP());
	delay(1000);
  http.begin("http://www.spiegel.de/schlagzeilen/eilmeldungen/index.rss");
  http.addHeader("Content-Type", "text/xml");
  int httpCode = http.GET();
      //Serial.print("HTTPCODE: ");
      //Serial.println(httpCode);

String payload = http.getString();
int index = 0;

  Serial.flush();
  while(payload.indexOf("<title>",index) != -1)
  {
   index = payload.indexOf("<title>",index);
    int tmp = payload.indexOf("</title>",index);

      if(jumpCount<2){
            index=tmp;
            jumpCount++;
            continue;
        }
        else{
           debugStr += ">>>  " + payload.substring(index + 7,tmp) + "\n";
           index=tmp;
          }
          
      jumpCount++;
  }
  //jumpCount = 2;
  debugStr.replace(": ","\n");
  debugStr.replace("ä","ae");
  debugStr.replace("ö","oe");
  debugStr.replace("ü","ue");
  debugStr.replace("ß","ss");

  int breakFeed=0;
  int lastSpace = 0;
  for(int i = 0;i<debugStr.length();i++)
  {
    if(debugStr.charAt(i) == '\n' && breakFeed < 35)
      breakFeed = 0;
    else
    {
      if(debugStr.charAt(i) == ' ' && breakFeed < 35)
        lastSpace = i;

      if(breakFeed>=35){
        debugStr.setCharAt(lastSpace,'\n');
        breakFeed = -1;
      }
    }
    breakFeed ++;
  }
  
  Serial.flush();
  Serial.println(debugStr);
  Serial.flush();
  http.end();
  SPIFFS.begin();                           // Start the SPI Flash Files System
  SPIFFS.format();


  server.on("/",handleNote);
  server.on("/getList", HTTP_GET, []() {
    server.send(200,"text/html","1. du, 2. bist, 3. ein, 4. Hurensohn");
  });

  
    server.onNotFound([]() {    
      server.send(404, "text/plain", "404: Not Found");
  });
   
  server.begin();
}


void loop() {
	server.handleClient();
  delay(10);
}

