#include <Time.h>
#include <TimeLib.h>

/*
  
  
  Description: 
    Have your Arduino get the date(mm/dd/yyyy) & time(hh:mm:ss) from the user via the serial
    monitor in the Arduino Development IDE software.
    Date includes day, month and year
    Time includes hour, minutes and seconds

  References: 
  References on Serial:
  https://www.arduino.cc/reference/en/language/functions/communication/serial/
  https://www.arduino.cc/reference/en/language/functions/communication/serial/available/
  https://www.arduino.cc/reference/en/language/functions/communication/serial/read/
  https://www.arduino.cc/reference/en/language/functions/communication/serial/readbytesuntil/
  
*/

// include statements for lcd and time

#include <LiquidCrystal.h>



// use the LiquidCrystal and initialize all the pins according to your circuit
// pin 12: RS
// pin 11: Enable
// pin 5: D4
// pin 4: D5
// pin 3: D6
// pin 2: D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd pins
int userInput[6];
int inhour = 0;
int inminute = 0;
int insecond = 0;
int inmonth = 0;
int indate = 0;
int inyear = 0;
int leap = 0;
int flag = 0;
int flag2 = 1;
int flag3 = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  //----------------------------------------------------
  // take hour input from the user
  flag =0;
  while(flag != 1){
    Serial.println("Enter the Hour.");
    while(Serial.available() == 0){}
    delay(1000);
    inhour = Serial.parseInt();
    Serial.print("Hours Entered: ");
    Serial.println(inhour);
    if(inhour < 0 || inhour > 23){
      Serial.println("Invalid Input, Enter between 0 to 23"); 
      lcd.print("Error"); 
      }
    else{
      flag = 1;
      }
  }
  //--------------------------------------------------------
  // take minute input from the user
  flag =0;
  while(flag != 1){
    Serial.println("Enter the Minutes.");
    while(Serial.available() == 0){}
    delay(4000);
    inminute = Serial.parseInt();
    Serial.print("Minutes Entered: ");
    Serial.println(inminute);
    if(inminute < 0 || inminute > 59){
      Serial.println("Invalid Input, Enter between 0 to 59");  
      lcd.print("Error");
      }
    else{
      flag = 1;
      }
  }
  //--------------------------------------------------------
  // take second input from the user
  flag =0;
  while(flag != 1){
    Serial.println("Enter the Seconds.");
    while(Serial.available() == 0){}
    delay(4000);
    insecond = Serial.parseInt();
    Serial.print("Seconds Entered: ");
    Serial.println(insecond);
    if(insecond < 0 || insecond > 59){
      Serial.println("Invalid Input, Enter between 0 to 59");
      lcd.print("Error");  
      }
    else{
      flag = 1;
      }
  }
  //--------------------------------------------------------
  // Now setup the Month, Date and Year -------------------------------------------------------------------------------------------
  // -------------------------------------------------------
  // take month input from the user
  flag =0;
  while(flag != 1){
    Serial.println("Enter the Month.");
    while(Serial.available() == 0){}
    delay(4000);
    inmonth = Serial.parseInt();
    Serial.print("Month Entered: ");
    Serial.println(inmonth);
    if(inmonth <= 0 || inmonth > 12){
      Serial.println("Invalid Input, Enter between 1 to 12");  
      lcd.print("Error");
      }
    else{
      flag = 1;
      }
  }
    //--------------------------------------------------------
  // take date input from the user
  flag =0;
  while(flag != 1){
    Serial.println("Enter the Date.");
    while(Serial.available() == 0){}
    delay(3000);
    indate = Serial.parseInt();
    Serial.print("Date Entered: ");
    Serial.println(indate);
    if(indate <= 0 || indate > 31){
      Serial.println("Invalid Input, Enter between 1 to 31");  
      }
    else if((inmonth == 4 || inmonth == 6 || inmonth == 9 || inmonth == 11) && (indate == 31)){
          Serial.println("Invalid Input, your date should be 30 or less than 30");
          lcd.print("Error");
    }
    else if((inmonth == 2) && (indate >= 30)){
        Serial.println("Invalid Input, your date should be 28 or 29 if a leap year");
        lcd.print("Error");
    }
    else{
      flag = 1;
    }
  }
  //--------------------------------------------------------
  // take year input from the user
  flag =0;
  while(flag != 1){
    Serial.println("Enter the Year in yyyy format.");
    while(Serial.available() == 0){}
    delay(4000);
    inyear = Serial.parseInt();
    Serial.print("Year Entered: ");
    Serial.println(inyear);
    if(inyear <= 0){
      Serial.println("Invalid Input, Enter above 0");  
      lcd.print("Error");
      }
    else{
      flag = 1;
      }
  }
  //--------------------------------------------------------
  setTime(inhour,inminute,insecond,indate,inmonth,inyear); // time function 
}

void loop() {
  // print time in the format (hh:mm:ss)
  // print time first
  lcd.setCursor(1,0);
  // Print the hour and change the format if necessary
  if(hour() < 10){
    lcd.print('0');
    lcd.print(hour());
  }
  else{
    lcd.print(hour());
  }
  // Print the delimiter ":"
  lcd.print(":");
  // print the minutes and change the format if necessary
  if(minute() < 10){
    lcd.print('0');
    lcd.print(minute());
  }
  else
  {
    lcd.print(minute());
  }
  // Print the delimiter ":"
  lcd.print(":"); 
  // print the seconds and change the format if necessary
  if(second() < 10){
    lcd.print('0');
    lcd.print(second());
  }
  else
  {
    lcd.print(second());
  }
  // print date in the format (mm/dd/yyyy)
  lcd.setCursor(1,2);
  
  // print the month and change the format if necessary
  if(month() < 10){
    lcd.print('0');
    lcd.print(month());
  }
  else
    lcd.print(month());
    
  // Print the delimiter "/"
  lcd.print("/");
  // print the date and change the format if necessary
  if(day() < 10){
    lcd.print('0');
    lcd.print(day());
  }
  else
  {
    lcd.print(day());
  }
  // Print the delimiter "/"
  lcd.print("/");
  lcd.print(year());

  

}
