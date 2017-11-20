#include <OneButton.h>

#include <Wire.h>
//#include <elapsedMillis.h>
//#include<avr/wdt.h>

#define SW1 2
#define SW2 3
#define SW3 4
#define SW4 5
#define SLAVEADDRESS 21

#define LDR A0
/*
int SW1=2;
int SW2=3;
int SW3=4;
int SW4=5;
*/
OneButton Button1(SW1,false);
OneButton Button2(SW2,false);
OneButton Button3(SW3,false);
OneButton Button4(SW4,false);


int checkbutton(int x);
byte t_read[4]={0,0,0,0} ;
byte s_read[5]={0,0,0,0,0};
int ls[4]={0,0,0,0};
void sense();


void doubleclick1(int x);
void doubleclick2();
void doubleclick3();
void doubleclick4();
//elapsedMillis last_t_time =0;    // the last time the output pin was toggled


void setup() {
  
Serial.begin(9600);
 // Serial.println("Watchdog Demo Starting");
  //pinMode(13, OUTPUT);
  //wdt_disable();  /* Disable the watchdog and wait for more than 2 seconds */
  //delay(3000);  /* Done so that the Arduino doesn't keep resetting infinitely in case of wrong configuration */
  //wdt_enable(WDTO_1S); 
 pinMode(SW1,INPUT);
 pinMode(SW2,INPUT);
 pinMode(SW3,INPUT);
 pinMode(SW4,INPUT);
 pinMode(A0,INPUT);
  Wire.begin(SLAVEADDRESS);                // join i2c bus with address #21
  Wire.onRequest(transmit); // register event
}

void loop() {
 digitalWrite(13,1);
 sense();

 digitalWrite(13,0);
 
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void transmit() {

  Wire.write(s_read,5);
  s_read[1]=0;
  s_read[2]=0;
  s_read[3]=0;
  s_read[4]=0;
}

void sense()
{

  s_read[0]=map(analogRead(LDR),0,1023 ,0,255);
 
      
 Button1.tick();
  Button2.tick();
  Button3.tick();
  Button4.tick();
Button1.attachDoubleClick(doubleclick1(2));
Button2.attachDoubleClick(doubleclick2);
Button3.attachDoubleClick(doubleclick3);
Button4.attachDoubleClick(doubleclick4);   


/*
//for(int k=0;k<5;k++)
//{
if (t_read[0]==1 && ls[0]==0 &&  last_t_time > debounce) {
     s_read[2]=1;
     ls[0]=1;
}
 else// if(t_read[0]==0&& ls[0]==1)
{ 
  s_read[2]=0;
  ls[0]=0;
 
}     */   

}

void doubleclick1(int x)
{
  s_read[x]=1;
} 

void doubleclick2()
{
  s_read[2]=1;
} 

void doubleclick3()
{
  s_read[3]=1;
} 

void doubleclick4()
{
  s_read[4]=1;
} 

