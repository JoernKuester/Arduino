#include <Wire.h>
#include<stdio.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library

#define I2C_ADDR    0x27  // Define I2C Address for controller
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define  LED_OFF  0
#define  LED_ON  1
LiquidCrystal_I2C 
lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

const byte hallPin = 2;     // the number of the hall effect sensor pin
const int ledPin =  13;     // the number of the LED pin
// variables will change:
int hallState = 0;          // variable for reading the hall sensor status
volatile byte state = LOW;
volatile unsigned long RPM_T2, RPM_Count;
volatile unsigned long RPM , RPM_T1;



void setup() 
{
  lcd.begin (20,4);  // initialize the lcd
// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the hall effect sensor pin as an input:
  pinMode(hallPin, INPUT);
  lcd.clear();
  
  lcd.home();
 
// Print on the LCD
 lcd.backlight();  
 lcd.setCursor(0,0); 
 lcd.print("Drehzahlmessung!");
  lcd.setCursor(0,1); 
  lcd.print("RPM: ");
  RPM=0;
  RPM_T1 = millis();
  RPM_T2 =millis();
  RPM_Count = 0;
  
  attachInterrupt(0,RPM_Meter, FALLING);
  
}



void loop() {
  
  char RPMStr[8];
  digitalWrite(ledPin, state);
 
 
  if (RPM_T2>RPM_T1){
    RPM = (unsigned)(long) ((RPM_Count*60000)/(RPM_T2-RPM_T1));
    RPM_T1=RPM_T2;
    RPM_Count=0;
    
  }
  
 
 
   sprintf(RPMStr, "%5u", RPM);
  lcd.setCursor(0,2);
  lcd.print(RPMStr);
  delay(20);
  
}

void blink() {
  state = !state;
  RPM=RPM+1;
}
void RPM_Meter () {

  RPM_Count++;
  RPM_T2 = millis();

}








