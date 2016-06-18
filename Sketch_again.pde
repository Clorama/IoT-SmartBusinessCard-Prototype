import processing.serial.*;
Serial arduino;

int idArduino;
int id = 0;

String val;

void setup() {

  // Get a list of serial ports
  String ports[] = Serial.list();
 
  // Find an Arduino tty.usb* port
  for ( int i = 0; i < ports.length; i++ ) {
    if ( ports[i].indexOf( "tty.usbmodem411" ) != -1 ){
      idArduino = i;
    }
  }
   // Connect to the Arduino
  println( "Connecting to: " + ports[idArduino] );
  arduino = new Serial( this, ports[idArduino], 2400 );
}
 
void draw() {
}
 
// New Serial Data Event
void serialEvent(Serial p) {
  //println( p.readChar() );
  
   //if (Serial.available())   { // If data is available to read,
     val = p.readStringUntil('\n'); // read it and store it in val
     
     //val = val.substring(0,val.length()-1);
   //}
   
   if(val != null){
     
     val = trim(val); 
     println(val);
     
     
      
     if (val.equals("041580978F") ) {
        int id = 11932467;
        String[] url = { "open", "http://linkedin.com/profile/view?id=" + id };
        println(url);
        open(url);
      }
      else if( val.equals("0415EAD421") ) {
        
        
        int id = 75577322;
        String[] url = { "open", "http://linkedin.com/profile/view?id=" + id };
        println(url);
        open(url);
        //11471446 nic
        //95744365 Eva
      }
   }
  
}
