#include <Wire.h>
#include<stdio.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library
#include <OneWire.h>
#include <DallasTemperature.h>

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

#define ONE_WIRE_BUS 9

OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


const byte hallPin = 2;     // the number of the hall effect sensor pin
const int ledPin =  13;     // the number of the LED pin

// variables will change:
int hallState = 0;          // variable for reading the hall sensor status
volatile byte state = LOW;
volatile unsigned long RPM_T2, RPM_Count;
volatile unsigned long RPM , RPM_T1;
float floatzahl = 0; // auszugebende Zahl
int floatlength = 5; // Gesamtlänge inkl. Punkt
int nks = 3; // Nachkommastellen




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
 
  
 
 
// Print on the LCD
 lcd.clear();
 lcd.home();
 lcd.backlight();  
 lcd.setCursor(0,0); 
 lcd.print("Drehzahl+ Temp");
 
  RPM=0;
  RPM_T1 = millis();
  RPM_T2 =millis();
  RPM_Count = 0;
  
  attachInterrupt(0,RPM_Meter, FALLING);

  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library for Dallas Temperature
  sensors.begin();
  
}



void loop() {
  
  char RPMStr[8];
  char TMPStr[8]="45.7";
  digitalWrite(ledPin, state);
  float Temperature;
  int intzahl = 4;
  
  

     // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
    Temperature=  sensors.getTempCByIndex(0);
    floatzahl=Temperature;

  Serial.print("Temperature is: ");
  Serial.print(Temperature); // Why "byIndex"? 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire
 
 
  if (RPM_T2>RPM_T1){
    RPM = (unsigned)(long) ((RPM_Count*60000)/(RPM_T2-RPM_T1));
    RPM_T1=RPM_T2;
    RPM_Count=0;
    
  }
  else  {RPM=0;}
  
 
 
   // sprintf(RPMStr, "%5u", RPM);
  // sprintf(TMPStr,"%-.2f",Temperature);
  lcd.setCursor(0,2);
  lcd.print(char_and_int("RPM :",RPM ));
  lcd.setCursor(0,3);
  lcd.print(char_and_float("Temp:", floatzahl, floatlength, nks));
  delay(1000);
  
}

void blink() {
  state = !state;
  RPM=RPM+1;
}
void RPM_Meter () {

  RPM_Count++;
  
  RPM_T2 = millis();

}


char* char_and_int(const char* inttext, int intzahl)
{
  char bwert[17];
  char ewert[17];
  strcpy(ewert,inttext);
  sprintf(bwert, "%s%.4i", ewert, intzahl);
  return bwert;
}


char* char_and_float(const char* floattext,float floatzahl, int floatlength, int nks)
{
  char ewert[17]; // Zwischenpuffer: max Länge = Breite LCD + 1
  char rwert[17];
  // Umwandlung Float nach Char
  dtostrf(floatzahl, floatlength, nks, rwert);
  // Text in Zwischenpuffer
  strcpy(ewert, floattext);
  // Char (von Float) ranhängen
  strcat(ewert, rwert);
  // Zwischenpuffer wandeln
  sprintf(rwert, "%s", ewert);
  return rwert;
}










