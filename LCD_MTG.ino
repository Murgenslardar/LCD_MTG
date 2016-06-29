/* YourDuino.com Example Software Sketch
 16 character 2 line I2C Display
 Backpack Interface labelled "A0 A1 A2" at lower right.
 ..and
 Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
 MOST use address 0x27, a FEW use 0x3F
 terry@yourduino.com */








/////////////////////////////// BUTTON INIT


 // Knappar pin
 const int buttonPin = 0;     // the number of the pushbutton pin
 const int ledPin =  13;      // the number of the LED pin for testing
 
 const int BUTTON1 = 1;
 const int BUTTON2 = 2;
 const int BUTTON3 = 3;
 const int BUTTON4 = 4;
 const int BUTTON5 = 5;


 // Knappar läsvärden
 const int BUTTON1LOW = 900;
 const int BUTTON1HIGH = 1024;
 const int BUTTON2LOW = 800;
 const int BUTTON2HIGH = 890;
 const int BUTTON3LOW = 650;
 const int BUTTON3HIGH = 750;
 const int BUTTON4LOW = 590;
 const int BUTTON4HIGH = 640;
 const int BUTTON5LOW = 500;
 const int BUTTON5HIGH = 580;
 
 // Olika lägen
 int ledState = HIGH;         // Nuvarande läge
 int buttonState;             // Nuvarandel värde
 int lastButtonState = LOW;   // Föregående värde

 long lastDebounceTime = 0;  // Senaste debounce
 long debounceDelay = 100;    // Debouncetid




/////////////////////////////////////// LCD INIT

int Player1 = 20;
int Player2 = 20;


 
#include <stdlib.h>
/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address



void setup()   
{
   pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  

  lcd.begin(16,2);   // 16 karaktärer, 2 rader


  lcd.backlight(); // Slå på bakgrundsbelysning


// Hälsningsfras
delay(1000);
lcd.setCursor(3,0); 
lcd.print("Magic The");
lcd.setCursor(3,1);
lcd.print("Gathering");
delay(5000);
lcd.clear();

// Första vyn

lcd.setCursor(0,0);
lcd.print("Player1");
lcd.setCursor(9,0);
lcd.print("Player2");
lcd.setCursor(3,1);
lcd.print(20);
lcd.setCursor(11,1);
lcd.print(20);







}


void loop()
{
  {
    if (Serial.available()) {
      delay(100);
      lcd.clear();
      while (Serial.available() > 0) {
        lcd.write(Serial.read());
      }
    }
  }





















////////////////////// BUTTON

int reading = analogRead(buttonPin);   
   int tmpButtonState = LOW;             // Standard ingen knapp
   
   if(reading>BUTTON5LOW && reading<BUTTON5HIGH){
     //Läs av knapp 5
     tmpButtonState = BUTTON5;
   }else if(reading>BUTTON4LOW && reading<BUTTON4HIGH){
     //Läs av knapp 4
     tmpButtonState = BUTTON4;
   }else if(reading>BUTTON3LOW && reading<BUTTON3HIGH){
     //Läs av knapp 3
     tmpButtonState = BUTTON3;
   }else if(reading>BUTTON2LOW && reading<BUTTON2HIGH){
     //Läs av knapp 2
     tmpButtonState = BUTTON2;
   }else if(reading>BUTTON1LOW && reading<BUTTON1HIGH){
     //Läs av knapp 1
     tmpButtonState = BUTTON1;
   }else{
     //Ingen knapp
     tmpButtonState = LOW;
   }

   // Knapptryck?

   // Knapptryck.
   if (tmpButtonState != lastButtonState) {
     // Återställ debounce
     lastDebounceTime = millis();
   } 

   if ((millis() - lastDebounceTime) > debounceDelay) {
     // Debounce
     buttonState = tmpButtonState;
     Serial.println(buttonState);
   }

   // Spara knappvärde
   lastButtonState = tmpButtonState;


   // Öka/sänk värdet på lcd
   switch(buttonState){
     case BUTTON1:
     Player1++;
     lcd.setCursor(3,1);
     lcd.print(Player1, DEC);
     lcd.setCursor(11,1);
     lcd.print(Player2, DEC);
     break;
     case BUTTON2:
     digitalWrite(ledPin, buttonState>0);
     break;
     case BUTTON3:
     digitalWrite(ledPin, buttonState>0);
     break;
     case BUTTON4:
     digitalWrite(ledPin, buttonState>0);
     break;
     case BUTTON5:
     digitalWrite(ledPin, buttonState>0);
     break;
   }






}/* --(end main loop )-- */


/* ( THE END ) */
