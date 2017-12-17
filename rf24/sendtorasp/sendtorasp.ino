
#include <SPI.h>

#include <RF24.h>
// ce, cn pins
RF24 radio (7,8);


void setup() {
  byte addresses[][6] ={"1Node","2Node"}; 
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  // radio.setChannel(0x76);
  radio.openWritingPipe(addresses[1]);
  // radio.enableDynamicPayloads();
  // radio.powerUp();
  
}

void loop(void) {
 
  
  const char text[]="Herld";
  radio.write(&text,sizeof(text));
  delay(1000);

}
