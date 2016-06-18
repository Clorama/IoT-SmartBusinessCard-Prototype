/**
 * Clears out the memory space for the tag to 0s.
 */
void clearCode() {
  for (int i = 0; i < CODE_LEN; i++) {
    tag[i] = 0;
  }
}


/**
 * Sends the tag to the computer.
 */
void sendCode() {
  //This is where I would add a return value (the code) to "validiate" or whatever at.
  Serial.print("LINKED TO:");

  String temp = "";

  char full_tag[10];
  for (int i = 0; i < CODE_LEN; i++) {

    temp = temp + "" + tag[i];


    if (i == 9)  //Edits by riley porter
      Serial.println(tag[i]);  //This checks to see if its the last byte
    else                       //If it is it will print a "new line" so that the codes to jumble together
      Serial.print(tag[i]);

  }

  if (temp.length() == 10) {
    Serial.println(temp);

    // stringOne = "John Doe";
    //stringTwo = "Community Organizer";
    //stringThree = "LinkedIn Profile Link";
    if (temp == "0415EAD421") {
      Serial.println("yadida");
      
      //readerclo();
    }
  

    
    else if (temp == "041580978F") {

   Serial.println("this is potus");
     
        }
      }

  }

  /*   else if(temp == "0415ED287E"){

      for(int i =0; i < ROWS; i++){
         for(int j = 0; j < COLS; j++){
            setColour(0,255,0);
            singlePixel(j,i);
            pixels.show();
            delay(500);
          }
       }
     }
     */


  



  //Serial.println(temp.length());





/**************************************************************/
/********************   RFID Functions  ***********************/
/**************************************************************/

void enableRFID() {
  digitalWrite(RFID_ENABLE, LOW);
  // digitalWrite(LED, LOW);
}
void disableRFID() {
  digitalWrite(RFID_ENABLE, HIGH);
  //  digitalWrite(LED, HIGH);
}

/**
 * Blocking function, waits for and gets the RFID tag.
 */
void getRFIDTag() {
  byte next_byte;
  while (mySerial.available() <= 0) {}
  if ((next_byte = mySerial.read()) == START_BYTE) {
    byte bytesread = 0;
    while (bytesread < CODE_LEN) {
      if (mySerial.available() > 0) { //wait for the next byte
        if ((next_byte = mySerial.read()) == STOP_BYTE) break;
        tag[bytesread++] = next_byte;
      }
    }
  }
}

/**
 * Waits for the next incoming tag to see if it matches
 * the current tag.
 */
boolean isCodeValid() {
  byte next_byte;
  int count = 0;
  while (mySerial.available() < 2) {  //there is already a STOP_BYTE in buffer
    delay(1); //probably not a very pure millisecond
    if (count++ > VALIDATE_LENGTH) return false;
  }
  mySerial.read(); //throw away extra STOP_BYTE
  if ((next_byte = mySerial.read()) == START_BYTE) {
    byte bytes_read = 0;
    while (bytes_read < CODE_LEN) {
      if (mySerial.available() > 0) { //wait for the next byte
        if ((next_byte = mySerial.read()) == STOP_BYTE) break;
        if (tag[bytes_read++] != next_byte) return false;
      }
    }
  }
  return true;
}



