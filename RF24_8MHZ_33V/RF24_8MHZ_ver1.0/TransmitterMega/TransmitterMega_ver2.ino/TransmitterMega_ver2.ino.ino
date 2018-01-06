#include <DallasTemperature.h>
#include <OneWire.h>


/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/
#include <SPI.h>
#include "RF24.h"
#include <string.h>
#include <stdlib.h>
#include<stdio.h>

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 9


// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"00003","00001"};

// Used to control whether this node is sending or receiving
bool role = 1;

void setup() {
  Serial.begin(115200);
  //Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  //sensors.begin();
  // Serial.println(F("RF24/examples/GettingStarted"));
  // Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_HIGH);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    Serial.println(F("Test"));
    radio.openReadingPipe(1,addresses[1]);
  }
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() {
  float Temperature=1;
  
  
/****************** Ping Out Role ***************************/  
if (role == 1)  {

     // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
 // Serial.print(" Requesting temperatures...");
 // sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
   // Temperature=  sensors.getTempCByIndex(0);

  //Serial.print("Temperature is: ");
 // Serial.print(Temperature); // Why "byIndex"? 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire

     
  
    //delay(1000);
    
    //radio.stopListening();                                    // First, stop listening so we can talk.
    
    
    //Serial.println(F("Now sending"));

    //const char text[40] = "Hello GiNberry";
    char dest_txt[10];
    String dest_text=String(Temperature,2);
       
    //unsigned long start_time = micros(); 
     
    //Take the time, and send it.  This will block until complete
  
    radio.startListening();                                    // Now, continue listening
  
   
    // Set up a variable to indicate if a response was received or not
    if (radio.available()){
                     while(radio.available()){
                    radio.read( &dest_txt, sizeof(dest_txt) );
                          }
     radio.stopListening();
     radio.write( &dest_txt, sizeof(dest_txt) );
     Serial.println(dest_txt);
     // Now, resume listening so we catch the next packets.
     delay(50);
    }
    
  
    // Try again 1s later
    delay(50);
  }



/****************** Pong Back Role ***************************/

 // if ( role == 0 )
  // {
    // unsigned long got_time;
    
   //  if( radio.available()){
                                                                    // Variable for the received timestamp
      // while (radio.available()) {                                   // While there is data ready
        // radio.read( &got_time, sizeof(unsigned long) );             // Get the payload
      // }
     
      // radio.stopListening();                                        // First, stop listening so we can talk   
      // radio.write( &got_time, sizeof(unsigned long) );              // Send the final one back.      
      // radio.startListening();                                       // Now, resume listening so we catch the next packets.     
      // Serial.print(F("Sent response "));
      // Serial.println(got_time);  
   // }
 // }




/****************** Change Roles via Serial Commands ***************************/

//if ( Serial.available() )
  // {
    // char c = toupper(Serial.read());
    // if ( c == 'T' && role == 0 ){      
      //Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      //role = 1;                  // Become the primary transmitter (ping out)
    
   // }else
    // if ( c == 'R' && role == 1 ){
      // Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));      
       // role = 0;                // Become the primary receiver (pong back)
       // radio.startListening();
      
    //}
  // }


} // Loop

