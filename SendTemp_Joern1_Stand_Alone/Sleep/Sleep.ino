#include <avr/sleep.h>
void setup() {
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_cpu (); 
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}



