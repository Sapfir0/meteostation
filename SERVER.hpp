
// #include <ESP8266HTTPClient.h>
// #include <ESP8266WebServer.h>
// #include <WiFiClient.h>
// #include "DHT.hpp"

// class homeServer {
//     private:
//         String server = "http://127.0.0.1:9000/";

//     public:
//     HTTPClient http;

//     int requestToHomeServer();
//     void postToThingSpeak();
// }

// int homeServer::requestToHomeServer() {
//     String postData;
//     postData = "dnsjsdbgbdbs";
//     http.begin(server);
//     http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // i dont know
//     int httpCode = http.POST(postData);
//     http.end();
//     return httpCode;
// }

//   String apiKey = "I7I84BBE02Z0LZ8G";  // replace with your channel’s thingspeak API key,
//   const char* server = "api.thingspeak.com";


// void homeServer::postToThingSpeak() {
//   Gradusnik grad;
//   if (client.connect(server, 80))  // "184.106.153.149" or api.thingspeak.com
//   {
//     String postStr = apiKey;
//     postStr +="&field1=";
//     postStr += grad.getTemperature();
//     postStr +="&field2=";
//     postStr += grad.getHumidity();
//     postStr +="&field3=";
//     postStr += getTemperature();
//     postStr +="&field4=";
//     postStr += getHumidity();
//     postStr +="&field5=";
//     postStr += getPressure();
//     postStr += "\r\n\r\n";

//     client.print("POST /update HTTP/1.1\n");
//     client.print("Host: api.thingspeak.com\n");
//     client.print("Connection: close\n");
//     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
//     client.print("Content-Type: application/x-www-form-urlencoded\n");
//     client.print("Content-Length: ");
//     client.print(postStr.length());
//     client.print("\n\n");
//     client.print(postStr);
//   }
//   client.stop();

//   Serial.println("Waiting…");       // thingspeak needs minimum 15 sec delay between updates
//   delay(5000);
// }