#include <ESP8266WiFi.h> // Used for the soft AP
#include <WiFiUdp.h> // used for UDP comms.

WiFiUDP Udp;

//*** Soft Ap variables ***
const char *APssid = "ESP8266-12E";
const char *APpassword = ""; // No password for the AP
IPAddress APlocal_IP(192, 168, 4, 1);
IPAddress APgateway(192, 168, 4, 1);
IPAddress APsubnet(255, 255, 255, 0);

//***STAtion variables ***
const char *STAssid = "SSID"; // Network to be joined as a station SSID
const char *STApassword = "PASSWORD"; // Network to be joined as a station password
IPAddress STAlocal_IP(192, 168, 0, 27);
IPAddress STAgateway(192, 168, 0, 1);
IPAddress STAsubnet(255, 255, 255, 0);

//***UDP Variables***
unsigned int localUdpPort = 4210;
char incomingPacket[255];
char replyPacket[] = "Hi there! Got the message :-)";

//***General Variables***
const int LEDpin = 2;

void setup() {
 Serial.begin(115200); //fire up the serial port
 pinMode(LEDpin,OUTPUT);
 digitalWrite(LEDpin,HIGH);
 
 WiFi.mode(WIFI_AP_STA);
 
 Serial.println("ESP8266 AP & Station & UDP System test");
 // Configure the Soft Access Point. Somewhat verbosely... (for completeness sake)
 Serial.print("Soft-AP configuration ... ");
 Serial.println(WiFi.softAPConfig(APlocal_IP, APgateway, APsubnet) ? "OK" : "Failed!"); // configure network
 Serial.print("Setting soft-AP ... ");
 Serial.println(WiFi.softAP(APssid, APpassword) ? "OK" : "Failed!"); // Setup the Access Point
 Serial.print("Soft-AP IP address = ");
 Serial.println(WiFi.softAPIP()); // Confirm AP IP address

 // Fire up wifi station
 Serial.printf("Station connecting to %s\n", STAssid);
 WiFi.begin(STAssid, STApassword);
 WiFi.config(STAlocal_IP, STAgateway, STAsubnet);
 while (WiFi.status() != WL_CONNECTED)
 {
 delay(500);
 Serial.print(".");
 }
 Serial.println();
 Serial.print("Station connected, IP address: ");
 Serial.println(WiFi.localIP());
 Serial.printf("Signal Strength: %d dBm\n", WiFi.RSSI());

 
 // Setup the UDP port
 Serial.println("begin UDP port");
 Udp.begin(localUdpPort);
 Serial.print("local UDP port: ",);
 Serial.println(localUdpPort );
 
 digitalWrite(LEDpin,LOW);

}

void loop() {
 
 //Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum()); // Print number os stations connected to AP

 int packetSize = Udp.parsePacket();
 if (packetSize)
 {
 // receive incoming UDP packets
 Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
 int len = Udp.read(incomingPacket, 255);
 if (len > 0)
 {
 incomingPacket[len] = 0;
 }
 Serial.printf("UDP packet contents: %s\n", incomingPacket);

 // send back a reply, to the IP address and port we got the packet from
 Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
 Udp.write(replyPacket);
 Udp.endPacket();
 }

}
