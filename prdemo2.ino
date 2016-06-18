/*********************************************************
 * VIZIC TECHNOLOGIES. COPYRIGHT 2013.
 * THE DATASHEETS, SOFTWARE AND LIBRARIES ARE PROVIDED "AS IS." 
 * VIZIC EXPRESSLY DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NONINFRINGEMENT. IN NO EVENT SHALL VIZIC BE LIABLE FOR 
 * ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
 * LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, 
 * ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO 
 * ANY DEFENCE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
 * OR OTHER SIMILAR COSTS.
 *********************************************************/

/********************************************************
 * IMPORTANT : This Example is created for the Arduino 1.0 Software IDE
 ********************************************************/

#include <SMARTGPU2.h>     //include the SMARTGPU2 library!

SMARTGPU2 lcd;             //create our object called LCD

//declare our general coodinates structs
POINT point;
ICON icon;

//Global variables
int hours=11,mins=19,secs=33;
char contactName[7][20]={
  "Adam Playford","Akash Krishnani","Alexis Barta","Alice Alcantara","Amanda Bannout","Andrea Jahanbozorg","Anna Kaltenbrunner"};



/////////////////////////////////////////////// RFID VARIABLES
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define RFID_ENABLE 24   //to RFID ENABLE
#define CODE_LEN 10     //Max length of RFID tag
#define VALIDATE_TAG 1  //should we validate tag?
#define VALIDATE_LENGTH  200 //maximum reads b/w tag read and validate
#define ITERATION_LENGTH 2000 //time, in ms, given to the user to move hand away
#define START_BYTE 0x0A
#define STOP_BYTE 0x0D
//#define LED

SoftwareSerial mySerial(A8, A9);


char tag[CODE_LEN];



/**************************************************/
/**************************************************/
//Initial setup
void setup() { //initial setup
  //Those two functions must always be called for SMARTGPU support
  lcd.init();  //configure the serial and pinout of arduino board for SMARTGPU support
  lcd.start(); //initialize the SMARTGPU processor
  
  
  // RFID SET UP
 
  Serial.begin(2400);
  mySerial.begin(2400);
  pinMode(RFID_ENABLE, OUTPUT);
  // pinMode(LED, OUTPUT);
  
  Serial.println("Test");
  
}

/**************************************************/
/****************** MAIN LOOP *********************/
/**************************************************/
/**************************************************/
void loop() { //main loop
  unsigned char i,n; //icon variable

  lcd.baudChange(BAUD7);        //set high baud for advanced applications
  lcd.orientation(PORTRAIT_LOW);     //change to portrait mode  

  lcd.SDFopenDir("Cellphone");    //Open the Cellphone folder that contains the images of the Application

  //Processing Intro
  lcd.imageBMPSD(0,20,"Intro");   //load main menu image  
  for(n=0;n<3;n++){
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,285,5,YELLOW,FILL);
      delay(200);      
    }
    for(i=0;i<60;i+=20){
      lcd.drawCircle(100+i,285,5,BLACK,FILL);
      delay(200);      
    }         
  }  

  //Main Menu
  while(1){                       //Forever loop
    lcd.orientation(PORTRAIT_LOW);//change to portrait mode
    lcd.imageBMPSD(0,0,"Menu");   //load main menu image
    clock(1);                     //Run clock app

    if(point.y>270){        //if Y coord is greater than 270       
      //obtain icon number and begin application based on touch icon number 
      if(point.x<60){       //if X coordinate is less than 60
        keypad();    
      }
      else if(point.x<120){//if X coordinate is less than 120
        logs();               
      }
      else if(point.x<180){//if X coordinate is less than 180
        apps();  
      }
      else{                      //then X coordinate is between 180-239
        contacts();        
      }    
    }
  }  
}


void theRFIDthings(){
  //Serial.print("HELLO");
  enableRFID();   //Enable the RFID card
  getRFIDTag();   //Reads the tag
  if (isCodeValid()) { //Validates that the tag is good
    disableRFID();  //Puts the RFID reader in to low power mode
    sendCode();     //Sends the code read to the serial port
    delay(ITERATION_LENGTH);  //Debounce?

  } else {
    disableRFID();  //Got a incomplete code..
    //digitalWrite(LED, LOW);
    Serial.println("Hit me, baby one more time");
  }
  Serial.flush();
  clearCode();
}

boolean RFIDAlt(){
  boolean temp2 = false;
  
  //Serial.print("HELLO");
  enableRFID();   //Enable the RFID card
  getRFIDTag();   //Reads the tag
  if (isCodeValid()) { //Validates that the tag is good
    disableRFID();  //Puts the RFID reader in to low power mode
    sendCode();     //Sends the code read to the serial port
    temp2 = true;
    delay(ITERATION_LENGTH);  //Debounce?

  } else {
    disableRFID();  //Got a incomplete code..
    //digitalWrite(LED, LOW);
    Serial.println("Hit me, baby one more time");
  }
  Serial.flush();
  clearCode(); 
  
  return temp2;
}
