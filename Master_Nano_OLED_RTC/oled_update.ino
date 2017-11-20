void oled_start()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3C (for the 128x32)
 display.display();
 display.dim(0); 
  int k,i;////////////////////////DISPLY INITILIZATION///////

 /////////////////////////////// RTC SETTING //////////////////////////////
     // if (! rtc.initialized()) {
    //     Serial.println("RTC is NOT running!");
    //following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    delay(100);
 display.clearDisplay();
  // text display testso
  display.setTextSize(1);
  display.setCursor(0,4);
  display.setTextColor(BLACK,WHITE); // 'inverted' text
 while(k<3)
 {
 for(i=0;i<20;i++)
 {
  display.clearDisplay();
  display.setCursor((i*5),6);
  display.print("    ");
  display.setCursor((100-(i*5)),15);
  display.print("    ");
 display.display();
 delay(10);
 
 }

for(i=20;i>0;i--)
 {
  display.clearDisplay();
  display.setCursor((i*5),6);
  display.print("    ");
   display.setCursor(100-(i*5),15);
  display.print("    ");
 display.display();
 delay(10);
 
 }
 k++;
 }  display.clearDisplay();
  display.display();


}
void time_update() {

display.setTextColor(WHITE);
 display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10,0);
  DateTime now = rtc.now();

 thour=(now.hour());
  tmin=(now.minute());
  tsec=(now.second());
   
  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(thour);
    Serial.print(':');
    Serial.print(tmin);
    Serial.print(':');
    Serial.print(tsec);
    Serial.println();
    

  
if(thour == 0){display.print("12");} //Convert zero hour for 12-hour display
    else if(thour < 13 && thour >= 10){display.print(thour);} //Just display hour if double digit hour
        else if(thour < 10){display.print(" "); display.print(thour);} //If single digit hour, add leading space
        else if(thour >= 13 && thour >= 22){display.print(thour-12);} //If double digit and PM, convert 24 to 12 hour
        else{display.print(" "); display.print(thour-12);} //If single digit and PM, convert to 12 hour and add leading space
        
        display.print(":"); //Display hour-minute separator
        if(tmin<10){display.print("0");} //Add leading zero if single-digit minute
        display.print(tmin); //Display retrieved minutes
        
        display.print(":"); //Display minute-seconds separator
        if(tsec<10){display.print("0");} //Add leading zero for single-digit seconds
        display.print(tsec); //Display retrieved seconds
        
        display.setTextSize(1);
        if(thour < 12){display.println(" AM");} //Display AM indicator, as needed
        else{display.print(" PM");} //Display PM indicator, as needed
        
        display.setTextSize(2);      
        display.setCursor(5,18);
        if(now.day()<10)display.print("0");
        display.print(now.day());display.print("-");display.print(now.month());display.print("-");display.print(now.year());

  display.display();
}
