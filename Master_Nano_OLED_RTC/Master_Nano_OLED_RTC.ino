#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

/////////////////OLED and RTC 
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int thour,tmin,tsec;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

byte flash = 0;
////////////////////////////

/*CONTROL */
#define SLAVE1 11  
#define SLAVE2 12

/*SWITCH*/
#define SLAVE3 21
#define SLAVE4 22

#define LIGHT1 101
#define LIGHT2 102 
#define LIGHT3 103
#define LIGHT4 104

#define LIGHT5 111
#define LIGHT6 112
#define LIGHT7 113
#define LIGHT8 114
//Device last stage

int slave_n,switch_n,device_n;
byte slave_reads[1][5];
byte device_ls[1][3];
byte Tdevice[7];

void read_all_slaves();
void write_all();
void control();



/* SLAVE TOGGLING FUNCTION*/
void tdevice (byte device_id) //passes slave address , device number ,and last state of device 
{
  int saddr,daddr;
  saddr=(device_id/10);
  daddr=(device_id%10);
  
   Wire.beginTransmission(saddr); // selects the slave 
  Wire.write(daddr);              // sends device address  
  Wire.endTransmission();    // stop transmitting
}
void int_control();
void time_update();
void oled_start();
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  oled_start();
 
 
}
void loop() {
  time_update();
  read_all_slaves();
  write_all();
//  int_control(); ///// SPECIAL FUNCTIONS change device state by altering Tdevice[0]==1 
  control();
  delay(50);
}
void read_all_slaves()
{
  /*/////////////////////////// READING FROM SLAVE /////////////////////////////*/
  Wire.requestFrom(SLAVE3,5);    // request 6 bytes from slave device #21
{ slave_n=0 ;
  switch_n=0;
  while (Wire.available()) { // slave may send less than requested
     slave_reads[slave_n][switch_n]=Wire.read(); //// receive a byte as character  
    Serial.println("21 ");
    Serial.println(slave_reads[slave_n][switch_n]);         // print the character
  switch_n++; 
}
  
}

  /*/////////////////////////// READING FROM SLAVE 4 /////////////////////////////*/
  Wire.requestFrom(SLAVE4,5);    // request 6 bytes from slave device #22
{ slave_n=1 ;
  switch_n=0;
  while (Wire.available()) { // slave may send less than requested
     
     slave_reads[slave_n][switch_n]=Wire.read(); //// receive a byte as character  
 Serial.println("22");    
    Serial.print(slave_reads[slave_n][switch_n]);         // print the character

  switch_n++; 
}
 Serial.println(); 
}



}

void write_all()
{
  int dcount=0;
 for(slave_n=0;slave_n<2;slave_n++) 
 {
  for(device_n=1 ; device_n<5 ; device_n++)
 {
 if(slave_reads[slave_n][device_n]==1)
{
  Tdevice[dcount]=1;
   dcount++;
}
else
{
  Tdevice[dcount]=0;
   dcount++;
  
}
}
}
}



