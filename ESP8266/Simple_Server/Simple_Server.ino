#include <ESP8266WiFi.h>
WiFiServer server (80); // Initialize the server on Port 80



void setup() {
  delay(1000);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Hello_IOT","12345");
  server.begin();

  // Looking under the hood
  Serial.begin(115200);
  IPAddress HTTPS_ServerIP = WiFi.softAPIP(); // Obtain the IP oof the server
  Serial.print("Server IP is :");
  Serial.println(HTTPS_ServerIP);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
