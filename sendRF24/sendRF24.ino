#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

byte rxAddr[6] = [0xe7, 0xe7, 0xe7, 0xe7, 0xe7];
void setup() {
   radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
  // put your setup code here, to run once:

}



void loop()
{
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  
  delay(1000);
}
